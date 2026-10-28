/*
Megoldás lényege:
Egy mérés harmadfokú készültségű, ha a vízállása meghaladja az 1000 cm-t (10 métert). A harmadfokú folyószakaszok a harmadfokú mérések maximális, egymás melletti sorozatai, amelyeket egyetlen balról jobbra haladó bejárással kapunk meg: ha egy mérés harmadfokú, addig lépünk tovább, amíg a feltétel teljesül, és közben rögzítjük a sorozat kezdő- és végsorszámát.
A darabszámot, a sorozatok sorszámait és hosszait kiírjuk. A leghosszabb szakaszt úgy választjuk ki, hogy csak a szigorúan hosszabb szakasz írja felül az eddigit, így egyenlőség esetén az első marad.
Az algoritmus O(N) időben fut, ami az N <= 10000 és a 0,1 mp-es időlimit mellett bőven elég.
*/
/*
Hint 1: || Csak azok a mérések számítanak, amelyek 1000 cm-nél magasabbak. A feladat tehát a harmadfokú mérések egymás melletti sorozatainak megkeresése. ||
Hint 2: || Balról jobbra haladva, ha egy mérés harmadfokú, nézd a következőket, amíg a feltétel teljesül. A sorozat kezdete és vége egyetlen bejárásból adódik, nem kell páronként ellenőrizni. ||
Hint 3: || A sorozat hossza vég - kezdet + 1. A leghosszabb kiválasztásánál csak szigorúan hosszabb sorozat írja felül az eddigit, így egyenlőség esetén az első marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // Harmadfokú (1000 cm-nél magasabb) mérések maximális sorozatai, 1-től indexelve.
    vector<pair<int, int>> szakaszok;
    int i = 1;
    while (i <= n) {
        if (a[i] <= 1000) {
            i++;
            continue;
        }
        int j = i;
        while (j + 1 <= n && a[j + 1] > 1000) j++;
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
