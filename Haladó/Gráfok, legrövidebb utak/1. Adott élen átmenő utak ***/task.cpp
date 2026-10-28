/*
Megoldás lényege:
Egy (p,q) pár akkor jó, ha van út p-ből q-ba, de az uv él nélkül már nincs. Ezt minden p kezdőpontból két szélességi bejárással döntjük el: az elsőt a teljes gráfban, a másodikat az uv él kihagyásával futtatjuk. A jó q pontok azok, amelyek az elsőben elérhetők, a másodikban nem; p-t a második bejárás mindig eléri, így önmagával nem számolunk. A gráf legfeljebb 500 pontos és 10000 élű, így az O(N·(N+M)) bejárás körülbelül 10^7 lépés, ami az 1 mp-es időlimitbe bőven belefér.
*/
/*
Hint 1: || Egy p-ből q-ba vezető út pontosan akkor tartalmazza mindig az uv élet, ha a gráf uv nélküli részében q már nem érhető el p-ből, miközben a teljes gráfban igen. ||
Hint 2: || N legfeljebb 500, ezért minden kezdőpontból külön végezhetsz két bejárást: egyet a teljes gráfban, egyet úgy, hogy az (u,v) irányú átmenetet nem követed. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Szélességi bejárás s-ből; skipUV esetén az u->v átmenet nem használható.
void bfs(int s, bool skipUV, const vector<vector<int>>& adj, int u, int v, vector<char>& seen) {
    fill(seen.begin(), seen.end(), 0);
    queue<int> que;
    seen[s] = 1;
    que.push(s);
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (int y : adj[x]) {
            if (skipUV && x == u && y == v) continue;
            if (!seen[y]) {
                seen[y] = 1;
                que.push(y);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, u, v;
    cin >> n >> m >> u >> v;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
    }

    vector<char> full(n + 1), part(n + 1);
    vector<pair<int, int>> ans;
    for (int p = 1; p <= n; p++) {
        bfs(p, false, adj, u, v, full);
        bfs(p, true, adj, u, v, part);
        for (int q = 1; q <= n; q++) {
            if (full[q] && !part[q]) ans.push_back({p, q});
        }
    }

    cout << ans.size() << '\n';
    for (auto [p, q] : ans) cout << p << ' ' << q << '\n';
    return 0;
}
