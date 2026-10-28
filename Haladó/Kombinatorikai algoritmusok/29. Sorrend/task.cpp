/*
Megoldás lényege:
A szomszédpárok száma N−1, és mindegyik vagy emelkedő, vagy süllyedő. A feltétel szerint a két darabszám egyenlő, így mindkettő pontosan (N−1)/2; N páratlan, ezért ez egész szám.
Tehát az N elemű permutációk közül azokat kell megszámolni, amelyekben pontosan (N−1)/2 emelkedés van; ez az Eulerian-szám A(N, (N−1)/2).
Az Eulerian-számokat a dp[n][k] = (k+1)·dp[n−1][k] + (n−k)·dp[n−1][k−1] rekurzióval töltjük ki, és csak a k = (N−1)/2 értékig tartjuk nyilván, modulo 2017.
Az időigény O(N²), N ≤ 99 esetén ez gyors.
*/
/*
Hint 1: || A két egyenlő darabszám összege N−1 (a szomszédpárok száma), így mindkettő pontosan (N−1)/2: a kérdés egyetlen Eulerian-szám kiszámítása. ||
Hint 2: || Az Eulerian-számok táblázatát a dp[n][k] rekurzióval töltsd ki, elég a k = (N−1)/2 értékig tartani, és minden lépésben modulo 2017 szerint számolj. ||
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