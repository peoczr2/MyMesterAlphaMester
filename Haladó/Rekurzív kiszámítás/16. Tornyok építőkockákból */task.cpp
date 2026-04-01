/*
Megoldás lényege:
Az előző feladat mintájára az utolsó elem vagy egy 1 magas kocka, vagy egy 3 magas fehér
tégla. Ezért a rekurzió: T(n)=2T(n-1)+T(n-3).

*/

// Hint 1: || Az 1 magas elemekből most is kettőféle van. ||
// Hint 2: || A 3 magas tégla egyetlen lépésben hozzáad 3 egységet a toronyhoz. ||
// Hint 3: || A modulos számolás miatt elég egy sima lineáris DP. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    if (!(cin >> M)) return 0;

    const long long MOD = 20201114LL;
    vector<long long> dp(max(3, M + 1));
    dp[0] = 1;
    if (M >= 1) dp[1] = 2;
    if (M >= 2) dp[2] = 4;
    for (int i = 3; i <= M; ++i) dp[i] = (2 * dp[i - 1] + dp[i - 3]) % MOD;

    cout << dp[M] << '\n';
    return 0;
}
