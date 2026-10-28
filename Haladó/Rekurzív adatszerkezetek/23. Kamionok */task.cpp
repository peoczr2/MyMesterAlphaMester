/*
Megoldási ötlet:
Minden városból pontosan egy kamionút indul, így a városok a központi raktár (1-es) felé
mutató gyökeres fát alkotnak. Egy részfából csak a részfa levelein indított kamionok juthatnak ki,
ezért a v-ben gyökerező részfa P(v) termelését csak az L(v) darab levélből induló kamion
szállíthatja el. Ebből P(v) <= C * L(v) szükséges minden v-re, és elegendő is.
A keresett legkisebb egész kapacitás tehát a max_v ceil(P(v) / L(v)) érték.

Ezt egy DFS-sel számoljuk: visszatérve összegezzük a részfa termelését és a leveleit.
*/
/*
Hint 1: || Egy részfa termelését csak a részfa levelein indított kamionok vihetik ki a fából. ||
Hint 2: || Minden v csúcsra számold ki, hány levél van a részfájában, és mennyi a részfa összes termelése. ||
Hint 3: || A v csúcsra szükséges kapacitás felfelé kerekített P(v) / L(v); a válasz ezek maximuma. Ezt egy DFS-sel, visszatéréskor egyszerre kiszámolhatod. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<long long> prod(N + 1, 0);
    vector<vector<int>> children(N + 1);
    for (int city = 2; city <= N; ++city) {
        int to;
        long long amount;
        cin >> to >> amount;
        prod[city] = amount;
        children[to].push_back(city);
    }

    // sum[v]: a v részfájának összes termelése, leaves[v]: a v részfájában lévő levelek száma
    vector<long long> sum(N + 1, 0), leaves(N + 1, 0);
    long long answer = 0;
    function<void(int)> dfs = [&](int u) {
        sum[u] += prod[u];
        if (children[u].empty()) leaves[u] = 1;
        for (int v : children[u]) {
            dfs(v);
            sum[u] += sum[v];
            leaves[u] += leaves[v];
        }
        long long need = (sum[u] + leaves[u] - 1) / leaves[u];
        answer = max(answer, need);
    };

    dfs(1);
    cout << answer << '\n';
    return 0;
}
