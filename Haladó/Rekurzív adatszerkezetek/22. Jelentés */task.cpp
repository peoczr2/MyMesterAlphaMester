#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
A jelentés útja a fában mindig a dolgozótól a gyökérig vezető út hossza.
Ezért a legrosszabb esetben a legmélyebb csomópont jelentése tart a legtovább.

Egy egyszerű DFS-sel minden dolgozónak megadjuk a mélységét és megkeressük a
legnagyobb mélységet. Holtversenyben a kisebb sorszámú dolgozót választjuk.

Hint 1: || A jelentés minden nap pontosan egy szinttel közelebb kerül az igazgatóhoz. ||
Hint 2: || A keresett napok száma a fa legnagyobb mélysége. ||
Hint 3: || A második sorba egy olyan dolgozót kell írni, aki ezen a mélységen áll, tie-breakként a legkisebb sorszámmal. ||
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<vector<int>> children(N + 1);
    for (int u = 1; u <= N; ++u) {
        while (true) {
            int v;
            cin >> v;
            if (v == 0) break;
            children[u].push_back(v);
        }
    }

    vector<int> depth(N + 1, 0);
    queue<int> q;
    q.push(1);
    int bestDepth = 0, bestNode = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : children[u]) {
            depth[v] = depth[u] + 1;
            if (depth[v] > bestDepth || (depth[v] == bestDepth && v < bestNode)) {
                bestDepth = depth[v];
                bestNode = v;
            }
            q.push(v);
        }
    }

    cout << bestDepth << '\n' << bestNode << '\n';
    return 0;
}