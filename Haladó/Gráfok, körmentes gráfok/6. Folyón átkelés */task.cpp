/*
Megoldás lényege:
A szigetek körmentes gráfot alkotnak, ezért topologikus sorrendben dolgozhatók fel. A bal parti félszigetekről
indulunk, egy sziget után a pénzünk: pénz - belépési díj + kincs. Egy szigetre csak akkor léphetünk be, ha a
pillanatnyi pénzünk legalább a belépési díj. Ha egy szigetre több úton is eljutunk, a nagyobb pénzzel érkezés soha
nem rosszabb, mert ugyanazok a további lépések megengedettek, és a végeredmény is nagyobb. Ezért szigetenként elég
a legnagyobb elérhető pénzt tárolni, és topologikus sorrendben továbbadni az éleken. A jobb parti (kimenő él nélküli)
szigetek közül azt választjuk, ahol a végén a legtöbb pénz van, az útvonalat a tárolt előző szigetekből visszafelé állítjuk össze.
Az időigény O(N + M).
*/
/*
Hint 1: || Egy útvonal végén a pénzünk K - (az útba eső díjak összege) + (az útba eső kincsek összege). Egy szigetre csak akkor léphetsz be, ha a pillanatnyi pénzed legalább a belépési díj. ||
Hint 2: || Egy szigetre több úton is eljuthatsz, de a nagyobb pénzzel érkezés sosem rosszabb. Ezért szigetenként elég a legnagyobb elérhető pénzt tárolni, és topologikus sorrendben továbbadni. ||
Hint 3: || A bal parti (bejövő él nélküli) szigetek kezdőértéke K - díj + kincs, ha K legalább a díj. Egy élen csak akkor mehetsz át, ha a pénz legalább a cél sziget díja. A jobb parti szigetek közül a legjobbat válaszd, és a tárolt előzőekből rekonstruáld az utat. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long k;
    cin >> n >> m >> k;

    vector<long long> fee(n + 1), treasure(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> fee[i] >> treasure[i];
    }

    vector<vector<int>> out(n + 1);
    vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        out[u].push_back(v);
        ++indeg[v];
        ++outdeg[u];
    }

    // best[v]: a v szigetet elhagyva elérhető legnagyobb pénz, -1 ha nem érhető el.
    vector<long long> best(n + 1, -1);
    vector<int> parent(n + 1, 0);
    for (int s = 1; s <= n; ++s) {
        if (indeg[s] == 0 && k >= fee[s]) {
            best[s] = k - fee[s] + treasure[s];
        }
    }

    // Topologikus sorrend (Kahn-algoritmus).
    vector<int> order;
    order.reserve(n);
    queue<int> ready;
    vector<int> left = indeg;
    for (int v = 1; v <= n; ++v) {
        if (left[v] == 0) ready.push(v);
    }
    while (!ready.empty()) {
        int u = ready.front();
        ready.pop();
        order.push_back(u);
        for (int v : out[u]) {
            if (--left[v] == 0) ready.push(v);
        }
    }

    // A sorrendben előre haladva továbbadjuk a legnagyobb pénzt az élek mentén.
    for (int u : order) {
        if (best[u] < 0) continue;
        for (int v : out[u]) {
            if (best[u] < fee[v]) continue;
            long long cand = best[u] - fee[v] + treasure[v];
            if (cand > best[v]) {
                best[v] = cand;
                parent[v] = u;
            }
        }
    }

    int target = 0;
    for (int v = 1; v <= n; ++v) {
        if (outdeg[v] == 0 && best[v] >= 0 && (target == 0 || best[v] > best[target])) {
            target = v;
        }
    }

    if (target == 0) {
        cout << -1 << "\n";
        return 0;
    }

    vector<int> path;
    for (int v = target; v != 0; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    cout << best[target] << "\n";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) cout << ' ';
        cout << path[i];
    }
    cout << "\n";
    return 0;
}
