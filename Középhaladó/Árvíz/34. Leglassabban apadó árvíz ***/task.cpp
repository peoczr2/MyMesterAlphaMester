/*
Megoldás lényege:
Árvízmentes folyószakasz a legfeljebb 800 cm-es mérések maximális sorozata, harmadfokú folyószakasz pedig az 1000 cm-nél magasabb mérések maximális sorozata. Mindkét lista egy balról jobbra haladó bejárással, sorrendben kapható meg.
Egy harmadfokú szakasz után azt az árvízmentes szakaszt keressük, amely még a következő harmadfokú szakasz kezdete előtt található. Ilyen pár akkor van, ha az első utána következő árvízmentes szakasz kezdete kisebb a következő harmadfokú szakasz kezdeténél. A két sorozatlistán egy-egy mutatóval haladva ez O(N) időben kiszámolható.
A legtávolabbi párt a harmadfokú szakasz vége és az árvízmentes szakasz kezdete közötti különbség alapján választjuk ki. Csak a szigorúan nagyobb különbség írja felül az eddigit, így egyenlőség esetén az első pár marad.
Az algoritmus O(N) időben fut, ami az N <= 10000 és a 0,1 mp-es időlimit mellett bőven elég.
*/
/*
Hint 1: || Két sorozatlistát kell előállítani: az árvízmentes (legfeljebb 800 cm) és a harmadfokú (1000 cm-nél magasabb) mérések maximális sorozatait. Mindkettő egy bejárással megkapható. ||
Hint 2: || Egy harmadfokú sorozat után az első árvízmentes sorozatot keresd. Ez akkor számít a P-be, ha még a következő harmadfokú sorozat kezdete előtt kezdődik. Mindkét lista sorrendben van, így két mutatóval végigmehetsz rajtuk. ||
Hint 3: || A legtávolabbi pár a harmadfokú sorozat vége és a hozzá tartozó árvízmentes sorozat kezdete közötti különbséggel dől el. Ezt a maximumkeresésnél a szigorúan nagyobb felülírással válaszd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

void kiirSzakaszok(const vector<pair<int, int>>& v) {
    for (size_t k = 0; k < v.size(); k++) {
        if (k) cout << ' ';
        cout << v[k].first << ' ' << v[k].second;
    }
    cout << '\n';
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // Maximális egymás melletti sorozatok, amelyekben a feltétel teljesül (1-től indexelve).
    auto sorozatok = [&](auto feltetel) {
        vector<pair<int, int>> v;
        int i = 1;
        while (i <= n) {
            if (!feltetel(a[i])) {
                i++;
                continue;
            }
            int j = i;
            while (j + 1 <= n && feltetel(a[j + 1])) j++;
            v.push_back({i, j});
            i = j + 1;
        }
        return v;
    };

    vector<pair<int, int>> arvizmentes = sorozatok([](int h) { return h <= 800; });
    vector<pair<int, int>> harmadfoku = sorozatok([](int h) { return h > 1000; });

    cout << arvizmentes.size() << '\n';
    if (!arvizmentes.empty()) kiirSzakaszok(arvizmentes);

    cout << harmadfoku.size() << '\n';
    if (!harmadfoku.empty()) kiirSzakaszok(harmadfoku);

    // P-párok: (harmadfokú szakasz indexe, az utána következő árvízmentes szakasz indexe),
    // ha nincs harmadfokú szakasz közéjük.
    vector<pair<int, int>> parok;
    size_t p = 0;
    for (size_t j = 0; j < harmadfoku.size(); j++) {
        while (p < arvizmentes.size() && arvizmentes[p].first < harmadfoku[j].second) p++;
        if (p == arvizmentes.size()) break;
        int kovetkezo = (j + 1 < harmadfoku.size()) ? harmadfoku[j + 1].first : n + 1;
        if (arvizmentes[p].first < kovetkezo) parok.push_back({(int)j, (int)p});
    }

    cout << parok.size() << '\n';
    if (parok.empty()) return 0;

    // Sor: a harmadfokú szakasz vége és az árvízmentes szakasz kezdete.
    for (size_t k = 0; k < parok.size(); k++) {
        if (k) cout << ' ';
        cout << harmadfoku[parok[k].first].second << ' ' << arvizmentes[parok[k].second].first;
    }
    cout << '\n';

    // A legtávolabbi pár (első a legkisebb sorszámú közül).
    int legtavolabb = -1, legJ = 0, legP = 0;
    for (auto [j, r] : parok) {
        int tav = arvizmentes[r].first - harmadfoku[j].second;
        if (tav > legtavolabb) {
            legtavolabb = tav;
            legJ = j;
            legP = r;
        }
    }
    cout << harmadfoku[legJ].first << ' ' << harmadfoku[legJ].second << ' '
         << arvizmentes[legP].first << ' ' << arvizmentes[legP].second << '\n';
    return 0;
}
