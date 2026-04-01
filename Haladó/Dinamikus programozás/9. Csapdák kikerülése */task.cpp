/*
Mivel csak jobbra és lefelé lehet lépni, és csapdára nem szabad ráállni, a mezők száma egyszerűen
összegezhető a két lehetséges elődből. Legyen dp[j] az aktuális sor j-edik mezőjére vezető utak száma
modulo 1 000 000. Ha a mező csapda, akkor 0 út vezet oda, különben a balról és felülről érkező utak
összegét vesszük. Egy soros DP-vel O(N*M) idő és O(M) memória elég.
*/
/*
Hint 1: || A mozgásirányok miatt egy mezőhöz csak balról és felülről lehet érkezni. ||
Hint 2: || Csapda mezőnél az oda vezető utak száma 0 lesz. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    const int MOD = 1000000;
    vector<int> dp(m + 1, 0);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int trap;
            cin >> trap;
            if (trap == 1) {
                dp[j] = 0;
            } else if (i == 1 && j == 1) {
                dp[j] = 1;
            } else {
                dp[j] += dp[j - 1];
                if (dp[j] >= MOD) {
                    dp[j] -= MOD;
                }
            }
        }
    }

    cout << dp[m] << '\n';
    return 0;
}