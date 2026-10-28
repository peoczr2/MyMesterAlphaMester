/*
Megoldás lényege:
Minden mérést készültségi szintre alakítunk: 800 cm-ig a szint 0 (nincs árvíz), különben legalább 1.
Az árvizek a legfeljebb 0-nál nagyobb szintű mérések maximális, egymás utáni sorozatai, ezeket egyetlen balról jobbra haladó bejárással gyűjtjük ki.
Egy árvíz csúcsmagassága a benne szereplő legnagyobb vízmagasság; az árvizek csúcsmagasságait a sorrendben egymás után összevetjük.
Az árvizek csúcsmagassága akkor "egyre alacsonyabb", ha minden következő csúcs szigorúan alacsonyabb az előzőnél; egyetlen árvíz esetén ez teljesül.
Az időigény O(N), a csúcsmagasságok ellenőrzése pedig egy további lineáris bejárás.
*/
/*
Hint 1: || Az árvizek a nullától nagyobb készültségi szintű mérések maximális, összefüggő sorozatai. Haladj balról jobbra, és amíg a szint nem 0, növeld az aktuális árvizet. ||
Hint 2: || Minden árvízhez a benne lévő maximális vízmagasságot tárold el, ez a csúcsmagasság. A két szélső sorszám a kezdet és a vég, ezeket a kiíráshoz külön is megőrizd. ||
Hint 3: || A csúcsmagasságokat végigjárva elég a szomszédos párokat nézni: ha bármelyik következő érték nem kisebb az előzőnél, a válasz NEM. Szigorúan kisebb kell, az egyenlőség már NEM. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Készültségi szint: 0 = nincs árvíz, 1 = elsőfokú, 2 = másodfokú, 3 = harmadfokú
int szint(int magassag) {
    if (magassag > 1000) return 3;
    if (magassag > 900) return 2;
    if (magassag > 800) return 1;
    return 0;
}

// Egy árvíz [bal, jobb] sorszámokkal és csúcsmagasságával (1-től indexelve)
struct Arviz {
    int bal, jobb, csucs;
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1), s(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = szint(a[i]);
    }

    vector<Arviz> arvizek;
    int i = 1;
    while (i <= n) {
        if (s[i] == 0) {
            i++;
            continue;
        }
        int j = i;
        int legnagyobb = a[i];
        while (j + 1 <= n && s[j + 1] >= 1) {
            j++;
            legnagyobb = max(legnagyobb, a[j]);
        }
        arvizek.push_back({i, j, legnagyobb});
        i = j + 1;
    }

    int k = arvizek.size();
    cout << k << '\n';
    if (k == 0) return 0;

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << arvizek[t].bal << ' ' << arvizek[t].jobb;
    }
    cout << '\n';

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << arvizek[t].csucs;
    }
    cout << '\n';

    // Egyre alacsonyabb: minden csúcs szigorúan kisebb az előzőnél
    bool csokkeno = true;
    for (int t = 1; t < k; t++) {
        if (arvizek[t].csucs >= arvizek[t - 1].csucs) csokkeno = false;
    }
    cout << (csokkeno ? "IGEN" : "NEM") << '\n';
    return 0;
}
