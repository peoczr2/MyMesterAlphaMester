/*
Megoldás lényege:
Egy szám önmagánál kisebb osztóinak összegét minden pároknál újra kiszámolni lassú lenne, ezért előre kiszámoljuk 1 és 100 000 között minden szám osztóösszegét egy rostához hasonló módszerrel. Minden d számra az összegéhez hozzáadjuk a d-t az összes olyan k számnál, amelynek d osztója és k nagyobb d-nél, azaz k = 2d, 3d, ... Ez O(M log M) időben elkészül, ahol M = 100 000. Ezután minden (X, Y) párra egyszerűen ellenőrizzük, hogy X osztóösszege egyenlő-e Y-nal, és Y osztóösszege egyenlő-e X-szel. Ha mindkét feltétel teljesül, a pár barátságos, és Igen-t írunk, különben Nem-et. Az egy párra jutó válasz időigénye O(1).
*/
/*
Hint 1: || Ne számold ki minden párnál újra az osztókat: egy egyszer előre kiszámolt tömbből minden szám osztóösszege egy egyszerű elemmel kérdezhető le. ||
Hint 2: || Ha d osztója k-nak és d kisebb k-nál, akkor d-t hozzáadhatod k osztóösszegéhez. Ezt úgy töltheted fel, hogy minden d-re a 2d, 3d, 4d, ... számokhoz hozzáadod d-t, így minden szám megkapja az összes önmagánál kisebb osztóját. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int MAX_SZAM = 100000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // osztoOsszeg[x]: x önmagánál kisebb pozitív osztóinak összege
    vector<long long> osztoOsszeg(MAX_SZAM + 1, 0);
    for (int d = 1; d <= MAX_SZAM; d++) {
        for (int k = 2 * d; k <= MAX_SZAM; k += d) {
            osztoOsszeg[k] += d;
        }
    }

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        bool baratsagos = (osztoOsszeg[x] == y) && (osztoOsszeg[y] == x);
        cout << (baratsagos ? "Igen" : "Nem") << "\n";
    }

    return 0;
}
