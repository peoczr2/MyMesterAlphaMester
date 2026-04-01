/*
Megoldás lényege:
A fizetős utak száma a keresett út költsége, az ingyenes utak költsége pedig 0.
Ezért a feladat egy 0-1 súlyozású legrövidebb út keresés. A szokásos 0-1 BFS-sel
számoljuk a minimális fizetős útszakaszok számát, majd a szülőmutatókból vissza-
építjük a konkrét útvonalat.
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int cost;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<Edge>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        int w = (c == 'F' ? 1 : 0);
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }

    int s, t;
    cin >> s >> t;

    const int INF = 1e9;
    vector<int> dist(n + 1, INF), parent(n + 1, -1);
    deque<int> dq;
    dist[s] = 0;
    dq.push_front(s);

    while (!dq.empty()) {
        int v = dq.front();
        dq.pop_front();
        for (const auto& e : g[v]) {
            int nd = dist[v] + e.cost;
            if (nd < dist[e.to]) {
                dist[e.to] = nd;
                parent[e.to] = v;
                if (e.cost == 0) dq.push_front(e.to);
                else dq.push_back(e.to);
            }
        }
    }

    vector<int> path;
    for (int v = t; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());

    cout << dist[t] << '\n';
    for (int i = 0; i < (int)path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}