/*
Megoldási ötlet:
A közös főnök a két dolgozó legalacsonyabb közös őséhez áll közel, de a feladat külön szabályt ad arra az esetre,
ha az egyik dolgozó a másik főnöke. Ilyenkor nem maga az ős, hanem az ő közvetlen főnöke a helyes válasz.

Ezért először egy sima LCA-t számolunk bináris emeléssel. Ha az LCA egybeesik az egyik kérdezett dolgozóval,
akkor annak a szülőjét kell kiírni, különben magát az LCA-t.
*/
/*
Hint 1: || Először a legközelebbi közös ősre van szükség, utána jön a speciális szabály. ||
Hint 2: || Ha az egyik dolgozó őse a másiknak, akkor az ő főnöke lesz a válasz. ||
Hint 3: || Egyetlen LCA + egy szülőlánc-lépés elég a megoldáshoz. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    cin >> n >> a >> b;
    vector<vector<int>> children(n + 1);
    vector<int> parent(n + 1, 0), indegree(n + 1, 0);
    for (int i = 0; i < n - 1; ++i) {
        int boss, child;
        cin >> boss >> child;
        parent[child] = boss;
        children[boss].push_back(child);
        ++indegree[child];
    }

    int root = 1;
    while (root <= n && indegree[root] != 0) ++root;
    int log = 1;
    while ((1 << log) <= n) ++log;
    vector<vector<int>> up(log, vector<int>(n + 1, 0));
    vector<int> depth(n + 1, 0);
    vector<int> stack = {root};
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        for (int child : children[node]) {
            depth[child] = depth[node] + 1;
            up[0][child] = node;
            stack.push_back(child);
        }
    }

    for (int k = 1; k < log; ++k) {
        for (int node = 1; node <= n; ++node) up[k][node] = up[k - 1][up[k - 1][node]];
    }

    auto lca = [&](int x, int y) {
        if (depth[x] < depth[y]) swap(x, y);
        int diff = depth[x] - depth[y];
        for (int k = 0; k < log; ++k) if (diff & (1 << k)) x = up[k][x];
        if (x == y) return x;
        for (int k = log - 1; k >= 0; --k) {
            if (up[k][x] != up[k][y]) {
                x = up[k][x];
                y = up[k][y];
            }
        }
        return up[0][x];
    };

    int x = lca(a, b);
    int answer = x;
    if (x == a || x == b) answer = parent[x];
    if (answer == 0) cout << -1 << '\n';
    else cout << answer << '\n';
    return 0;
}
