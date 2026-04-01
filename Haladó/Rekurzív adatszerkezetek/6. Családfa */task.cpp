#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
A fa generációi egyszerűen a gyökértől mért mélységek. Egy BFS-sel vagy DFS-sel
ki tudjuk számolni minden csomópont generációszámát, majd megszámoljuk, hogy
hány tag tartozik az egyes generációkba.

A legnépesebb generációt a legnagyobb elemszám, holtversenyben a gyökérhez
közelebbi generáció nyeri. A legkevesebb létszámú generációnál a gyökér saját
generációja nem jöhet szóba, ezért a 2..maxDepth tartományban keresünk, ott is
holtversenyben a kisebb sorszám nyer.

Hint 1: || Minden generáció pontosan egy mélységi szintnek felel meg. ||
Hint 2: || Számold meg szintenként a csomópontokat, és ebből választod ki a maximumot és minimumot. ||
Hint 3: || A gyökér generációját nem szabad a minimumkeresésbe belevenni. ||
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<int>> children(N + 1);
    for (int v = 2; v <= N; ++v) {
        int p;
        cin >> p;
        children[p].push_back(v);
    }

    vector<int> depth(N + 1, 0);
    queue<int> q;
    q.push(1);
    int maxDepth = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : children[u]) {
            depth[v] = depth[u] + 1;
            maxDepth = max(maxDepth, depth[v] + 1);
            q.push(v);
        }
    }

    vector<int> cnt(maxDepth + 1, 0);
    for (int i = 1; i <= N; ++i) ++cnt[depth[i] + 1];

    int bestMaxGen = 1;
    for (int g = 2; g <= maxDepth; ++g) {
        if (cnt[g] > cnt[bestMaxGen] || (cnt[g] == cnt[bestMaxGen] && g < bestMaxGen)) {
            bestMaxGen = g;
        }
    }

    int bestMinGen = 2;
    for (int g = 3; g <= maxDepth; ++g) {
        if (cnt[g] < cnt[bestMinGen] || (cnt[g] == cnt[bestMinGen] && g < bestMinGen)) {
            bestMinGen = g;
        }
    }

    cout << bestMaxGen << '\n' << bestMinGen << '\n';
    return 0;
}