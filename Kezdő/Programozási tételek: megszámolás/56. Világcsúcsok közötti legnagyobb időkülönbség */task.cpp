/*
Megoldás lényege:
A világcsúcsok (a beállításokat is beleértve) időpontjait egymás után olvassuk be. Két szomszédos rekord között eltelt évek száma az évszámok különbsége, és az évszámok a magasság szerinti sorrendben sem csökkennek. Ezért egyetlen végigolvasásban minden szomszédos párra kiszámoljuk a különbséget, és a legnagyobbat tartjuk meg. Az időigény O(N), a tárigény O(1).
*/
/*
Hint 1: || A kérdés a szomszédos rekordpárokra vonatkozik. A beállítások (azonos magasság) is világcsúcsnak számítanak, tehát nem elég a szigorúan magasabb rekordokat nézni. ||
Hint 2: || Egy változóban tartsd az előző rekord évét, és minden új rekordnál számold ki a különbséget az előzőhöz képest. A legnagyobb különbséget egy másik változóban tartsd karban. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int elozo_ev = 0, legnagyobb = 0;
    for (int i = 0; i < n; i++) {
        int ev, mag;
        cin >> ev >> mag;
        if (i > 0) legnagyobb = max(legnagyobb, ev - elozo_ev);
        elozo_ev = ev;
    }
    cout << legnagyobb << "\n";
    return 0;
}
