/*
Hungarian megoldás: minden tanuló pontosan egy iskolába kerül, ezért a feladat
kapacitásos bipartit párosítás.

Hint 1: || A tanuló csak a megadott két iskola egyikébe mehet. ||
Hint 2: || Az iskolák férőhelyei kapacitásként jelennek meg a hálózatban. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> valasz(n);
    for (int i = 0; i < n; ++i) {
        cin >> valasz[i].first >> valasz[i].second;
    }
    vector<int> kap(m + 1);
    for (int i = 1; i <= m; ++i) cin >> kap[i];

    int S = 0, stu0 = 1, sch0 = 1 + n, T = 1 + n + m;
    Dinic din(T + 1);
    for (int i = 0; i < n; ++i) din.addEdge(S, stu0 + i, 1);
    for (int i = 1; i <= m; ++i) din.addEdge(sch0 + i - 1, T, kap[i]);
    for (int i = 0; i < n; ++i) {
        auto [a, b] = valasz[i];
        if (a) din.addEdge(stu0 + i, sch0 + a - 1, 1);
        if (b) din.addEdge(stu0 + i, sch0 + b - 1, 1);
    }
    if (din.maxflow(S, T) != n) {
        cout << -1 << '\n';
        return 0;
    }
    vector<int> ans(n, -1);
    for (int i = 0; i < n; ++i) {
        for (auto &e : din.g[stu0 + i]) {
            if (e.to >= sch0 && e.to < sch0 + m && e.cap == 0) ans[i] = e.to - sch0 + 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}