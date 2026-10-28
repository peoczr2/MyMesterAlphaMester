/*
Megoldás lényege:
Egy város kilométerenkénti ára Á/T forint, ez akkor nagyobb 100-nál, ha Á > 100*T.
Az egyenlőtlenséget egész számokkal írjuk fel, így nincs lebegőpontos osztásból adódó kerekítési hiba.
Egyetlen bejárással minden városnál ellenőrizzük a feltételt, és a teljesítő városok sorszámát egy vektorba tesszük.
Mivel a városokat sorszám szerint dolgozzuk fel, a vektorban a sorszámok már növekvő sorrendben vannak.
Az időigény N-nel arányos, és N legfeljebb 100, így ez bőven belefér.
*/
/*
Hint 1: || Ne írd fel a kilométerenkénti árat törtként, hanem alakítsd át a feltételt: az ár akkor nagyobb 100-nál, ha az utazási ár nagyobb, mint 100-szor a távolság. ||
Hint 2: || A feltétel szigorú: pontosan 100 forint/km még nem számít bele. Az összehasonlítást egész számokkal végezd, és 64 bites típust használj az Á és a T szorzatához. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> chosen;
    for (int i = 1; i <= n; ++i) {
        long long dist, price;
        cin >> dist >> price;
        if (price > 100LL * dist) chosen.push_back(i);
    }

    cout << chosen.size();
    for (int city : chosen) cout << ' ' << city;
    cout << '\n';
    return 0;
}
