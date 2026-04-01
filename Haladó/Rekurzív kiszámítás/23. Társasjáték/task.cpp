/*
Megoldás lényege:
A lépések csak előre mennek, ezért a mezők egy irányított aciklikus gráfot alkotnak.
Visszafelé számolva minden mezőből a következő és az ugrómező közül a kisebb távolságot
választjuk.

*/

// Hint 1: || A gráf itt DAG, ezért elég hátulról előre számolni. ||
// Hint 2: || A következő mező mindig elérhető, az ugrás csak akkor, ha valóban előre visz. ||
// Hint 3: || A válasz a startmezőből induló legrövidebb út hossza. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<int> jump(N + 1);
    for (int i = 1; i <= N; ++i) cin >> jump[i];

    const int INF = 1e9;
    vector<int> dp(N + 2, INF);
    dp[N] = 0;
    for (int i = N - 1; i >= 1; --i) {
        dp[i] = 1 + dp[i + 1];
        if (jump[i] > i) dp[i] = min(dp[i], 1 + dp[jump[i]]);
    }

    cout << dp[1] << '\n';
    return 0;
}
