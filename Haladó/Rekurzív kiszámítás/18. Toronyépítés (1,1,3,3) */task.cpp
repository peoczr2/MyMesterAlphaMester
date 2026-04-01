/*
Megoldás lényege:
Az 1 magas elemekből kettő, a 3 magas elemekből szintén kettő van. Így T(n)=2T(n-1)+2T(n-3).

*/

// Hint 1: || Az 1 magas és a 3 magas elemek között most két-két szín közül választhatsz. ||
// Hint 2: || Az első három értéket kézzel is fel lehet írni, ebből indul a rekurzió. ||
// Hint 3: || Az eredményt 20210108-cal kell venni modulo. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    const long long MOD = 20210108LL;
    vector<long long> dp(max(3, N + 1));
    dp[0] = 1;
    if (N >= 1) dp[1] = 2;
    if (N >= 2) dp[2] = 4;
    for (int i = 3; i <= N; ++i) dp[i] = (2 * dp[i - 1] + 2 * dp[i - 3]) % MOD;

    cout << dp[N] << '\n';
    return 0;
}
