/*
Megoldás lényege:
A gráf erősen összefüggő komponenseit Kosaraju-algoritmussal határozzuk meg. Mivel bármely két csúcs között legfeljebb egy út van, a komponensek közötti élek fát alkotnak: minden nem gyökér komponensbe pontosan egy él vezet be, a gyökérből minden komponens elérhető. Egy csúcsból elérhető csúcsok száma így a csúcs komponensének és a fában alatta lévő komponensek méretének összege, amit a fa visszafelé bejárásával kapunk. Az erősen összefüggé tételhez minden olyan nem gyökér komponensre, amelynek belépési csúcsából nem indul kimenő fa-él, egy új él kell; ezek száma adja a minimális K-t. A fa-éleket láncokba fűzzük úgy, hogy egy láncban a belépési csúcsnál a következő él a belépési csúcsból induljon, és minden láncnak egy új él felel meg: a lánc alsó élének feje felől a felső él farkába. Az időigény O(N+M).
*/
/*
Hint 1: || Az erősen összefüggő komponensek közötti élek fát alkotnak, mert két csúcs között legfeljebb egy út van. Egy csúcsból elérhető csúcsok száma így a saját komponens méretének és a fában lefelé lévő komponensek méreteinek összege. ||
Hint 2: || Minden nem gyökér komponensnek egyetlen bejövő fa-éle van, ami egy belépési csúcsba fut. Ha ebből a belépési csúcsból nem indul kimenő fa-él, ott új élnek kell kiindulnia; a többi komponens az ilyen komponensek számából kiszámolható. ||
Hint 3: || Építs láncokat a fa-élekből: egy élről a belépési csúcs kimenő élére lépj tovább, amíg lehet. Minden láncra pontosan egy új él kell: a lánc utolsó élének fejéből a lánc első élének farkába. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, r;
    cin >> n >> m >> r;
    vector<pair<int, int>> edges(m);
    for (auto &e : edges) cin >> e.first >> e.second;
    sort(edges.begin(), edges.end());
    edges.erase(unique(edges.begin(), edges.end()), edges.end());

    vector<vector<int>> g(n + 1), rg(n + 1);
    for (auto [p, q] : edges) {
        g[p].push_back(q);
        rg[q].push_back(p);
    }

    // 1. Kosaraju: befejezési sorrend a gráfon
    vector<int> order;
    order.reserve(n);
    vector<char> seen(n + 1, 0);
    for (int s = 1; s <= n; s++) {
        if (seen[s]) continue;
        vector<pair<int, int>> st;  // (csúcs, következő kimenő él sorszáma)
        st.push_back({s, 0});
        seen[s] = 1;
        while (!st.empty()) {
            int v = st.back().first;
            int idx = st.back().second;
            if (idx < (int)g[v].size()) {
                st.back().second++;
                int u = g[v][idx];
                if (!seen[u]) {
                    seen[u] = 1;
                    st.push_back({u, 0});
                }
            } else {
                order.push_back(v);
                st.pop_back();
            }
        }
    }

    // 2. Komponensek: a fordított gráfon, befejezési sorrend szerint visszafelé
    vector<int> comp(n + 1, -1);
    int C = 0;
    for (int i = n - 1; i >= 0; i--) {
        int s = order[i];
        if (comp[s] != -1) continue;
        vector<int> stk = {s};
        comp[s] = C;
        while (!stk.empty()) {
            int v = stk.back();
            stk.pop_back();
            for (int u : rg[v])
                if (comp[u] == -1) {
                    comp[u] = C;
                    stk.push_back(u);
                }
        }
        C++;
    }

    vector<long long> sz(C, 0);
    for (int v = 1; v <= n; v++) sz[comp[v]]++;

    // 3. Komponensek közötti élek: a fa élei
    int root = comp[r];
    vector<pair<int, int>> te;  // (tail, head), a komponensek különbözők
    for (auto [p, q] : edges)
        if (comp[p] != comp[q]) te.push_back({p, q});

    vector<int> headv(C, 0);       // belépési csúcs (a bejövő fa-él feje)
    vector<vector<int>> child(C);  // gyermek komponensek
    for (auto [p, q] : te) {
        headv[comp[q]] = q;
        child[comp[p]].push_back(comp[q]);
    }

    // 4. Elérhető csúcsok száma: a fa részfáinak méretösszege
    vector<int> bfs = {root};
    for (size_t i = 0; i < bfs.size(); i++)
        for (int c : child[bfs[i]]) bfs.push_back(c);
    vector<long long> reach(C, 0);
    for (int i = (int)bfs.size() - 1; i >= 0; i--) {
        int c = bfs[i];
        reach[c] = sz[c];
        for (int d : child[c]) reach[c] += reach[d];
    }

    // 5. Minden nem gyökér komponensből a belépési csúcsból választunk egy kimenő fa-élt
    vector<int> sel(C, -1);
    for (int i = 0; i < (int)te.size(); i++) {
        int p = te[i].first;
        int cp = comp[p];
        if (cp != root && p == headv[cp] && sel[cp] == -1) sel[cp] = i;
    }

    // 6. Láncok: minden lánc egy új éllel zárul
    vector<pair<int, int>> add;
    for (int i = 0; i < (int)te.size(); i++) {
        int p = te[i].first;
        int cp = comp[p];
        if (sel[cp] == i) continue;  // ennek a fa-élnek van elődje a láncban
        int cur = i;
        while (true) {
            int cq = comp[te[cur].second];
            if (sel[cq] == -1) break;
            cur = sel[cq];
        }
        add.push_back({te[cur].second, p});
    }

    // 7. Kiírás
    for (int v = 1; v <= n; v++) {
        cout << reach[comp[v]] << (v == n ? '\n' : ' ');
    }
    cout << add.size() << '\n';
    for (auto [u, v] : add) cout << u << ' ' << v << '\n';
    return 0;
}
