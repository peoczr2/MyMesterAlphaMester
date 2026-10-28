/*
Megoldás lényege:
Egy kereszteződés pontosan akkor része valamelyik körútnak, ha legalább egy hozzá csatlakozó út nem híd, vagyis benne van valamelyik körben.
Ezért Tarjan-féle DFS-sel (tin és low értékekkel) megkeressük az összes hidat, majd a nem híd élek végpontjait körútnak jelöljük.
Az éleket azonosítóval kezeljük, így a párhuzamos utak is körnek számítanak. Az idő O(N + M).
*/
/*
Hint 1: || Egy kereszteződés akkor nem része körútnak, ha minden hozzá csatlakozó út híd, vagyis az út elvágásával a két vége már nem érhető el egymásból. ||
Hint 2: || Hidak kereséséhez DFS-t futtass, és minden csúcsra számold ki a low értéket: a legkisebb DFS-sorszámot, amelyet a csúcs részfájából egy éllel el lehet érni. Az (u,v) gyermekél akkor híd, ha low[v] > tin[u]. ||
Hint 3: || A szülőélt az élazonosító alapján hagyd ki, ne a szülő csúcs alapján: így a párhuzamos utakat is helyesen kezeled. ||
*/
#include <bits/stdc++.h>
using namespace std;

int timer_ = 0;
vector<vector<pair<int, int>>> g; // (szomszéd, élazonosító)
vector<int> tin, low;
vector<bool> isBridge;

void dfs(int u, int parentEdge) {
    tin[u] = low[u] = ++timer_;
    for (auto [v, id] : g[u]) {
        if (id == parentEdge) continue;
        if (tin[v]) {
            low[u] = min(low[u], tin[v]);
        } else {
            dfs(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) isBridge[id] = true;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    g.assign(n + 1, {});
    vector<int> ex(m), ey(m);
    for (int i = 0; i < m; i++) {
        cin >> ex[i] >> ey[i];
        g[ex[i]].push_back({ey[i], i});
        g[ey[i]].push_back({ex[i], i});
    }

    tin.assign(n + 1, 0);
    low.assign(n + 1, 0);
    isBridge.assign(m, false);
    for (int s = 1; s <= n; s++) {
        if (!tin[s]) dfs(s, -1);
    }

    vector<bool> onRoad(n + 1, false);
    for (int i = 0; i < m; i++) {
        if (!isBridge[i]) {
            onRoad[ex[i]] = true;
            onRoad[ey[i]] = true;
        }
    }

    vector<int> res;
    for (int v = 1; v <= n; v++) {
        if (!onRoad[v]) res.push_back(v);
    }

    cout << res.size() << '\n';
    for (size_t i = 0; i < res.size(); i++) {
        if (i) cout << ' ';
        cout << res[i];
    }
    cout << '\n';
    return 0;
}
