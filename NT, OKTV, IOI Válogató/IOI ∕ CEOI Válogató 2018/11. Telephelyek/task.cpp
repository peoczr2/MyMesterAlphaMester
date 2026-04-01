/*
Megoldás lényege:
N legfeljebb 100, ezért minden csúcsból lefuttatjuk a Dijkstra-algoritmust, és
eltároljuk a legrövidebb utak szülőit. Egy vállalat három telephelye esetén az
optimális összekötés egy Steiner-fa, amelyet úgy kapunk meg, hogy minden lehetséges
középpontot kipróbálunk, és az adott középpontból a három telephelyre vezető
legrövidebb utak uniójának költségét számoljuk.

A vállalatok száma nagy lehet, de az N kicsi, ezért a 100 lehetséges középpont és
a három rövid út újraépítése bőven belefér. A kiválasztott éleket egyedi azonosító
szerint gyűjtjük és összköltségüket összeadjuk.
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, w, id;
};

struct DState {
    long long dist;
    int v;
    bool operator<(const DState& other) const { return dist > other.dist; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<Edge>> g(n + 1);
    vector<int> eu(m), ev(m), ew(m);
    vector<vector<int>> edgeId(n + 1, vector<int>(n + 1, -1));
    for (int i = 0; i < m; ++i) {
        int a, b, d;
        cin >> a >> b >> d;
        eu[i] = a; ev[i] = b; ew[i] = d;
        g[a].push_back({b, d, i});
        g[b].push_back({a, d, i});
        edgeId[a][b] = edgeId[b][a] = i;
    }

    int k;
    cin >> k;
    vector<array<int,3>> companies(k);
    for (int i = 0; i < k; ++i) {
        cin >> companies[i][0] >> companies[i][1] >> companies[i][2];
    }

    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, (1LL << 60)));
    vector<vector<int>> parent(n + 1, vector<int>(n + 1, -1));

    for (int src = 1; src <= n; ++src) {
        priority_queue<DState> pq;
        dist[src][src] = 0;
        pq.push({0, src});
        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            if (cur.dist != dist[src][cur.v]) continue;
            for (const auto& e : g[cur.v]) {
                long long nd = cur.dist + e.w;
                if (nd < dist[src][e.to]) {
                    dist[src][e.to] = nd;
                    parent[src][e.to] = cur.v;
                    pq.push({nd, e.to});
                }
            }
        }
    }

    for (const auto& comp : companies) {
        long long bestCost = (1LL << 60);
        vector<int> bestEdges;

        for (int center = 1; center <= n; ++center) {
            vector<char> used(m, 0);
            long long cost = 0;
            bool ok = true;

            for (int t = 0; t < 3; ++t) {
                int target = comp[t];
                if (dist[center][target] >= (1LL << 50)) {
                    ok = false;
                    break;
                }

                int v = target;
                while (v != center) {
                    int p = parent[center][v];
                    if (p == -1) {
                        ok = false;
                        break;
                    }
                    int id = edgeId[v][p];
                    if (id == -1) {
                        ok = false;
                        break;
                    }
                    if (!used[id]) {
                        used[id] = 1;
                        cost += ew[id];
                    }
                    v = p;
                }
                if (!ok) break;
            }

            if (!ok) continue;
            if (cost < bestCost) {
                bestCost = cost;
                bestEdges.clear();
                for (int id = 0; id < m; ++id) if (used[id]) bestEdges.push_back(id);
            }
        }

        cout << bestCost << '\n';
        cout << bestEdges.size() << '\n';
        for (int id : bestEdges) {
            cout << eu[id] << ' ' << ev[id] << '\n';
        }
    }

    return 0;
}