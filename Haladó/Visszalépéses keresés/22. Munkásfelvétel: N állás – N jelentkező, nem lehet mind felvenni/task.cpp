/*
Hungarian megoldás: a maximum számú felvehető munkást keressük, és ezek közül a
legolcsóbb teljes párosítást.

Hint 1: || Először a lehető legtöbb munkást kell beosztani. ||
Hint 2: || Az azonos méretű megoldások közül a kisebb összköltségű a jó. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
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
    int S = 0, worker0 = 1, job0 = 1 + n, T = 1 + n + n;
    MinCostMaxFlow mcmf(T + 1);
    for (int i = 0; i < n; ++i) mcmf.addEdge(S, worker0 + i, 1, 0);
    for (int j = 0; j < n; ++j) mcmf.addEdge(job0 + j, T, 1, 0);
    for (int i = 0; i < n; ++i) for (auto [job, cost] : ajanlatok[i]) mcmf.addEdge(worker0 + i, job0 + job, 1, cost);
    auto [flow, cost] = mcmf.minCostMaxFlow(S, T, n);
    cout << flow << '\n' << cost << '\n';
    return 0;
}