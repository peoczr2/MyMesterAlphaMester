/*
Megoldás lényege:
Minden útvonalat két szempont szerint hasonlítunk össze: először a teljes hossz,
majd az út menti legkisebb teherbírás. A keresett út a legrövidebbek közül az,
amelynek a minimális teherbírása a lehető legnagyobb.

Ez klasszikus Dijkstra lexikografikus állapottal. Minden csúcsnál eltároljuk a
legjobb (legrövidebb, és azon belül legnagyobb bottleneck) értéket. Relaxáláskor
az új bottleneck az előző és az él teherbírásának minimuma. A prioritási sor a
legrövidebb távolságot, azon belül a nagyobb bottlenecket preferálja.
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int len;
    int cap;
};

struct State {
    long long dist;
    int bottleneck;
    int v;
    bool operator<(const State& other) const {
        if (dist != other.dist) return dist > other.dist;
        if (bottleneck != other.bottleneck) return bottleneck < other.bottleneck;
        return v > other.v;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<Edge>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b, h, t;
        cin >> a >> b >> h >> t;
        g[a].push_back({b, h, t});
        g[b].push_back({a, h, t});
    }

    int s, t;
    cin >> s >> t;

    const long long INF = (1LL << 60);
    vector<long long> dist(n + 1, INF);
    vector<int> bottleneck(n + 1, -1), parent(n + 1, -1);
    priority_queue<State> pq;

    dist[s] = 0;
    bottleneck[s] = INT_MAX;
    pq.push({0, INT_MAX, s});

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        if (cur.dist != dist[cur.v] || cur.bottleneck != bottleneck[cur.v]) continue;
        for (const auto& e : g[cur.v]) {
            long long nd = cur.dist + e.len;
            int nb = min(cur.bottleneck, e.cap);
            if (nd < dist[e.to] || (nd == dist[e.to] && nb > bottleneck[e.to])) {
                dist[e.to] = nd;
                bottleneck[e.to] = nb;
                parent[e.to] = cur.v;
                pq.push({nd, nb, e.to});
            }
        }
    }

    vector<int> path;
    for (int v = t; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());

    cout << dist[t] << ' ' << bottleneck[t] << '\n';
    for (int i = 0; i < (int)path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}