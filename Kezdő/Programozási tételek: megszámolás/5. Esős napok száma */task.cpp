/*
Megoldás lényege:
Egy napon akkor esett az eső, ha a mért csapadék nagyobb, mint 0 mm. A feladat tehát azt kérdezi, hogy hány olyan mérés van, ahol a csapadék pozitív.
Ezért nem kell a mérési adatokat tárolni: a bemenetet soronként olvassuk, és minden pozitív értéknél egy számlálót növelünk 1-gyel.
Egy nap döntése független a többitől, így egyetlen menetben megkapjuk az eredményt.
Az időigény O(N), a tárigény O(1).
*/
/*
Hint 1: || Egy nap akkor volt esős, ha a mért csapadék nagyobb, mint 0 mm. Nem a csapadék mennyisége (összege) a kérdés, hanem az, hogy hány nap felel meg ennek a feltételnek. ||
Hint 2: || Elég egyetlen számlálót tartani: a napi mérések beolvasásakor, ha az adott érték pozitív, növeld a számlálót. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int esos_napok = 0;
    for (int i = 0; i < n; i++) {
        int mm;
        cin >> mm;
        if (mm > 0) {
            esos_napok++;
        }
    }
    cout << esos_napok << endl;
    return 0;
}
