/*
Megoldás lényege:
A gráf összefüggő fa, mert bármely két pont között pontosan egy út van. Gyökérnek az 1. pontot választjuk, és minden
csúcsra kiszámoljuk a gyökértől mért élszámot (mélység) és a gyökértől mért súlyösszeget. Két pont a és b távolsága
dist[a] + dist[b] - 2 * dist[lca(a, b)], ahol lca a legmélyebb közös ős. A legközelebbi közös őst bináris ugrótáblával
keressük meg, így egy kérdés O(log N) idő alatt megoldható. Az összes előfeldolgozás O(N log N), a kérdések O(K log N).
*/
/*
Hint 1: || Fában két pont távolsága a gyökértől mért távolságaik összegéből vonható ki: a közös ős úthosszát kétszer le kell vonni. ||
Hint 2: || A közös őst úgy keresd, hogy a mélyebb csúcsot a másik szintjére ugratod, majd mindkettőt együtt ugratod fölfelé, amíg a szülők különböznek. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    const int LOG = 14;  // 2^14 = 16384 > 10000
    vector<array<int, LOG>> up(n + 1);
    vector<int> depth(n + 1, 0);
    vector<long long> dist(n + 1, 0);

    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    up[1][0] = 1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (const auto& [to, w] : graph[v]) {
            if (visited[to]) {
                continue;
            }
            visited[to] = true;
            up[to][0] = v;
            depth[to] = depth[v] + 1;
            dist[to] = dist[v] + w;
            q.push(to);
        }
    }

    for (int j = 1; j < LOG; ++j) {
        for (int v = 1; v <= n; ++v) {
            up[v][j] = up[up[v][j - 1]][j - 1];
        }
    }

    auto lca = [&](int a, int b) {
        if (depth[a] < depth[b]) {
            swap(a, b);
        }
        int diff = depth[a] - depth[b];
        for (int j = 0; j < LOG; ++j) {
            if ((diff >> j) & 1) {
                a = up[a][j];
            }
        }
        if (a == b) {
            return a;
        }
        for (int j = LOG - 1; j >= 0; --j) {
            if (up[a][j] != up[b][j]) {
                a = up[a][j];
                b = up[b][j];
            }
        }
        return up[a][0];
    };

    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        int c = lca(a, b);
        cout << dist[a] + dist[b] - 2 * dist[c] << "\n";
    }
    return 0;
}
