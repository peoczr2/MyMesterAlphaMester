/*
Megoldás lényege:
A keresett sorrendek az N elemű permutációk közül azok, amelyekben az emelkedő
és a süllyedő szomszédpárok száma megegyezik. Ez pontosan az Eulerian szám
középső eleme, mert N páratlan.

Ugyanazt a DP-rekurziót használjuk, mint az előző feladatban.
*/

#include <bits/stdc++.h>
using namespace std;

static const int MOD = 2017;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    int k = (n - 1) / 2;
    vector<int> dp(k + 1, 0), nextDp(k + 1, 0);
    dp[0] = 1;
    for (int len = 2; len <= n; ++len) {
        fill(nextDp.begin(), nextDp.end(), 0);
        int lim = min(k, len - 1);
        for (int j = 0; j <= lim; ++j) {
            long long val = 1LL * (j + 1) * dp[j] % MOD;
            if (j > 0) val = (val + 1LL * (len - j) * dp[j - 1]) % MOD;
            nextDp[j] = (int)val;
        }
        dp.swap(nextDp);
    }

    cout << dp[k] % MOD << '\n';
    return 0;
}