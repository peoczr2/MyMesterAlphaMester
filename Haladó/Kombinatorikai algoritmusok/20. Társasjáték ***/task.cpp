/*
   Társasjáték: dinamikusan számoljuk, hogy hány dobássorozat juttat el a
   játékost az N. mezőre legfeljebb K dobás alatt. A célmezőn megáll a
   folyamat, ezért onnan nem vezetünk tovább.
*/
#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    vector<vector<int>> dp(K + 1, vector<int>(N + 1, 0));
    dp[0][1] = 1;
    for (int step = 0; step < K; ++step) {
        for (int pos = 1; pos <= N; ++pos) {
            if (!dp[step][pos] || pos == N) continue;
            for (int roll = 1; roll <= 6; ++roll) {
                int nxt = pos + roll;
                if (nxt > N) nxt = 2 * N - nxt;
                dp[step + 1][nxt] = (dp[step + 1][nxt] + dp[step][pos]) % MOD;
            }
        }
    }

    int ans = 0;
    for (int step = 1; step <= K; ++step) ans = (ans + dp[step][N]) % MOD;
    cout << ans << '\n';
    return 0;
}