/*
Megoldás lényege:
A lépcsőfokok frontjának koordinátáit prefixösszegekkel számoljuk ki. Egy fokra akkor
tudunk lépni egy másikról, ha a vízszintes és függőleges különbség is belefér a korlátokba.
Ez egy egyszerű DAG-dinamikát ad.

*/

// Hint 1: || A lépcsőfokok frontjának helye prefix szélességből és prefix magasságból adódik. ||
// Hint 2: || Minden lépcsőre az előző, még elérhető lépcsőkből gyűjtsd össze a számokat. ||
// Hint 3: || N csak 1000, ezért az O(N^2) megoldás is bőven elég. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Hlim, Tlim;
    if (!(cin >> N >> Hlim >> Tlim)) return 0;

    vector<long long> w(N + 1), h(N + 1), x(N + 1), y(N + 1);
    for (int i = 1; i <= N; ++i) cin >> w[i];
    for (int i = 1; i <= N; ++i) cin >> h[i];

    for (int i = 1; i <= N; ++i) {
        x[i] = x[i - 1] + w[i];
        y[i] = y[i - 1] + h[i];
    }

    const long long MOD = 20210327LL;
    vector<long long> dp(N + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= N; ++i) {
        long long sum = 0;
        for (int j = 0; j < i; ++j) {
            if (x[i] - x[j] <= Tlim && y[i] - y[j] <= Hlim) {
                sum += dp[j];
            }
        }
        dp[i] = sum % MOD;
    }

    cout << dp[N] << '\n';
    return 0;
}
