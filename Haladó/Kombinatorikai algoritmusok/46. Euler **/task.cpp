/*
   Euler-számok: az 1..N permutációinak száma pontosan K emelkedéssel. Legyen E(n,k) az n elemű, k emelkedéses
   permutációk száma. Az n-edik (legnagyobb) elemet beszúrva egy (n-1) elemű, k emelkedéses sorrendbe k+1 helyen
   nem változik az emelkedések száma, egy (n-1) elemű, (k-1) emelkedéses sorrendbe pedig n-k helyen eggyel nő.
   Így E(n,k) = (k+1)·E(n-1,k) + (n-k)·E(n-1,k-1), E(1,0) = 1, és minden lépésben modulo 20191019.
   Az időigény O(N·K).
*/
/*
Hint 1: || N legfeljebb 1000, ezért a sorrendek felsorolása szóba sem jöhet. Gondold végig, mi történik az emelkedések számával, ha a legnagyobb elemet egy rövidebb, már számolt sorrendbe szúrod be. ||
Hint 2: || Ha az (n-1) elemű sorrend k emelkedéses, k+1 helyre szúrva nem változik az emelkedések száma; ha k-1 emelkedéses, n-k helyre szúrva eggyel nő. Ebből a rekurzió: E(n,k) = (k+1)·E(n-1,k) + (n-k)·E(n-1,k-1). ||
*/
#include <bits/stdc++.h>
using namespace std;

static const int MOD = 20191019;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    vector<int> dp(K + 1), ndp(K + 1);
    dp[0] = 1;
    for (int n = 2; n <= N; ++n) {
        fill(ndp.begin(), ndp.end(), 0);
        for (int k = 0; k <= min(K, n - 1); ++k) {
            long long val = 1LL * (k + 1) * dp[k];
            if (k > 0) val += 1LL * (n - k) * dp[k - 1];
            ndp[k] = (int)(val % MOD);
        }
        dp.swap(ndp);
    }
    cout << dp[K] % MOD << '\n';
    return 0;
}