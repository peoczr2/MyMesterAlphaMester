/*
   Lépcsők: a feljutási módok száma az N összeg K-ig terjedő pozitív
   lépésekre bontása. Ez egy egyszerű összegző DP.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    vector<unsigned long long> dp(N + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= N; ++i) {
        for (int jump = 1; jump <= K && i - jump >= 0; ++jump) {
            dp[i] += dp[i - jump];
        }
    }
    cout << dp[N] << '\n';
    return 0;
}