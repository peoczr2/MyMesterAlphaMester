/*
Megoldás lényege:
A gyakorlati jegyet egy segédfüggvény számolja: ha a röpzárthelyi pontszáma 10-nél kisebb, vagy valamelyik zárthelyi
jegye 0 (nem írta meg), a jegy 1. Különben a (Cs1 + Cs2 + 2*Ef) / 4 + 0,5 egész része, de legalább 1.
A 0,5-ös kerekítés egész számokkal: az (S + 2) / 4 egész osztás pontosan az egész részt adja, ha S = Cs1 + Cs2 + 2*Ef.
Minden hallgatóra egyesével megnézzük, javulna-e a jegye, ha a röpzárthelyi pontszáma eggyel nőne, vagy a megírt
zárthelyik valamelyikének jegye eggyel nőne. Az utóbbinál az 5-ös jegyet nem növeljük, mert a jegy legfeljebb 5 lehet.
Az első ilyen hallgató sorszámát írjuk ki, különben 0-t. Az időigény O(N).
*/
/*
Hint 1: || Írj külön függvényt a gyakorlati jegy kiszámítására a pontszám és a három jegy alapján, hogy a szabályt többször is fel tudd használni. ||
Hint 2: || Hallgatónként vizsgáld meg az egy lépéses változtatásokat: a pontszám eggyel nő, vagy a három zárthelyi közül egy megírt jegy eggyel nő. Ha bármelyik javít a jegyen, ez a hallgató a válasz. ||
Hint 3: || A kerekítés az egész osztással megoldható, ha az összeghez kettőt adsz, és 4-gyel osztasz. Ügyelj arra, hogy a 0-s jegyű (meg nem írt) zárthelyik nem növelhető, és az 5-ös jegy sem. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A gyakorlati jegy kiszámítása a röpzárthelyi pontszám és a három zárthelyi jegy alapján.
int gyakorlati_jegy(int r, int cs1, int cs2, int ef) {
    if (r < 10 || cs1 == 0 || cs2 == 0 || ef == 0) return 1;
    return max(1, (cs1 + cs2 + 2 * ef + 2) / 4);
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int r, cs1, cs2, ef;
        cin >> r >> cs1 >> cs2 >> ef;
        int jegy = gyakorlati_jegy(r, cs1, cs2, ef);
        bool javulna = false;
        if (r < 20 && gyakorlati_jegy(r + 1, cs1, cs2, ef) > jegy) javulna = true;
        if (cs1 != 0 && cs1 < 5 && gyakorlati_jegy(r, cs1 + 1, cs2, ef) > jegy) javulna = true;
        if (cs2 != 0 && cs2 < 5 && gyakorlati_jegy(r, cs1, cs2 + 1, ef) > jegy) javulna = true;
        if (ef != 0 && ef < 5 && gyakorlati_jegy(r, cs1, cs2, ef + 1) > jegy) javulna = true;
        if (javulna) {
            cout << i << "\n";
            return 0;
        }
    }
    cout << 0 << "\n";
    return 0;
}
