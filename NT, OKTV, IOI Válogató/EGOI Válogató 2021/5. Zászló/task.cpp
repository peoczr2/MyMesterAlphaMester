/*
Megoldas: ket binaris keresessel megkeressuk a szinek hatarait.
Az elso keresessel megkapjuk a piros resz veget (elso nem piros helyet), a masodik
keresessel az elso zold helyet. Innen egyszeruen szamolhato a feher es zold hossz.
Az idoigeny es a kerdesek szama is O(log N).
*/
/*
Hint 1: || A három szín a korláton sorban következik: előbb piros, aztán fehér, végül zöld. Ezért a piros rész vége és a zöld rész kezdete egy-egy határ, amelyet a kerdes válaszai monoton módon jeleznek. ||
Hint 2: || A határt bináris kereséssel keresd: a kerdes(k) válasza alapján el tudod dönteni, hogy a határ k-tól balra vagy jobbra van. Az első kereséshez az első nem piros mezőt, a másodikhoz az első zöld mezőt keresd. ||
Hint 3: || Ha az első nem piros mező sorszáma p+1, a piros hossz p. Ha az első zöld mező sorszáma z0, akkor a fehér hossz z0−p−1, a zöld hossz N−z0+1. Az eredményt egyszer add meg az eredmeny függvénnyel, a program végén. ||
*/

#include "zaszlo.h"

int main() {
    int n = kezdet();

    int bal = 1, jobb = n;
    while (bal < jobb) {
        int kozep = (bal + jobb) / 2;
        if (kerdes(kozep) == 1) bal = kozep + 1;
        else jobb = kozep;
    }
    int p = bal - 1;

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