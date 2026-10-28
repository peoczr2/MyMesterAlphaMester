/*
Megoldás lényege:
Minden mérést készültségi szintre alakítunk: 800 cm felett 1, 900 cm felett 2, 1000 cm felett 3, különben 0.
Az árvizek a legalább 1-es szintű mérések maximális, egymás utáni sorozatai, ezeket egy balról jobbra haladó bejárással találjuk meg.
A folyószakasz egyforma szintű mérések maximális sorozata, így egy árvízen belül a harmadfokú szakaszok száma a 3-as szintű mérések új sorozatainak számával egyezik.
Új sorozat ott kezdődik, ahol a 3-as szintű mérés előtt nem 3-as szintű mérés áll (vagy az árvíz kezdete van ott).
Az árvizeket a kezdetükkel, a végükkel és a harmadfokú szakaszaik számával együtt tároljuk; a negyedik sorba a legtöbb ilyen szakaszt tartalmazó árvíz első előfordulása kerül, ha ez 0, akkor 0.
Az algoritmus egyetlen bejárás, így O(N) időben fut.
*/
/*
Hint 1: || Az árvizek ugyanúgy adódnak, mint az előző feladatokban: a legalább 1-es szintű mérések maximális, egymás utáni sorozatai. ||
Hint 2: || Egy árvízen belül egy új harmadfokú folyószakasz akkor kezdődik, ha egy 3-as szintű mérés előtt nem 3-as szintű mérés áll, vagy az árvíz első mérése az. ||
Hint 3: || Az árvíz végén jegyezd fel a kezdetét, a végét és a harmadfokú szakaszok számát. A legjobbat csak szigorúan nagyobb érték esetén cseréld le, így az első előfordulás marad meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Készültségi szint: 0 (nincs), 1 (elsőfokú), 2 (másodfokú), 3 (harmadfokú)
int szint(int h) {
    if (h <= 800) return 0;
    if (h <= 900) return 1;
    if (h <= 1000) return 2;
    return 3;
}

int main() {
    const int CEL_SZINT = 3;  // a harmadfokú készültségű folyószakaszokat számoljuk

    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        int h;
        cin >> h;
        s[i] = szint(h);
    }

    vector<pair<int, int>> arviz;  // az árvizek [kezdet, vég] sorszámai (1-től)
    vector<int> db_szakasz;        // az egyes árvizek célszintű folyószakaszainak száma

    int i = 0;
    while (i < n) {
        if (s[i] == 0) {
            i++;
            continue;
        }
        int kezdet = i;
        int db = 0;
        while (i < n && s[i] >= 1) {
            if (s[i] == CEL_SZINT && (i == kezdet || s[i - 1] != CEL_SZINT)) db++;
            i++;
        }
        arviz.push_back({kezdet + 1, i});
        db_szakasz.push_back(db);
    }

    int k = arviz.size();
    cout << k << "\n";
    if (k == 0) return 0;

    for (int j = 0; j < k; j++) {
        if (j) cout << ' ';
        cout << arviz[j].first << ' ' << arviz[j].second;
    }
    cout << "\n";

    for (int j = 0; j < k; j++) {
        if (j) cout << ' ';
        cout << db_szakasz[j];
    }
    cout << "\n";

    int legjobb = 0;
    for (int j = 1; j < k; j++) {
        if (db_szakasz[j] > db_szakasz[legjobb]) legjobb = j;
    }
    if (db_szakasz[legjobb] == 0) {
        cout << 0 << "\n";
    } else {
        cout << arviz[legjobb].first << ' ' << arviz[legjobb].second << "\n";
    }
    return 0;
}
