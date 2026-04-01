/*
Megoldási ötlet:
Minden járat i<j irányú, tehát a gráf aciklikus. A legkevesebb átszállás ugyanaz, mint a lehető legkevesebb járatból álló út az 1-es
állomástól az N-esig.

Legyen dp[v] a v állomásra vezető legrövidebb úthoz szükséges járatok száma. Az állomásokat növekvő sorrendben feldolgozva minden éllel
egyszer frissítünk. A szülőjárat és szülőállomás eltárolásával a végén visszaállítható az egyik optimális járatsorozat.
*/
/*
Hint 1: || Az i<j feltétel miatt a gráf eleve topologikusan rendezett. ||
Hint 2: || A cél most nem súlyösszeg, hanem az élek darabszáma. ||
Hint 3: || Minden állomásnál tárold el, melyik éllel jutottál oda optimálisan. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> g(n + 1);
    for (int id = 1; id <= m; ++id) {
        int u, v;
        cin >> u >> v;
        g[u].push_back({v, id});
    }

    const int INF = 1e9;
    vector<int> dp(n + 1, INF), parentNode(n + 1, -1), parentEdge(n + 1, -1);
    dp[1] = 0;
    for (int u = 1; u <= n; ++u) {
        if (dp[u] == INF) continue;
        for (const Edge& e : g[u]) {
            if (dp[u] + 1 < dp[e.to]) {
                dp[e.to] = dp[u] + 1;
                parentNode[e.to] = u;
                parentEdge[e.to] = e.id;
            }
        }
    }

    if (dp[n] == INF) {
        cout << 0 << '\n';
        return 0;
    }

    vector<int> path;
    for (int cur = n; cur != 1; cur = parentNode[cur]) path.push_back(parentEdge[cur]);
    reverse(path.begin(), path.end());

    cout << path.size() << '\n';
    for (int i = 0; i < (int)path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}