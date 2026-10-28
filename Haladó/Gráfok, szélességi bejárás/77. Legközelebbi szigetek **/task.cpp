/*
Megoldás lényege:
Két pont távolsága a koordináták különbségeinek abszolút értékének összege, és a tenger nem akadály, ezért a rácson végzett szélességi bejárás (BFS) pontosan ezt a távolságot adja.
Minden i sziget celláit egyszerre, több forrásból indított BFS-be tesszük, így minden cellához megkapjuk a legközelebbi i-s cella távolságát.
Ebből az i. és a j. sziget távolsága a j-s cellák közül vett minimum. K ≤ 100 sziget és N*M ≤ 10^4 cella mellett K darab BFS összesen
körülbelül K*N*M ≈ 10^6 lépés, ami bőven belül van az időkorláton. A végén a legkisebb távolságú (i, j) párt írjuk ki; ha több ilyen van, az első (i < j) pár kerül ki.
*/
/*
Hint 1: || Két pont távolsága a koordináták különbségeinek abszolút értékének összege, és a tenger nem akadály. Így a rácson a szomszédos cellákra lépő szélességi bejárás pontosan ezt a távolságot adja meg. ||
Hint 2: || Egy szigetet kezelj egyetlen forráshalmazként: az összes celláját tedd egyszerre a sorba, és futtass BFS-t. Így minden cellához megkapod a legközelebbi azonos szigetű cella távolságát. ||
Hint 3: || Minden i sziget BFS-e után járd végig a rácsot, és minden olyan j szigetre, amely különbözik i-től, tartsd nyilván a legkisebb talált távolságot egy K*K méretű táblázatban. A táblázat minimumát adó pár lesz a válasz. ||
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

    int best = INF, ba = 1, bb = 2;
    for (int i = 1; i <= k; ++i)
        for (int j = i + 1; j <= k; ++j)
            if (d[i][j] < best) {
                best = d[i][j];
                ba = i;
                bb = j;
            }

    cout << ba << ' ' << bb << '\n';
    return 0;
}
