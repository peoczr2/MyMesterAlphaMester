#include <bits/stdc++.h>
using namespace std;

/*
    A csoportok távolsága a rendezett pontszámok két egymást követő eleme közti
    rés. Ezért elég a sorozatot rendezni, majd a T-nél nagyobb legnagyobb rést
    megkeresni.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t;
    cin >> n >> m >> t;
    vector<int> e(n);
    for (int i = 0; i < n; ++i) cin >> e[i];
    sort(e.begin(), e.end());

    int ans = -1;
    for (int i = 0; i + 1 < n; ++i) {
        int gap = e[i + 1] - e[i];
        if (gap > t) ans = max(ans, gap);
    }
    cout << ans << '\n';
    return 0;
}
