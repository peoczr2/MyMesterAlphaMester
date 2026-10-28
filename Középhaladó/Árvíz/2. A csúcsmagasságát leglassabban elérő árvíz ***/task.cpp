/*
Megoldás lényege:
Az árvíz a legalább elsőfokú, egymás melletti mérések maximális sorozata; ezeket egyetlen balról jobbra haladó bejárással gyűjtjük ki.
Minden árvízben megkeressük a csúcsmagasság első előfordulását: a legnagyobb érték helyét, egyenlőség esetén a korábbit.
Az árvíz kezdete és a csúcs helye közötti távolság (csúcs mínusz kezdet) mutatja, mennyire lassan éri el a csúcsot.
A legnagyobb ilyen távolságú árvizet keressük egy végigmenéssel, egyenlőségnél a korábbit tartjuk meg.
Az időigény O(N), ami N ≤ 10 000 esetén messze az időlimit alatt van.
*/
/*
Hint 1: || Az árvíz határait úgy kapod meg, hogy addig haladsz, amíg a mérés legalább elsőfokú. A szint kiszámításához a 800, 900 és 1000 cm küszöbök elegendőek. ||
Hint 2: || Minden árvízben a csúcs helye az első legnagyobb érték helye. A leglassabban elérő árvíz az, ahol a csúcs helye mínusz az árvíz kezdete a legnagyobb. ||
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

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << arvizek[t].first + 1 << ' ' << arvizek[t].second + 1;
    }
    cout << '\n';

    // Minden árvízben a csúcs helye (a legnagyobb érték első előfordulása)
    vector<int> csucs(k);
    for (int t = 0; t < k; t++) {
        int p = arvizek[t].first;
        for (int q = arvizek[t].first; q <= arvizek[t].second; q++)
            if (a[q] > a[p]) p = q;
        csucs[t] = p;
    }
    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << csucs[t] + 1;
    }
    cout << '\n';

    // A leglassabban elérő árvíz: a csúcs és az árvíz kezdete legnagyobb távolságú (egyenlőségnél az első)
    int legjobb = 0;
    for (int t = 1; t < k; t++)
        if (csucs[t] - arvizek[t].first > csucs[legjobb] - arvizek[legjobb].first) legjobb = t;

    cout << arvizek[legjobb].first + 1 << ' ' << arvizek[legjobb].second + 1 << '\n';
    return 0;
}
