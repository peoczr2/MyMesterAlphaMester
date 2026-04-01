/*
Megoldási ötlet:
Mivel csak jobbra és lefelé léphetünk, a rács DAG, ezért minden mezőből a leghosszabb könnyű túra hossza
visszafelé kiszámolható. Egy mezőről csak akkor léphetünk a jobb vagy alsó szomszédba, ha a magasságkülönbség
legfeljebb 1.

A dp[i][j] az (i,j)-ből induló leghosszabb út lépésszáma. Emellett eltároljuk a következő mezőt is, így a
legjobb kezdőpontból a végpont könnyen meghatározható.
*/
/*
Hint 1: || A mozgás irányai miatt nincs kör, tehát visszafelé számolható a DP. ||
Hint 2: || Egy mezőből legfeljebb két helyre lehet továbbmenni: jobbra vagy lefelé. ||
Hint 3: || A végpont megtalálásához elég a tárolt „következő mező” mutatókat követni. ||
*/

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> h(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> h[i][j];
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<vector<pair<int, int>>> nextCell(n + 1, vector<pair<int, int>>(m + 1, {-1, -1}));

    for (int i = n; i >= 1; --i) {
        for (int j = m; j >= 1; --j) {
            auto relax = [&](int ni, int nj) {
                if (ni < 1 || ni > n || nj < 1 || nj > m) return;
                if (abs(h[ni][nj] - h[i][j]) > 1) return;
                if (dp[ni][nj] + 1 > dp[i][j]) {
                    dp[i][j] = dp[ni][nj] + 1;
                    nextCell[i][j] = {ni, nj};
                }
            };
            relax(i + 1, j);
            relax(i, j + 1);
        }
    }

    int sr = 1, sc = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (dp[i][j] > dp[sr][sc]) {
                sr = i;
                sc = j;
            }
        }
    }

    int er = sr, ec = sc;
    while (nextCell[er][ec].first != -1) {
        tie(er, ec) = nextCell[er][ec];
    }

    cout << dp[sr][sc] << '\n';
    cout << sr << ' ' << sc << '\n';
    cout << er << ' ' << ec << '\n';
    return 0;
}