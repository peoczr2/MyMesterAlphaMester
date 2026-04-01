/*
Megoldás lényege:
Az éppen egymás után álló feladatok között pontosan K alkalommal kell növekednie
a nehézségnek. Ez az Euler-féle számokra vezető klasszikus Eulerian DP.

A dp[n][k] azt jelenti, hogy az 1..n permutációi közül hányban pontosan k
emelkedés van. A rekurzió:
  dp[n][k] = (k+1) * dp[n-1][k] + (n-k) * dp[n-1][k-1].
*/

#include <bits/stdc++.h>
using namespace std;

static const int MOD = 20160322;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> dp(k + 1, 0), nextDp(k + 1, 0);
    dp[0] = 1;
    for (int len = 2; len <= n; ++len) {
        fill(nextDp.begin(), nextDp.end(), 0);
        int lim = min(k, len - 1);
        for (int j = 0; j <= lim; ++j) {
            long long val = 1LL * (j + 1) * dp[j] % MOD;
            if (j > 0) val = (val + 1LL * (len - j) * dp[j - 1]) % MOD;
            nextDp[j] = (int)val;
        }
        dp.swap(nextDp);
    }

    cout << (k <= n - 1 ? dp[k] : 0) % MOD << '\n';
    return 0;
}