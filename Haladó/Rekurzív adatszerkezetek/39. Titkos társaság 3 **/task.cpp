/*
Megoldási ötlet:
A társaság egy gyökerezett fa. A három kérdéshez elég a fa alapvető adatait kiszámolni:
- mélység minden csúcsra;
- részfaméret minden csúcsra;
- ancestor-reláció `tin/tout` időkkel.

Az első kérdésnél csak lefelé lehet levelet küldeni, tehát akkor küldhet X Y-nak, ha Y X részfájában van;
ha ez fordítva igaz, akkor a válasz 2, különben 3. A második kérdés a két csúcs távolsága a fában, amit az LCA-val
számolunk ki. A harmadik kérdés mindkét csúcs leszármazottainak száma, azaz a részfaméret mínusz 1.
*/
/*
Hint 1: || „Csak a beosztottaknak küldhet levelet” pontosan azt jelenti, hogy a címzett a feladó részfájában van. ||
Hint 2: || A távolságot legegyszerűbben a legkisebb közös őssel lehet kiszámolni. ||
Hint 3: || A nem csak közvetlen beosztottak száma = a csúcs részfájának mérete mínusz egy. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x, y;
    cin >> n >> x >> y;

    vector<vector<int>> children(n + 1);
    vector<int> parent(n + 1, 0);
    for (int node = 2; node <= n; ++node) {
        cin >> parent[node];
        children[parent[node]].push_back(node);
    }

    vector<int> depth(n + 1, 0), tin(n + 1, 0), tout(n + 1, 0), subtree(n + 1, 1);
    vector<int> order;
    order.reserve(n);
    vector<pair<int, int>> stack = {{1, 0}};
    int timer = 0;
    while (!stack.empty()) {
        auto [node, phase] = stack.back();
        stack.pop_back();
        if (phase == 0) {
            tin[node] = ++timer;
            stack.push_back({node, 1});
            for (int i = static_cast<int>(children[node].size()) - 1; i >= 0; --i) {
                int child = children[node][i];
                depth[child] = depth[node] + 1;
                stack.push_back({child, 0});
            }
        } else {
            tout[node] = timer;
            order.push_back(node);
        }
    }

    for (int node : order) {
        for (int child : children[node]) {
            subtree[node] += subtree[child];
        }
    }

    auto isAncestor = [&](int ancestor, int node) {
        return tin[ancestor] <= tin[node] && tout[node] <= tout[ancestor];
    };

    int firstAnswer = 3;
    if (isAncestor(x, y)) {
        firstAnswer = 1;
    } else if (isAncestor(y, x)) {
        firstAnswer = 2;
    }

    int a = x, b = y;
    while (depth[a] > depth[b]) {
        a = parent[a];
    }
    while (depth[b] > depth[a]) {
        b = parent[b];
    }
    while (a != b) {
        a = parent[a];
        b = parent[b];
    }
    int lca = a;
    int distance = depth[x] + depth[y] - 2 * depth[lca];

    cout << firstAnswer << '\n';
    cout << distance << '\n';
    cout << subtree[x] - 1 << ' ' << subtree[y] - 1 << '\n';
    return 0;
}
