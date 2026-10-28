/*
Megoldás lényege: hálózati folyamként modellezzük. A forrásból minden munkás 1 kapacitású, 0 költségű
élen érkezik, a munkás minden vállalt munkájába az ajánlott árral költséges, 1 kapacitású él vezet, és
minden munkából 1 kapacitású, 0 költségű él megy a nyelőbe. Minimális költségű, M egység értékű folyamot
keresünk; ha ez nem érhető el, nincs megoldás (-1). A min-költségű folyam Dijkstra-algoritmussal
(potenciálokkal) N ≤ 20 esetén is gyorsan kiszámítható.
*/
/*
Hint 1: || Minden munkás legfeljebb egy munkát vállalhat, és minden munkát egy munkás végez; ez egy hozzárendelési (párosítási) feladat. ||
Hint 2: || Építs hálózatot: forrás → munkás (kapacitás 1, költség 0), munkás → munka (kapacitás 1, költség az ajánlott ár), munka → nyelő (kapacitás 1, költség 0). ||
Hint 3: || Keress M egység folyamot a legkisebb összköltséggel (minimális költségű folyam, növelő utakkal); ha nem telik be az M egység, a válasz -1. ||
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