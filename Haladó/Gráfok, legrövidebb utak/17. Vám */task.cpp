/*
Megoldás lényege:
A városokat csúcsoknak, az utakat éleknek tekintjük, a vámot pedig a csúcsok súlyának. A vámot csak az útközben érintett városokban kell fizetni, az A kezdő- és a B célvárosban nem, ezért az útvonal költsége a közbenső csúcsok vámjainak összege. Súlyozott csúcsokkal Dijkstra-algoritmust futtatunk az A csúcsból: egy csúcsba érve a csúcs vámját adjuk a távolsághoz, így a B csúcs távolsága a B vámját is tartalmazza, amit a végén kivonunk. Az útvonalat az elődtömbből visszafelé követve állítjuk össze. Mivel a vámok nemnegatívak, a Dijkstra helyes, és az időigény O((N + M) log N).
*/
/*
Hint 1: || Gondold át, mely városokban kell vámot fizetni: a kezdő és a cél városban nem, csak a köztes városokban. Így a költség csúcsokra írt súlyok összege egy úton, ami nemnegatív súlyú legrövidebb út feladat. ||
Hint 2: || Dijkstra-algoritmusban egy csúcsba érkezéskor add hozzá a csúcs vámját a távolsághoz, és jegyezd meg az elődjét. A cél csúcs távolságából a cél vámját vond ki, az útvonalat pedig az elődökön keresztül kapod meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, b;
    cin >> n >> m >> a >> b;

    vector<long long> tax(n + 1);
    for (int i = 1; i <= n; i++) cin >> tax[i];

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    const long long INF = LLONG_MAX / 4;
    vector<long long> dist(n + 1, INF);
    vector<int> parent(n + 1, 0);

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[a] = 0;
    pq.push({0, a});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        if (u == b) break;
        for (int v : adj[u]) {
            long long nd = d + tax[v];
            if (nd < dist[v]) {
                dist[v] = nd;
                parent[v] = u;
                pq.push({nd, v});
            }
        }
    }

    if (dist[b] == INF) {
        cout << -1 << '\n';
        return 0;
    }

    // A B csúcs vámját a távolság tartalmazza, de a célvárosban nem kell fizetni.
    cout << dist[b] - tax[b] << '\n';

    vector<int> path;
    for (int v = b;; v = parent[v]) {
        path.push_back(v);
        if (v == a) break;
    }
    reverse(path.begin(), path.end());
    for (size_t i = 0; i < path.size(); i++) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}
