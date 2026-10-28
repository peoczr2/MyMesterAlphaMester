/*
Megoldás lényege:
A gráf erősen összefüggő komponenseit Tarjan-algoritmussal határozzuk meg, iteratívan, hogy a mély láncok se okozzanak veremtúlcsordulást. Egy komponenst nyelőnek nevezünk, ha egyetlen pontjából sem vezet él másik komponensbe. Egy nyelő komponens pontjaiból csak a saját komponensük pontjai érhetők el, ezért minden nyelőből legalább egy pontot be kell venni a C halmazba. Fordítva, a komponensekből álló gráf körmentes, ezért minden pontból van út legalább egy nyelő komponensbe, és a komponens erősen összefüggő, így bármelyik pontja elérhető belőle. A minimum tehát a nyelő komponensek száma, és mindegyikből egy pont (a legkisebb sorszámú) elég. Az időigény O(N + M).
*/
/*
Hint 1: || Ha egy komponensből nem vezet él kifelé, a komponens pontjai csak egymást érik el. Ezért minden ilyen komponensből kell legalább egy pont a C halmazba. ||
Hint 2: || Az erősen összefüggő komponenseket Tarjan-algoritmussal keresd meg. Utána minden élre nézd meg, hogy a két végpontja különböző komponensbe esik-e: ha igen, az élt kiinduló komponens nem nyelő. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    vector<pair<int, int>> edges(m);
    for (auto &[u, v] : edges) {
        cin >> u >> v;
        g[u].push_back(v);
    }

    // Tarjan-algoritmus, iteratív változatban
    vector<int> idx(n + 1, 0), low(n + 1, 0), it(n + 1, 0), comp(n + 1, -1);
    vector<char> onStack(n + 1, 0);
    vector<int> stk;
    int timer = 0, compCnt = 0;
    for (int s = 1; s <= n; ++s) {
        if (idx[s]) continue;
        vector<int> call{s};
        idx[s] = low[s] = ++timer;
        stk.push_back(s);
        onStack[s] = 1;
        while (!call.empty()) {
            int v = call.back();
            if (it[v] < (int)g[v].size()) {
                int w = g[v][it[v]++];
                if (!idx[w]) {
                    idx[w] = low[w] = ++timer;
                    stk.push_back(w);
                    onStack[w] = 1;
                    call.push_back(w);
                } else if (onStack[w]) {
                    low[v] = min(low[v], idx[w]);
                }
            } else {
                call.pop_back();
                if (!call.empty()) low[call.back()] = min(low[call.back()], low[v]);
                if (low[v] == idx[v]) {
                    int w;
                    do {
                        w = stk.back();
                        stk.pop_back();
                        onStack[w] = 0;
                        comp[w] = compCnt;
                    } while (w != v);
                    ++compCnt;
                }
            }
        }
    }

    // Nyelő komponens: nincs belőle él másik komponensbe
    vector<char> hasOut(compCnt, 0);
    for (auto [u, v] : edges)
        if (comp[u] != comp[v]) hasOut[comp[u]] = 1;

    vector<int> rep(compCnt, INT_MAX);
    for (int v = 1; v <= n; ++v) rep[comp[v]] = min(rep[comp[v]], v);

    vector<int> ans;
    for (int c = 0; c < compCnt; ++c)
        if (!hasOut[c]) ans.push_back(rep[c]);
    sort(ans.begin(), ans.end());

    cout << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << "\n";
    return 0;
}
