/*
Megoldás lényege:
Egy oázisból akkor juthat el áru az összes többibe, ha a karavánok irányított gráfjában onnan minden csúcs elérhető. Ha ilyen oázis van, akkor vele kölcsönösen elérhető, és így ugyanazokat az oázisokat éri el, mint a többi jó oázis, ezért elég egyetlen jó oázist megtalálni. Jelöltnek a mélységi bejárás utolsó gyökerét választjuk: ha van jó oázis, a jelölt is jó lesz. A jelöltből egy BFS megmondja, minden oázis elérhető-e (ha nem, nincs megoldás), a jó oázisok pedig azok, amelyekből a jelölt elérhető; ezt a fordított élekkel induló BFS adja. Az időigény O(N + M).
*/
/*
Hint 1: || Ha egy oázisból minden más elérhető, akkor azok az oázisok is jók, amelyekből ez az oázis elérhető, mert az elérhetőség tranzitív. Így a jó oázisok halmaza egyetlen jó oázis ismeretében visszafelé gyűjthető össze. ||
Hint 2: || Mélységi bejárást indíts sorban minden még nem látott csúcsból, és az utoljára indított bejárás gyökerét tekintsd jelöltnek: ha van jó csúcs, a jelölt is jó lesz. ||
Hint 3: || A jelöltből BFS-sel ellenőrizd, hogy minden csúcs elérhető-e (ha nem, a válasz -1). Ha igen, a jó csúcsok azok, amelyekből a jelölt elérhető: ezt a BFS-t a fordított élek mentén futtasd. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g, rg;
vector<char> vis;

// Mélységi bejárás a g gráfon.
void dfs(int v) {
    vis[v] = 1;
    for (int w : g[v])
        if (!vis[w]) dfs(w);
}

// BFS: a s csúcsból elérhető csúcsokat jelöli az adj gráfon.
vector<char> bfs(const vector<vector<int>> &adj, int s) {
    int n = adj.size() - 1;
    vector<char> seen(n + 1, 0);
    queue<int> q;
    seen[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int w : adj[v])
            if (!seen[w]) {
                seen[w] = 1;
                q.push(w);
            }
    }
    return seen;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    g.assign(n + 1, {});
    rg.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    // Jelölt: az utoljára indított mélységi bejárás gyökere.
    vis.assign(n + 1, 0);
    int cand = 1;
    for (int v = 1; v <= n; ++v)
        if (!vis[v]) {
            dfs(v);
            cand = v;
        }

    vector<char> fromCand = bfs(g, cand);
    for (int v = 1; v <= n; ++v)
        if (!fromCand[v]) {
            cout << -1 << '\n';
            return 0;
        }

    vector<char> toCand = bfs(rg, cand);
    bool first = true;
    for (int v = 1; v <= n; ++v)
        if (toCand[v]) {
            if (!first) cout << ' ';
            cout << v;
            first = false;
        }
    cout << '\n';
    return 0;
}
