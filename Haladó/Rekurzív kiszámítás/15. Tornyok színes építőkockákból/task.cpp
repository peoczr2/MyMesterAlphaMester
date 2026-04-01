/*
Megoldás lényege:
Ha a torony magassága 1-gyel nő, kétféle egységkockát tehetünk rá. Ha 2-vel nő,
akkor egy fehér téglát választunk. Ez a fenti két lehetőség miatt a T(n)=2T(n-1)+T(n-2)
rekurzíót adja.

*/

// Hint 1: || Az utolsó elem vagy 1 magas színes kocka, vagy 2 magas fehér tégla. ||
// Hint 2: || A két színes kocka csak a darabszámot szorozza meg kettővel. ||
// Hint 3: || A feladatban a válasz modult kell venni, ezért a számolás végig maradhat egész. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    if (!(cin >> M)) return 0;

    const long long MOD = 20201114LL;
    vector<long long> dp(max(2, M + 1));
    dp[0] = 1;
    if (M >= 1) dp[1] = 2;
    for (int i = 2; i <= M; ++i) dp[i] = (2 * dp[i - 1] + dp[i - 2]) % MOD;

    cout << dp[M] << '\n';
    return 0;
}
