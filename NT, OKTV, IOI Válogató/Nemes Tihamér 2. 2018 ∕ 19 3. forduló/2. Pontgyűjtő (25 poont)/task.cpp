/*
Megoldás lényege:
Jobbról balra haladó dinamikával minden (i, j) mezőre kiszámoljuk a jobb szélig elérhető legnagyobb összeget: dp[i][j] = a[i][j] + max(dp[i-1][j+1], dp[i][j+1], dp[i+1][j+1]), ahol a táblán kívüli sorokat kihagyjuk. A bal szélső oszlop dp értékei közül a legnagyobbat keressük, döntetlennél a kisebb sorszámú sort választjuk. Az időigény és a memóriaigény O(N*M).
*/
/*
Hint 1: || Ne a bal szélről indulva próbálkozz, hanem a jobb szélről visszafelé: a jobb szélső oszlop mezői önmagukban is elérhető pontszámok. ||
Hint 2: || Egy (i, j) mezőből a következő oszlop i-1, i és i+1 sorában lévő mezők közül a legjobb már kiszámolt értéket kell hozzáadni a saját pontszámodhoz. A válasz a bal szélső oszlop legnagyobb értéke; döntetlennél a kisebb sor. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 2, vector<int>(m + 2, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> a[i][j];
    }

    const int NEG = -1e9;
    vector<vector<int>> dp(n + 2, vector<int>(m + 2, NEG));

    for (int i = 1; i <= n; ++i) dp[i][m] = a[i][m];
    for (int j = m - 1; j >= 1; --j) {
        for (int i = 1; i <= n; ++i) {
            int best = dp[i][j + 1];
            if (i > 1) best = max(best, dp[i - 1][j + 1]);
            if (i < n) best = max(best, dp[i + 1][j + 1]);
            dp[i][j] = a[i][j] + best;
        }
    }

    int bestScore = NEG, bestRow = 1;
    for (int i = 1; i <= n; ++i) {
        if (dp[i][1] > bestScore) {
            bestScore = dp[i][1];
            bestRow = i;
        }
    }

    cout << bestScore << '\n' << bestRow << '\n';
    return 0;
}