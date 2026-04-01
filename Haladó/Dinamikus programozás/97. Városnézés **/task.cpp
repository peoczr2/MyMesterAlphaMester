/*
Megoldási ötlet:
Itt is i<j irányúak a járatok, tehát a gráf DAG. A lehető legtöbb meglátogatott város azzal ekvivalens, hogy a lehető legtöbb élből álló
utat keressük az 1-es városból indulva.

Legyen dp[v] a v városba vezető leghosszabb út élszáma. Az állomásokat növekvő sorrendben feldolgozva minden éllel egyszer relaxálunk.
A szülőélek visszamutatóiból a végén visszaállítható egy maximális útvonal.
*/
/*
Hint 1: || A gráf itt is topologikusan rendezett, ezért elég egyszer balról jobbra végigmenni rajta. ||
Hint 2: || A legtöbb meglátogatott város az induló város miatt a legtöbb járatot jelenti. ||
Hint 3: || Ugyanúgy tárolj szülőélt, mint a legrövidebb útnál, csak most maximumot számolsz. ||
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

    const int NEG = -1e9;
    vector<int> dp(n + 1, NEG), parentNode(n + 1, -1), parentEdge(n + 1, -1);
    dp[1] = 0;
    for (int u = 1; u <= n; ++u) {
        if (dp[u] == NEG) continue;
        for (const Edge& e : g[u]) {
            if (dp[u] + 1 > dp[e.to]) {
                dp[e.to] = dp[u] + 1;
                parentNode[e.to] = u;
                parentEdge[e.to] = e.id;
            }
        }
    }

    int bestNode = 1;
    for (int v = 2; v <= n; ++v) {
        if (dp[v] > dp[bestNode]) bestNode = v;
    }

    vector<int> path;
    for (int cur = bestNode; cur != 1; cur = parentNode[cur]) path.push_back(parentEdge[cur]);
    reverse(path.begin(), path.end());

    cout << path.size() << '\n';
    for (int i = 0; i < (int)path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}