/*
Megoldás lényege:
Két lap akkor van egymás mellett, ha a sorrendben közvetlenül egymás után állnak, vagyis az i-edik és az (i+1)-edik lap.
A színt a kártya első karaktere adja, az értéket (a második karaktert) most figyelmen kívül hagyjuk.
Balról jobbra végigmegyünk a szomszédos párokon, és az első olyan i sorszámot írjuk ki (1-től számozva), ahol a két szín egyezik.
Ha nincs ilyen pár, a válasz 0. A lapok száma fix (32), így az időigény konstans.
*/
/*
Hint 1: || Két lap csak akkor „egymás mellett” van, ha a sorszámuk egymást követő, így elég minden i-re az i-edik és az (i+1)-edik lapot összevetni. ||
Hint 2: || Egy kártya két betűből áll: az első a szín, a második az érték. Most csak az első betűt kell összehasonlítanod. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int n = 32;
    vector<char> color(n);
    for (char& c : color) {
        char value;
        cin >> c >> value;
    }

    for (int i = 0; i + 1 < n; ++i) {
        if (color[i] == color[i + 1]) {
            cout << i + 1 << "\n";
            return 0;
        }
    }

    cout << 0 << "\n";
    return 0;
}
