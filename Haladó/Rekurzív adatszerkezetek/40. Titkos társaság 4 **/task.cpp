/*
Megoldási ötlet:
Ez is egy gyökerezett fa. Az első két kérdés ugyanazt igényli, mint az előző feladat: részfaméretek és a két csúcs
távolsága. A harmadik kérdés azt kéri, hogy bármely feladó-címzett párra biztosan elég legyen a lépésszám, vagyis
a fa legnagyobb két csúcsa közti távolságát kell megadni: ez a fa átmérője.

A részfákat postorderben számoljuk. A két csúcs távolsága az LCA-val adódik. Az átmérő két BFS-sel számolható:
egy tetszőleges csúcsból elmegyünk a legtávolabbiba, onnan pedig újra a legtávolabbiba; a második távolság lesz az átmérő.
*/
/*
Hint 1: || A „bárki legyen is a feladó és a címzett” mondat a fa legrosszabb esetű távolságát kéri. ||
Hint 2: || Ez a legrosszabb eset a fa átmérője. ||
Hint 3: || A részfaméretet és az LCA-alapú távolságot ugyanúgy számolhatod, mint az előző titkos társaság feladatban. ||
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

pair<int, int> farthestNode(int start, const vector<vector<int>>& graph) {
    int n = static_cast<int>(graph.size()) - 1;
    vector<int> dist(n + 1, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    int bestNode = start;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        if (dist[node] > dist[bestNode]) {
            bestNode = node;
        }
        for (int next : graph[node]) {
            if (dist[next] == -1) {
                dist[next] = dist[node] + 1;
                q.push(next);
            }
        }
    }

    return {bestNode, dist[bestNode]};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x, y;
    cin >> n >> x >> y;

    vector<int> parent(n + 1, 0);
    for (int node = 1; node <= n; ++node) {
        cin >> parent[node];
    }

    vector<vector<int>> children(n + 1), graph(n + 1);
    for (int node = 2; node <= n; ++node) {
        children[parent[node]].push_back(node);
        graph[parent[node]].push_back(node);
        graph[node].push_back(parent[node]);
    }

    vector<int> depth(n + 1, 0), subtree(n + 1, 1), order;
    order.reserve(n);
    vector<pair<int, int>> stack = {{1, 0}};
    while (!stack.empty()) {
        auto [node, phase] = stack.back();
        stack.pop_back();
        if (phase == 0) {
            stack.push_back({node, 1});
            for (int i = static_cast<int>(children[node].size()) - 1; i >= 0; --i) {
                int child = children[node][i];
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

    auto [far1, _d1] = farthestNode(1, graph);
    auto [_far2, diameter] = farthestNode(far1, graph);

    cout << subtree[x] - 1 << ' ' << subtree[y] - 1 << '\n';
    cout << distance << '\n';
    cout << diameter << '\n';
    return 0;
}