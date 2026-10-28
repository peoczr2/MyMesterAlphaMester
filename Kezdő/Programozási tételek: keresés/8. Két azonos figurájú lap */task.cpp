/*
Megoldás lényege:
Két lap akkor van egymás mellett, ha a sorrendben közvetlenül egymás után állnak, vagyis az i-edik és az (i+1)-edik lap.
A figurát a kártya második karaktere adja, a színt (az első karaktert) most figyelmen kívül hagyjuk.
Balról jobbra végigmegyünk a szomszédos párokon, és az első olyan i sorszámot írjuk ki (1-től számozva), ahol a két figura egyezik.
Ha nincs ilyen pár, a válasz 0. A lapok száma fix (32), így az időigény konstans.
*/
/*
Hint 1: || Két lap csak akkor „egymás mellett” van, ha a sorszámuk egymást követő, így elég minden i-re az i-edik és az (i+1)-edik lapot összevetni. ||
Hint 2: || Egy kártya két betűből áll: az első a szín, a második a figura. Most csak a második betűt kell összehasonlítanod, és figyelj a kis- és nagybetűkre is. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int n = 32;
    vector<char> value(n);
    for (char& v : value) {
        char color;
        cin >> color >> v;
    }

    for (int i = 0; i + 1 < n; ++i) {
        if (value[i] == value[i + 1]) {
            cout << i + 1 << "\n";
            return 0;
        }
    }

    cout << 0 << "\n";
    return 0;
}
