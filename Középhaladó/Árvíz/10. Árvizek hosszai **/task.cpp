/*
Megoldás lényege:
A vízállásokból készültségi szint lesz: 800 cm fölött a mérés legalább elsőfokú, egyébként nincs árvíz.
Az árvizek a legalább elsőfokú, egymás utáni mérések maximális sorozatai, ezeket egyetlen balról jobbra haladó bejárással gyűjtjük ki.
Egy árvíz kezdő és záró indexe ismeretében a hossza záró - kezdő + 1, így a kiírandó adatok közvetlenül adódnak.
Az időigény O(N), ami N ≤ 10 000 esetén az időlimit alatt van.
*/
/*
Hint 1: || Egy mérés akkor része árvíznek, ha vízállása meghaladja a 800 cm-t. Az árvizek ezek egymás utáni sorozatai, amelyek egyetlen bejárással megtalálhatók. ||
Hint 2: || Amikor egy árvíz véget ér, tárold el a kezdő és záró indexét. A hossz ebből záró - kezdő + 1, a kiírás pedig az árvizek sorrendjét követi. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Készültségi szint: 0 = nincs árvíz, 1..3 = elsőfokú..harmadfokú
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

    // Az árvizek [kezdet, vége] párjai, 0-indexelve
    vector<pair<int, int>> arvizek;
    int i = 0;
    while (i < n) {
        if (szint(a[i]) == 0) {
            i++;
            continue;
        }
        int j = i;
        while (j + 1 < n && szint(a[j + 1]) > 0) j++;
        arvizek.push_back({i, j});
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
        cout << arvizek[t].second - arvizek[t].first + 1;
    }
    cout << '\n';
    return 0;
}
