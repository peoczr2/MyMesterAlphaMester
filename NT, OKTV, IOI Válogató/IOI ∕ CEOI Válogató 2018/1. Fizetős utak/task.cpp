/*
Megoldás lényege:
A fizetős utak száma a keresett út költsége, az ingyenes utak költsége pedig 0.
Ezért a feladat egy 0-1 súlyozású legrövidebb út keresés. A szokásos 0-1 BFS-sel
számoljuk a minimális fizetős útszakaszok számát, majd a szülőmutatókból vissza-
építjük a konkrét útvonalat.
*/
/*
Hint 1: || Rendeljünk súlyt az utaknak: a fizetős szakasz 1, az ingyenes 0. Így a keresett szám egy V-ből W-be vezető legrövidebb út hossza ebben a súlyozásban. ||
Hint 2: || A súlyok csak 0 és 1 lehetnek, ezért nem kell a teljes Dijkstra: egy deque-val a 0 súlyú élet az elejére, az 1 súlyút a végére tehetjük (0-1 BFS). ||
Hint 3: || Minden csúcsnál jegyezd fel az előző csúcsot, majd W-ből visszafelé haladva építsd fel az útvonalat, és fordítsd meg. ||
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