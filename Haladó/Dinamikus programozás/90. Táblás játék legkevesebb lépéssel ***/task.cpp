/*
Megoldási ötlet:
Balra nem lehet lépni, ezért az út oszloponként halad előre. Egy oszlopon belül fel vagy le mozoghatunk, de mezőt nem látogathatunk
meg kétszer, ezért egy oszlopon belüli mozgás mindig monoton: vagy csak lefelé, vagy csak felfelé haladunk, mielőtt jobbra lépnénk.

Oszloponként két söpréssel számolunk. Az entry[r] érték azt adja, mennyi a legkisebb lépésszám, ha balról érkezünk az aktuális oszlop
r. sorába. Ebből egy lefelé és egy felfelé söpréssel kiszámítható az oszlop minden mezőjének optimális értéke. Az utolsó választott előd
irányát eltároljuk, így a teljes J/L/F útvonal visszafejthető.
*/
/*
Hint 1: || Mivel nincs balra lépés, az út természetesen oszloponként épül fel. ||
Hint 2: || Egy oszlopban nem mehetsz egyszer fel és le is, mert akkor ismételnél mezőt. ||
Hint 3: || Ugyanarra az oszlopra külön számold ki a lefelé söpört és a felfelé söpört legjobb értékeket. ||
*/

#include <bits/stdc++.h>
using namespace std;

static const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<char>> blocked(n + 1, vector<char>(m + 1, 0));
    for (int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        blocked[x][y] = 1;
    }

    if (blocked[1][1] || blocked[n][m]) {
        cout << -1 << '\n';
        return 0;
    }

    vector<vector<int>> dist(n + 1, vector<int>(m + 1, INF));
    vector<vector<char>> parent(n + 1, vector<char>(m + 1, 0));

    vector<int> entry(n + 2), down(n + 2), up(n + 2), prevCol(n + 2, INF);
    if (!blocked[1][1]) prevCol[1] = 0;

    for (int col = 1; col <= m; ++col) {
        fill(entry.begin(), entry.end(), INF);
        fill(down.begin(), down.end(), INF);
        fill(up.begin(), up.end(), INF);
        vector<char> downPar(n + 2, 0), upPar(n + 2, 0);

        for (int row = 1; row <= n; ++row) {
            if (blocked[row][col]) continue;
            if (col == 1) {
                if (row == 1 && prevCol[row] != INF) {
                    entry[row] = 0;
                }
            } else if (dist[row][col - 1] != INF) {
                entry[row] = dist[row][col - 1] + 1;
            }
        }

        for (int row = 1; row <= n; ++row) {
            if (blocked[row][col]) continue;
            down[row] = entry[row];
            if (entry[row] != INF) {
                downPar[row] = (col == 1 && row == 1 ? 'S' : 'J');
            }
            if (row > 1 && !blocked[row - 1][col] && down[row - 1] + 1 < down[row]) {
                down[row] = down[row - 1] + 1;
                downPar[row] = 'L';
            }
        }

        for (int row = n; row >= 1; --row) {
            if (blocked[row][col]) continue;
            up[row] = entry[row];
            if (entry[row] != INF) {
                upPar[row] = (col == 1 && row == 1 ? 'S' : 'J');
            }
            if (row < n && !blocked[row + 1][col] && up[row + 1] + 1 < up[row]) {
                up[row] = up[row + 1] + 1;
                upPar[row] = 'F';
            }
        }

        for (int row = 1; row <= n; ++row) {
            if (blocked[row][col]) continue;
            if (down[row] <= up[row]) {
                dist[row][col] = down[row];
                parent[row][col] = downPar[row];
            } else {
                dist[row][col] = up[row];
                parent[row][col] = upPar[row];
            }
        }
    }

    if (dist[n][m] == INF) {
        cout << -1 << '\n';
        return 0;
    }

    string path;
    int row = n, col = m;
    while (!(row == 1 && col == 1)) {
        char c = parent[row][col];
        path.push_back(c);
        if (c == 'J') {
            --col;
        } else if (c == 'L') {
            --row;
        } else if (c == 'F') {
            ++row;
        }
    }
    reverse(path.begin(), path.end());

    cout << dist[n][m] << '\n';
    cout << path << '\n';
    return 0;
}