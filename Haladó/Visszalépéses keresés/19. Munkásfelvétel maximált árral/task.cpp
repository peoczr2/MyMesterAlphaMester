/*
Megoldás lényege: a jelentkezőket sorban (1-től N-ig) rendeljük az állásokhoz. A DP-tábla indexe egy
bitmaszk: a maszk azokat az állásokat jelöli, amelyeket az eddigi jelentkezők már betöltöttek, értéke
pedig a legkisebb összköltség. A teljes maszkhoz tartozó dp érték a legolcsóbb teljes kiosztás költsége;
ha ez meghaladja X-et, a válasz NINCS. Visszakövetéssel állapítjuk meg, melyik állást melyik jelentkező
kapta. Időigény: O(2^N * N^2), N ≤ 15 esetén ez gyors.
*/
/*
Hint 1: || A jelentkezőket egymás után dolgozd fel, és jegyezd meg, mely állások már betöltöttek. ||
Hint 2: || dp[maszk] legyen a legkisebb költség, amellyel az első popcount(maszk) jelentkező a maszkban lévő állásokat betölti. Az i-edik jelentkezőt egy szabad j állásra téve dp[maszk | (1 << j)] frissíthető cost[i][j] költséggel. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;
    vector<vector<int>> cost(n, vector<int>(n, INT_MAX / 4));
    for (int i = 0; i < n; ++i) {
        int db;
        cin >> db;
        for (int j = 0; j < db; ++j) {
            int job, c;
            cin >> job >> c;
            cost[i][job - 1] = min(cost[i][job - 1], c);
        }
    }
    int full = (1 << n) - 1;
    const int INF = 1e9;
    vector<int> dp(1 << n, INF), prevMask(1 << n, -1), prevJob(1 << n, -1);
    dp[0] = 0;
    for (int mask = 0; mask <= full; ++mask) {
        int i = __builtin_popcount((unsigned)mask);
        if (i >= n || dp[mask] == INF) continue;
        for (int j = 0; j < n; ++j) if (!(mask & (1 << j)) && cost[i][j] < INF / 2) {
            int nmask = mask | (1 << j);
            int nd = dp[mask] + cost[i][j];
            if (nd < dp[nmask]) {
                dp[nmask] = nd;
                prevMask[nmask] = mask;
                prevJob[nmask] = j;
            }
        }
    }
    if (dp[full] > x) {
        cout << "NINCS\n";
        return 0;
    }
    // ans[j]: a j-edik állásra felvett jelentkező sorszáma
    vector<int> ans(n);
    int mask = full;
    for (int i = n - 1; i >= 0; --i) {
        int j = prevJob[mask];
        ans[j] = i + 1;
        mask = prevMask[mask];
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}