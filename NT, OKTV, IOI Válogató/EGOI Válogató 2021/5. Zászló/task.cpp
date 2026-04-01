/*
Megoldas: ket binaris keresessel megkeressuk a szinek hatarait.
Az elso keresessel megkapjuk a piros resz veget (elso nem piros helyet), a masodik
keresessel az elso zold helyet. Innen egyszeruen szamolhato a feher es zold hossz.
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