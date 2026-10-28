/*
Megoldás lényege:
A központból (1) minden csúcs pontosan egy egyszerű úton érhető el, ezért az 1-ből induló bejárás fája egy gyökeres fa, a többi él pedig olyan visszaél, amely egy ősére mutat. Minden visszaélt pontosan egyszer használunk. Egy szülő-gyerek fa-élt annyiszor kell bevenni, ahány visszaél vezet a gyerek részfájából a gyerek szülőjénél magasabbra. Ezzel a kiegészített élhalmazban minden csúcs befoka megegyezik a kifokával, és az élhalmaz összefüggő, így van 1-ből induló és 1-be érkező Euler-körút. Ezt Hierholzer-algoritmussal keressük. A részfa-összegek és a bejárás O(N+M) idejűek, a körséta hossza legfeljebb M+N.
*/
/*
Hint 1: || A központból minden csúcs egyetlen úton érhető el, ezért az 1-ből induló bejárás fája egy gyökeres fát ad, a többi él pedig mind olyan visszaél, amely egy ősére mutat. ||
Hint 2: || Minden csúcsnál számold ki, hány visszaél indul ki belőle és hány érkezik bele, majd a részfákban ezeket összegezve megkapod, hány példányban kell a szülő-gyerek élt bevenni. ||
Hint 3: || Ha a visszaéleket egyszer, a fa-éleket pedig a fenti példányszámmal veszed, minden csúcsban befok = kifok lesz, így Hierholzer-algoritmussal kapsz 1-ből induló és 1-be érkező Euler-körutat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    vector<vector<int>> adj(n + 1);
    for (auto &e : edges) {
        cin >> e.first >> e.second;
        adj[e.first].push_back(e.second);
    }

    // BFS a központból: a fa a csúcsok egyetlen-úti fája.
    vector<int> par(n + 1, 0), order;
    vector<bool> seen(n + 1, false);
    order.push_back(1);
    seen[1] = true;
    for (size_t i = 0; i < order.size(); ++i) {
        int u = order[i];
        for (int w : adj[u]) {
            if (!seen[w]) {
                seen[w] = true;
                par[w] = u;
                order.push_back(w);
            }
        }
    }

    // A visszaélek használata; g[v] = visszaélek kifoka - befoka.
    vector<pair<int, int>> walkEdges;
    vector<long long> g(n + 1, 0);
    for (auto [u, v] : edges) {
        if (par[v] == u) continue;  // fa-él
        walkEdges.push_back({u, v});
        g[u]++;
        g[v]--;
    }

    // g részfa-összege: hány visszaél lép ki a részfából a gyerek szülője fölé.
    for (int i = (int)order.size() - 1; i >= 1; --i) {
        int v = order[i];
        g[par[v]] += g[v];
    }

    // A szülő -> gyerek fa-élt g[v]-szer vesszük be.
    for (int i = 1; i < (int)order.size(); ++i) {
        int v = order[i];
        for (long long k = 0; k < g[v]; ++k) walkEdges.push_back({par[v], v});
    }

    // Hierholzer: Euler-körút 1-ből.
    int K = walkEdges.size();
    vector<vector<int>> out(n + 1);
    for (int i = 0; i < K; ++i) out[walkEdges[i].first].push_back(i);
    vector<int> ptr(n + 1, 0), st{1}, circ;
    while (!st.empty()) {
        int u = st.back();
        if (ptr[u] < (int)out[u].size()) {
            int e = out[u][ptr[u]++];
            st.push_back(walkEdges[e].second);
        } else {
            circ.push_back(u);
            st.pop_back();
        }
    }
    reverse(circ.begin(), circ.end());

    for (size_t i = 0; i < circ.size(); ++i) {
        if (i) cout << ' ';
        cout << circ[i];
    }
    cout << '\n';
    return 0;
}
