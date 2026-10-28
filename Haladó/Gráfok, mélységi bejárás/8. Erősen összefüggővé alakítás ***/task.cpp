/*
Megoldás lényege:
A gráf félig összefüggő, ezért az erősen összefüggő komponensek kondenzációja egy irányított lánc: van egyetlen forrás-komponens (ahonnan minden más elérhető) és egyetlen nyelő-komponens (amelyből minden más elérhető). Ha csak egy komponens van, a gráf már erősen összefüggő, és a válasz 0 0. Egyébként a nyelő-komponensből egy u csúcsba húzott uv él (u a nyelő-komponensben, v a forrás-komponensben) záró kört hoz létre: a lánc végigvezet a forrástól a nyelőig, az új él pedig visszavezet. Az erős komponenseket Kosaraju-algoritmussal kapjuk: az első bejárás befejezési sorrendjéből, a fordított gráfon végzett második bejárás a komponenseket a topologikus sorrendben adja, így az első komponens forrás, az utolsó nyelő. Az idő O(N+M).
*/
/*
Hint 1: || Az erős komponensekre bontott gráfban nézd meg, melyik komponensbe lehet eljutni mindenhonnan, és melyikből lehet mindenhova eljutni. Ha csak egy komponens van, a gráf már erősen összefüggő. ||
Hint 2: || Kosaraju-algoritmussal kapod a komponenseket: előbb egy bejárás a befejezési sorrendet adja, majd a fordított élekkel végzett második bejárás a komponenseket topologikus sorrendben találja meg. ||
Hint 3: || Válassz egy csúcsot az utolsó (nyelő) komponensből és egyet az első (forrás) komponensből: a nyelőből a forrásba mutató él zárja a kört, ezt kell kiírnod. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> g, rg;
vector<int> order_, comp;
vector<char> vis;

void dfs1(int u) {
    vis[u] = 1;
    for (int v : g[u]) {
        if (!vis[v]) {
            dfs1(v);
        }
    }
    order_.push_back(u);
}

void dfs2(int u, int c) {
    comp[u] = c;
    for (int v : rg[u]) {
        if (comp[v] == -1) {
            dfs2(v, c);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    g.assign(n + 1, {});
    rg.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int p, q;
        cin >> p >> q;
        g[p].push_back(q);
        rg[q].push_back(p);
    }

    vis.assign(n + 1, 0);
    for (int u = 1; u <= n; u++) {
        if (!vis[u]) {
            dfs1(u);
        }
    }

    comp.assign(n + 1, -1);
    vector<int> rep;
    for (int i = (int)order_.size() - 1; i >= 0; i--) {
        int u = order_[i];
        if (comp[u] == -1) {
            rep.push_back(u);
            dfs2(u, (int)rep.size() - 1);
        }
    }

    int k = rep.size();
    if (k == 1) {
        cout << "0 0\n";
    } else {
        // rep[0] forrás-komponens, rep[k-1] nyelő-komponens
        cout << rep[k - 1] << " " << rep[0] << "\n";
    }
    return 0;
}
