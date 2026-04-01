/*
Hungarian megoldás: itt csak a teljes munkás-állás hozzárendelés létezik vagy
nem létezik, ezért elég egy sima párosításkeresés.

Hint 1: || Minden munkás pontosan egy állást kap. ||
Hint 2: || Ha nem jut minden munkásnak külön munka, akkor NINCS a válasz. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> tud(n);
    for (int i = 0; i < n; ++i) {
        int db;
        cin >> db;
        for (int j = 0; j < db; ++j) {
            int job;
            cin >> job;
            tud[i].push_back(job - 1);
        }
    }
    int S = 0, worker0 = 1, job0 = 1 + n, T = 1 + n + n;
    Dinic din(T + 1);
    for (int i = 0; i < n; ++i) din.addEdge(S, worker0 + i, 1);
    for (int j = 0; j < n; ++j) din.addEdge(job0 + j, T, 1);
    for (int i = 0; i < n; ++i) for (int job : tud[i]) din.addEdge(worker0 + i, job0 + job, 1);
    if (din.maxflow(S, T) != n) {
        cout << "NINCS\n";
        return 0;
    }
    vector<int> ans(n, -1);
    for (int i = 0; i < n; ++i) {
        for (auto &e : din.g[worker0 + i]) {
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