#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
Ha két ember között új közvetlen kapcsolatot hozunk létre, akkor a kialakuló kör
hossza a köztük lévő fa-beli távolság + 1. Tehát a leghosszabb körhöz a fa két
legtávolabbi pontját kell megkeresni.

Ez pontosan a fa átmérője. Egy tetszőleges csúcsból BFS-sel megtaláljuk a
legtávolabbi pontot, onnan indulva pedig a másik végpontot és a távolságot.

Hint 1: || A leghosszabb körhöz a fa két legtávolabbi csúcsát kell összekötni. ||
Hint 2: || Egy fa átmérőjét két BFS-sel vagy DFS-sel is meg lehet találni. ||
Hint 3: || Az eredmény hossza a távolság + 1, mert az új él is része a körnek. ||
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<vector<int>> g(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    auto bfs = [&](int start) {
        vector<int> dist(N + 1, -1), parent(N + 1, 0);
        queue<int> q;
        q.push(start);
        dist[start] = 0;
        int far = start;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (dist[u] > dist[far] || (dist[u] == dist[far] && u < far)) far = u;
            for (int v : g[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
        return tuple<int, vector<int>, vector<int>>(far, dist, parent);
    };

    auto [a, d1, p1] = bfs(1);
    auto [b, d2, p2] = bfs(a);

    cout << d2[b] + 1 << '\n' << a << ' ' << b << '\n';
    return 0;
}