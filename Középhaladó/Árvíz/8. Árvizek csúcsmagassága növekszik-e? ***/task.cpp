/*
Megoldás lényege:
Egy mérés akkor legalább elsőfokú készültségű, ha vízállása meghaladja a 800 cm-t, az árvizek pedig ezeknek a méréseknek a maximális, egymás melletti sorozatai.
Egyetlen balról jobbra haladó bejárással kigyűjtjük az árvizek kezdő és záró indexét, és minden árvízhez a sorozat közben megkeressük a csúcsmagasságot.
A csúcsokat sorrendben egyesével összevetjük: a növekedés akkor áll fenn, ha minden következő csúcs szigorúan nagyobb az előzőnél, így az egyenlő csúcsok már NEM-et adnak.
Ha nincs árvíz, csak a 0 kerül ki; ha egy árvíz van, nincs mit összevetni, így a válasz IGEN.
Az időigény O(N), ami N ≤ 10 000 esetén messze az időlimit (0,1 mp) alatt van.
*/
/*
Hint 1: || Egy mérés akkor része árvíznek, ha magassága 800 cm-nél nagyobb. Az árvizek ezeknek a méréseknek a maximális, egymás melletti sorozatai, így egy balról jobbra haladó bejárás mindet megtalálja. ||
Hint 2: || Árvíz közben tartsd egy változóban az eddigi legnagyobb magasságot, és az árvíz végén tárold el a csúcsként. Így minden árvízhez egy csúcs tartozik, a kezdő és záró index mellett. ||
Hint 3: || A növekedést a csúcsok sorában szomszédos párokon vizsgáld: a válasz csak akkor IGEN, ha minden csúcs szigorúan nagyobb az előzőnél. Egyetlen csúcs esetén nincs ellenőrizendő pár, így a válasz IGEN. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Készültségi szint: 0 = nincs, 1 = elsőfokú, 2 = másodfokú, 3 = harmadfokú
int szint(int magassag) {
    if (magassag > 1000) return 3;
    if (magassag > 900) return 2;
    if (magassag > 800) return 1;
    return 0;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    // Az árvizek [kezdet, vége] párjai (0-indexelve) és csúcsmagasságaik
    vector<pair<int, int>> arvizek;
    vector<int> csucs;
    int i = 0;
    while (i < n) {
        if (szint(a[i]) == 0) {
            i++;
            continue;
        }
        int j = i;
        int legnagyobb = a[i];
        while (j + 1 < n && szint(a[j + 1]) > 0) {
            j++;
            legnagyobb = max(legnagyobb, a[j]);
        }
        arvizek.push_back({i, j});
        csucs.push_back(legnagyobb);
        i = j + 1;
    }

    int k = arvizek.size();
    cout << k << '\n';
    if (k == 0) return 0;

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << arvizek[t].first + 1 << ' ' << arvizek[t].second + 1;
    }
    cout << '\n';

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << csucs[t];
    }
    cout << '\n';

    // Szigorú növekedés: egyetlen egyenlő vagy csökkenő szomszédos pár már NEM
    bool noveksziki = true;
    for (int t = 1; t < k; t++)
        if (csucs[t] <= csucs[t - 1]) noveksziki = false;
    cout << (noveksziki ? "IGEN" : "NEM") << '\n';
    return 0;
}
