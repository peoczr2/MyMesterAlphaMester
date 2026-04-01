/*
    Örökösök: N gyémántot kell K unoka között szétosztani úgy, hogy mindenki
    legalább 1-et, legfeljebb M-et kapjon, és az összegek mind különbözőek.
    A kiosztások sorrendje nem számít, ezért 0/1 partíció-DP-t használunk.
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
        for (int c = K; c >= 1; --c) {
            for (int s = N; s >= v; --s) {
                dp[c][s] += dp[c - 1][s - v];
                if (dp[c][s] >= MOD) dp[c][s] -= MOD;
            }
        }
    }
    cout << dp[K][N] % MOD << '\n';
    return 0;
}