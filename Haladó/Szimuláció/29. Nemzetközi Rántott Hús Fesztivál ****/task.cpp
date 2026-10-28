/*
Megoldás lényege:
Egy túra i-től j-ig akkor járható, ha minden prefixben a köretek száma (K és M bódékból
vett köret) legalább a rántott húsok száma (H). Ezért K és M legyen +1, H legyen -1,
és a túra akkor járható, ha a kezdőponthoz képest a prefixösszeg végig nemnegatív.
Minden kezdőponthoz a legtávolabbi járható végpontot monoton veremmel találjuk meg,
jobbról balra haladva. A járható szakaszon a húsok maximuma: a fix H-k száma plusz
az M-ekből húsnak választható darabok száma, ez utóbbi egy prefixminimum-képlettel
adódik, amelyhez a szakasz minimumát szintén verem tartja nyilván. Az összes
művelet lineáris, így N = 10^6 is belefér az időlimitbe.
*/
/*
Hint 1: || Tekintsd a bódékat +1 (K vagy M) és -1 (H) lépéseknek: egy rántott hús csak akkor lehet teljes adag, ha addig legalább ugyanannyi köret is gyűlt össze. ||
Hint 2: || Egy kezdőpontból a túra addig járható, amíg a prefixösszeg a kezdőpont értékéhez képest nem esik le; ezt a végpontot monoton veremmel lehet megkeresni, jobbról balra haladva. ||
Hint 3: || A járható szakaszon az M-bódék közül annyi választható húsnak, amennyit a prefixek korlátja enged; ez egy min_p floor((E_p - D_{i-1}) / 2) alakú minimum, ahol E_p = K_p - M_p - H_p, így a szakaszminimum is verem segítségével számolható. ||
*/

#include <bits/stdc++.h>
using namespace std;

// Lefelé kerekítő egész osztás 2-vel (negatív számokra is helyes).
long long floorDiv2(long long a) {
    return a >= 0 ? a / 2 : -((-a + 1) / 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    string s;
    cin >> s;

    // D_p: K és M +1, H -1 prefixösszeg; Hc_p, Mc_p: H, illetve M darabszám a prefixben;
    // E_p = D_p - 2*Mc_p = K_p - M_p - H_p.
    vector<int> D(n + 1, 0), Hc(n + 1, 0), Mc(n + 1, 0), E(n + 1, 0);
    for (int p = 1; p <= n; ++p) {
        char c = s[p - 1];
        Hc[p] = Hc[p - 1] + (c == 'H');
        Mc[p] = Mc[p - 1] + (c == 'M');
        D[p] = D[p - 1] + (c == 'H' ? -1 : 1);
        E[p] = D[p] - 2 * Mc[p];
    }

    // Jobbról balra haladunk. x = i-1 kezdőpont, R a legtávolabbi járható prefixindex:
    // R + 1 az első q > x, ahol D_q < D_x. segMin[x] = min E_p a [x, R] szakaszon.
    vector<int> segMin(n + 1, 0);
    vector<int> ans(n + 1, 0);
    vector<int> st;
    st.reserve(n + 1);
    for (int x = n; x >= 0; --x) {
        int cur = E[x];
        while (!st.empty() && D[st.back()] >= D[x]) {
            cur = min(cur, segMin[st.back()]);
            st.pop_back();
        }
        int R = st.empty() ? n : st.back() - 1;
        segMin[x] = cur;
        st.push_back(x);

        // A fix H-k száma a szakaszon + az M-ekből húsnak választható maximum.
        long long hFixed = Hc[R] - Hc[x];
        long long mHuses = (long long)Mc[R] + floorDiv2((long long)segMin[x] - D[x]);
        ans[x] = (int)(hFixed + mHuses);
    }

    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << ans[i - 1];
    }
    cout << '\n';
    return 0;
}
