/*
Megoldási ötlet:
A mozgások és a teleportok is mindig nagyobb oszlopsorszámú mezőre visznek, ezért továbbra is aciklikus a gráf.
Egy mezőre érkezve a legfontosabb információ az, hogy mennyi pénzünk marad. Ha a mező teleport, akkor ráérkezéskor
azonnal a célmezőre jutunk, ezért az átmenetet rögtön a teleport láncának végére vezetjük.

A dp[i][j] a mezőn állva elérhető maximális pénz. Egy szomszédba lépésnél levonjuk az L költséget, majd hozzáadjuk
annak a végső mezőnek a pénzét, ahová a teleportok után ténylegesen megérkezünk.
*/
/*
Hint 1: || A teleport mindig nagyobb oszlopba visz, ezért a teleportláncok nem alkotnak ciklust. ||
Hint 2: || Nem érdemes teleportforrás mezőn állapotot tárolni, mert onnan azonnal tovább kell ugrani. ||
Hint 3: || Előre számold ki minden mező végső célját a teleportlánc mentén. ||
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, stepCost;
    cin >> n >> m >> stepCost;
    vector<vector<long long>> money(n + 1, vector<long long>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> money[i][j];
    }

    vector<vector<pair<int, int>>> tele(n + 1, vector<pair<int, int>>(m + 1, {-1, -1}));
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int r, c, tr, tc;
        cin >> r >> c >> tr >> tc;
        tele[r][c] = {tr, tc};
        money[r][c] = 0;
    }

    vector<vector<pair<int, int>>> finalCell(n + 1, vector<pair<int, int>>(m + 1));
    for (int j = m; j >= 1; --j) {
        for (int i = 1; i <= n; ++i) {
            if (tele[i][j].first == -1) finalCell[i][j] = {i, j};
            else finalCell[i][j] = finalCell[tele[i][j].first][tele[i][j].second];
        }
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, -1));
    pair<int, int> start = finalCell[1][1];
    dp[start.first][start.second] = money[start.first][start.second];

    for (int j = 1; j <= m; ++j) {
        for (int i = 1; i <= n; ++i) {
            if (dp[i][j] < 0) continue;
            auto relax = [&](int nr, int nc) {
                if (nr < 1 || nr > n || nc < 1 || nc > m) return;
                if (dp[i][j] < stepCost) return;
                long long remaining = dp[i][j] - stepCost;
                auto [fr, fc] = finalCell[nr][nc];
                if (tele[nr][nc].first != -1) {
                    if (remaining < stepCost) return;
                    remaining -= stepCost;
                }
                dp[fr][fc] = max(dp[fr][fc], remaining + money[fr][fc]);
            };
            relax(i, j + 1);
            relax(i + 1, j);
            relax(i + 1, j + 1);
        }
    }

    cout << dp[n][m] << '\n';
    return 0;
}