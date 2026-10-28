/*
Megoldás lényege:
A lámpa a K magasságban álló pont; egy sarok akkor meg van világítva, ha a lámpától hozzá húzott szakasz nem megy át
más ház belsején (az érintés megengedett). A lámpától jobbra álló háznál a lámpától távolabbi, vagyis a jobb felső sarok
a legkönnyebben megvilágítható (ha a közelebbi felső sarok megvilágított, akkor ez is az), balra a bal felső sarok.
Ha egy lámpa megvilágít egy házat, akkor a lámpa és a ház közti réseknél álló összes lámpa is, mert közelebbről a látóvonal
magasabban halad a közbülső házak fölött. Ezért minden j. házat a lámpák egy összefüggő [a_j, b_j] intervalluma világít meg,
és a feladat az összes intervallumot metsző (szúró) lámpák minimális száma, amit mohón, a jobb végpontok szerint haladva
kapunk. Az a_j-hez a j. ház jobb felső sarkából húzunk érintőt a korábbi házak jobb felső sarkainak felső konvex burkához
(monoton verem): ahol ez az egyenes eléri a K magasságot, onnan jobbra álló lámpák világítják meg a házat, a legkisebb ilyen
lámpát bináris kereséssel találjuk meg. A b_j-t ugyanígy a tükrözött bemenetből kapjuk. A rések felezőpontja nem mindig
egész, ezért a koordinátákat megduplázzuk. Ha csak egy ház van, nincs rés, így nem helyezünk el lámpát (0).
Idő: O(N log N).
*/
/*
Hint 1: || Egy sarok akkor látszik a lámpából, ha a köztük húzott szakasz nem megy át más ház belsején. A lámpától jobbra
lévő háznál elég a jobb felső sarkot nézni (balra a bal felsőt): ha a közelebbi felső sarok megvilágított, a távolabbi is az. ||
Hint 2: || Ha egy lámpa megvilágít egy házat, akkor a lámpa és a ház között álló bármelyik másik lámpa is megvilágítja,
mert közelebbről a látóvonal magasabban halad a közbülső házak fölött. Így minden házat a lámpák egy összefüggő [a, b]
intervalluma világít meg, és a feladat a legkevesebb lámpa kiválasztása úgy, hogy minden intervallumba essen egy (mohó
algoritmus a jobb végpontok szerint). ||
Hint 3: || Az a kiszámításához a j. ház jobb felső sarkából húzz érintőt a korábbi házak jobb felső sarkainak felső konvex
burkához (monoton verem). Ahol ez az egyenes eléri a K magasságot, onnan jobbra álló lámpák világítják meg a házat; a
legkisebb ilyen lámpát bináris kereséssel találod meg. A b kiszámításához tükrözd a bemenetet. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Visszaadja a[j]-t: a legkisebb g (1 <= g < j) lámpaindex, amelyből (a háztól balra állva) a j. ház megvilágított.
// A g. lámpa a g. és a (g+1). ház között áll. a[1] = 1 (a j=1 háznál nincs bal oldali lámpa).
// left[j] a j. ház bal széle, right2[j] a jobb szélének kétszerese, h[j] a magassága.
static vector<int> firstLamp(int n, int K, const vector<ll>& left, const vector<ll>& right2, const vector<int>& h) {
    vector<int> a(n + 1, 1), st;
    for (int j = 1; j <= n; ++j) {
        // felső burok a j-nél előző csúcsokra, majd j hozzáadása; a j előtti szomszéd a tangenspont
        while (st.size() >= 2) {
            int p = st[st.size() - 2], q = st.back();
            ll c = (right2[q] - right2[p]) * (ll)(h[j] - h[p]) - (ll)(h[q] - h[p]) * (right2[j] - right2[p]);
            if (c >= 0) st.pop_back();
            else break;
        }
        if (j >= 2) {
            int t = st.back();
            if (h[t] > h[j]) {
                // g jó, ha az (E_j - M_g) * (h_t - h_j) <= (K - h_j) * (E_j - E_t) teljesül,
                // ahol E a jobb szél (duplázva), M_g a g. lámpa duplázott x-koordinátája
                int lo = 1, hi = j - 1;
                while (lo < hi) {
                    int g = (lo + hi) / 2;
                    ll m = right2[g] / 2 + left[g + 1];
                    ll lhs = (right2[j] - m) * (ll)(h[t] - h[j]);
                    ll rhs = (ll)(K - h[j]) * (right2[j] - right2[t]);
                    if (lhs <= rhs) hi = g;
                    else lo = g + 1;
                }
                a[j] = lo;
            }
        }
        st.push_back(j);
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    if (!(cin >> n >> K)) return 0;
    vector<ll> x(n + 1), w(n + 1);
    vector<int> h(n + 1);
    for (int i = 1; i <= n; ++i) cin >> x[i] >> w[i] >> h[i];

    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }

    vector<ll> left(n + 1), right2(n + 1);
    for (int i = 1; i <= n; ++i) {
        left[i] = x[i];
        right2[i] = 2 * (x[i] + w[i]);
    }
    vector<int> a = firstLamp(n, K, left, right2, h);

    // tükrözött bemenet: a j. ház az (n+1-j). lesz, bal és jobb széle felcserélődik
    vector<ll> left2(n + 1), right22(n + 1);
    vector<int> h2(n + 1);
    for (int j = 1; j <= n; ++j) {
        int m = n + 1 - j;
        left2[m] = -(x[j] + w[j]);
        right22[m] = 2 * (-x[j]);
        h2[m] = h[j];
    }
    vector<int> am = firstLamp(n, K, left2, right22, h2);

    // a j. házat az [a[j], b[j]] lámpák világítják meg
    vector<int> maxA(n, 0);
    for (int j = 1; j <= n; ++j) {
        int b = n - am[n + 1 - j];
        maxA[b] = max(maxA[b], a[j]);
    }

    // mohó szúrás: ha a p végű intervallumok valamelyike nincs lefedve, p-be lámpát teszünk
    int ans = 0, last = 0;
    for (int p = 1; p <= n - 1; ++p) {
        if (maxA[p] > last) {
            ++ans;
            last = p;
        }
    }
    cout << ans << '\n';
    return 0;
}
