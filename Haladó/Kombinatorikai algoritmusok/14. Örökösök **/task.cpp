/*
   Örökösök: a vármegyék száma K nemnövekvő, pozitív részre bontásának
   száma. A klasszikus partitió-rekurziót használjuk.
*/
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    vector<vector<ull>> dp(N + 1, vector<ull>(K + 1, 0));
    dp[0][0] = 1;
    for (int n = 1; n <= N; ++n) {
        for (int k = 1; k <= K; ++k) {
            ull ans = 0;
            if (n - 1 >= 0 && k - 1 >= 0) ans += dp[n - 1][k - 1];
            if (n - k >= 0) ans += dp[n - k][k];
            dp[n][k] = ans;
        }
    }
    cout << dp[N][K] << '\n';
    return 0;
}