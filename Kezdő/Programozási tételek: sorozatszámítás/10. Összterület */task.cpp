/*
Megoldás lényege:
Egy négyzet területe az oldalhosszának négyzete, ezért a birtok összterülete a földek szélességeinek négyzeteinek összege. A K szélességet egyenként beolvassuk, mindegyiket négyzetre emeljük, és egy összeg-változóhoz adjuk. Minden földdarabot pontosan egyszer dolgozunk fel, így az időigény O(K), ami K ≤ 100 esetén messze az időlimit alatt marad. Mivel a szélesség nincs felülről korlátozva, az összeget long long típusban tároljuk, hogy ne legyen túlcsordulás.
*/
/*
Hint 1: || Figyeld meg, hogy a négyzet területe az oldalhosszának négyzete, így a feladat a szélességek négyzeteinek összegzése. ||
Hint 2: || Az összeg-változót nullázd le, majd K körben olvass be egy számot, és minden körben add hozzá a négyzetét. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int k;
    cin >> k;

    long long osszeg = 0;
    for (int i = 0; i < k; i++) {
        long long szelesseg;
        cin >> szelesseg;
        osszeg += szelesseg * szelesseg;
    }

    cout << osszeg << "\n";
    return 0;
}
