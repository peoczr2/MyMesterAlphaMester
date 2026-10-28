/*
Megoldás lényege:
Az új él akkor teszi erősen összefüggővé a hálózatot, ha az erős komponensek DAG-jában egyetlen forrásból (befok 0) egyetlen nyelőbe (kifok 0) mutat, és így a forrásból minden komponens elérhető, minden komponensből pedig a nyelőbe eljut. Ezért az erős komponenseket Tarjan-algoritmussal keressük meg, majd minden komponens befokát és kifokát számoljuk. A megoldás egy nyelő-komponensbeli csúcsból a forrás-komponensbeli csúcsba mutató él. Az időigény O(N+M).
*/
/*
Hint 1: || Az erős komponensek közti élekből építs DAG-ot. Keresd meg az erős komponenseket Tarjan-algoritmussal, és minden élre nézd meg, hogy két különböző komponens közé mutat-e. ||
Hint 2: || Számold ki minden komponensre a befokot és a kifokot. A javításhoz a DAG-nak pontosan egy forrása (befok 0) és egy nyelője (kifok 0) kell legyen, különben egy él nem elég. ||
Hint 3: || Az új él a nyelő komponens egy csúcsából a forrás komponens egy csúcsába mutasson. Így a forrásból minden csúcs elérhető, és minden csúcsból el lehet jutni a nyelőbe, tehát a gráf erősen összefüggő lesz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> g;
vector<int> idx, low, comp, stk;
vector<char> onStk;
int tmr = 0, C = 0;

void tarjan(int u) {
    idx[u] = low[u] = ++tmr;
    stk.push_back(u);
    onStk[u] = 1;
    for (int v : g[u]) {
        if (!idx[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (onStk[v]) {
            low[u] = min(low[u], idx[v]);
        }
    }
    if (low[u] == idx[u]) {
        while (true) {
            int w = stk.back();
            stk.pop_back();
            onStk[w] = 0;
            comp[w] = C;
            if (w == u) break;
        }
        C++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    g.assign(n + 1, {});
    vector<pair<int, int>> ed(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        ed[i] = {u, v};
        g[u].push_back(v);
    }
    idx.assign(n + 1, 0);
    low.assign(n + 1, 0);
    comp.assign(n + 1, -1);
    onStk.assign(n + 1, 0);
    for (int v = 1; v <= n; v++)
        if (!idx[v]) tarjan(v);

    vector<int> indeg(C, 0), outdeg(C, 0);
    for (auto [u, v] : ed)
        if (comp[u] != comp[v]) {
            outdeg[comp[u]]++;
            indeg[comp[v]]++;
        }
    int src = -1, snk = -1;
    for (int c = 0; c < C; c++) {
        if (indeg[c] == 0 && src == -1) src = c;
        if (outdeg[c] == 0 && snk == -1) snk = c;
    }
    int x = -1, y = -1;
    for (int v = 1; v <= n; v++) {
        if (x == -1 && comp[v] == snk) x = v;
        if (y == -1 && comp[v] == src) y = v;
    }
    cout << x << ' ' << y << '\n';
    return 0;
}
