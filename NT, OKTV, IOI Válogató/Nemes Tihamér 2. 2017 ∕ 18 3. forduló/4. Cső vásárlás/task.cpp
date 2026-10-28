/*
    Teljesen kitöltött hosszt kell venni, ezért unbounded knapsack DP-t használunk
    minimális költséggel, és az elődmutatókból visszaállítjuk a vásárlást.
    Az időigény O(N·M), ami a korlátok mellett bőven belefér.
*/
/*
Hint 1: || Mivel pontosan M hosszt kell megvásárolni, a részproblémák: dp[l] az l hosszú, pontosan kitöltött csővezeték minimális ára, ha elérhető. Kezdetben dp[0] = 0, a többi végtelen, és egy üzlet csöve tetszőleges számban vásárolható. ||

Hint 2: || Üzletenként haladva a hosszakat növekvő sorrendben frissítsd: dp[l] frissíthető a dp[l-H_i] + A_i értékkel, így ugyanarról az üzletről több csövet is figyelembe veszel. Frissítéskor jegyezd fel az előző hosszt és az üzletet. ||

Hint 3: || Ha dp[M] végtelen, a válasz 0. Különben M-ből kiindulva a feljegyzett előző hosszakat visszafelé követve eljutsz 0-ig, és minden lépésnél az adott üzletből egy darabbal többet számolsz. ||
*/
#include <bits/stdc++.h>
using namespace std;

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