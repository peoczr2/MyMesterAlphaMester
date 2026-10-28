/*
Megoldás lényege:
Minden mérést készültségi szintre alakítunk: 800 cm felett 1, 900 cm felett 2, 1000 cm felett 3, különben 0.
Az árvízmentes folyószakaszok a 0-s szintű mérések maximális, egymás utáni sorozatai, ezeket egy balról jobbra haladó bejárással gyűjtjük össze.
Két szomszédos árvízmentes szakasz távolsága a második szakasz kezdő sorszámának és az első szakasz záró sorszámának a különbsége.
A legközelebbi párt a minimális távolság keresésével találjuk meg; ha több ilyen van, a legelsőt írjuk ki.
Az algoritmus egyetlen bejárás, így O(N) időben fut.
*/
/*
Hint 1: || Az árvízmentes folyószakaszok a 0-s készültségi szintű mérések maximális, egymás utáni sorozatai. Számold ki a szinteket, majd egy bejárásban gyűjtsd össze a szakaszokat. ||
Hint 2: || Két szomszédos árvízmentes szakasz között a távolság a következő szakasz kezdete mínusz az előző szakasz vége. Elég a szomszédos párokat vizsgálni, mert a legközelebbi pár mindig szomszédos szakaszok között van. ||
Hint 3: || Ha K < 2, a második sor után nincs több kiírás. Egyébként a távolságok közül keresd a legkisebbet, és csak szigorúan kisebb értéknél frissítsd, így az első előfordulás marad meg. ||
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
    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        int h;
        cin >> h;
        s[i] = szint(h);
    }

    vector<pair<int, int>> szakasz;  // az árvízmentes folyószakaszok [kezdet, vég] sorszámai (1-től)
    int i = 0;
    while (i < n) {
        if (s[i] != 0) {
            i++;
            continue;
        }
        int kezdet = i;
        while (i < n && s[i] == 0) i++;
        szakasz.push_back({kezdet + 1, i});
    }

    int k = szakasz.size();
    cout << k << "\n";
    if (k == 0) return 0;

    for (int j = 0; j < k; j++) {
        if (j) cout << ' ';
        cout << szakasz[j].first << ' ' << szakasz[j].second;
    }
    cout << "\n";
    if (k < 2) return 0;

    // Két szomszédos szakasz távolsága: a második kezdete mínusz az első vége
    vector<int> tav(k - 1);
    for (int j = 0; j + 1 < k; j++) {
        tav[j] = szakasz[j + 1].first - szakasz[j].second;
    }
    for (int j = 0; j < k - 1; j++) {
        if (j) cout << ' ';
        cout << tav[j];
    }
    cout << "\n";

    int legjobb = 0;
    for (int j = 1; j < k - 1; j++) {
        if (tav[j] < tav[legjobb]) legjobb = j;
    }
    cout << szakasz[legjobb].first << ' ' << szakasz[legjobb].second << ' '
         << szakasz[legjobb + 1].first << ' ' << szakasz[legjobb + 1].second << "\n";
    return 0;
}
