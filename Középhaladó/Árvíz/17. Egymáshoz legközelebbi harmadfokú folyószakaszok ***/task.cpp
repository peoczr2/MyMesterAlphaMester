/*
Megoldás lényege:
A mérésekből előbb készültségi szintet számolunk: 800 cm fölött 1., 900 cm fölött 2., 1000 cm fölött 3. szint, egyébként 0.
Egy balról jobbra haladó bejárással kigyűjtjük az azonos szintű, egymás melletti mérések maximális szakaszait, és a harmadfokúakat megtartjuk.
Két szomszédos harmadfokú szakasz távolsága a második kezdete mínusz az első vége, ezt a K-1 távolságot írjuk ki.
A legkisebb távolságú szomszédos párt egy lineáris végigmenéssel keressük, egyenlőségnél a korábbit tartjuk meg.
Az időigény O(N), N ≤ 10 000 esetén bőven az időlimit alatt marad.
*/
/*
Hint 1: || Először minden mérést alakíts át készültségi szintté, majd az azonos szintű egymás melletti mérések maximális szakaszait keresd. ||
Hint 2: || A harmadfokú szakaszok kezdő és záró indexét egy balról jobbra haladó bejárásban gyűjtsd ki. Két szomszédos szakasz távolsága a második kezdete és az első vége különbsége. ||
Hint 3: || A legkisebb távolságú pár megkereséséhez elég egyetlen változóban tartani az eddigi legjobb indexet. Csak szigorúan kisebb távolságnál frissíts, így egyenlőségnél a korábbi pár marad. ||
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
    vector<int> sz(n);
    for (int &x : sz) {
        int a;
        cin >> a;
        x = szint(a);
    }

    // A harmadfokú folyószakaszok [kezdet, vége] párjai, 0-indexelve
    vector<pair<int, int>> szakaszok;
    int i = 0;
    while (i < n) {
        int j = i;
        while (j + 1 < n && sz[j + 1] == sz[i]) j++;
        if (sz[i] == 3) szakaszok.push_back({i, j});
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

    if (k == 1) {
        cout << "0\n";
        return 0;
    }

    // Az első K-1 szakasz távolsága a következőtől: a következő kezdete mínusz az aktuális vége
    vector<int> tav(k - 1);
    for (int t = 0; t + 1 < k; t++) tav[t] = szakaszok[t + 1].first - szakaszok[t].second;
    for (int t = 0; t + 1 < k; t++) {
        if (t > 0) cout << ' ';
        cout << tav[t];
    }
    cout << '\n';

    // A legkisebb távolságú szomszédos pár (egyenlőségnél a korábbi)
    int legjobb = 0;
    for (int t = 1; t + 1 < k; t++)
        if (tav[t] < tav[legjobb]) legjobb = t;

    cout << szakaszok[legjobb].first + 1 << ' ' << szakaszok[legjobb].second + 1 << ' '
         << szakaszok[legjobb + 1].first + 1 << ' ' << szakaszok[legjobb + 1].second + 1 << '\n';
    return 0;
}
