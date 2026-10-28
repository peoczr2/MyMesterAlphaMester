/*
Megoldás lényege:
A torony legfelső eleme vagy egy 1 magas elem (piros vagy zöld), vagy egy 3 magas elem (fehér vagy sárga). Így T(n)=2T(n-1)+2T(n-3), ahol T(k) a k magasságú tornyok száma. A T(0)=1, T(1)=2 és T(2)=4 kezdőértékekből a sorozatot egy tömbben, 20210108-cal vett maradékkal számoljuk. Az időigény O(N), a memóriaigény szintén O(N).
*/
/*
Hint 1: || Mindkét magasságból (1 és 3) két-két szín közül választhatsz. ||
Hint 2: || Az első három értéket kézzel is fel lehet írni, ebből indul a rekurzió. ||
*/
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
