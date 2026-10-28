/*
Megoldás lényege:
A főnöki kapcsolatok gyökeres fát alkotnak, a gyökér a vállalat vezetője. Minden csúcs 2^k-adik ősét előre kiszámoljuk (bináris emelés), így két csúcs legközelebbi közös ősét (LCA) O(log N) lépésben kapjuk meg: a mélyebb csúcsot a mélységkülönbséggel felemeljük, majd mindkettőt együtt ugratjuk, amíg a szüleik még különböznek. Ha az LCA maga az A vagy a B, a keresett főnök az LCA közvetlen főnöke, egyébként maga az LCA. Az előfeldolgozás O(N log N), egy lekérdezés O(log N).
*/
/*
Hint 1: || A főnöki lánc gyökeres fa, a két dolgozó legközelebbi közös főnöke a legmélyebb közös ős. Külön figyelj arra az esetre, amikor az egyik dolgozó a másik főnöke. ||
Hint 2: || Számold ki minden csúcs mélységét és 2^k-adik ősét (bináris emelés), így a mélyebb csúcsot a mélységkülönbséggel fel tudod emelni a másik szintjére. ||
Hint 3: || Ha a legközelebbi közös ős maga az egyik dolgozó (például A), akkor a keresett főnök annak közvetlen főnöke, tehát még egy lépéssel feljebb kell menni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    cin >> n >> a >> b;
    vector<int> parent(n + 1, 0), indeg(n + 1, 0);
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        parent[y] = x;
        ++indeg[y];
        g[x].push_back(y);
    }

    int root = 1;
    for (int i = 1; i <= n; ++i) if (indeg[i] == 0) root = i;

    int LOG = 1;
    while ((1 << LOG) <= n) ++LOG;
    vector<vector<int>> up(LOG, vector<int>(n + 1, 0));
    vector<int> depth(n + 1, 0);
    queue<int> q;
    q.push(root);
    up[0][root] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            depth[to] = depth[v] + 1;
            up[0][to] = v;
            q.push(to);
        }
    }
    for (int k = 1; k < LOG; ++k) {
        for (int v = 1; v <= n; ++v) up[k][v] = up[k - 1][up[k - 1][v]];
    }

    auto lift = [&](int v, int d) {
        for (int k = 0; k < LOG; ++k) if (d & (1 << k)) v = up[k][v];
        return v;
    };

    auto lca = [&](int x, int y) {
        if (depth[x] < depth[y]) swap(x, y);
        x = lift(x, depth[x] - depth[y]);
        if (x == y) return x;
        for (int k = LOG - 1; k >= 0; --k) {
            if (up[k][x] != up[k][y]) {
                x = up[k][x];
                y = up[k][y];
            }
        }
        return up[0][x];
    };

    int c = lca(a, b);
    if (c == a || c == b) c = up[0][c];
    if (c == 0) cout << -1 << '\n';
    else cout << c << '\n';
    return 0;
}