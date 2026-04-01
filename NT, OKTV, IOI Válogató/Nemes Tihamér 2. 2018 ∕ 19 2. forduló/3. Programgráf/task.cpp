#include <bits/stdc++.h>
using namespace std;

/*
    Kosaraju-val erősen összefüggő komponensekre bontjuk a gráfot.
    Egy kétkimenetű csomópont ciklust jelez, ha van olyan utódja, amely ugyanabba
    az SCC-be tartozik; különben elágazás.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1), rg(n + 1);
    vector<int> outdeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        rg[v].push_back(u);
        ++outdeg[u];
    }

    vector<int> vis(n + 1, 0), order;
    order.reserve(n);
    for (int s = 1; s <= n; ++s) {
        if (vis[s]) continue;
        stack<pair<int, int>> st;
        st.push({s, 0});
        vis[s] = 1;
        while (!st.empty()) {
            auto& [u, it] = st.top();
            if (it < (int)g[u].size()) {
                int v = g[u][it++];
                if (!vis[v]) {
                    vis[v] = 1;
                    st.push({v, 0});
                }
            } else {
                order.push_back(u);
                st.pop();
            }
        }
    }

    vector<int> comp(n + 1, 0);
    int cc = 0;
    for (int idx = n - 1; idx >= 0; --idx) {
        int s = order[idx];
        if (comp[s]) continue;
        ++cc;
        stack<int> st;
        st.push(s);
        comp[s] = cc;
        while (!st.empty()) {
            int u = st.top();
            st.pop();
            for (int v : rg[u]) {
                if (!comp[v]) {
                    comp[v] = cc;
                    st.push(v);
                }
            }
        }
    }

    int cycles = 0, branches = 0;
    for (int u = 1; u <= n; ++u) {
        if (outdeg[u] != 2) continue;
        bool cyc = false;
        for (int v : g[u]) if (comp[v] == comp[u]) cyc = true;
        if (cyc) ++cycles;
        else ++branches;
    }

    cout << cycles << '\n' << branches << '\n';
    return 0;
}