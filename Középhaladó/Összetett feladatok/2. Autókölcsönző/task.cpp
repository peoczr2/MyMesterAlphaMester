/*
Megoldás lényege:
Az autókat az első előfordulásuk sorrendjében nyilvántartjuk, és minden kölcsönzésnél növeljük az autó kölcsönzéseinek számát, a kölcsönzött napok összegét (U - E + 1), valamint a napi darabszámot a kölcsönzés minden napján. Az 1. részfeladat a napok összegét adja. A 2. részfeladatban a napi darabszám első maximumát keressük, a 3. részfeladatban pedig az 1. naptól kezdve végigjárjuk a napokat, és kiírjuk azokat, ahol a darabszám szigorúan nagyobb az addigi maximumnál; az 1. nap nem kerül a listába, mert előtte nincs nap. A 4. részfeladatban a legtöbbször (hányszor) kölcsönzött autót keressük; egyenlőség esetén a több napra kölcsönzött autót választjuk, a feladat szerint bármelyik megengedett. Az 5. részfeladatban autónként kiírjuk a kölcsönzések számát és a napok számát, az autók első előfordulásának sorrendjében.
Az időigény O(N·30), ami N ≤ 1000 esetén elhanyagolható.
*/
/*
Hint 1: || Egy kölcsönzés [E, U] napjainak száma U-E+1, a napi darabszámot pedig egy 31 elemű tömbben tárold: a kölcsönzés minden napján növeld a megfelelő elemet. ||
Hint 2: || Az autókat rendszám szerint egy map-ben azonosítsd, és tartsd nyilván autónként a kölcsönzések számát és az összes napot; így a 4. és 5. részfeladat is közvetlenül kiolvasható. ||
Hint 3: || A 3. részfeladatban az 1. napot ne vedd figyelembe, a 2. naptól pedig az eddigi legnagyobb napi darabszámot tartsd, és akkor írd ki a napot, ha a mostani szigorúan nagyobb. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> plates;        // az autók rendszáma, első előfordulás sorrendjében
    map<string, int> id;          // rendszám -> sorszám a plates-ben
    vector<int> rentals;          // hányszor vették kölcsön az autót
    vector<int> days;             // hány napra vették kölcsön az autót
    vector<int> dayCars(31, 0);   // dayCars[d]: a d. napon kölcsönben lévő autók száma

    long long totalDays = 0;
    for (int i = 0; i < n; ++i) {
        string plate;
        int e, u;
        cin >> plate >> e >> u;

        int a;
        auto it = id.find(plate);
        if (it == id.end()) {
            a = (int)plates.size();
            id[plate] = a;
            plates.push_back(plate);
            rentals.push_back(0);
            days.push_back(0);
        } else {
            a = it->second;
        }

        ++rentals[a];
        days[a] += u - e + 1;
        totalDays += u - e + 1;
        for (int d = e; d <= u; ++d) ++dayCars[d];
    }

    // 1. részfeladat: az autók kölcsönzött napjainak összes száma
    cout << "#\n" << totalDays << "\n";

    // 2. részfeladat: a legtöbb autóval kölcsönzött nap (egyenlőségnél a legkorábbi)
    int busiest = 1;
    for (int d = 2; d <= 30; ++d)
        if (dayCars[d] > dayCars[busiest]) busiest = d;
    cout << "#\n" << busiest << "\n";

    // 3. részfeladat: azok a napok, amikor több autó volt kölcsönben, mint előtte bármikor (az 1. nap nem számít)
    vector<int> more;
    int mx = dayCars[1];
    for (int d = 2; d <= 30; ++d) {
        if (dayCars[d] > mx) more.push_back(d);
        mx = max(mx, dayCars[d]);
    }
    cout << "#\n";
    if (more.empty()) {
        cout << 0 << "\n";
    } else {
        for (size_t k = 0; k < more.size(); ++k) cout << (k ? " " : "") << more[k];
        cout << "\n";
    }

    // 4. részfeladat: a legtöbbször kölcsönzött autó (egyenlőségnél a több napra kölcsönzött)
    int best = 0;
    for (int a = 1; a < (int)plates.size(); ++a)
        if (rentals[a] > rentals[best] || (rentals[a] == rentals[best] && days[a] > days[best])) best = a;
    cout << "#\n" << plates[best] << "\n";

    // 5. részfeladat: autónként a kölcsönzések száma és a napok száma
    cout << "#\n";
    for (int a = 0; a < (int)plates.size(); ++a)
        cout << plates[a] << ' ' << rentals[a] << ' ' << days[a] << "\n";

    return 0;
}
