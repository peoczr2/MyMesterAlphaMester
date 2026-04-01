/*
   Euler-számok: az 1..N permutációinak száma pontosan K emelkedéssel.
   Klasszikus Eulerian DP-t használunk.
*/
#include <bits/stdc++.h>
using namespace std;

static const int MOD = 20191019;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    vector<int> dp(K + 1), ndp(K + 1);
    dp[0] = 1;
    for (int n = 2; n <= N; ++n) {
        fill(ndp.begin(), ndp.end(), 0);
        for (int k = 0; k <= min(K, n - 1); ++k) {
            long long val = 1LL * (k + 1) * dp[k];
            if (k > 0) val += 1LL * (n - k) * dp[k - 1];
            ndp[k] = (int)(val % MOD);
        }
        dp.swap(ndp);
    }
    cout << dp[K] % MOD << '\n';
    return 0;
}