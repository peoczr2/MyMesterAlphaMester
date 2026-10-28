/*
Megoldás lényege: a kaktuszgráfban bármely két kör élidegen, ezért minden kör pontosan egy visszaélhez tartozik a mélységi bejárás fájában.
A bejárás során egy (u, v) visszaél akkor zár le kört, ha v az u egyik őse a fában, és ilyenkor a kör hossza depth[u] - depth[v] + 1.
Egy összefüggő kaktuszgráfban a körök száma M - N + 1, ami megegyezik a visszaélek számával, így minden kör előáll egy visszaélből.
Ezért a leghosszabb kör hossza a visszaélekből számolt maximum. Az időigény O(N + M).
*/
/*
Hint 1: || Figyeld meg, hogy a mélységi bejárás fájában minden nem fa-él egy őséhez köti a leszármazottat. Egy ilyen él egy kört zár le. ||
Hint 2: || Egy (u, v) visszaélnél a kör hossza a két csúcs mélységének különbsége plusz egy. A megoldás ezek maximuma. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<pair<int, int>>> g;  // (szomszéd, élazonosító)
vector<int> depthOf, parentEdge;
int best = 0;

void dfs(int u) {
    for (auto [v, id] : g[u]) {
        if (id == parentEdge[u]) continue;
        if (depthOf[v] == -1) {
            depthOf[v] = depthOf[u] + 1;
            parentEdge[v] = id;
            dfs(v);
        } else if (depthOf[v] < depthOf[u]) {
            best = max(best, depthOf[u] - depthOf[v] + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    g.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }

    depthOf.assign(n + 1, -1);
    parentEdge.assign(n + 1, -1);
    for (int s = 1; s <= n; ++s) {
        if (depthOf[s] == -1) {
            depthOf[s] = 0;
            dfs(s);
        }
    }

    cout << best << "\n";
    return 0;
}
