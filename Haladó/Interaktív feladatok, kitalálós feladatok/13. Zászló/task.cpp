/*
Megoldás lényege:
A zászló színei sorrendben piros, fehér, zöld, ezért a kerdes(a) függvény értéke
a pozíció szerint nemcsökkenő (1, 2, 3). Két bináris kereséssel megkeressük a
piros rész végét (az első nem piros pozíciót) és a zöld rész kezdetét (az első
zöld pozíciót). Ebből a piros, fehér és zöld hossz egyszerűen kiszámolható.
Az időigény O(log N) kérdés, ami a 100-as korláton belül van.
*/
/*
Hint 1: || Figyeld meg, hogy a színek a korláton sorban következnek: piros, majd fehér, majd zöld. Ezért a kerdes értéke nemcsökkenő a sorszám szerint. ||
Hint 2: || Bináris kereséssel keresd meg az első olyan pozíciót, ahol a szín nem piros, és az első olyan pozíciót, ahol a szín zöld. ||
*/
#include "zaszlo.h"

int main() {
    int n = kezdet();

    // Az első nem piros pozíció keresése.
    int bal = 1, jobb = n;
    while (bal < jobb) {
        int kozep = (bal + jobb) / 2;
        if (kerdes(kozep) == 1) bal = kozep + 1;
        else jobb = kozep;
    }
    int p = bal - 1;

    // Az első zöld pozíció keresése.
    bal = 1; jobb = n;
    while (bal < jobb) {
        int kozep = (bal + jobb) / 2;
        if (kerdes(kozep) == 3) jobb = kozep;
        else bal = kozep + 1;
    }
    int zKezdet = bal;

    int f = zKezdet - p - 1;
    int z = n - zKezdet + 1;
    eredmeny(p, f, z);
    return 0;
}
