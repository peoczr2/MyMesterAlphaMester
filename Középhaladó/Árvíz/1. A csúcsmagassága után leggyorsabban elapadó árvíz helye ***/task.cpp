/*
Megoldás lényege:
A vízállásokat először készültségi szintre alakítjuk: 800 cm fölött 1., 900 cm fölött 2., 1000 cm fölött 3. szintű a mérés, egyébként 0.
Az árvíz a legalább 1. szintű, egymás utáni mérések maximális sorozata, ezeket egyetlen balról jobbra haladó bejárással gyűjtjük ki.
Minden árvízhez megkeressük a csúcsmagasság helyét, ami a legnagyobb érték első előfordulása, majd kiszámoljuk a csúcs és az árvíz vége közötti távolságot.
A legkisebb távolságú árvíz a leggyorsabban elapadó; egyenlőség esetén a korábbit írjuk ki.
Az időigény O(N), ami N ≤ 10 000 esetén az időlimit alatt van.
*/
/*
Hint 1: || A mérést előbb alakítsd készültségi szintté: 800 cm fölött legalább 1., 900 cm fölött legalább 2., 1000 cm fölött 3. szint. Az árvíz a legalább 1. szintű mérések egymás utáni sorozata. ||
Hint 2: || Egyetlen balról jobbra haladó bejárásban gyűjtsd ki az árvizek kezdő és záró indexét. Minden árvízben a csúcs helye a legnagyobb érték első előfordulása. ||
Hint 3: || Az elapadás gyorsaságát a csúcs és az árvíz vége közötti különbség adja. Egy lineáris végigmenéssel keresd a legkisebb különbséget, és egyenlőségnél tartsd meg az első árvizet. ||
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

    // Minden árvízben a csúcsmagasság helye (a legnagyobb érték első előfordulása)
    vector<int> csucs(k);
    for (int t = 0; t < k; t++) {
        int p = arvizek[t].first;
        for (int q = arvizek[t].first; q <= arvizek[t].second; q++)
            if (a[q] > a[p]) p = q;
        csucs[t] = p;
    }

    // A leggyorsabban elapadó árvíz: a csúcs és az árvíz vége legkisebb távolságú
    int legjobb = 0;
    for (int t = 1; t < k; t++)
        if (arvizek[t].second - csucs[t] < arvizek[legjobb].second - csucs[legjobb])
            legjobb = t;

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << arvizek[t].first + 1 << ' ' << arvizek[t].second + 1;
    }
    cout << '\n';

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << csucs[t] + 1;
    }
    cout << '\n';

    cout << arvizek[legjobb].first + 1 << ' ' << arvizek[legjobb].second + 1 << '\n';
    return 0;
}
