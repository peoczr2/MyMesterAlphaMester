/*
Ha a lehetséges számok intervalluma [l,r], akkor egy x kérdés után vagy [l,x], vagy [x+1,r] marad, és a legrosszabb
eset költségét kell minimalizálni. Ezért a dp[l][r] értéke a lehetséges első kérdések minimuma: f(x) + max(dp[l][x],
dp[x+1][r]). Az intervallumhossz szerint növekvő feldolgozás minden részfeladatot időben kiszámít.
*/
/*
Hint 1: || A részfeladat a még szóba jövő számok intervalluma legyen. ||
Hint 2: || Egy kérdés költségéhez a két ág közül a rosszabbikat kell hozzáadni, nem az átlagot. ||
Hint 3: || Ha az intervallum egyelemű, már nincs szükség új kérdésre. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> cost(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> cost[i];
    }

    const int INF = 1e9;
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
    for (int len = 2; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            int best = INF;
            for (int x = l; x < r; ++x) {
                best = min(best, cost[x] + max(dp[l][x], dp[x + 1][r]));
            }
            dp[l][r] = best;
        }
    }

    cout << dp[1][n] << '\n';
    return 0;
}
