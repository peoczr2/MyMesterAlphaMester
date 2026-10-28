/*
Megoldás lényege:
A legalább másodfokú készültség azt jelenti, hogy a vízállás meghaladja a 900 cm-t, mert a másod- és harmadfokú mérések együtt alkotják a keresett tulajdonságot. Így a folyószakaszok a 900 cm-nél magasabb mérések maximális, egymás melletti sorozatai, nem a pontos szint egyezése szerint.
Ezeket egyetlen balról jobbra haladó bejárással kapjuk meg: amikor találunk ilyen mérést, addig lépünk tovább, amíg a feltétel teljesül, és közben rögzítjük a kezdő- és végsorszámot.
A darabszámot, a sorozatok sorszámait és hosszait kiírjuk. A leghosszabb szakaszt úgy választjuk ki, hogy csak a szigorúan hosszabb szakasz írja felül az eddigit, így egyenlőség esetén az első marad.
Az algoritmus O(N) időben fut, ami az N <= 10000 és a 0,1 mp-es időlimit mellett bőven elég.
*/
/*
Hint 1: || Most a másod- és harmadfokú mérések együtt számítanak, vagyis a 900 cm-nél magasabb mérések. Nem kell megkülönböztetni a két szintet. ||
Hint 2: || Balról jobbra haladva keresd az összefüggő, 900 cm-nél magasabb mérésekből álló sorozatokat. A sorozat kezdetét találod meg először, a végét pedig az első nem megfelelő mérésnél. ||
Hint 3: || A sorozat hossza vég - kezdet + 1. A leghosszabb kiválasztásánál csak szigorúan hosszabb sorozat írja felül az eddigit, így egyenlőség esetén az első marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // A 900 cm-nél magasabb mérések maximális sorozatai, 1-től indexelve.
    vector<pair<int, int>> szakaszok;
    int i = 1;
    while (i <= n) {
        if (a[i] <= 900) {
            i++;
            continue;
        }
        int j = i;
        while (j + 1 <= n && a[j + 1] > 900) j++;
        szakaszok.push_back({i, j});
        i = j + 1;
    }

    cout << szakaszok.size() << '\n';
    if (szakaszok.empty()) return 0;

    for (size_t k = 0; k < szakaszok.size(); k++) {
        if (k) cout << ' ';
        cout << szakaszok[k].first << ' ' << szakaszok[k].second;
    }
    cout << '\n';

    int legHossz = 0, legKezdet = 0, legVege = 0;
    for (size_t k = 0; k < szakaszok.size(); k++) {
        int hossz = szakaszok[k].second - szakaszok[k].first + 1;
        if (k) cout << ' ';
        cout << hossz;
        if (hossz > legHossz) {
            legHossz = hossz;
            legKezdet = szakaszok[k].first;
            legVege = szakaszok[k].second;
        }
    }
    cout << '\n';

    cout << legKezdet << ' ' << legVege << '\n';
    return 0;
}
