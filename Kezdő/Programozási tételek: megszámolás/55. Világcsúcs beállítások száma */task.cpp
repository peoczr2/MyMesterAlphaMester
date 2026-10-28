/*
Megoldás lényege:
A világcsúcsok magasság szerint növekvő sorrendben vannak, így egy világcsúcs-beállítás pontosan akkor történik, ha egy rekord magassága megegyezik az őt megelőző rekord magasságával. Ezek az egyezések mindig egymás után állnak, ezért elég egyetlen végigolvasás, amely az előző magasságot tartja nyilván. Az évszámot beolvassuk, de a kérdés szempontjából nem kell. Az időigény O(N), a tárigény O(1).
*/
/*
Hint 1: || Két egymás utáni világcsúcs akkor beállítás, ha a magasságuk pontosan megegyezik. A magasságok sorrendben vannak, ezért az egyező párok egymás mellett állnak. ||
Hint 2: || Tartsd nyilván az előző rekord magasságát egy változóban, és minden új rekordnál hasonlítsd össze a magasságát az előzővel. Az évszám ehhez nem kell. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int elozo_mag = -1, beallitas = 0;
    for (int i = 0; i < n; i++) {
        int ev, mag;
        cin >> ev >> mag;
        if (mag == elozo_mag) beallitas++;
        elozo_mag = mag;
    }
    cout << beallitas << "\n";
    return 0;
}
