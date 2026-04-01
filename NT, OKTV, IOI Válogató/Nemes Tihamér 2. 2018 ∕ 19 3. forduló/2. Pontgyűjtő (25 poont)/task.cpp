#include <bits/stdc++.h>
using namespace std;

/*
    Dinamikával jobbról balra számoljuk ki minden mezőből a jobb szélre vezető
    legnagyobb pontszámot. Az induló sor az a bal szélső mező, amelyhez a legjobb
    összpontszám tartozik.
*/

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