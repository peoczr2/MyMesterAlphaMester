/*
Megoldás lényege:
Minden pozícióban az a_i + b_i összeg vagy legalább 10 (biztosan átvitelt ad), vagy legfeljebb 8 (biztosan nem ad), vagy
pontosan 9, ekkor a jobbról érkező átvitel dönt. Egy jegy értéke tehát csak attól függ, hogy a tőle jobbra lévő első nem
9-es összeg ad-e átvitelt, ezért a 9-esek sorozatát függőben tartjuk. Amint egy nem 9-es összeg megjelenik, a függő
szakasz minden jegye egyszerre meghatározottá válik, és azonnal kiírjuk őket balról jobbra. A legelső nem 9-es összeg
dönti el a legelső jegyet is: ha az legalább 10, az eredmény elé 1 kerül. A rövidebb számot balról nullákkal egészítjük
ki, a végén pedig egy virtuális 0 összeggel zárjuk a függő szakaszt. Időigény: O(N).
*/
/*
Hint 1: || Minden pozícióban az összeg három esetet adhat: legalább 10 (átvitelt ad), legfeljebb 8 (nem ad), vagy pontosan 9. Csak a 9-es összeg függ attól, hogy jobbról jön-e átvitel. ||
Hint 2: || Egy jegy értékét az határozza meg, hogy a tőle jobbra lévő első nem 9-es összeg ad-e átvitelt. Ezért a 9-esekből álló szakaszt tartsd függőben, és amint egy nem 9-es összeg megjelenik, a szakasz összes jegyét egyszerre írd ki. ||
Hint 3: || Az első nem 9-es összeg dönti el az eredmény legelső jegyét: ha az legalább 10, elé 1 kerül. A rövidebb számot balról nullákkal egészítsd ki, a végén pedig egy virtuális 0 összeggel zárd le a függő szakaszt. ||
*/
#include "osszead.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    int na = getaN();
    int nb = getbN();
    int len = max(na, nb);
    vector<int> d(len + 1, 0);  // pozíciónkénti összeg; a végén egy virtuális 0
    bool first = true;
    int pending = 0;             // az első még ki nem írt pozíció
    // carry: a p-edik pozícióból a bal szomszédba menő átvitel; ezzel a függő szakasz jegyei meghatározottak
    auto event = [&](int p, int carry) {
        if (first) {
            if (carry == 1) kiir(1);
            first = false;
        }
        for (int q = pending; q < p; q++) kiir((d[q] + carry) % 10);
        pending = p;
    };
    for (int p = 0; p < len; p++) {
        int a = (p >= len - na) ? geta() : 0;
        int b = (p >= len - nb) ? getb() : 0;
        d[p] = a + b;
        if (d[p] != 9) event(p, d[p] >= 10 ? 1 : 0);
    }
    event(len, 0);
    kiir(-1);
    return 0;
}
