/*
Megoldás lényege:
DP a megtett lépések számára és a lépcsőfokra: dp[s][p] azt adja meg, hányféleképpen juthatunk a p-edik
lépcsőfokra pontosan s lépésben. Hibás lépcsőfokra nem léphetünk, ezért ott az érték 0. Az átmenet az előző
K lépcsőfok értékeit összegzi, a válasz pedig az N-edik lépcsőfokra érkező utak száma minden s<=L lépésszámra.
Csak összeadás van, így a 64 bites túlcsordulás modulo 2^64 nem rontja el a végeredményt, amely a feladat
szerint elfér 64 biten. Az időigény O(L*N*K), ami N, K, L legfeljebb 100 mellett 10^6 művelet.
*/
/*
Hint 1: || Az állapot két dimenziós: hány lépés után és melyik lépcsőfokon állunk. Mivel legfeljebb L lépést számolunk, minden lépésszámra külön kell összegezni. ||
Hint 2: || Egy lépcsőfokra az előző lépés előtt az előző K lépcsőfok valamelyikéről érkezhettünk. A hibás lépcsőfokokra az érték legyen 0, és ott ne számoljunk tovább. ||
Hint 3: || A kiindulópont a 0-s lépcsőfok, és a válasz az N-edik lépcsőfokra érkező utak számainak összege minden lépésszámra, legfeljebb L-ig. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, H, L;
    cin >> N >> K >> H >> L;
    vector<int> bad(N + 1, 0);
    for (int i = 0; i < H; ++i) {
        int x;
        cin >> x;
        bad[x] = 1;
    }

    vector<vector<unsigned long long>> dp(L + 1, vector<unsigned long long>(N + 1, 0));
    dp[0][0] = 1;
    for (int step = 1; step <= L; ++step) {
        for (int pos = 1; pos <= N; ++pos) {
            if (bad[pos]) continue;
            unsigned long long ways = 0;
            for (int jump = 1; jump <= K && pos - jump >= 0; ++jump) {
                ways += dp[step - 1][pos - jump];
            }
            dp[step][pos] = ways;
        }
    }

    unsigned long long ans = 0;
    for (int step = 0; step <= L; ++step) ans += dp[step][N];
    cout << ans << '\n';
    return 0;
}