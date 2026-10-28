/*
    A híd egy 2xN-es súlyozott gráf. Minden átmenetnél a következő mező súlyát
    kell kifizetni, ezért a feladat egy legrövidebb út keresése a két oldalon és
    az oszlopok között. Minden járdalap egy csúcs, a csúcsba lépés költsége a
    járdalap veszélyességi mértéke. A két oldal kezdőcsúcsából és a híd utáni
    célcsúcsból indulva Dijkstra-val kapjuk a minimumot, majd a szülőkből
    visszaállítjuk a mozgássort. Időigény: O(N log N).
*/
/*
Hint 1: || Ábrázold a hidat gráfként: minden járdalap egy csúcs, és egy lépés a mezőre lépés (előre) vagy a másik sorba váltás ugyanabban az oszlopban. ||
Hint 2: || Vegyél fel egy kezdőcsúcsot mindkét oldalra (0 költséggel) és egy célcsúcsot az utolsó oszlop után. A legkisebb összköltségű út ezen a gráfon Dijkstra-algoritmussal megkapható. ||
Hint 3: || Minden csúcsnál tárold az előző csúcsot és az odavezető lépés betűjét (B, J vagy E). A kezdőcsúcstól a célig a betűk sorrendje adja a második sort. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int cost;
    char ch;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> bal(n + 1), jobb(n + 1);
    for (int i = 1; i <= n; ++i) cin >> bal[i];
    for (int i = 1; i <= n; ++i) cin >> jobb[i];

    int S = 0, WL = 1, WR = 2;
    auto idL = [&](int i) { return 2 + 2 * (i - 1) + 1; };
    auto idR = [&](int i) { return 2 + 2 * (i - 1) + 2; };
    int T = 2 + 2 * n + 1;
    int tot = T + 1;

    vector<vector<Edge>> g(tot);
    g[S].push_back({WL, 0, 'B'});
    g[S].push_back({WR, 0, 'J'});
    g[WL].push_back({idL(1), bal[1], 'E'});
    g[WR].push_back({idR(1), jobb[1], 'E'});
    for (int i = 1; i < n; ++i) {
        g[idL(i)].push_back({idL(i + 1), bal[i + 1], 'E'});
        g[idR(i)].push_back({idR(i + 1), jobb[i + 1], 'E'});
    }
    for (int i = 1; i <= n; ++i) {
        g[idL(i)].push_back({idR(i), jobb[i], 'J'});
        g[idR(i)].push_back({idL(i), bal[i], 'B'});
    }
    g[idL(n)].push_back({T, 0, 'E'});
    g[idR(n)].push_back({T, 0, 'E'});

    const long long INF = (1LL << 60);
    vector<long long> dist(tot, INF);
    vector<int> parent(tot, -1);
    vector<char> parentCh(tot, '?');
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dist[S] = 0;
    pq.push({0, S});
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d != dist[v]) continue;
        if (v == T) break;
        for (auto e : g[v]) {
            if (dist[e.to] > d + e.cost) {
                dist[e.to] = d + e.cost;
                parent[e.to] = v;
                parentCh[e.to] = e.ch;
                pq.push({dist[e.to], e.to});
            }
        }
    }

    string path;
    for (int v = T; v != S; v = parent[v]) path.push_back(parentCh[v]);
    reverse(path.begin(), path.end());
    cout << dist[T] << '\n' << path << '#'
         << '\n';
    return 0;
}