/*
Megoldás lényege: a meghívásokat a határnapjuk (u) szerint növekvő sorrendben dolgozzuk fel, és mindegyiket
a saját [e, u] intervallumának legkorábbi még szabad napjára tesszük. A határidő szerinti sorrend miatt
a korábban lejáró igények kapják meg előbb a napot, a legkorábbi szabad nap választása pedig a későbbi
igényeknek hagyja a legtöbb lehetőséget, így a maximális számú fellépés elérhető (csereargumentummal
igazolható). A "következő szabad nap" keresést egy DSU gyorsítja. Időigény: O(N log N), mert a napok
kezelése gyakorlatilag konstans, a rendezés dominál.
*/
/*
Hint 1: || Ha egy meghívás korán lejár, azt előbb kell elhelyezni. ||
Hint 2: || A legkorábbi szabad nap kiválasztása a többi meghívásnak még több lehetőséget hagy. ||
Hint 3: || A szabad napok kezelésére elég egy DSU vagy egy hasonló "következő szabad nap" struktúra. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n + 2);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void use(int x) { p[x] = find(x + 1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i].first >> a[i].second;

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 1);
    sort(ord.begin(), ord.end(), [&](int x, int y) {
        if (a[x].second != a[y].second) return a[x].second < a[y].second;
        if (a[x].first != a[y].first) return a[x].first < a[y].first;
        return x < y;
    });

    DSU dsu(365);
    vector<pair<int, int>> chosen;
    for (int id : ord) {
        int day = dsu.find(a[id].first);
        if (day <= a[id].second) {
            chosen.push_back({id, day});
            dsu.use(day);
        }
    }

    cout << chosen.size() << '\n';
    for (auto [id, day] : chosen) {
        cout << id << ' ' << day << '\n';
    }
    return 0;
}