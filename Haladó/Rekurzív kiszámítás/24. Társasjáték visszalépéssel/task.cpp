/*
Megoldás lényege:
Most az ugrás hátra is mehet, ezért a feladat egy egysúlyú legrövidebb út keresése egy
kis fokszámú gráfban. BFS-sel meghatározzuk a legkevesebb lépésszámot.

*/

// Hint 1: || Az élek már nem aciklikusak, ezért visszafelé számolás helyett BFS kell. ||
// Hint 2: || Minden mezőről legfeljebb két él indul, így a bejárás nagyon olcsó. ||
// Hint 3: || A távolságot az első mezőtől indulva számold. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<int> jump(N + 1);
    for (int i = 1; i <= N; ++i) cin >> jump[i];

    vector<int> dist(N + 1, -1);
    queue<int> q;
    dist[1] = 0;
    q.push(1);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        auto relax = [&](int to) {
            if (to < 1 || to > N || dist[to] != -1) return;
            dist[to] = dist[v] + 1;
            q.push(to);
        };
        relax(v + 1);
        relax(jump[v]);
    }

    cout << dist[N] << '\n';
    return 0;
}
