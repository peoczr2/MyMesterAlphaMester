/*
Megoldás lényege:
A feladatok sorrendje egy 1..N permutáció, a „nehezebb az előzőnél” pedig egy emelkedés, így a keresett szám az Eulerian-szám: az 1..N permutációi közül hányban van pontosan K emelkedés.
A dp[n][k] az 1..n permutációi közül a k emelkedésűek számát adja. Az n legnagyobb elemét az (n−1)-es permutációba szúrjuk: a k emelkedésű permutációkba k+1 helyre szúrva marad k emelkedés, a k−1 emelkedésűekbe pedig n−k helyre szúrva lesz k, így dp[n][k] = (k+1)·dp[n−1][k] + (n−k)·dp[n−1][k−1].
Elég az előző sort tárolni, az időigény O(N·K), és N ≤ 100 miatt ez bőven elég; a számolás modulo 20160322 történik.
*/
/*
Hint 1: || Rekurzívan gondolkodj: az 1..N−1 permutációkból indulj ki, és az N-es (legnagyobb) elemet szúrd be, nézd meg, hogyan változik az emelkedések száma. ||
Hint 2: || Ha egy k emelkedésű permutációba a legnagyobb elemet szúrod, k+1 hely megtartja az emelkedések számát; a k−1 emelkedésűekből n−k hely ad k emelkedést. Ebből írd fel a dp[n][k] rekurziót. ||
*/

#include <bits/stdc++.h>
using namespace std;

static const int MOD = 20160322;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;

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

    cout << (k <= n - 1 ? dp[k] : 0) % MOD << '\n';
    return 0;
}