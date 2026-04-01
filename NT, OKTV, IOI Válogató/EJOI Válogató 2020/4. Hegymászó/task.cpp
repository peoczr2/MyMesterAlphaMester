/*
Megoldas: a graf aciklikus, mert minden él kisebb csucsbol nagyobba megy. Ezert
topologikus DP-vel megszamoljuk, hany ut vezet minden csucsba a forrasoktol. A
vonalak szama a sarkok kozotti osszes ut, vagyis a kilepo csucsokba eso darabok
osszege modulo 721.
*/

#include <bits/stdc++.h>
using namespace std;

static const int MOD = 721;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> pred(n + 1);
    vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        pred[v].push_back(u);
        ++indeg[v];
        ++outdeg[u];
    }

    vector<int> ways(n + 1, 0);
    for (int v = 1; v <= n; ++v) {
        if (indeg[v] == 0) ways[v] = 1;
        for (int u : pred[v]) {
            ways[v] += ways[u];
            if (ways[v] >= MOD) ways[v] %= MOD;
        }
    }

    int ans = 0;
    for (int v = 1; v <= n; ++v) {
        if (outdeg[v] == 0) {
            ans += ways[v];
            if (ans >= MOD) ans %= MOD;
        }
    }

    cout << ans % MOD << '\n';
    return 0;
}
