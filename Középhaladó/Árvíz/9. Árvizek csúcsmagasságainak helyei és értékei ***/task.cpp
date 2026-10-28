/*
Megoldás lényege:
Az árvíz itt is a legalább elsőfokú, egymás utáni mérések maximális sorozata, ezeket egy balról jobbra haladó bejárással gyűjtjük ki.
Minden árvízben egy második végigmenéssel keressük a legnagyobb vízállást, és csak szigorúan nagyobb értéknél frissítjük a helyét, így egyenlő értékek esetén az első előfordulás marad.
A kiírás sorrendje: K, majd az árvizek kezdő és záró sorszáma, végül árvizenként a csúcs helye és értéke.
Az időigény O(N), ami N ≤ 10 000 esetén messze az időlimit (0,1 mp) alatt van.
*/
/*
Hint 1: || Az árvizek megtalálása ugyanaz, mint egy sorozat maximális szakaszainak kigyűjtése: a 800 cm-nél magasabb mérések egymás utáni blokkjai az árvizek. ||
Hint 2: || Egy árvízben a csúcs helyét és értékét úgy keresd, hogy az új mérést csak akkor fogadd el csúcsnak, ha szigorúan nagyobb a jelenleginél. Így egyenlőség esetén az első előfordulás marad. ||
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

    for (int t = 0; t < k; t++) {
        // Az árvíz csúcsa: a legnagyobb érték első előfordulása
        int p = arvizek[t].first;
        for (int q = arvizek[t].first + 1; q <= arvizek[t].second; q++)
            if (a[q] > a[p]) p = q;
        if (t > 0) cout << ' ';
        cout << p + 1 << ' ' << a[p];
    }
    cout << '\n';
    return 0;
}
