/*
Megoldás lényege:
Egy P pontra akkor van R-ből P-be és P-ből R-be vezető, csak a végpontjaikban közös két út, ha P és R rajta van egy közös körön, azaz ugyanabban a legalább két élű kétszeresen összefüggő blokkban vannak. A blokkokat Tarjan-féle DFS-sel keressük: a bejárás közben az éleket verembe tesszük, és ha egy u-v fa-élre low[v] >= disc[u], akkor a veremből az (u,v) élig kivett élek egy blokkot alkotnak. Mivel R a DFS gyökere, az R-et tartalmazó blokk pontosan az R-nél záródik, ezért csak az R-nél záródó, legalább két élű blokkok pontjait kell kiírni. Maga R triviálisan benne van a halmazban. Az időigény O(N+M), ami a bemenet olvasásával együtt elfér a 0.1 másodpercben.
*/
/*
Hint 1: || Egy P pont akkor jó, ha P és R rajta van egy közös körön, vagyis a gráfnak van olyan kétszeresen összefüggő része, amelyik mindkettőt tartalmazza. Keresd tehát a gráf kétszeresen összefüggő blokkjait. ||
Hint 2: || A Tarjan-algoritmus DFS-sel dolgozik: minden csúcsnak van egy sorszáma (disc) és egy low értéke, amely a részfából visszamutató élek legkisebb sorszáma. Az éleket tedd egy verembe, és a fa-élek mellett a visszamutató éleket is. ||
Hint 3: || Ha egy u-v fa-élnél low[v] >= disc[u], akkor a veremből az (u,v) élig kivett élek egy blokkot adnak. Ha u = R, akkor ez a blokk tartalmazza R-et, és csak a legalább két élű blokk pontjai jók. ||
Hint 4: || Az R pontot külön is vedd be a halmazba, a többi pont a blokkok alapján kerül be. A második sor tetszőleges sorrendben lehet, ezért nem kell rendezni, de a rendezés sem hiba. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m, r;
vector<vector<pair<int, int>>> adj;
vector<int> disc, low;
vector<pair<int, int>> st;
vector<char> ans;
int timer_ = 0;

void dfs(int u, int pe) {
    disc[u] = low[u] = ++timer_;
    for (auto [v, id] : adj[u]) {
        if (id == pe) continue;
        if (!disc[v]) {
            st.push_back({u, v});
            dfs(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] >= disc[u]) {
                vector<pair<int, int>> block;
                while (true) {
                    auto e = st.back();
                    st.pop_back();
                    block.push_back(e);
                    if (e == make_pair(u, v)) break;
                }
                if (u == r && block.size() >= 2)
                    for (auto [a, b] : block) ans[a] = ans[b] = 1;
            }
        } else if (disc[v] < disc[u]) {
            st.push_back({u, v});
            low[u] = min(low[u], disc[v]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> r;
    adj.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    disc.assign(n + 1, 0);
    low.assign(n + 1, 0);
    ans.assign(n + 1, 0);
    dfs(r, -1);
    ans[r] = 1;
    vector<int> res;
    for (int v = 1; v <= n; v++)
        if (ans[v]) res.push_back(v);
    cout << res.size() << '\n';
    for (size_t i = 0; i < res.size(); i++) cout << res[i] << (i + 1 < res.size() ? ' ' : '\n');
    return 0;
}
