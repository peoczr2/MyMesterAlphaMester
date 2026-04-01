/*
   Hibás lépcsők: DP a lépésszámra és az elfoglalt fokra.
   A hibás fokokra nem érkezhetünk meg, a válasz a legfeljebb L lépéses
   bejutások száma.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, H, L;
    cin >> N >> K >> H >> L;
    vector<int> bad(N + 1, 0);
    for (int i = 0; i < H; ++i) {
        int x;
        cin >> x;
        bad[x] = 1;
    }

    vector<vector<unsigned long long>> dp(L + 1, vector<unsigned long long>(N + 1, 0));
    dp[0][0] = 1;
    for (int step = 1; step <= L; ++step) {
        for (int pos = 1; pos <= N; ++pos) {
            if (bad[pos]) continue;
            unsigned long long ways = 0;
            for (int jump = 1; jump <= K && pos - jump >= 0; ++jump) {
                ways += dp[step - 1][pos - jump];
            }
            dp[step][pos] = ways;
        }
    }

    unsigned long long ans = 0;
    for (int step = 0; step <= L; ++step) ans += dp[step][N];
    cout << ans << '\n';
    return 0;
}