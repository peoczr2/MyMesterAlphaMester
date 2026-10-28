/*
Megoldás lényege:
Egy v város akkor kap járatot, ha van 1-ből v-be vezető egyszerű út, amely átmegy legalább egy látványosság-élen. Az egyszerű utak a kétszeresen összefüggő komponensek (blokkok) blokk-vágópont fáján haladnak végig: a 1-ből v-be vezető fa-úton lévő blokkokon kell áthaladnia. Egy 2-összefüggő blokkon belül bármely két csúcs között van olyan egyszerű út, amely egy adott élen megy át, ezért elég azt tudni, hogy a fa-úton van-e olyan blokk, amely tartalmaz látványosság-élt. A blokkokat mélységi bejárással, éltveremmel és low-értékekkel kapjuk meg (O(N+M)), majd a blokk-vágópont fán BFS-sel terjesztjük a jelzőbitet a gyökérből. Az időigény O(N+M).
*/
/*
Hint 1: || Egy egyszerű úton akkor megy át látványosság-él, ha az 1-ből v-be vezető blokk-fa úton van olyan blokk, amely tartalmaz látványosság-élt. Egy 2-összefüggő blokkon belül bármely két csúcs között van olyan út, amely a kívánt élen megy át. ||
Hint 2: || Keresd meg a kétszeresen összefüggő komponenseket (blokkokat) mélységi bejárással: a low-értékekkel és egy éltveremmel gyűjtsd össze minden blokk éleit. Ha egy gyermek low-értéke nem kisebb a szülő discovery-idejénél, a szülőtől lefelé lévő élek egy blokkot alkotnak. ||
Hint 3: || A blokkokat és csúcsokat összekötve blokk-vágópont fát kapsz. Ebben a gyökérből BFS-sel terjeszd: a blokkon áthaladva a látványosság-jelzés VAGY-kapcsolattal öröklődik a csúcsokra, és a jelzett csúcsok (az 1-es kivételével) a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;
    vector<int> A(M), B(M);
    vector<vector<pair<int, int>>> adj(N + 1);
    for (int e = 0; e < M; e++) {
        cin >> A[e] >> B[e];
        adj[A[e]].push_back({B[e], e});
        adj[B[e]].push_back({A[e], e});
    }

    // Blokkok (kétszeresen összefüggő komponensek) iteratív Tarjan-algoritmussal, az 1-ből elérhető részen.
    vector<int> disc(N + 1, 0), low(N + 1, 0), itp(N + 1, 0), parentEdge(N + 1, -1);
    vector<int> estack, dfs;
    vector<char> sight;                 // sight[b]: a b blokk tartalmaz látványosság-élt
    vector<vector<int>> bverts;         // bverts[b]: a b blokk csúcsai
    vector<int> stamp(N + 1, -1);
    int timer = 0;

    disc[1] = low[1] = ++timer;
    dfs.push_back(1);
    while (!dfs.empty()) {
        int u = dfs.back();
        if (itp[u] < (int)adj[u].size()) {
            auto [v, eid] = adj[u][itp[u]++];
            if (eid == parentEdge[u]) continue;
            if (disc[v] == 0) {
                parentEdge[v] = eid;
                estack.push_back(eid);
                disc[v] = low[v] = ++timer;
                dfs.push_back(v);
            } else if (disc[v] < disc[u]) {
                // hátsó él
                estack.push_back(eid);
                low[u] = min(low[u], disc[v]);
            }
        } else {
            dfs.pop_back();
            if (!dfs.empty()) {
                int p = dfs.back();
                low[p] = min(low[p], low[u]);
                if (low[u] >= disc[p]) {
                    // a p-től u-ig tartó blokk éleit kivesszük a veremből
                    int bid = (int)sight.size();
                    sight.push_back(0);
                    bverts.emplace_back();
                    while (true) {
                        int e = estack.back();
                        estack.pop_back();
                        if (e < K) sight[bid] = 1;
                        for (int x : {A[e], B[e]}) {
                            if (stamp[x] != bid) {
                                stamp[x] = bid;
                                bverts[bid].push_back(x);
                            }
                        }
                        if (e == parentEdge[u]) break;
                    }
                }
            }
        }
    }

    // Csúcs -> blokkok leképezés a blokk-vágópont fa éleihez.
    int nb = (int)sight.size();
    vector<vector<int>> vb(N + 1);
    for (int b = 0; b < nb; b++)
        for (int x : bverts[b]) vb[x].push_back(b);

    // BFS a blokk-vágópont fán, a gyökér az 1-es csúcs. A jelzőbit VAGY-kapcsolattal öröklődik.
    vector<char> vis(N + 1, 0), flag(N + 1, 0), bvis(nb, 0);
    queue<int> q;
    vis[1] = 1;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int b : vb[u]) {
            if (bvis[b]) continue;
            bvis[b] = 1;
            char fb = flag[u] | sight[b];
            for (int w : bverts[b]) {
                if (!vis[w]) {
                    vis[w] = 1;
                    flag[w] = fb;
                    q.push(w);
                }
            }
        }
    }

    vector<int> ans;
    for (int v = 2; v <= N; v++)
        if (vis[v] && flag[v]) ans.push_back(v);

    cout << ans.size() << '\n';
    for (size_t i = 0; i < ans.size(); i++) {
        cout << ans[i] << (i + 1 == ans.size() ? '\n' : ' ');
    }
    if (ans.empty()) cout << '\n';
    return 0;
}
