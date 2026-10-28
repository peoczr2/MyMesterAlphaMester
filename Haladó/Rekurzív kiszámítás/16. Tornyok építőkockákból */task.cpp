/*
Megoldás lényege:
Az utolsó elem vagy egy 1 magas kocka (ebből kétféle szín van), vagy egy 3 magas fehér tégla. Ezért a T(n)=2T(n-1)+T(n-3) rekurzió adja a megoldást, ahol T(k) a k magasságú tornyok száma. A T(0)=1, T(1)=2 és T(2)=4 kezdőértékekből a sorozatot egy tömbben, 20 201 114-gyel vett maradékkal számoljuk. Az időigény O(M), a memóriaigény szintén O(M).
*/
/*
Hint 1: || Gondold végig, mi lehet a torony legfelső eleme: az 1 magas kockákból kétféle van, a 3 magas téglából egy. ||
Hint 2: || A 3 magas tégla egyetlen lépésben hozzáad 3 egységet a toronyhoz. ||
*/
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
