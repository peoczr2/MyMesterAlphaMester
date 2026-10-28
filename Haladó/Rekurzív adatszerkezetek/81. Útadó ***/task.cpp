/*
Megoldás lényege:
Ha egy út alatti részfában s város van, akkor az úton 2·s·(N−s) utazás halad át (mindkét irányban), így az út együtthatója 2·s·(N−s).
A bevétel az adók és az együtthatók szorzatösszege, és ez akkor maximális, ha a nagyobb adó a nagyobb együtthatójú útra kerül (átrendezési egyenlőtlenség).
Ezért az utakat és az adókat is növekvő sorrendbe rendezzük, majd párosával hozzárendeljük őket; a részfa-méreteket BFS-szel számoljuk a fővárosból.
Az időigény O(N log N) a rendezések miatt; a végösszeget 32609 szerinti maradékkal írjuk ki.
*/
/*
Hint 1: || Számold meg, hány utazás halad át egy adott úton: ha az út egyik oldalán s város van, akkor a két oldal között s·(N−s) pár utazik, mindkét irányban. ||
Hint 2: || Ha minden útnak ki van számolva az együtthatója, a feladat úgy írható le, hogy az adókat és az együtthatókat kell párosítani. Melyik párosítás adja a legnagyobb összeget? ||
Hint 3: || Rendezd mindkét listát, és a kisebbet a kisebbel párosítsd. Az élek végpontjait tartsd meg a kiíráshoz, a szorzatösszeget pedig előbb-utóbb moduláris maradékkal számold. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const long long MOD = 32609;

    int n;
    cin >> n;
    vector<int> ea(n - 1), eb(n - 1);
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> ea[i] >> eb[i];
        adj[ea[i]].push_back(eb[i]);
        adj[eb[i]].push_back(ea[i]);
    }
    vector<long long> w(n - 1);
    for (auto& x : w) cin >> x;

    // BFS a fővárosból: szülő és részfa-méret
    vector<int> par(n + 1, -1), order{1};
    par[1] = 0;
    for (size_t h = 0; h < order.size(); ++h)
        for (int u : adj[order[h]])
            if (par[u] == -1) {
                par[u] = order[h];
                order.push_back(u);
            }
    vector<long long> sz(n + 1, 1);
    for (int i = (int)order.size() - 1; i > 0; --i)
        sz[par[order[i]]] += sz[order[i]];

    // minden él együtthatója: hány utazás halad át rajta
    struct Edge {
        long long coef;
        int a, b;
    };
    vector<Edge> es;
    for (int i = 0; i < n - 1; ++i) {
        int child = (par[eb[i]] == ea[i]) ? eb[i] : ea[i];
        long long s = sz[child];
        es.push_back({2 * s * (n - s), ea[i], eb[i]});
    }
    sort(es.begin(), es.end(), [](const Edge& x, const Edge& y) {
        if (x.coef != y.coef) return x.coef < y.coef;
        if (x.a != y.a) return x.a < y.a;
        return x.b < y.b;
    });
    sort(w.begin(), w.end());

    long long total = 0;
    for (int i = 0; i < n - 1; ++i)
        total = (total + (es[i].coef % MOD) * (w[i] % MOD)) % MOD;

    cout << total << "\n";
    for (int i = 0; i < n - 1; ++i)
        cout << es[i].a << ' ' << es[i].b << ' ' << w[i] << '\n';
    return 0;
}
