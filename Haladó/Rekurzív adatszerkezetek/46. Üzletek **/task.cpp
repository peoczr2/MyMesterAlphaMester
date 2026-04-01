/*
Megoldási ötlet:
A megye úthálózata fa, a raktárnál gyökerezzük. Ha egy gyerekrészfában legalább egy üzletet nyitunk, akkor a szülőhöz
vezető út díját egyszer mindenképp ki kell fizetni; ha egyáltalán nem nyitunk ott üzletet, akkor ezt a díjat sem kell.

Ezért egy `u` csúcs részfájára a legjobb érték:
`dp[u] = profit[u] + Σ max(0, dp[gyerek] - élköltség)`.
Azért szerepel benne mindig `profit[u]`, mert ha már eljut a szállítás `u`-ig, akkor ott üzletet nyitni mindig érdemes:
ez további költséget nem okoz, csak növeli a hasznot.

A kiválasztott üzletek listája visszaépíthető: egy gyerekrészfát akkor veszünk be, ha annak hozzájárulása pozitív.
*/
/*
Hint 1: || Egy él díját csak akkor kell kifizetni, ha az alatta levő részfában legalább egy üzlet nyílik. ||
Hint 2: || Ha már elvitted az árut egy csúcsig, ott üzletet nyitni csak javít az eredményen. ||
Hint 3: || A gyerekrészfák egymástól függetlenek, ezért a hozzájárulásuk külön-külön `max(0, ...)` alakban adódik. ||
*/

#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int to;
    int cost;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, root;
    cin >> n >> root;

    vector<long long> profit(n + 1);
    for (int node = 1; node <= n; ++node) {
        cin >> profit[node];
    }

    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b, cost;
        cin >> a >> b >> cost;
        graph[a].push_back({b, cost});
        graph[b].push_back({a, cost});
    }

    vector<int> parent(n + 1, 0), parentCost(n + 1, 0), order;
    order.reserve(n);
    vector<int> stack = {root};
    parent[root] = -1;
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        order.push_back(node);
        for (const Edge& edge : graph[node]) {
            if (edge.to == parent[node]) {
                continue;
            }
            parent[edge.to] = node;
            parentCost[edge.to] = edge.cost;
            stack.push_back(edge.to);
        }
    }

    vector<long long> dp(n + 1, 0);
    for (int index = n - 1; index >= 0; --index) {
        int node = order[index];
        dp[node] = profit[node];
        for (const Edge& edge : graph[node]) {
            if (edge.to == parent[node]) {
                continue;
            }
            long long contribution = dp[edge.to] - edge.cost;
            if (contribution > 0) {
                dp[node] += contribution;
            }
        }
    }

    vector<int> chosen;
    stack = {root};
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        chosen.push_back(node);
        for (const Edge& edge : graph[node]) {
            if (edge.to == parent[node]) {
                continue;
            }
            if (dp[edge.to] - edge.cost > 0) {
                stack.push_back(edge.to);
            }
        }
    }

    cout << dp[root] << '\n';
    cout << chosen.size() << '\n';
    for (int i = 0; i < static_cast<int>(chosen.size()); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}