/*
Megoldás lényege:
A szabad mezők és a köztük lévő szomszédsági kapcsolatok egy fát alkotnak, mert bármely két szabad mező között pontosan egy út van.
Így a leghosszabb útvonal hossza a fa átmérője, azaz a legtávolabbi mezőpár távolsága (élekben mérve).
Az átmérő két BFS-sel megkapható: egy tetszőleges szabad mezőből BFS-sel megkeressük a legtávolabbi mezőt, majd onnan újabb BFS-sel a legtávolabbit; ez a távolság az átmérő.
Az időigény és a memóriaigény is O(N·M), ami a korlátokon belül van.
*/
/*
Hint 1: || A szabad mezők között a szomszédsággal fát kapsz, ezért a keresett út a fa átmérője. ||
Hint 2: || Egy tetszőleges szabad mezőből indítva a BFS-sel keress legtávolabbi mezőt, majd onnan indítva másodszor is BFS-sel keresd a legtávolabbi mezőt: a két távolság maximuma adja a választ. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<string> g(n);
    for (auto &row : g) cin >> row;

    int start = -1;
    for (int i = 0; i < n && start < 0; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '.') {
                start = i * m + j;
                break;
            }
        }
    }
    if (start < 0) {
        cout << 0 << '\n';
        return 0;
    }

    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};

    vector<int> dist(n * m, -1);

    // BFS a szabad mezőkön: visszaadja a legtávolabbi mezőt, a távolságok a dist tömbbe kerülnek
    auto bfs = [&](int src) {
        fill(dist.begin(), dist.end(), -1);
        queue<int> q;
        q.push(src);
        dist[src] = 0;
        int far = src;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            if (dist[v] > dist[far]) far = v;
            int r = v / m, c = v % m;
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                if (g[nr][nc] != '.') continue;
                int u = nr * m + nc;
                if (dist[u] >= 0) continue;
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
        return far;
    };

    int a = bfs(start);
    int b = bfs(a);
    cout << dist[b] << '\n';
    return 0;
}
