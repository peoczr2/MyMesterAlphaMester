/*
Megoldás lényege:
Minden vízállást készültségi szintre osztunk: 3, ha meghaladja az 1000 cm-t, 2, ha meghaladja a 900 cm-t, 1, ha meghaladja a 800 cm-t, egyébként 0.
Az elsőfokú készültségű folyószakasz az egymás melletti, pontosan 1 szintű mérések maximális sorozata, ezeket egy balról jobbra haladó bejárással megkapjuk.
Minden ilyen szakasz kezdő- és végsorszámát, valamint hosszát (vég - kezdet + 1) kiírjuk, a leghosszabb szakaszt pedig a legelső,
szigorúan hosszabb hossz alapján választjuk ki, így egyenlőség esetén az első marad. Az algoritmus O(N) időben fut.
*/
/*
Hint 1: || Most csak azok a mérések számítanak, amelyek elsőfokúak, vagyis 800 cm-nél magasabbak, de 900 cm-nél nem magasabbak. A feladat ezek egymás melletti sorozatainak keresése. ||
Hint 2: || Balról jobbra haladva minden mérés szintjét egyszer kiszámolod. Egy azonos szintű sorozat kezdetét a bejárás során kapod meg, a végét pedig abban a pillanatban, amikor a szint megváltozik. ||
Hint 3: || A szakasz hossza vég − kezdet + 1. Tartsd meg az eddigi legjobb szakaszt, és csak szigorúan hosszabbnál írd felül, így egyenlőség esetén az első marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int szint(int h) {
    if (h > 1000) return 3;
    if (h > 900) return 2;
    if (h > 800) return 1;
    return 0;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<pair<int, int>> szakaszok;
    int i = 1;
    while (i <= n) {
        int s = szint(a[i]);
        int j = i;
        while (j + 1 <= n && szint(a[j + 1]) == s) j++;
        if (s == 1) szakaszok.push_back({i, j});
        i = j + 1;
    }

    cout << szakaszok.size() << '\n';
    if (szakaszok.empty()) return 0;

    for (size_t k = 0; k < szakaszok.size(); k++) {
        if (k > 0) cout << ' ';
        cout << szakaszok[k].first << ' ' << szakaszok[k].second;
    }
    cout << '\n';

    int legjobbKezdet = 0, legjobbVege = 0, legjobbHossz = 0;
    for (size_t k = 0; k < szakaszok.size(); k++) {
        int hossz = szakaszok[k].second - szakaszok[k].first + 1;
        if (k > 0) cout << ' ';
        cout << hossz;
        if (hossz > legjobbHossz) {
            legjobbHossz = hossz;
            legjobbKezdet = szakaszok[k].first;
            legjobbVege = szakaszok[k].second;
        }
    }
    cout << '\n';

    cout << legjobbKezdet << ' ' << legjobbVege << '\n';

    return 0;
}
