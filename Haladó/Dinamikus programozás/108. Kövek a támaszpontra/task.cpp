/*
Megoldási ötlet:
A marsjáró ugyanúgy csak jobbra vagy lefelé haladhat, ezért minden mezőre meg tudjuk mondani,
hogy az odáig vezető optimális monotonn úton legfeljebb hány követ szedhet össze. Az aktuális mező
értéke a felső és bal oldali DP-érték maximuma plusz az itt levő kövek száma.

Miután kitöltöttük a teljes táblát, a támaszpontok között egyszerűen kiválasztjuk azt, amelyikhez a DP
érték a legnagyobb.
*/
/*
Hint 1: || A mozgásirányok pontosan ugyanazt jelentik, mint a klasszikus rács-DP feladatokban. ||
Hint 2: || Egy mezőre érkezve csak a felső vagy bal szomszédból jöhetsz. ||
Hint 3: || A teljes rács kitöltése után minden támaszponthoz azonnal kiolvasható a legjobb eredmény. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, t;
    cin >> n >> m >> k >> t;

    vector<vector<int>> stones(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < k; ++i) {
        int r, c;
        cin >> r >> c;
        ++stones[r][c];
    }

    vector<pair<int, int>> bases(t);
    for (int i = 0; i < t; ++i) cin >> bases[i].first >> bases[i].second;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + stones[i][j];
        }
    }

    pair<int, int> bestBase = bases[0];
    int bestValue = dp[bestBase.first][bestBase.second];
    for (const auto& base : bases) {
        int current = dp[base.first][base.second];
        if (current > bestValue) {
            bestValue = current;
            bestBase = base;
        }
    }

    cout << bestValue << '\n';
    cout << bestBase.first << ' ' << bestBase.second << '\n';
    return 0;
}