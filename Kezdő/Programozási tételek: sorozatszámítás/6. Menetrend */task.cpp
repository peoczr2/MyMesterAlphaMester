/*
Megoldás lényege:
Egy állomáson akkor áll meg minden vonat, ha az állomás oszlopában minden sorban 1 áll. Ezt egy A elemű tömbbel követjük nyomon, amely kezdetben minden elemében 1-et tartalmaz. A sorokat egyenként olvassuk be, és ha egy beolvasott érték 0, a hozzá tartozó oszlop bitjét nullázzuk. Így minden bemeneti számot pontosan egyszer dolgozunk fel, az időigény O(V * A), ami legfeljebb 10^4 elem. A kimenetben az A bitet szóközzel elválasztva írjuk ki.
*/
/*
Hint 1: || Egy állomás bitje pontosan akkor 1, ha az adott oszlopban minden vonat sorában 1 áll. Hogyan vizsgálhatod az oszlopokat úgy, hogy a sorokat egyenként olvasod be? ||
Hint 2: || Készíts egy A elemű tömböt, amelynek minden eleme kezdetben 1. Amikor a bemenetből 0 érkezik, állítsd nullára a tömb aktuális oszlopnak megfelelő elemét. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int v, a;
    cin >> v >> a;

    vector<int> megall(a, 1);
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < a; j++) {
            int bit;
            cin >> bit;
            if (bit == 0) {
                megall[j] = 0;
            }
        }
    }

    for (int j = 0; j < a; j++) {
        cout << megall[j] << (j + 1 < a ? " " : "\n");
    }
    return 0;
}
