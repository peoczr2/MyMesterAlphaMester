/*
Megoldás lényege:
    Minden napszámos keresete egyszerűen a ledolgozott napok száma szorozva a
    napi bérrel. A teljes költség ezek összege, a legtöbbet kereső pedig az,
    akinek a keresete maximális; holtversenyben a több napot dolgozó előnyt élvez.
    Ha ez is egyenlő, bármelyik megfelelő, itt az első marad.
*/
/*
Hint 1: || Egy napszámos ledolgozott napjainak száma Végi - Kezdi + 1, a keresete ennek és a napi bérnek a szorzata. A teljes költség ezeknek az összege, így a sorokat egyszer kell beolvasni. ||
Hint 2: || Közben tartsd nyilván az eddigi legnagyobb keresetet, a hozzá tartozó sorszámot és munkanapszámot. Egyenlő keresetnél akkor frissíts, ha ennek a napszámosnak több munkanapja van. Az összeg akár 10^10 is lehet, ezért 64 bites típust használj. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    long long osszeg = 0;
    long long legjobb_kereset = -1;
    int legjobb_nap = -1;
    int legjobb_sor = 1;

    for (int i = 1; i <= n; ++i) {
        int kezdi, vegi, ber;
        cin >> kezdi >> vegi >> ber;
        long long napok = vegi - kezdi + 1;
        long long kereset = napok * 1LL * ber;
        osszeg += kereset;

        if (kereset > legjobb_kereset || (kereset == legjobb_kereset && napok > legjobb_nap)) {
            legjobb_kereset = kereset;
            legjobb_nap = napok;
            legjobb_sor = i;
        }
    }

    cout << osszeg << '\n' << legjobb_sor << '\n';
    return 0;
}
