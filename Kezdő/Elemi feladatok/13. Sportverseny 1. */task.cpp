/*
Megoldás lényege: a röplabdacsapatok (6 fő) és a kézilabdacsapatok (7 fő) minden lehetséges darabszám-párját végigpróbáljuk, és azt a párost tartjuk meg, amelyben a csapatokba osztott tanulók száma a legnagyobb, de nem nagyobb N-nél. A kimaradók száma ekkor N - (csapatba osztottak száma), így ez lesz a legkevesebb. Mivel N legfeljebb 100, a két ciklus csak néhány száz lépés, az időigény elhanyagolható.
*/
/*
Hint 1: || Nem kell képletet keresni: a csapatok száma kicsi, ezért próbálhatod az összes lehetséges röplabda- és kézilabdacsapat-számot. ||
Hint 2: || Egy párra a csapatokba osztott tanulók száma 6 * rop + 7 * kez; ezt akkor tartsd meg, ha nem nagyobb N-nél, és nagyobb a korábbi legjobbnál. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int legjobb = -1, legjobbRop = 0, legjobbKez = 0;
    for (int rop = 0; 6 * rop <= n; rop++) {
        for (int kez = 0; 6 * rop + 7 * kez <= n; kez++) {
            int lefedett = 6 * rop + 7 * kez;
            if (lefedett > legjobb) {
                legjobb = lefedett;
                legjobbRop = rop;
                legjobbKez = kez;
            }
        }
    }
    cout << legjobbRop << " " << legjobbKez << " " << n - legjobb << "\n";
    return 0;
}
