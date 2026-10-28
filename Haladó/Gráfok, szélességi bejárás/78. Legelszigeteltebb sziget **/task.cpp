/*
Megoldás lényege:
Egy sziget elszigeteltségét a hozzá legközelebbi másik sziget távolsága adja, a legelszigeteltebb pedig az, amelynél ez a távolság a legnagyobb.
Az akadálymentes rácson a Manhattan-távolság megegyezik a szomszédos cellákra lépő szélességi bejárás (BFS) lépésszámával.
Minden i sziget celláit egyszerre forrásnak véve BFS-sel megkapjuk minden cella távolságát az i. szigettől, és ebből a legkisebb távolságot a többi szigetig egy K*K táblázatba írjuk.
Ezután minden szigetre a legközelebbi másik sziget távolsága a táblázata sorának minimuma (önmagát kihagyva), végül a legnagyobb ilyen értékű sziget a válasz; döntetlen esetén a kisebb sorszámú.
Az időigény O(K*N*M), ami 100 sziget és 100x100 rács mellett körülbelül 10^6 lépés.
*/
/*
Hint 1: || Egy sziget elszigeteltsége a hozzá legközelebbi másik sziget távolsága. Minden szigetre ki kell számolnod ezt a minimumot, majd a legnagyobb ilyen értékű szigetet keresed. ||
Hint 2: || Akadálymentes rácson a Manhattan-távolság a szomszédos cellákra lépő BFS-lépésszámmal egyezik meg. Egy sziget összes celláját tekintsd egyszerre kezdőpontnak, így a BFS minden cellához megadja a legközelebbi cella távolságát. ||
Hint 3: || Minden i szigetre futtass egy BFS-t, majd a rácson végigmenve minden j != i szigetre tartsd nyilván a legkisebb talált távolságot egy K*K táblázatban. Ezután soronként vedd a minimumot, és a legnagyobb minimumú sziget sorszáma lesz a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> g(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> g[i][j];

    const int INF = INT_MAX;
    // d[i][j]: az i. és a j. sziget legkisebb távolsága
    vector<vector<int>> d(k + 1, vector<int>(k + 1, INF));

    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};

    for (int s = 1; s <= k; ++s) {
        // több forrásból induló BFS: minden cellához az s. sziget legközelebbi celláig mért távolság
        vector<vector<int>> dist(n, vector<int>(m, -1));
        queue<pair<int, int>> q;
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < m; ++c)
                if (g[r][c] == s) {
                    dist[r][c] = 0;
                    q.push({r, c});
                }

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (int t = 0; t < 4; ++t) {
                int nr = r + dr[t], nc = c + dc[t];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        for (int r = 0; r < n; ++r)
            for (int c = 0; c < m; ++c) {
                int t = g[r][c];
                if (t >= 1 && t <= k && t != s && dist[r][c] >= 0)
                    d[s][t] = min(d[s][t], dist[r][c]);
            }
    }

    int ans = 1, bestVal = -1;
    for (int i = 1; i <= k; ++i) {
        int nearest = INF;
        for (int j = 1; j <= k; ++j)
            if (j != i) nearest = min(nearest, d[i][j]);
        if (nearest != INF && nearest > bestVal) {
            bestVal = nearest;
            ans = i;
        }
    }

    cout << ans << '\n';
    return 0;
}
