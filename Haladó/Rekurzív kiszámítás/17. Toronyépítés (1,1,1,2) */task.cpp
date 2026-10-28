/*
Megoldás lényege:
A torony legfelső eleme vagy egy 1 magas elem, vagy egy 2 magas fehér tégla. Az 1 magas elemekből háromféle van (piros, sárga, zöld), ezért T(n)=3T(n-1)+T(n-2), ahol T(k) a k magasságú tornyok száma. A T(0)=1 és T(1)=3 kezdőértékekből a sorozatot egy tömbben, 20210108-cal vett maradékkal számoljuk. Az időigény O(N), a memóriaigény szintén O(N).
*/
/*
Hint 1: || Az 1 magas réteget háromféle színnel választhatod. ||
Hint 2: || A 2 magas fehér elem csak egyetlen lehetőség, de két szintet fed le. ||
*/
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
