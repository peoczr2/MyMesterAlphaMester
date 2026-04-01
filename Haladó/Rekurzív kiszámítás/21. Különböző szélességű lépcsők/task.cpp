/*
Megoldás lényege:
Ez az előző feladat speciális esete, ahol minden lépcső egységmagas. Így csak a
szélességek prefixösszegét kell figyelni, és ugyanaz a DAG-dinamikus összegzés működik.

*/

// Hint 1: || A magasság most minden foknál 1, ezért a függőleges különbség egyszerűen a fokok száma. ||
// Hint 2: || A vízszintes különbséget továbbra is prefix szélességekkel számoljuk. ||
// Hint 3: || A legfelső fokra vezető utak száma egy sima összegezős DP. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Hlim, Tlim;
    if (!(cin >> N >> Hlim >> Tlim)) return 0;

    vector<long long> w(N + 1), pos(N + 1);
    for (int i = 1; i <= N; ++i) cin >> w[i];
    pos[0] = 0;
    // i. lépcső eleje: az előző lépcsők szélességeinek összege + 1.
    for (int i = 1; i <= N; ++i) pos[i] = pos[i - 1] + w[i - 1];
    for (int i = 1; i <= N; ++i) ++pos[i];

    const long long MOD = 20210327LL;
    vector<long long> dp(N + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= N; ++i) {
        long long sum = 0;
        for (int j = 0; j < i; ++j) {
            if (pos[i] - pos[j] <= Tlim && i - j <= Hlim) sum += dp[j];
        }
        dp[i] = sum % MOD;
    }

    cout << dp[N] << '\n';
    return 0;
}
