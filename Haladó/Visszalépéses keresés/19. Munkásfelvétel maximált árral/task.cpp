/*
Hungarian megoldás: a munkás-felvételhez min-költségű tökéletes párosítást
keresünk, majd ellenőrizzük a költségkeretet.

Hint 1: || Minden munkás legfeljebb egy állást kaphat. ||
Hint 2: || Elég a legolcsóbb teljes megoldás, és utána összevetjük a kerettel. ||
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
    vector<int> ans(n);
    int mask = full;
    for (int i = n - 1; i >= 0; --i) {
        int j = prevJob[mask];
        ans[i] = j + 1;
        mask = prevMask[mask];
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}