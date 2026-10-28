/*
Megoldás lényege:
A gráf körmentes, ezért a csomópontok topologikus sorrendjében haladva dinamikus programozással számoljuk a start csomópontból
az egyes csomópontokba vezető utak számát: egy csomópontba vezető utak száma a hozzá vezető élek kezdőpontjaiba vezető utak
számának összege. A topologikus sorrendet Kahn-algoritmussal kapjuk meg. Mivel csak a start csomópontból induló utakat
számoljuk, a start előtti csomópontok értéke nulla marad. Az értékeket 100000007-tel vett maradékban tároljuk, így a számok
nem nőnek túl. Az időigény O(N + M).
*/
/*
Hint 1: || Egy csomópontba érkező utak mindig valamelyik bemenő élen érkeznek, így az ide vezető utak száma a kezdőpontból
az élek kezdőpontjaiba vezető utak számának összege. Ehhez a csomópontokat olyan sorrendben kell feldolgozni, hogy minden él
kezdőpontja előbb kerüljön sorra. ||
Hint 2: || A topologikus sorrendet Kahn-algoritmussal kapod meg: a bemenő élek számát csökkentve, a nullára csökkent csomópontokat
sorba állítva. Az összegzést mindig a 100000007-es maradékkal végezd. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long long MOD = 100000007;

    int n, m, s, c;
    cin >> n >> m >> s >> c;

    vector<vector<int>> out(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        out[u].push_back(v);
        ++indeg[v];
    }

    // Topologikus sorrend (Kahn-algoritmus).
    vector<int> order;
    order.reserve(n);
    for (int v = 1; v <= n; ++v) {
        if (indeg[v] == 0) {
            order.push_back(v);
        }
    }
    for (size_t i = 0; i < order.size(); ++i) {
        for (int w : out[order[i]]) {
            if (--indeg[w] == 0) {
                order.push_back(w);
            }
        }
    }

    // ways[v]: a start csomópontból v-be vezető utak száma (modulo MOD).
    vector<long long> ways(n + 1, 0);
    ways[s] = 1;
    for (int v : order) {
        if (ways[v] == 0) {
            continue;
        }
        for (int w : out[v]) {
            ways[w] = (ways[w] + ways[v]) % MOD;
        }
    }

    cout << ways[c] << '\n';
    return 0;
}
