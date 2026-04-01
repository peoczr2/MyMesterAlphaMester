#include <bits/stdc++.h>
using namespace std;

/*
    Minden napszámos keresete egyszerűen a ledolgozott napok száma szorozva a
    napi bérrel. A teljes költség ezek összege, a legtöbbet kereső pedig az,
    akinek a keresete maximális; holtversenyben a több napot dolgozó előnyt élvez.
*/

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