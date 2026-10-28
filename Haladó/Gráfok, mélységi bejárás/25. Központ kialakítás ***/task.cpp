/*
Megoldás lényege:
A kérdés az, hány új irányított élt kell húzni ahhoz, hogy a központból minden csúcs elérhető legyen. Az erősen összefüggő komponensekre bontással (Kosaraju-algoritmus, két mélységi bejárással) a gráf kondenzált DAG-ra egyszerűsödik. Ha egy komponensbe a többi komponensből egyetlen él sem vezet, akkor oda csak új él vezethet, és ezek száma adja a minimumot. Mindegyik ilyen komponensbe egy új élt húzunk a központból egy tetszőleges csúcsába. A központ komponensét nem kell figyelembe venni. Az időigény O(N), mert a gráf csak N csúcsot és 2N élt tartalmaz.
*/
/*
Hint 1: || Gondold meg, miért kell minden olyan erősen összefüggő komponensnek új bejövő élet kapnia, amelybe a többi komponensből nem vezet él, és amely nem érhető el a központból. ||
Hint 2: || Erősen összefüggő komponensekre bontás (Kosaraju: mélységi bejárás a kifutási sorrendhez, majd a fordított gráfon bejárás) után a bejövő él nélküli komponensek száma adja a választ. ||
Hint 3: || Minden ilyen komponensbe húzz egy új élt a központból egy tetszőleges csúcsába, a központ saját komponensét hagyd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, ctr;
    cin >> n >> ctr;
    vector<vector<int>> g(n + 1), rg(n + 1);
    for (int i = 1; i <= n; ++i) {
        int u, v;
        if (!(cin >> u >> v)) break;
        if (u < 1 || u > n || v < 1 || v > n) continue;
        g[i].push_back(u);
        g[i].push_back(v);
        rg[u].push_back(i);
        rg[v].push_back(i);
    }

    // 1. mélységi bejárás: kifutási sorrend.
    vector<int> order;
    vector<char> vis(n + 1, 0);
    for (int s = 1; s <= n; ++s) {
        if (vis[s]) continue;
        vector<pair<int, int>> st;
        st.push_back({s, 0});
        vis[s] = 1;
        while (!st.empty()) {
            int v = st.back().first;
            if (st.back().second < (int)g[v].size()) {
                int w = g[v][st.back().second++];
                if (!vis[w]) {
                    vis[w] = 1;
                    st.push_back({w, 0});
                }
            } else {
                order.push_back(v);
                st.pop_back();
            }
        }
    }

    // 2. bejárás a fordított gráfon, a kifutási sorrend fordítottjában: komponensek.
    vector<int> comp(n + 1, -1);
    int C = 0;
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int s = order[i];
        if (comp[s] != -1) continue;
        vector<int> st{s};
        comp[s] = C;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            for (int w : rg[v]) {
                if (comp[w] == -1) {
                    comp[w] = C;
                    st.push_back(w);
                }
            }
        }
        ++C;
    }

    // Van-e bejövő él másik komponensből.
    vector<char> hasIn(C, 0);
    for (int u = 1; u <= n; ++u) {
        for (int v : g[u]) {
            if (comp[u] != comp[v]) hasIn[comp[v]] = 1;
        }
    }

    // Minden bejövő él nélküli, nem a központ komponensébe tartozó komponensből egy új él a központból.
    vector<int> rep(C, INT_MAX);
    for (int v = 1; v <= n; ++v) {
        if (rep[comp[v]] == INT_MAX) rep[comp[v]] = v;
    }
    vector<int> added;
    for (int v = 1; v <= n; ++v) {
        int c = comp[v];
        if (v == rep[c] && c != comp[ctr] && !hasIn[c]) added.push_back(v);
    }

    cout << added.size() << '\n';
    for (int v : added) cout << ctr << ' ' << v << '\n';
    return 0;
}
