/*
Megoldási ötlet:
A legközelebbi közös ős a gyökér felé vezető útak első közös pontja, ezért klasszikus LCA-feladatot kapunk.
Mivel a családfa fa, elég bináris emelést használni: előre kiszámítjuk minden csúcs 2^k-adik ősét, majd a mélyebb
csúcsot felhozzuk a másik szintjére, utána együtt emeljük őket, amíg eltérnek.
*/
/*
Hint 1: || Saját magának mindenki őse, tehát a keresett közös ős a két út közös legfelső pontja. ||
Hint 2: || Ha minden csúcsról tudod a 2^k-adik ősét, a lekérdezés logaritmikus időben megoldható. ||
Hint 3: || Előbb a mélységeket egyenlítsd ki, utána a legnagyobb lehetséges ugrásokkal emeld a két csúcsot egyszerre. ||
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> children(n + 1);
    vector<int> indegree(n + 1, 0);
    for (int i = 0; i < n - 1; ++i) {
        int mother, child;
        cin >> mother >> child;
        children[mother].push_back(child);
        ++indegree[child];
    }

    int root = 1;
    while (root <= n && indegree[root] != 0) ++root;

    int log = 1;
    while ((1 << log) <= n) ++log;
    vector<vector<int>> up(log, vector<int>(n + 1, 0));
    vector<int> depth(n + 1, 0);
    vector<int> order;
    order.reserve(n);
    vector<int> stack = {root};
    order.push_back(root);
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        for (int child : children[node]) {
            depth[child] = depth[node] + 1;
            up[0][child] = node;
            order.push_back(child);
            stack.push_back(child);
        }
    }

    for (int k = 1; k < log; ++k) {
        for (int node = 1; node <= n; ++node) {
            up[k][node] = up[k - 1][up[k - 1][node]];
        }
    }

    auto lca = [&](int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        int diff = depth[a] - depth[b];
        for (int k = 0; k < log; ++k) {
            if (diff & (1 << k)) a = up[k][a];
        }
        if (a == b) return a;
        for (int k = log - 1; k >= 0; --k) {
            if (up[k][a] != up[k][b]) {
                a = up[k][a];
                b = up[k][b];
            }
        }
        return up[0][a];
    };

    int q;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << '\n';
    }
    return 0;
}
