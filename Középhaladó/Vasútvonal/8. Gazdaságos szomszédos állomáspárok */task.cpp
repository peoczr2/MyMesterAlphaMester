/*
Megoldás lényege:
Az i-edik és (i+1)-edik állomás közötti szakaszon annyi utas utazik, amennyi az első i állomásnál felszálló és leszálló utasok különbségének összege. Ezt futó összegben tartjuk nyilván, az állomásokat sorban olvassuk be.
A szakasz bevétele K forint utasonként, vagyis K · utasszám, a kiadása M forint. A szakasz akkor gazdaságos, ha a bevétel nagyobb a kiadásnál, azaz K · utasszám > M.
Az utolsó állomás után már nincs szakasz, ezért a számlálás N − 1 szakaszra terjed ki. Az időigény O(N), N ≤ 1000 mellett ez bőven az időlimit alatt van.
*/
/*
Hint 1: || Az i-edik szakaszon a vonaton lévő utasok száma: az első i állomás felszállóinak összege mínusz a leszállóinak összege. ||
Hint 2: || Egy ciklusban olvasd be az állomásokat, frissítsd az utasszámot, és ha nem az utolsó állomásnál vagy, hasonlítsd össze a K · utasszámot az M-mel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k, m;
    cin >> n >> k >> m;
    long long utasok = 0;
    int gazdasagos = 0;
    for (int i = 1; i <= n; i++) {
        long long le, fel;
        cin >> le >> fel;
        utasok += fel - le;
        if (i < n && k * utasok > m) {
            gazdasagos++;
        }
    }
    cout << gazdasagos << endl;
    return 0;
}
