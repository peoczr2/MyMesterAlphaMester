/*
Megoldás lényege: minden munkás pontosan egy állást kap, és minden állás pontosan egy munkást, tehát a feladat a munkások és az állások egy minimális költségű teljes párosítása.
Ezt min-költségű folyammal oldjuk meg: a forrásból a munkásokba, onnan az ajánlott állásokba (az ajánlat költségével) és az állásokból a nyelőbe vezető élek kapacitása 1.
A folyam növelése mindig a legolcsóbb augmentáló úton történik (Dijkstra potenciálokkal), így N egység folyam után a kapott költség a minimális teljes párosítás költsége.
Ha a folyam nem éri el N-et, nincs olyan kiosztás, amely minden állást betölt, ekkor a válasz NINCS.
A munkás-állás élek telítettségéből visszaolvasható, melyik munkás melyik állást kapta.
Időigény: N ≤ 20 esetén N augmentáló lépés, mindegyik O(E log V), ami bőven gyors.
*/
/*
Hint 1: || Minden munkás legfeljebb egy állást kap, minden állásnak pedig jutnia kell valaki. ||
Hint 2: || Ez egy minimális költségű teljes párosítás, amelyet min-költségű folyammal számolhatunk: forrás, munkások, állások, nyelő. ||
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
    if (flow != n) {
        cout << "NINCS\n";
        return 0;
    }
    cout << cost << '\n';
    vector<int> ans(n, -1);
    for (int i = 0; i < n; ++i) {
        for (auto &e : mcmf.g[worker0 + i]) {
            if (e.to >= job0 && e.to < job0 + n && e.cap == 0) ans[i] = e.to - job0 + 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}