/*
    Örökség: N gyémántot kell K unoka között szétosztani úgy, hogy mindenki
    legalább 1-et, legfeljebb M-et kapjon. A kiosztások sorrendje nem számít,
    ezért partíciószámot számolunk.
*/
#include <bits/stdc++.h>
using namespace std;

static const int MOD = 20200202;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, M;
    cin >> N >> K >> M;
    vector<vector<int>> dp(K + 1, vector<int>(N + 1, 0));
    dp[0][0] = 1;
    for (int v = 1; v <= M; ++v) {
        for (int k = 1; k <= K; ++k) {
            for (int s = v; s <= N; ++s) {
                dp[k][s] += dp[k - 1][s - v];
                if (dp[k][s] >= MOD) dp[k][s] -= MOD;
            }
        }
    }
    cout << dp[K][N] % MOD << '\n';
    return 0;
}