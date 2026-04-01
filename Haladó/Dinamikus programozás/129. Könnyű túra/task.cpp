/*
Megoldási ötlet:
Ugyanaz a feladat, mint a 128-as: a rácsban csak délre és keletre léphetünk, és csak akkor, ha a magasságkülönbség
legfeljebb 1. Ezért minden mezőből a leghosszabb elérhető út hossza visszafelé dinamikus programozással számolható.

A dp[i][j] az (i,j)-ből induló leghosszabb út hossza, a nextCell pedig eltárolja a folytatás mezőjét. A maximális
dp-jű kezdőmezőből a végpont egyszerű pointerkövetéssel megkapható.
*/
/*
Hint 1: || Jobbra és lefelé lépés miatt a rács egy aciklikus gráf. ||
Hint 2: || Egy mező értéke a két lehetséges utód legjobb értékéből számolható. ||
Hint 3: || A kezdő- és végpont meghatározásához nem kell az egész útvonalat kiírni, elég a következő mezőt tárolni. ||
*/

#include <cstdlib>
#include <iostream>
#include <tuple>
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