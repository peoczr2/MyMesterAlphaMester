/*
Megoldás lényege:
Az elemek közül a piros és a zöld 2 magas, a sárga és a fehér 3 magas, és mindkét magasságból kétféle szín van. A legfelső elem szerinti felbontásból T(n)=2T(n-2)+2T(n-3) adódik, ahol T(k) a k magasságú tornyok száma. A T(0)=1, T(1)=0 és T(2)=2 kezdőértékekből a sorozatot egy tömbben, 20210108-cal vett maradékkal számoljuk. Az időigény O(N), a memóriaigény szintén O(N).
*/
/*
Hint 1: || Nincs 1 magas elem, ezért N=1 esetén nem építhető torony; az első nem nulla érték a 2 magasságnál van. ||
Hint 2: || A 2 magas elemből kétféle, a 3 magasból szintén kétféle darab van. ||
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
    if (N >= 1) dp[1] = 0;
    if (N >= 2) dp[2] = 2;
    for (int i = 3; i <= N; ++i) dp[i] = (2 * dp[i - 2] + 2 * dp[i - 3]) % MOD;

    cout << dp[N] << '\n';
    return 0;
}
