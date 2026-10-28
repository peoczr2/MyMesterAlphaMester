/*
Megoldás lényege:
Az árvizek most is a 800 cm-nél magasabb mérések maximális, egymás utáni sorozatai. Egy árvíz legfeljebb másodfokú készültségű, ha az egész ideje alatt nem lép harmadfokra, vagyis egyik mérése sem haladja meg az 1000 cm-t.
Egy bejárás során minden árvizet végigellenőrizünk, és ha nincs benne 1000 cm-nél magasabb mérés, a kezdő és a záró sorszámát eltároljuk.
A talált árvizek a bejárás miatt már sorszám szerint növekvő sorrendben vannak, így közvetlenül kiírhatók.
Az időigény O(N), ami N ≤ 10 000 esetén az időkorláton belül van.
*/
/*
Hint 1: || Az árvizek a 800 cm-nél magasabb mérések egymás utáni sorozatai. Egy árvíz akkor felel meg, ha egyik mérése sem haladja meg az 1000 cm-t, vagyis nincs benne harmadfokú mérés. ||
Hint 2: || Balról jobbra haladva minden árvízre ellenőrizd a méréseit, és csak a hibátlan árvizek kezdő és záró sorszámát tárold. A darabszám a tárolt párok száma, és nulla esetén a kimenet csak a 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    vector<pair<int, int>> arvizek;  // [kezdet, vége], 1-től számozva
    int i = 0;
    while (i < n) {
        if (a[i] <= 800) {
            i++;
            continue;
        }
        int l = i, r = i;
        while (r + 1 < n && a[r + 1] > 800) r++;

        bool legfeljebb2 = true;
        for (int k = l; k <= r; k++) {
            if (a[k] > 1000) legfeljebb2 = false;
        }
        if (legfeljebb2) arvizek.push_back({l + 1, r + 1});
        i = r + 1;
    }

    cout << arvizek.size() << '\n';
    if (arvizek.empty()) return 0;
    for (size_t k = 0; k < arvizek.size(); k++) {
        if (k > 0) cout << ' ';
        cout << arvizek[k].first << ' ' << arvizek[k].second;
    }
    cout << '\n';
    return 0;
}
