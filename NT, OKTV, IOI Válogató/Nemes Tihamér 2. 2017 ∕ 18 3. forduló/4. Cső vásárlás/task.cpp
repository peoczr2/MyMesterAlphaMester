#include <bits/stdc++.h>
using namespace std;

/*
    Teljesen kitöltött hosszt kell venni, ezért unbounded knapsack DP-t használunk
    minimális költséggel, és az elődmutatókból visszaállítjuk a vásárlást.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> h(n + 1), a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> h[i] >> a[i];

    const int INF = 1e9;
    vector<int> dp(m + 1, INF), prevLen(m + 1, -1), prevShop(m + 1, -1);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int len = h[i]; len <= m; ++len) {
            if (dp[len - h[i]] + a[i] < dp[len]) {
                dp[len] = dp[len - h[i]] + a[i];
                prevLen[len] = len - h[i];
                prevShop[len] = i;
            }
        }
    }

    if (dp[m] >= INF) {
        cout << 0 << '\n';
        return 0;
    }

    vector<int> cnt(n + 1, 0);
    for (int len = m; len > 0; len = prevLen[len]) ++cnt[prevShop[len]];

    vector<pair<int,int>> ans;
    for (int i = 1; i <= n; ++i) if (cnt[i]) ans.push_back({i, cnt[i]});

    cout << dp[m] << '\n' << ans.size() << '\n';
    for (auto [i, c] : ans) cout << i << ' ' << c << '\n';
    return 0;
}