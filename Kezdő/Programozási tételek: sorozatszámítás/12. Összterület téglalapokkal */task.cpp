/*
Megoldás lényege:
Egy téglalap területe a két oldal szorzata, így a birtok összterülete az egyes téglalapok szélesség·hosszúság értékeinek összege. Az első sorban álló K után K sort olvasunk be, mindegyikben két egész számot, és a szorzatukat hozzáadjuk egy összeg-változóhoz. Minden téglalapot pontosan egyszer dolgozunk fel, így az időigény O(K), ami K ≤ 100 esetén bőven az időlimiten belül marad. Az oldalak legfeljebb 1000-esek, így az összeg legfeljebb 100 · 10^6 = 10^8, ez long long típusban biztosan elfér.
*/
/*
Hint 1: || Minden sorban két szám van: a szélesség és a hosszúság. Egy téglalap területe ezek szorzata, így a feladat a területek összegzése. ||
Hint 2: || Egy ciklusban olvasd be a két számot egymás után (cin >> a >> b), és minden körben a·b szorzatot add az összeghez. Az összeg típusa long long legyen. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int k;
    cin >> k;

    long long osszeg = 0;
    for (int i = 0; i < k; i++) {
        long long szelesseg, hosszusag;
        cin >> szelesseg >> hosszusag;
        osszeg += szelesseg * hosszusag;
    }

    cout << osszeg << "\n";
    return 0;
}
