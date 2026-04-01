#include <bits/stdc++.h>
using namespace std;

/*
    A zsákfalu olyan fokszám-1 csúcs, amelyből indulva a szűk, választási lehetőség
    nélküli szakaszok hossza maximalizálható. A gráfban a választási lehetőség nélküli
    szakaszok a fokszám-2 láncok; ezek hosszát minden levélből kiszámítjuk.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    vector<int> deg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
        ++deg[a];
        ++deg[b];
    }

    vector<int> leaves;
    for (int i = 1; i <= n; ++i) if (deg[i] == 1) leaves.push_back(i);
    if (leaves.empty()) {
        cout << -1 << '\n';
        return 0;
    }

    vector<int> bestFrom(n + 1, 0);
    int best = 0;
    vector<int> ans;
    for (int s : leaves) {
        int prev = -1, v = s, len = 0;
        while (true) {
            int next = -1;
            for (int to : g[v]) if (to != prev) { next = to; break; }
            if (next == -1) break;
            ++len;
            if (deg[next] != 2) break;
            prev = v;
            v = next;
        }
        if (len > best) {
            best = len;
            ans.clear();
            ans.push_back(s);
        } else if (len == best) {
            ans.push_back(s);
        }
    }

    sort(ans.begin(), ans.end());
    cout << best << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}