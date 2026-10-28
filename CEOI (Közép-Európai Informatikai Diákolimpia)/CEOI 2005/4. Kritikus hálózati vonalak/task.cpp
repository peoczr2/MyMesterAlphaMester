/*
Megoldás lényege:
Ha egy vonal nem híd (a gráf nem esik szét a törlésétől), a törlés után a hálózat továbbra is összefüggő, így minden csomópont elér minden szolgáltatást, tehát az ilyen vonal nem kritikus. Híd törlése a gráfot két részre bontja: a vonal akkor kritikus, ha valamelyik részben nincs A-típusú vagy nincs B-típusú csomópont. A hidakat Tarjan-féle low-link bejárással keressük (iteratív mélységi keresés, hogy nagy N esetén se legyen mélységi túlcsordulás), és a DFS-fa minden részfájában összeszámoljuk az A- és B-csomópontokat. Az időigény O(N + M), a memóriaigény O(N + M).
*/
/*
Hint 1: || Csak a hidak lehetnek kritikusok: egy kör élének törlése után a gráf összefüggő marad. Keresd meg a gráf hídjait. ||
Hint 2: || Egy híd törlése után két komponens keletkezik. A híd kritikus, ha valamelyik komponensben nincs A-típusú vagy nincs B-típusú csomópont, ezért elég a két komponens A- és B-darabszámát ismerni. ||
Hint 3: || Mélységi bejárásban minden csomóponthoz tárold a belépési sorszámot (tin) és a low értéket, vagyis a részfából visszaélen elérhető legkisebb tin-t. A (p, c) fa-él akkor híd, ha low[c] > tin[p]. A részfák A/B-számlálóit a visszatéréskor add össze a szülőhöz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, l;
    cin >> n >> m >> k >> l;

    vector<int> isA(n + 1, 0), isB(n + 1, 0);
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        isA[x] = 1;
    }
    for (int i = 0; i < l; i++) {
        int x;
        cin >> x;
        isB[x] = 1;
    }
    int totA = 0, totB = 0;
    for (int v = 1; v <= n; v++) {
        totA += isA[v];
        totB += isB[v];
    }

    vector<int> eu(m), ev(m), deg(n + 2, 0);
    for (int i = 0; i < m; i++) {
        cin >> eu[i] >> ev[i];
        deg[eu[i]]++;
        deg[ev[i]]++;
    }

    // Szomszédsági lista (CSR): a v csomópont élei adj[off[v] .. off[v+1]-1].
    vector<int> off(n + 2, 0);
    for (int v = 1; v <= n; v++) off[v + 1] = off[v] + deg[v];
    vector<int> adj(2 * m);
    vector<int> fillPos(off.begin(), off.end());
    for (int i = 0; i < m; i++) {
        adj[fillPos[eu[i]]++] = i;
        adj[fillPos[ev[i]]++] = i;
    }

    vector<int> tin(n + 1, 0), low(n + 1, 0), parEdge(n + 1, -1), par(n + 1, 0), it(n + 1, 0);
    vector<int> cntA(n + 1, 0), cntB(n + 1, 0);
    vector<int> critical;

    int timer = 0;
    vector<int> st;
    st.reserve(n + 1);

    // A hálózat összefüggő, így az 1-es csomópontból indított bejárás mindent elér.
    tin[1] = low[1] = ++timer;
    cntA[1] = isA[1];
    cntB[1] = isB[1];
    it[1] = off[1];
    st.push_back(1);

    while (!st.empty()) {
        int v = st.back();
        if (it[v] < off[v + 1]) {
            int e = adj[it[v]++];
            if (e == parEdge[v]) continue;
            int u = eu[e] ^ ev[e] ^ v;
            if (tin[u]) {
                low[v] = min(low[v], tin[u]);
            } else {
                tin[u] = low[u] = ++timer;
                parEdge[u] = e;
                par[u] = v;
                cntA[u] = isA[u];
                cntB[u] = isB[u];
                it[u] = off[u];
                st.push_back(u);
            }
        } else {
            st.pop_back();
            int p = par[v];
            if (p != 0) {
                low[p] = min(low[p], low[v]);
                cntA[p] += cntA[v];
                cntB[p] += cntB[v];
                if (low[v] > tin[p]) {
                    // A (p, v) híd: a v részfája az egyik komponens.
                    bool bad = cntA[v] == 0 || cntB[v] == 0 ||
                               totA - cntA[v] == 0 || totB - cntB[v] == 0;
                    if (bad) critical.push_back(parEdge[v]);
                }
            }
        }
    }

    cout << critical.size() << '\n';
    for (int e : critical) cout << eu[e] << ' ' << ev[e] << '\n';
    return 0;
}
