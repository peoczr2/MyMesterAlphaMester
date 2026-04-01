/*
Megoldás lényege:
Most az elemek 2 és 3 magasak, mindkettőből kétféle szín van. A toronyépítés ezért
T(n)=2T(n-2)+2T(n-3) rekurziót követ.

*/

// Hint 1: || 1 magas elemek már nincsenek, ezért az első nem nulla érték a 2 magasságnál jelenik meg. ||
// Hint 2: || A 2 magas elemből kétféle, a 3 magasból szintén kétféle darab van. ||
// Hint 3: || Figyelj arra, hogy N=1 esetén semmilyen torony nem építhető. ||

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
