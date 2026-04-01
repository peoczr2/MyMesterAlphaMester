/*
Megoldás lényege:
A feltételek miatt a pálya egy rétegzett irányított aciklikus gráfként fogható fel:
van egy forrás (start) és egy nyelő (cél), és minden csúcs egy jól meghatározott
szinten helyezkedik el a starttól mért út-hossz alapján. A 2. feltétel azt jelenti,
hogy minden szomszédos réteg közti út ugyanannyi ellenőrző pontot tartalmaz, tehát
az élek csak egymást követő szintek között mehetnek.

Minden két szomszédos réteg között egy bipartit gráfunk van. Olyan legkevesebb élt
kell választani, hogy a bal oldali szint minden csúcsa rendelkezzen legalább egy
kimenő éllel, és a jobb oldali szint minden csúcsa legalább egy bejövő éllel.
Ez pontosan bipartit minimum él-fedés: maximum párosítást számolunk, majd a még
nem fedett csúcsokat tetszőleges incident élekkel lefedjük.
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, id;
};

struct HopcroftKarp {
    int nL, nR;
    vector<vector<int>> adj;
    vector<int> dist, matchL, matchR;

    HopcroftKarp(int nL, int nR) : nL(nL), nR(nR), adj(nL), dist(nL), matchL(nL, -1), matchR(nR, -1) {}

    void addEdge(int u, int v) { adj[u].push_back(v); }

    bool bfs() {
        queue<int> q;
        bool found = false;
        for (int u = 0; u < nL; ++u) {
            if (matchL[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = -1;
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                int mu = matchR[v];
                if (mu == -1) {
                    found = true;
                } else if (dist[mu] == -1) {
                    dist[mu] = dist[u] + 1;
                    q.push(mu);
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int mu = matchR[v];
            if (mu == -1 || (dist[mu] == dist[u] + 1 && dfs(mu))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int maxMatching() {
        int res = 0;
        while (bfs()) {
            for (int u = 0; u < nL; ++u) {
                if (matchL[u] == -1 && dfs(u)) ++res;
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> g(n + 1), gr(n + 1);
    vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
        g[u].push_back(v);
        gr[v].push_back(u);
        ++indeg[v];
        ++outdeg[u];
    }

    int source = 0, sink = 0;
    for (int i = 1; i <= n; ++i) {
        if (indeg[i] == 0) source = i;
        if (outdeg[i] == 0) sink = i;
    }

    vector<int> topo;
    topo.reserve(n);
    queue<int> q;
    vector<int> deg = indeg;
    for (int i = 1; i <= n; ++i) if (deg[i] == 0) q.push(i);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        topo.push_back(v);
        for (int to : g[v]) if (--deg[to] == 0) q.push(to);
    }

    vector<int> level(n + 1, -1);
    level[source] = 0;
    for (int v : topo) {
        if (level[v] == -1) continue;
        for (int to : g[v]) {
            level[to] = max(level[to], level[v] + 1);
        }
    }

    int maxLevel = 0;
    for (int i = 1; i <= n; ++i) maxLevel = max(maxLevel, level[i]);

    vector<vector<int>> byLevel(maxLevel + 1);
    for (int i = 1; i <= n; ++i) {
        if (level[i] >= 0) byLevel[level[i]].push_back(i);
    }

    vector<int> posInLevel(n + 1, -1);
    for (int lv = 0; lv <= maxLevel; ++lv) {
        for (int i = 0; i < (int)byLevel[lv].size(); ++i) posInLevel[byLevel[lv][i]] = i;
    }

    vector<int> answerEdges;
    for (int lv = 0; lv < maxLevel; ++lv) {
        auto &L = byLevel[lv];
        auto &R = byLevel[lv + 1];
        if (L.empty() || R.empty()) continue;

        HopcroftKarp hk((int)L.size(), (int)R.size());
        vector<vector<pair<int, int>>> outEdges(L.size()), inEdges(R.size());

        for (int id = 0; id < m; ++id) {
            auto [u, v] = edges[id];
            if (level[u] == lv && level[v] == lv + 1) {
                int lu = posInLevel[u];
                int rv = posInLevel[v];
                hk.addEdge(lu, rv);
                outEdges[lu].push_back({rv, id});
                inEdges[rv].push_back({lu, id});
            }
        }

        hk.maxMatching();

        vector<char> coveredL(L.size(), 0), coveredR(R.size(), 0);
        vector<char> used(m, 0);

        for (int u = 0; u < (int)L.size(); ++u) {
            int v = hk.matchL[u];
            if (v != -1) {
                int id = -1;
                for (auto [rv, eid] : outEdges[u]) {
                    if (rv == v) {
                        id = eid;
                        break;
                    }
                }
                if (id != -1 && !used[id]) {
                    used[id] = 1;
                    answerEdges.push_back(id);
                    coveredL[u] = coveredR[v] = 1;
                }
            }
        }

        for (int u = 0; u < (int)L.size(); ++u) {
            if (coveredL[u]) continue;
            if (outEdges[u].empty()) continue;
            int id = outEdges[u][0].second;
            int v = outEdges[u][0].first;
            if (!used[id]) {
                used[id] = 1;
                answerEdges.push_back(id);
            }
            coveredL[u] = 1;
            coveredR[v] = 1;
        }

        for (int v = 0; v < (int)R.size(); ++v) {
            if (coveredR[v]) continue;
            if (inEdges[v].empty()) continue;
            int id = inEdges[v][0].second;
            int u = inEdges[v][0].first;
            if (!used[id]) {
                used[id] = 1;
                answerEdges.push_back(id);
            }
            coveredL[u] = 1;
            coveredR[v] = 1;
        }
    }

    cout << answerEdges.size() << '\n';
    for (int id : answerEdges) {
        cout << edges[id].first << ' ' << edges[id].second << '\n';
    }

    return 0;
}