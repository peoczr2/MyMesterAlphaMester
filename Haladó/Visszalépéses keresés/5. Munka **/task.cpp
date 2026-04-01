/*
Hungarian megoldás: a munkák és a munkások között minimális költségű bipartit
párosítást keresünk.

Hint 1: || Egy munkás legfeljebb egy munkát kaphat. ||
Hint 2: || A megoldás min-költségű maximális folyamként írható fel. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> ajanlatok(n);
    for (int i = 0; i < n; ++i) {
        int db;
        cin >> db;
        for (int j = 0; j < db; ++j) {
            int job, cost;
            cin >> job >> cost;
            ajanlatok[i].push_back({job - 1, cost});
        }
    }
    int S = 0, worker0 = 1, job0 = 1 + n, T = 1 + n + m;
    MinCostMaxFlow mcmf(T + 1);
    for (int i = 0; i < n; ++i) mcmf.addEdge(S, worker0 + i, 1, 0);
    for (int j = 0; j < m; ++j) mcmf.addEdge(job0 + j, T, 1, 0);
    for (int i = 0; i < n; ++i) {
        for (auto [job, cost] : ajanlatok[i]) {
            mcmf.addEdge(worker0 + i, job0 + job, 1, cost);
        }
    }
    auto [flow, cost] = mcmf.minCostMaxFlow(S, T, m);
    if (flow != m) {
        cout << -1 << '\n';
        return 0;
    }
    cout << cost << '\n';
    return 0;
}