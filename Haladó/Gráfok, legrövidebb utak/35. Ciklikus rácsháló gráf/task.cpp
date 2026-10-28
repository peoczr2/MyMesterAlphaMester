/*
Megoldás lényege:
A rács legfeljebb 200 csúcsú, ezért egy új él felvétele után az összes csúcsból futtatott BFS még bőven belefér az időkorlátba. Az új élt a szomszédsági listákba felvesszük, majd minden csúcsból BFS-t indítunk: a BFS során kapott legnagyobb távolság az adott csúcs excentricitása, az ezek közül vett maximum pedig a gráf átmérője, vagyis az a lépésszám, amely alatt bármely pontból bármely másik pontba eljutunk. A rács mindig összefüggő, így minden BFS minden csúcsot elér. Az időigény K·V·(V+E) ahol V = N·M <= 200 és E = O(V+K), ez a 0,5 mp-es időlimitbe bőven belefér.
*/
/*
Hint 1: || Mivel N·M legfeljebb 200, nem kell bonyolult gráfalgoritmus: minden új él után kiszámolhatod az összes pontpár távolságát. ||
Hint 2: || Egy pontpár távolsága BFS-sel adódik. Ha az összes csúcsból lefuttatod a BFS-t, a talált legnagyobb távolság a gráf átmérője, és ez a kiírandó érték. ||
Hint 3: || A sorfolytonos számozásból a pont sora (x-1) / M, oszlopa (x-1) % M; a szomszédok sora és oszlopa ±1 modulo N, illetve modulo M. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    int v = n * m;

    // A ciklikus rácsháló szomszédai: fel, le, jobbra, balra (a széleken körbeér)
    vector<vector<int>> adj(v);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            int x = r * m + c;
            adj[x].push_back(((r + 1) % n) * m + c);
            adj[x].push_back(((r + n - 1) % n) * m + c);
            adj[x].push_back(r * m + (c + 1) % m);
            adj[x].push_back(r * m + (c + m - 1) % m);
        }
    }

    vector<int> dist(v);
    queue<int> q;
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        adj[x].push_back(y);
        adj[y].push_back(x);

        // Átmérő: minden csúcsból BFS, a legnagyobb távolság kell
        int diameter = 0;
        for (int s = 0; s < v; s++) {
            fill(dist.begin(), dist.end(), -1);
            dist[s] = 0;
            q.push(s);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                diameter = max(diameter, dist[u]);
                for (int w : adj[u]) {
                    if (dist[w] < 0) {
                        dist[w] = dist[u] + 1;
                        q.push(w);
                    }
                }
            }
        }
        cout << diameter << '\n';
    }
    return 0;
}
