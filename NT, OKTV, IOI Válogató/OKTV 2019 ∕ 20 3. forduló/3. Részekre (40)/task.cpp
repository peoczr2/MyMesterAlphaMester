/*
Megoldás lényege:
Két elem akkor kerülhet ugyanabba a növekvő részsorozatba, ha a korábbi szigorúan kisebb a későbbinél. Így a sorozat elemei egy részbenrendezés elemei, a növekvő részsorozatok pedig láncok. Dilworth tétele szerint a legkisebb láncfedés száma megegyezik a legnagyobb antiláncéval, vagyis azzal a legnagyobb részsorozattal, amelyben a későbbi elem mindig nem nagyobb a korábbinál. Ennek hosszát a -A_i értékekre számolt leghosszabb nem csökkenő részsorozatként kapjuk meg: minden hosszhoz a legkisebb lehetséges utolsó elemet tároljuk, és minden új elemet bináris kereséssel helyezünk el. Az időigény O(N log N), N <= 100 000 esetén bőven belefér.
*/
/*
Hint 1: || Két elem ugyanabba a növekvő részsorozatba csak akkor tehető, ha a korábbi kisebb a későbbinél. Keress olyan részsorozatot, amelyben a későbbi elem mindig nem nagyobb a korábbinál: ezeket egyetlen növekvő részsorozatba sem teheted, ezért mindegyiknek külön sorozat kell. ||
Hint 2: || Ennek a részsorozatnak a hossza megegyezik a keresett minimális számmal (Dilworth-tétel). Ezt a leghosszabb nem növekvő részsorozatot megkapod úgy, hogy a számok helyett a negáltjaikat tekinted, és a leghosszabb nem csökkenő részsorozatot keresed. ||
Hint 3: || A leghosszabb nem csökkenő részsorozat hosszát O(N log N) időben számolhatod: tarts egy tömböt, amelynek i-edik eleme az i hosszú részsorozatok legkisebb lehetséges utolsó eleme. Minden új elemnél bináris kereséssel keresd meg az első olyan helyet, ahová beilleszthető, és ott írd felül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;

    // A minimális szám a leghosszabb nem növekvő részsorozat hossza (Dilworth).
    // Ezt a -a_i sorozat leghosszabb nem csökkenő részsorozataként számoljuk.
    vector<long long> tail;  // tail[i]: i+1 hosszú részsorozat legkisebb utolsó eleme
    for (long long x : a) {
        long long y = -x;
        auto it = upper_bound(tail.begin(), tail.end(), y);
        if (it == tail.end())
            tail.push_back(y);
        else
            *it = y;
    }

    cout << tail.size() << "\n";
    return 0;
}
