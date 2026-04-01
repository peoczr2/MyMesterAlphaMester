/*
Az állapot legyen az aktuális állomásra megérkezés után a hátizsákban levő dobozok száma. Egy állomáson bármennyi,
de legfeljebb a készletből és a kapacitásból engedett mennyiséget lehet venni, és ha pozitív mennyiséget veszünk, az
pontosan egy új vásárlást jelent. Mivel K legfeljebb 100, az állomásokon végigfuttatott O(NK^2) DP kényelmesen elég.
*/
/*
Hint 1: || Az fontos állapot, hogy egy állomásra hány dobozzal érkezel meg. ||
Hint 2: || Egy vásárlás költsége nem a dobozok száma, hanem az, hogy adott boltban vettél-e legalább egyet. ||
Hint 3: || A célállapotban pontosan 0 doboznak kell maradnia. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;
    vector<int> dist(n + 1), stock(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> dist[i] >> stock[i];
    }

    const int INF = 1e9;
    vector<int> dp(K + 1, INF), next_dp(K + 1, INF);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        fill(next_dp.begin(), next_dp.end(), INF);
        for (int have = 0; have <= K; ++have) {
            if (dp[have] == INF) {
                continue;
            }
            int max_buy = min(stock[i], K - have);
            for (int buy = 0; buy <= max_buy; ++buy) {
                if (have + buy < dist[i]) {
                    continue;
                }
                int remain = have + buy - dist[i];
                next_dp[remain] = min(next_dp[remain], dp[have] + (buy > 0));
            }
        }
        dp.swap(next_dp);
    }

    cout << (dp[0] == INF ? -1 : dp[0]) << '\n';
    return 0;
}
