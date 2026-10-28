/*
Megoldás lényege:
Az indulók száma N legfeljebb 1024, és a rajtszámok pontosan az 1..N számok
egy permutációjából egyetlen hiányzó értékkel állnak elő. Minden megjelent
versenyző rajtszámát a bitjeiből rekonstruálhatjuk.

Elég a legalsó 10 bitet lekérdezni minden megjelent versenyzőre, mert az 1..1024
tartományban ezekből egyértelműen meghatározható az érték: az összes nemnulla
10 bites mintához pontosan egy szám tartozik, az összes nulla minta pedig 1024.
Miután bejelöltük a látott számokat, a hiányzó az első, amely nem szerepelt.
*/
/*
Hint 1: || Egy 1 és 1024 közötti szám tízbites bináris alakja egyértelmű: ha minden megjelent versenyzőre lekérdezed a 0-tól a 9-ig terjedő biteket, megkapod a rajtszámát. Az 1024 tízbites alakja csupa nulla, ezt külön kezeld. ||
Hint 2: || Az 1..N-1 sorszámú versenyzőket kérdezd meg, és egy logikai tömbben jelöld, mely rajtszámok szerepeltek. A hiányzó rajtszám az 1 és N közötti első nem jelölt szám. ||
*/
#include <bits/stdc++.h>
#include "valasz.h"
using namespace std;

int main() {
    int n = induloszam();
    vector<char> seen(n + 1, 0);

    for (int x = 1; x < n; ++x) {
        int value = 0;
        for (int bit = 0; bit < 10; ++bit) {
            if (kerdes(x, bit)) value |= (1 << bit);
        }
        if (value == 0) value = 1024;
        if (value <= n) seen[value] = 1;
    }

    for (int a = 1; a <= n; ++a) {
        if (!seen[a]) {
            megoldas(a);
            return 0;
        }
    }

    megoldas(1);
    return 0;
}