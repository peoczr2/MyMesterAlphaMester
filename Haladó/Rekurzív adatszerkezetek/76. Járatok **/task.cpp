/*
Megoldási ötlet:
Minden teremhez egy rácspozíciót rendelünk: a bal oldali járat x координátája -1-gyel, a jobb oldali +1-gyel változik.
A felszínről függőlegesen lefelé fúrt sugár egy adott x koordinátán a legmélyebben fekvő termet találja meg.

Ezért elég egy DFS-sel kiszámítani minden terem (x, mélység) koordinátáját, majd minden x-re eltárolni a legnagyobb
mélységű termet. A válasz a kiválasztott termek halmaza.
*/
/*
Hint 1: || A bal és jobb járatok x koordinátája rendre -1 és +1 irányban tolódik. ||
Hint 2: || Egy függőleges fúrásnál ugyanazon x koordinátán a legmélyebb terem látszik. ||
Hint 3: || DFS-sel számold ki az összes terem koordinátáját, majd x szerint tartsd meg a legnagyobb mélységet. ||
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Edge {
    int to;
    char dir;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        char c;
        cin >> a >> c >> b;
        g[a].push_back({b, c});
    }

    vector<int> x(n + 1, 0), depth(n + 1, 0);
    vector<int> order = {1};
    for (int idx = 0; idx < static_cast<int>(order.size()); ++idx) {
        int node = order[idx];
        for (const auto& e : g[node]) {
            x[e.to] = x[node] + (e.dir == 'J' ? 1 : -1);
            depth[e.to] = depth[node] + 1;
            order.push_back(e.to);
        }
    }

    map<int, pair<int, int>> best; // x -> (depth, node)
    for (int node = 1; node <= n; ++node) {
        auto it = best.find(x[node]);
        if (it == best.end() || depth[node] > it->second.first) {
            best[x[node]] = {depth[node], node};
        }
    }

    vector<int> answer;
    for (const auto& [coord, info] : best) answer.push_back(info.second);
    cout << answer.size() << '\n';
    for (int i = 0; i < static_cast<int>(answer.size()); ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}
