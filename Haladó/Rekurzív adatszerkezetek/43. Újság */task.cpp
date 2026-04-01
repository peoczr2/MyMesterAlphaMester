/*
Megoldási ötlet:
Minden csomópont pontosan egy szülőtől kapja az újságot, ezért az egész rendszer egy gyökerezett fa. A három kérdés
közül kettő közvetlenül a fa alapadataiból megadható:
- az A csomópontból még tovább ellátott helyek száma = A részfájának mérete mínusz 1;
- az A csomópontig szükséges átrakások száma = az A csomópont mélysége mínusz 1, mert a gyökérben nyomtatnak,
  és minden köztes csomópontban egyszer kell új szerelvényre rakni.

A harmadik kérdés a két csomópontba menő útvonal közös utolsó pontját kéri, ami a két csomópont legmélyebb közös őse.
Elég a két csúcsot azonos mélységre hozni, majd együtt lépkedni felfelé az első egyezésig.
*/
/*
Hint 1: || A „közvetlenül honnan kapja” kapcsolat egyértelmű szülőt ad minden csomóponthoz, tehát egy fa keletkezik. ||
Hint 2: || Az A-ból tovább ellátott helyek pontosan az A részfájának többi csúcsai. ||
Hint 3: || Az A és B közös szállítási útvonala a legmélyebb közös ősükig tart. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    cin >> n >> a >> b;

    vector<int> parent(n + 1, 0);
    vector<vector<int>> children(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int child, par;
        cin >> child >> par;
        parent[child] = par;
        children[par].push_back(child);
    }

    int root = 1;
    while (parent[root] != 0) {
        root = parent[root];
    }

    vector<int> depth(n + 1, 0), subtree(n + 1, 1), order;
    order.reserve(n);
    vector<pair<int, int>> stack = {{root, 0}};
    while (!stack.empty()) {
        auto [node, phase] = stack.back();
        stack.pop_back();
        if (phase == 0) {
            stack.push_back({node, 1});
            for (int child : children[node]) {
                depth[child] = depth[node] + 1;
                stack.push_back({child, 0});
            }
        } else {
            order.push_back(node);
        }
    }

    for (int node : order) {
        for (int child : children[node]) {
            subtree[node] += subtree[child];
        }
    }

    int x = a, y = b;
    while (depth[x] > depth[y]) {
        x = parent[x];
    }
    while (depth[y] > depth[x]) {
        y = parent[y];
    }
    while (x != y) {
        x = parent[x];
        y = parent[y];
    }

    cout << subtree[a] - 1 << '\n';
    cout << max(0, depth[a] - 1) << '\n';
    cout << x << '\n';
    return 0;
}