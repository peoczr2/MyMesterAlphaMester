/*
Megoldás lényege:
Háromféle 1 magas elem és egyféle 2 magas elem van. Ezért T(n)=3T(n-1)+T(n-2).

*/

// Hint 1: || Az 1 magas réteget háromféle színnel választhatod. ||
// Hint 2: || A 2 magas fehér elem csak egyetlen lehetőség, de két szintet fed le. ||
// Hint 3: || A keresett szám mod 20210108. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    const long long MOD = 20210108LL;
    vector<long long> dp(max(2, N + 1));
    dp[0] = 1;
    if (N >= 1) dp[1] = 3;
    for (int i = 2; i <= N; ++i) dp[i] = (3 * dp[i - 1] + dp[i - 2]) % MOD;

    cout << dp[N] << '\n';
    return 0;
}
