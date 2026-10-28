/*
Megoldás lényege:
A 2. feltétel miatt minden ellenőrző pont szintje egyértelmű: a starttól mért
legrövidebb út hossza (BFS-szel számolható). Ebben a szintezésben az élek csak
egymást követő szintek között mehetnek, és a megtartott s–t utak hossza megegyezik
a terv legrövidebb s–t útjának hosszával, így a pálya rétegzett irányított aciklikus gráf.

Két szomszédos szint között bipartit gráf van. Olyan legkevesebb élt kell választani,
hogy az alsó szint minden csúcsából legyen kiválasztott kimenő él, és a felső szint
minden csúcsába legyen kiválasztott bejövő él. Ez bipartit minimum él-fedés: az
érintett két szint csúcsszámának összege mínusz a maximális párosítás. A maximális
párosítást Hopcroft–Karp algoritmussal számoljuk, majd a még nem fedett csúcsokat
tetszőleges incidens élekkel lefedjük.
*/
/*
Hint 1: || A 2. feltétel miatt minden ellenőrző pont fix szinten van: a starttól mért legrövidebb út hossza adja a szintet. Így a megtartott élek csak egymást követő szintek között futhatnak. ||
Hint 2: || Két szomszédos szint között bipartit gráfot kapunk. A feladat: a lehető legkevesebb élt kiválasztani úgy, hogy az alsó szint minden csúcsából és a felső szint minden csúcsába legyen kiválasztott él. ||
Hint 3: || Ez minimális élfedés: a kiválasztott élek száma a két szint csúcsszámának összege mínusz a maximális párosítás. A párosítást Hopcroft–Karp algoritmussal keressük, a nem párosított csúcsokat pedig tetszőleges incidens éllel fedjük le. ||
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

    vector<int> level(n + 1, -1);
    level[source] = 0;
    queue<int> q;
    q.push(source);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (level[to] == -1) {
                level[to] = level[v] + 1;
                q.push(to);
            }
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