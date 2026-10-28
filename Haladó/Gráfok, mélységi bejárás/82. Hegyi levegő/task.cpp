/*
Megoldás lényege:
A kérdés: mekkora a legmagasabb hegy minimális magassága egy A-ból C-be vezető úton. Ez egy "minimax" út, és egy küszöb-szemlélettel könnyen kezelhető: egy T magassághoz tartozó összefüggő részgráf a T-nél nem magasabb hegyekből áll. A legkisebb T, amelynél két hegy összefügg, adja a választ. A hegyeket növekvő magasság szerint aktiváljuk, és az újonnan aktív hegyet az aktív szomszédaival egy DSU-ban egyesítjük. Minden tényleges egyesítés egy új csúcsot hoz létre (Kruskal-rekonstrukciós fa), amelynek értéke az aktuális hegy magassága. Két hegy válasza ekkor a közös ősük értéke, amelyet bináris felfelé ugrással (LCA) kérdezünk le. A fa O(N*M) csúcsú, a lekérdezés O(log(N*M)).
*/
/*
Hint 1: || Ne keress utat minden kérdéshez külön: a hegyeket magasság szerint növekvő sorrendben add hozzá, és nézd meg, mikor lesz két adott pont összefüggő. ||
Hint 2: || Minden összevonásnál egy új csúcsot vegyél fel, amelynek értéke az aktuális hegy magassága. A két pont legalacsonyabb közös őse ebben a fában adja a választ, így bináris ugrótábla kell az LCA-hoz. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int LOG = 20;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;
    int cells = n * m;

    vector<int> h(cells);
    for (int i = 0; i < cells; ++i) cin >> h[i];

    // Kruskal-rekonstrukciós fa: a levelek a hegyek, a belső csúcsok az összevonások
    int maxNodes = 2 * cells;
    vector<int> par(maxNodes), val(maxNodes), depth(maxNodes, 0);
    for (int i = 0; i < maxNodes; ++i) par[i] = i;
    for (int i = 0; i < cells; ++i) val[i] = h[i];
    int total = cells;

    vector<int> dsu(cells), kn(cells);
    iota(dsu.begin(), dsu.end(), 0);
    iota(kn.begin(), kn.end(), 0);   // kn[gyök]: az adott komponens fa-csúcsa
    auto find = [&](int x) {
        while (dsu[x] != x) {
            dsu[x] = dsu[dsu[x]];
            x = dsu[x];
        }
        return x;
    };

    vector<int> order(cells);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return h[a] < h[b]; });

    vector<char> active(cells, 0);
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    for (int c : order) {
        active[c] = 1;
        int row = c / m, col = c % m;
        for (int d = 0; d < 4; ++d) {
            int nr = row + dr[d], nc = col + dc[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            int nb = nr * m + nc;
            if (!active[nb]) continue;
            int a = find(c), b = find(nb);
            if (a == b) continue;
            int node = total++;
            val[node] = h[c];
            par[kn[a]] = node;
            par[kn[b]] = node;
            par[node] = node;
            dsu[b] = a;
            kn[a] = node;
        }
    }

    // A fa szülője mindig nagyobb sorszámú, ezért a mélység visszafelé számolható
    for (int x = total - 1; x >= 0; --x)
        depth[x] = (par[x] == x) ? 0 : depth[par[x]] + 1;

    vector<vector<int>> up(LOG, vector<int>(total));
    for (int x = 0; x < total; ++x) up[0][x] = par[x];
    for (int k = 1; k < LOG; ++k)
        for (int x = 0; x < total; ++x) up[k][x] = up[k - 1][up[k - 1][x]];

    auto lca = [&](int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int k = 0; k < LOG; ++k)
            if ((diff >> k) & 1) u = up[k][u];
        if (u == v) return u;
        for (int k = LOG - 1; k >= 0; --k)
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        return up[0][u];
    };

    for (int i = 0; i < q; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int u = (a - 1) * m + (b - 1);
        int v = (c - 1) * m + (d - 1);
        cout << val[lca(u, v)] << '\n';
    }
    return 0;
}
