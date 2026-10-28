/*
Megoldás lényege:
Minden számhoz egy következő-mutatót tárolunk: ha a szám még nincs a halmazban, önmagára mutat; beszúráskor a következő számra mutat. Mex(a) a-tól indulva a mutatókat követi, és az első olyan számot adja, amely még nincs a halmazban: ez a legkisebb kizárt a-tól. A mutatókat útközben átírjuk az eredményre (útkompresszió, path halving), így a műveletek közel állandó idejűek. A számok legfeljebb 10^7, a Mex eredménye legfeljebb 10^7 + 10^5 + 1, ezért a tömb ennél valamivel nagyobb.
*/
/*
Hint 1: || Mex(a) a legkisebb olyan b ≥ a szám, amely nincs a halmazban. Nem kell a teljes halmazt végigjárni, csak az a-tól kezdődő, már beszúrt számokat kell átugrani. ||
Hint 2: || Ha egy szám benne van, a keresés ugorhat a következő számra. Tároljunk minden számhoz egy mutatót, amely egy nagyobb szám felé mutat, és az első szabad számnál áll meg. ||
Hint 3: || Beszúráskor a szám mutatóját állítsd a következő számra. A keresés közben a mutatókat rövidítsd le (útkompresszió), és a tömb mérete legyen legalább 10^7 + 10^5 + 2. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 10200010;
int par[MAXV];  // par[x] == x: x nincs a halmazban; különben a következő jelölt szám

struct Init {
    Init() {
        for (int i = 0; i < MAXV; ++i) par[i] = i;
    }
} initObj;

int keres(int x) {
    while (par[x] != x) {
        par[x] = par[par[x]];
        x = par[x];
    }
    return x;
}

void Adat(int x) {
    if (par[x] == x) par[x] = x + 1;
}

int Mex(int a) {
    return keres(a);
}

int main() {
    // Helyi próba: első sor a műveletek száma, utána "A x" (Adat(x)) vagy "M a" (Mex(a)) sorok.
    // Az M sorokra a Mex eredményét írjuk ki.
    int q;
    cin >> q;
    while (q--) {
        char c;
        int v;
        cin >> c >> v;
        if (c == 'A') Adat(v);
        else cout << Mex(v) << '\n';
    }
    return 0;
}
