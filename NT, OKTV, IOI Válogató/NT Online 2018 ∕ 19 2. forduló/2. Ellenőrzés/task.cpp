#include <bits/stdc++.h>
using namespace std;

/*
    Az értékek legfeljebb 100-félék lehetnek, ezért minden számhoz készítünk
    prefixösszeg tömböt. Egy Ai érték minden két szomszédos előfordulása között
    a Bi darabszáma így egyetlen kivonással megkapható. Minden (Ai, Bi) párra
    előre kiszámítjuk a legnagyobb ilyen darabszámot.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i) cin >> v[i];

    vector<vector<int>> pref(m + 1, vector<int>(n + 1, 0));
    for (int x = 1; x <= m; ++x) {
        for (int i = 1; i <= n; ++i) {
            pref[x][i] = pref[x][i - 1] + (v[i] == x);
        }
    }

    vector<vector<int>> pos(m + 1);
    for (int i = 1; i <= n; ++i) pos[v[i]].push_back(i);

    vector<vector<int>> ans(m + 1, vector<int>(m + 1, -1));
    for (int a = 1; a <= m; ++a) {
        if ((int)pos[a].size() < 2) continue;
        for (int idx = 0; idx + 1 < (int)pos[a].size(); ++idx) {
            int l = pos[a][idx];
            int r = pos[a][idx + 1];
            for (int b = 1; b <= m; ++b) {
                int cnt = pref[b][r - 1] - pref[b][l];
                ans[a][b] = max(ans[a][b], cnt);
            }
        }
    }

    while (k--) {
        int a, b;
        cin >> a >> b;
        cout << ans[a][b] << '\n';
    }
    return 0;
}
