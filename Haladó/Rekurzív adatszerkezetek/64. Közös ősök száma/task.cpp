/*
Megoldási ötlet:
A közös ősök száma két embernél pontosan a legközelebbi közös ős mélységéből adódik. Ha a gyökér mélysége 0,
akkor az LCA mélysége + 1 adja az összes közös ős darabszámát.

Ezért ugyanazt a bináris emeléses LCA-előkészítést használjuk, mint a közös ős feladatban, majd minden lekérdezésre
kiszámoljuk az LCA-t, és abból egyetlen sorral megkapjuk a választ.
*/
/*
Hint 1: || A közös ősök a két ember és az LCA gyökér felé vezető útjának közös elemei. ||
Hint 2: || Ha az LCA mélységét ismered, az ősszám már csak egy egyszerű képlet. ||
Hint 3: || Gyökérmélység 0 esetén a válasz: mélység(LCA) + 1. ||
*/

#include <algorithm>
#include <iostream>
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
        int ancestor = lca(a, b);
        cout << depth[ancestor] + 1 << '\n';
    }
    return 0;
}
