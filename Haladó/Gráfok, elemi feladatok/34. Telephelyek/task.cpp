/*
Megoldás lényege:
Egy vállalat három telephelye pontosan akkor köthető össze, ha van olyan középpont, ahonnan a három telephelyre vezető legrövidebb utak összköltsége minimális; ezek az utak adják az optimális fát.
Ezért minden csúcspárra Floyd–Warshall-lal kiszámoljuk a legrövidebb távolságot, és közben tároljuk az első lépést is, hogy az utak éleit vissza tudjuk állítani.
Egy vállalatra minden lehetséges középpontra kiszámoljuk a három távolság összegét, és a minimumot választjuk. A telephelyekről a középpont felé lépkedve kiírjuk az utak éleit; ezek száma adja az utak U számát.
Az előfeldolgozás O(N³), minden vállalatra O(N) keresés és az utak hossza, így az összes vállalat O(K·N) időben lefut.
*/
/*
Hint 1: || Három csúcs összekötéséhez van olyan optimális megoldás, amelyben egyetlen közös csúcs (középpont) van, és a három telephelyből oda vezető utak adják a fát. ||
Hint 2: || Minden csúcspár legrövidebb távolságát számold ki Floyd–Warshall-lal (N ≤ 100). Egy vállalatra próbáld végig az összes lehetséges középpontot, és nézd a három távolság összegét. ||
Hint 3: || A legrövidebb utak rekonstruálásához minden párra tárold az első lépés utáni csúcsot. Így a telephelyről a középpont felé lépkedve megkapod az utak éleit, és ezek száma adja U-t. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    const int INF = 100000000;
    vector<vector<int>> d(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> nx(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        d[i][i] = 0;
        nx[i][i] = i;
    }
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (c < d[a][b]) {
            d[a][b] = d[b][a] = c;
            nx[a][b] = b;
            nx[b][a] = a;
        }
    }

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    nx[i][j] = nx[i][k];
                }

    int K;
    cin >> K;
    while (K--) {
        int x, y, z;
        cin >> x >> y >> z;

        int best = INT_MAX, center = x;
        for (int c = 1; c <= n; c++) {
            int s = d[x][c] + d[y][c] + d[z][c];
            if (s < best) {
                best = s;
                center = c;
            }
        }

        vector<pair<int, int>> edges;
        for (int t : {x, y, z}) {
            int u = t;
            while (u != center) {
                int v = nx[u][center];
                edges.push_back({u, v});
                u = v;
            }
        }

        cout << best << '\n' << edges.size() << '\n';
        for (auto [u, v] : edges) cout << u << ' ' << v << '\n';
    }
    return 0;
}
