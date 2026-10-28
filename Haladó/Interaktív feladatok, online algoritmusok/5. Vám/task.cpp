/*
Megoldás lényege:
Az út vámja a rajta lévő települések vámjainak összege, ezért az élek költsége az érkező település vámja, a kiinduló település vámját pedig a lekérdezéskor egyszer hozzáadjuk. Kezdetben a Floyd–Warshall algoritmussal kiszámoljuk minden párra a legolcsóbb utat (N ≤ 250, ez O(N^3) időben belefér). Új út (x, y) építésekor nem kell mindent újraszámolni: egy (i, j) pár útja csak akkor olcsóbb az új úttal, ha az i-ből x-be, onnan y-ba, majd j-be vezet (vagy fordítva), ezért minden párt a régi távolságokból O(N^2) időben frissítünk. Az összidő O(N^3 + T·N^2), ahol T az új utak száma (T ≤ 1000).
*/
/*
Hint 1: || Az út vámja a rajta lévő települések vámjainak összege, ezért nem az éleket, hanem a csúcsokat kell súlyozottnak tekinteni, és minden párra a legolcsóbb utat kell keresni. ||
Hint 2: || Tárold úgy a távolságot, hogy egy élhez a célba érkező település vámja tartozik, a kiinduló település vámját pedig csak a lekérdezésnél add hozzá. Így az útvonal minden települése pontosan egyszer szerepel. ||
Hint 3: || Új út építésekor ne futtasd újra a teljes algoritmust: egy (i, j) párt az új út akkor rövidít, ha az i–x és y–j (vagy az i–y és x–j) régi távolságok összegéből kisebb értéket kapunk. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int INF = 100000000;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> vam(n + 1);
    for (int i = 1; i <= n; ++i) cin >> vam[i];

    // d[i][j]: az i-ből j-be vezető legolcsóbb út vámja úgy, hogy i vámját nem számoljuk, j-ét igen.
    vector<vector<int>> d(n + 1, vector<int>(n + 1, INF));
    for (int i = 1; i <= n; ++i) d[i][i] = 0;
    for (int k = 0; k < m; ++k) {
        int x, y;
        cin >> x >> y;
        d[x][y] = min(d[x][y], vam[y]);
        d[y][x] = min(d[y][x], vam[x]);
    }

    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    while (true) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 0) break;

        if (t == 1) {
            if (d[x][y] >= INF) cout << -1 << '\n';
            else cout << vam[x] + d[x][y] << '\n';
        } else {
            // Új út x és y között: a régi távolságokat másoljuk, hogy a frissítés ne zavarja magát.
            vector<int> rowX = d[x], rowY = d[y];
            vector<int> colX(n + 1), colY(n + 1);
            for (int i = 1; i <= n; ++i) {
                colX[i] = d[i][x];
                colY[i] = d[i][y];
            }
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j) {
                    int viaXY = colX[i] + vam[y] + rowY[j];
                    int viaYX = colY[i] + vam[x] + rowX[j];
                    d[i][j] = min(d[i][j], min(viaXY, viaYX));
                }
        }
    }
    return 0;
}
