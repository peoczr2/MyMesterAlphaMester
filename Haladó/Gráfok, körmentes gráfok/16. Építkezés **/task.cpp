/*
Megoldás lényege:
Az A és B közé csak azok a munkák kerülhetnek kötelezően, amelyek A-ból elérhetők és amelyekből B elérhető: ezek A után és B előtt
szükségszerűen sorra kerülnek. Minden más munkát vagy A elé, vagy B mögé lehet ütemezni a megelőzési előírások megtartásával,
így a minimum pontosan ezeknek a köztes munkáknak a száma. Ezt két bejárással számoljuk meg: A-ból előre, és B-ből az éleket
megfordítva hátrafelé. A-t és B-t nem számoljuk bele. Az időigény O(N + M).
*/
/*
Hint 1: || Egy munka akkor kerül A és B közé, ha A-ból el lehet jutni hozzá, és onnan el lehet jutni B-hez. Ezeket a munkákat
nem lehet elkerülni, a többit pedig el lehet tolni. ||
Hint 2: || Két bejárást végezz: az egyik az A-ból kiinduló éleken, a másik a B-be érkező éleket megfordítva; a két bejárásban
is elért, A-tól és B-től különböző csomópontok számát add vissza. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, b;
    cin >> n >> m >> a >> b;

    vector<vector<int>> out(n + 1), in(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        out[u].push_back(v);
        in[v].push_back(u);
    }

    // Egy kezdőcsomópontból elérhető csomópontok (adott irányú élekkel).
    auto reachable = [n](const vector<vector<int>>& adj, int start) {
        vector<bool> seen(n + 1, false);
        vector<int> todo = {start};
        seen[start] = true;
        while (!todo.empty()) {
            int v = todo.back();
            todo.pop_back();
            for (int w : adj[v]) {
                if (!seen[w]) {
                    seen[w] = true;
                    todo.push_back(w);
                }
            }
        }
        return seen;
    };

    vector<bool> fromA = reachable(out, a);
    vector<bool> toB = reachable(in, b);

    int count = 0;
    for (int v = 1; v <= n; ++v) {
        if (v != a && v != b && fromA[v] && toB[v]) {
            ++count;
        }
    }

    cout << count << '\n';
    return 0;
}
