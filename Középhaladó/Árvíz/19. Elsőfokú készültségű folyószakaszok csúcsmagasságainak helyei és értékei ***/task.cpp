/*
Megoldás lényege:
Az elsőfokú folyószakasz az azonos szintű, egymás melletti mérések maximális sorozata, amelynek szintje 1. A szintek szerinti szakaszokat egyetlen balról jobbra haladó bejárással gyűjtjük ki, és csak az 1. szintűeket tartjuk meg.
Minden ilyen szakaszban egy végigmenéssel megkeressük a legnagyobb csúcsmagasságot; egyenlőség esetén az első előfordulás a jó.
A második sorba a szakaszok kezdő és záró sorszáma kerül, a harmadikba pedig szakaszonként a csúcs helye és értéke.
Az időigény O(N), ami N ≤ 10 000 esetén messze az időlimit alatt van.
*/
/*
Hint 1: || A folyószakasz nem a legalább elsőfokú mérések sorozata, hanem az azonos szintű egymás melletti mérések maximális sorozata. Így egy 2. vagy 3. szintű mérés már szakaszhatár. ||
Hint 2: || Egy szakasz csúcsát egy végigmenéssel keresd: tartsd az eddigi legnagyobb érték helyét, és csak szigorúan nagyobb értéknél írd felül, hogy az első előfordulás maradjon. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Készültségi szint: 0 = nincs, 1 = elsőfokú, 2 = másodfokú, 3 = harmadfokú
int szint(int magassag) {
    if (magassag > 1000) return 3;
    if (magassag > 900) return 2;
    if (magassag > 800) return 1;
    return 0;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n), sz(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sz[i] = szint(a[i]);
    }

    // Az elsőfokú folyószakaszok [kezdet, vége] párjai, 0-indexelve
    vector<pair<int, int>> szakaszok;
    int i = 0;
    while (i < n) {
        int j = i;
        while (j + 1 < n && sz[j + 1] == sz[i]) j++;
        if (sz[i] == 1) szakaszok.push_back({i, j});
        i = j + 1;
    }

    int k = szakaszok.size();
    cout << k << '\n';
    if (k == 0) return 0;

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << szakaszok[t].first + 1 << ' ' << szakaszok[t].second + 1;
    }
    cout << '\n';

    for (int t = 0; t < k; t++) {
        // A szakasz csúcsa: a legnagyobb érték első előfordulása
        int p = szakaszok[t].first;
        for (int q = szakaszok[t].first; q <= szakaszok[t].second; q++)
            if (a[q] > a[p]) p = q;
        if (t > 0) cout << ' ';
        cout << p + 1 << ' ' << a[p];
    }
    cout << '\n';
    return 0;
}
