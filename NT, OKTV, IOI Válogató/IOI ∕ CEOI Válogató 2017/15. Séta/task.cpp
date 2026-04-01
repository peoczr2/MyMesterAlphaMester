/*
Megoldás lényege:
Az útvonal során egy erősen összefüggő komponensen belül tetszőlegesen sok csúcsot
érinthetünk, mert a komponensen belül bármelyik pontból bármelyik másikba el lehet
jutni. Ezért a feladatot az SCC-k kondenzációs DAG-jára visszük le.

Minden SCC súlya a benne lévő csúcsok száma. A keresett válasz a DAG-on az A
komponensétől a B komponenséig vezető leghosszabb súlyú út súlya. Az SCC-ket
Kosaraju-algoritmussal határozzuk meg, majd topologikus sorrendben dinamikus
programozással számoljuk a maximumot.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, b;
    if (!(cin >> n >> m >> a >> b)) return 0;

    vector<vector<int>> g(n + 1), gr(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        gr[v].push_back(u);
    }

    vector<int> order, vis(n + 1, 0);
    order.reserve(n);
    for (int s = 1; s <= n; ++s) {
        if (vis[s]) continue;
        vector<pair<int, int>> st;
        st.push_back({s, 0});
        vis[s] = 1;
        while (!st.empty()) {
            int v = st.back().first;
            int &idx = st.back().second;
            if (idx == (int)g[v].size()) {
                order.push_back(v);
                st.pop_back();
                continue;
            }
            int to = g[v][idx++];
            if (!vis[to]) {
                vis[to] = 1;
                st.push_back({to, 0});
            }
        }
    }

    vector<int> comp(n + 1, -1), compSize;
    int cc = 0;
    for (int i = n - 1; i >= 0; --i) {
        int s = order[i];
        if (comp[s] != -1) continue;
        compSize.push_back(0);
        vector<int> st = {s};
        comp[s] = cc;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            ++compSize[cc];
            for (int to : gr[v]) {
                if (comp[to] == -1) {
                    comp[to] = cc;
                    st.push_back(to);
                }
            }
        }
        ++cc;
    }

    vector<vector<int>> dag(cc);
    vector<int> indeg(cc, 0);
    for (int v = 1; v <= n; ++v) {
        for (int to : g[v]) {
            int cv = comp[v], ct = comp[to];
            if (cv != ct) {
                dag[cv].push_back(ct);
            }
        }
    }
    for (int i = 0; i < cc; ++i) {
        sort(dag[i].begin(), dag[i].end());
        dag[i].erase(unique(dag[i].begin(), dag[i].end()), dag[i].end());
        for (int to : dag[i]) ++indeg[to];
    }

    vector<long long> dp(cc, -(1LL << 60));
    int sa = comp[a], sb = comp[b];
    dp[sa] = compSize[sa];

    queue<int> q;
    for (int i = 0; i < cc; ++i) if (indeg[i] == 0) q.push(i);
    vector<int> topo;
    topo.reserve(cc);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        topo.push_back(v);
        for (int to : dag[v]) {
            if (--indeg[to] == 0) q.push(to);
        }
    }

    for (int v : topo) {
        if (dp[v] < 0) continue;
        for (int to : dag[v]) {
            dp[to] = max(dp[to], dp[v] + compSize[to]);
        }
    }

    cout << dp[sb] << '\n';
    return 0;
}