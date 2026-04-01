/*
Egy lepessel csak olyan szomszedba lehet menni, amelynek a magassaga pontosan eggyel nagyobb,
ezert az utak iranyitott kormentes grafot adnak. Legyen dp[r][c] a (r,c) mezobol indulva megteheto
leghosszabb ut hossza csucsok szamaban. Ezt DFS-es memoizalassal vagy erteksorrendben fel lehet
szamitani, mert minden atmenet szigoruan nagyobb magasagba megy. A keresett ut a szelerol indul,
ezert a valasz a peremmezok kozul adodik; a kimenetre a lepesek szama kell, vagyis a csucsszam-1.
*/
/*
Hint 1: || A lepesek mindig szigoruan novelo magassagra mennek, tehat nincs kor. ||
Hint 2: || Szamold ki minden mezore, milyen hosszu ut indulhat onnan. ||
Hint 3: || A vegso maximumot csak a peremen levo kezdohelyek kozul kell venni. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> height(n, vector<int>(n));
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            cin >> height[row][col];
        }
    }

    vector<vector<int>> memo(n, vector<int>(n, 0));
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    auto dfs = [&](auto&& self, int row, int col) -> int {
        if (memo[row][col] != 0) {
            return memo[row][col];
        }
        int best = 1;
        for (int dir = 0; dir < 4; ++dir) {
            int nr = row + dr[dir];
            int nc = col + dc[dir];
            if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
                continue;
            }
            if (height[nr][nc] == height[row][col] + 1) {
                best = max(best, 1 + self(self, nr, nc));
            }
        }
        memo[row][col] = best;
        return best;
    };

    int best_length = -1;
    int best_row = 0;
    int best_col = 0;
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            if (row != 0 && row != n - 1 && col != 0 && col != n - 1) {
                continue;
            }
            int current = dfs(dfs, row, col) - 1;
            if (current > best_length) {
                best_length = current;
                best_row = row;
                best_col = col;
            }
        }
    }

    cout << best_length << '\n';
    cout << best_row + 1 << ' ' << best_col + 1 << '\n';
    return 0;
}