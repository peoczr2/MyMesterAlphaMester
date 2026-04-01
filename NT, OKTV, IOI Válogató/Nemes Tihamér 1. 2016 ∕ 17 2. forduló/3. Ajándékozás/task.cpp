#include <bits/stdc++.h>
using namespace std;

/*
    Az N szaloncukor felbontásainak száma pontosan az N összegpartícióinak száma,
    ahol minden rész legfeljebb M lehet. Ezt egyszerű pénzváltós dinamikával
    számoljuk.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> dp(n + 1);
    dp[0] = 1;
    for (int resz = 1; resz <= m; ++resz) {
        for (int s = resz; s <= n; ++s) {
            dp[s] += dp[s - resz];
        }
    }

    cout << dp[n] << '\n';
    return 0;
}