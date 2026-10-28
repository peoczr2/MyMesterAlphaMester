/*
Megoldás lényege:
Az autó indulás előtt teli tankkal van. Egy teli tankkal az autó T / F száz kilométert tud megtenni, mert T liter elég T / F darab 100 kilométeres szakaszhoz. Mivel F osztója T-nek, a T / F hányados egész szám, így a hatótávolság (T / F) * 100 kilométer pontosan kiszámolható. Ha az út hossza H nagyobb a hatótávolságnál, akkor az autónak tankolnia kell, különben nem. Az egyenlőség még belefér, mert ekkor az autó éppen elér a célig üres tankkal. A számok legfeljebb 10^13 nagyságúak, ezért 64 bites egészeket használunk. Az időigény és a memóriaigény O(1).
*/
/*
Hint 1: || Számold ki, hány kilométert tud megtenni az autó egyetlen teli tankkal: T liter elég T / F darab 100 kilométeres szakaszra. ||
Hint 2: || Hasonlítsd össze az út hosszát ezzel a távolsággal. Mivel F osztója T-nek, a T / F egész szám, és a számolás egészekkel pontos marad, nem kell lebegőpontos számokat használni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long h, t, f;
    cin >> h >> t >> f;

    long long hatotav = (t / f) * 100;
    if (h > hatotav) {
        cout << "igen\n";
    } else {
        cout << "nem\n";
    }

    return 0;
}
