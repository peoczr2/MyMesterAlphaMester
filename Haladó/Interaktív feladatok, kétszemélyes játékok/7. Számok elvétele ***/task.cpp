/*
Megoldás lényege:
A sor bal végéről mindig 1, 2 vagy 3 szám vehető el, ezért az állapotot egyetlen szám, az első még el nem vett szám indexe írja le.
Hátulról előre kiszámoljuk, hogy az i-edik számtól kezdve a soron lévő játékos legfeljebb mennyi többletpontot tud szerezni az ellenfelénél: f[i] = max(L = 1..3) (a[i] + ... + a[i+L-1] - f[i+L]), ahol f[N+1] = 0.
Az első játékos mindig az optimumot adó L-t lépi, ezért a játék végén a pontkülönbsége legalább f[1]; a feladat garantálja, hogy f[1] > 0, tehát nyer, bárhogyan lép az ellenfele.
A Szamit eljárást a modul Meret-en belül hívja, de akkor a Tabla még nem használható, ezért a törzse üres; a számítás a Meret után történik.
Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Az állapot leírásához elég tudni, hogy a sor bal végéről eddig hány számot vettek el. ||
Hint 2: || Hátulról haladva számold ki minden kezdőindexre, hogy a soron lévő játékos mennyi előnyt érhet el: az épp elvett 1–3 szám összege mínusz az ellenfél előnye a maradékon. ||
Hint 3: || Meret után olvasd be a számokat Tabla(i)-vel, majd ciklusban add ki az EnLep(L) lépést, utána hívd a TeLep()-et; a játék végét a modul maga kezeli. ||
*/
#include "ellenfel.h"
#include <bits/stdc++.h>
using namespace std;

// A modul Meret-en belül hívja, a Tabla viszont csak Meret után használható: itt nincs teendő.
void Szamit() {}

int main() {
    int n = Meret();

    vector<long long> pre(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + Tabla(i);
    }

    // f[i]: a soron lévő játékos legnagyobb pontelőnye az i-edik számtól kezdve
    vector<long long> f(n + 4, 0);
    vector<int> valasz(n + 2, 1);
    for (int i = n; i >= 1; i--) {
        long long legjobb = LLONG_MIN;
        for (int L = 1; L <= 3 && i + L - 1 <= n; L++) {
            long long ertek = (pre[i + L - 1] - pre[i - 1]) - f[i + L];
            if (ertek > legjobb) {
                legjobb = ertek;
                valasz[i] = L;
            }
        }
        f[i] = legjobb;
    }

    int ix = 1;  // az első még el nem vett szám indexe
    while (ix <= n) {
        int L = valasz[ix];
        EnLep(L);       // ha ez volt az utolsó lépés, a modul itt befejezi a programot
        ix += L;
        ix += TeLep();  // az ellenfél lépése
    }
    return 0;
}
