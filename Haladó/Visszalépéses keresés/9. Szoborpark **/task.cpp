/*
Hungarian megoldás: az egyszerű utak számát DFS-sel számoljuk meg a bejárattól
Árpád szobráig, miközben egy csúcsot legfeljebb egyszer látogatunk.

Hint 1: || Minden út egyszerű út, tehát a bejárt csúcsokat jelölni kell. ||
Hint 2: || A keresés a célcsúcs elérésénél egy útat számol. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n, m, b, a;
vector<vector<int>> g;
vector<char> vis;
long long ans = 0;

void dfs(int v) {
    if (v == a) {
        ++ans;
        return;
    }
    vis[v] = 1;
    for (int to : g[v]) if (!vis[to]) dfs(to);
    vis[v] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> b >> a;
    g.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vis.assign(n + 1, 0);
    dfs(b);
    cout << ans << '\n';
    return 0;
}