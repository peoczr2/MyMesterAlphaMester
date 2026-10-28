/*
Megoldás lényege:
Egy csúcs pontosan akkor van körben, ha rajta van nem híd él, ezért a hidak elhagyása után a csúcs 2-élösszefüggő komponense legalább 2 csúcsú. A körben nem lévő csúcsok tehát az egyelemű komponensek. A komponenseket a hidakkal összekötve fát kapunk, és egy új él e fa egy útját körbe zárja, így a feladat a fa egyelemű komponenseit lefedő legkevesebb út megkeresése. Ha a lefedendő csúcsok Steiner-részfájának L levele van, legalább ceil(L/2) út kell, és a levelek DFS-sorrendben i-t az i+ceil(L/2)-edik levéllel párosítva ez el is érhető. Az időigény a hidakra és a komponensekre O(N+M), a párosítás az N csúcsú szomszédsági mátrix miatt legfeljebb O(N^2).
*/
/*
Hint 1: || Egy csúcs pontosan akkor van körben, ha van hozzá kapcsolódó olyan él, amely nem híd. Keresd meg a gráf hidait Tarjan low-link módszerével. ||
Hint 2: || A hidak elhagyása után kapott összefüggő részek a kétszeresen összefüggő komponensek. Az egyelemű komponens csúcsai nincsenek körben, és a hidakból a komponensek közt fa épül. ||
Hint 3: || Ha a fa levelei l_0 ... l_(L-1) DFS-sorrendben, és m = ceil(L/2), akkor a párosítás: páratlan L esetén a végére még tedd l_0-t, majd az i-edik és az (i+m)-edik elemet kösd össze, i = 0 ... m-1. Egy új él végpontja mindig más, még nem szomszédos csúcs legyen. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<pair<int, int>>> adj;
vector<pair<int, int>> ed;
vector<char> isBridge;
vector<int> dsc, lw;
int tmr = 0;
vector<vector<char>> g;
int C;
vector<int> comp;
vector<vector<int>> mem, tadj;
vector<int> par, cnt;
vector<pair<int, int>> added;

void findBridges(int u, int pe) {
    dsc[u] = lw[u] = ++tmr;
    for (auto [v, id] : adj[u]) {
        if (id == pe) continue;
        if (dsc[v]) {
            lw[u] = min(lw[u], dsc[v]);
        } else {
            findBridges(v, id);
            lw[u] = min(lw[u], lw[v]);
            if (lw[v] > dsc[u]) isBridge[id] = 1;
        }
    }
}

bool treeAdj(int u, int v) { return par[u] == v || par[v] == u; }

void addPair(int u, int v) {
    if (treeAdj(u, v) && mem[u].size() == 1 && mem[v].size() == 1) {
        int w = -1;
        for (int x : tadj[v])
            if (x != u) { w = x; break; }
        if (w != -1) {
            v = w;
        } else {
            for (int x : tadj[u])
                if (x != v) { u = x; break; }
        }
    }
    for (int a : mem[u])
        for (int b : mem[v])
            if (!g[a][b]) {
                added.push_back({a, b});
                g[a][b] = g[b][a] = 1;
                return;
            }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    adj.assign(n + 1, {});
    ed.resize(m);
    g.assign(n + 1, vector<char>(n + 1, 0));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        ed[i] = {u, v};
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        g[u][v] = g[v][u] = 1;
    }
    dsc.assign(n + 1, 0);
    lw.assign(n + 1, 0);
    isBridge.assign(m, 0);
    findBridges(1, -1);

    comp.assign(n + 1, -1);
    C = 0;
    for (int s = 1; s <= n; s++) {
        if (comp[s] != -1) continue;
        mem.push_back({});
        queue<int> q;
        q.push(s);
        comp[s] = C;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            mem[C].push_back(u);
            for (auto [v, id] : adj[u]) {
                if (isBridge[id] || comp[v] != -1) continue;
                comp[v] = C;
                q.push(v);
            }
        }
        C++;
    }

    tadj.assign(C, {});
    for (int i = 0; i < m; i++)
        if (isBridge[i]) {
            int a = comp[ed[i].first], b = comp[ed[i].second];
            tadj[a].push_back(b);
            tadj[b].push_back(a);
        }

    vector<int> bad;
    for (int c = 0; c < C; c++)
        if (mem[c].size() == 1) bad.push_back(mem[c][0]);
    int K = bad.size();
    if (K == 0) {
        cout << "0\n\n0\n";
        return 0;
    }

    int root = comp[bad[0]];
    par.assign(C, -1);
    cnt.assign(C, 0);
    vector<int> order{root};
    vector<char> seen(C, 0);
    seen[root] = 1;
    for (size_t i = 0; i < order.size(); i++) {
        int c = order[i];
        for (int d : tadj[c])
            if (!seen[d]) {
                seen[d] = 1;
                par[d] = c;
                order.push_back(d);
            }
    }
    for (int i = C - 1; i >= 0; i--) {
        int c = order[i];
        if (mem[c].size() == 1) cnt[c]++;
        if (par[c] != -1) cnt[par[c]] += cnt[c];
    }

    if (K == 1) {
        addPair(root, tadj[root][0]);
    } else {
        vector<int> hdeg(C, 0);
        for (int c = 0; c < C; c++) {
            if (cnt[c] == 0) continue;
            if (par[c] != -1) hdeg[c]++;
            for (int d : tadj[c])
                if (d != par[c] && cnt[d] >= 1) hdeg[c]++;
        }
        vector<int> leaves;
        function<void(int)> go = [&](int c) {
            if (hdeg[c] == 1) leaves.push_back(c);
            for (int d : tadj[c])
                if (d != par[c] && cnt[d] >= 1) go(d);
        };
        go(root);
        int L = leaves.size();
        int mm = (L + 1) / 2;
        vector<int> ext = leaves;
        if (L % 2 == 1) ext.push_back(leaves[0]);
        for (int i = 0; i < mm; i++) addPair(ext[i], ext[i + mm]);
    }

    cout << K << '\n';
    for (int i = 0; i < K; i++) cout << bad[i] << (i + 1 < K ? ' ' : '\n');
    cout << added.size() << '\n';
    for (auto [a, b] : added) cout << a << ' ' << b << '\n';
    return 0;
}
