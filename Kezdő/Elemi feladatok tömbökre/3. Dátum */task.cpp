/*
Megoldás lényege:
1901. január 1. keddi nap volt. Egy év január 1-jétől a következő év január 1-jéig 365 nap telik el, szökőévben 366. Ezért E év január 1-je úgy kapható meg, hogy 1901-től E-1-ig minden évnél a hét napját a napok számával (365 vagy 366) léptetjük, mod 7. A szökőév szabálya: a 4-gyel osztható évek, kivéve a 100-zal osztható évek, kivéve a 400-zal osztható évek. Legfeljebb 10 000 év van, így az egyszerű végigléptetés bőven belefér az időlimitbe.
*/
/*
Hint 1: || Egy év hossza 365 nap, szökőévben 366. Mivel 7 nap alkot egy hetet, az év napjainak számát 7-tel osztva a maradék megmondja, hány nappal tolódik el a hét napja. ||
Hint 2: || A szökőév döntéséhez használd a 4, a 100 és a 400 szerinti osztási maradékot. Egy ciklusban menj végig az 1901-től E-1-ig tartó éveken, és minden évnél léptesd a hét napját (hétfő = 0, kedd = 1, ...). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int e;
    cin >> e;

    const string napok[7] = {"hetfo", "kedd", "szerda", "csutortok", "pentek", "szombat", "vasarnap"};

    // 1901. január 1. kedd, a hét napjai hétfőtől indexelve
    int nap = 1;
    for (int ev = 1901; ev < e; ev++) {
        bool szokoev = (ev % 4 == 0 && ev % 100 != 0) || ev % 400 == 0;
        nap = (nap + (szokoev ? 366 : 365)) % 7;
    }

    cout << napok[nap] << "\n";
    return 0;
}
