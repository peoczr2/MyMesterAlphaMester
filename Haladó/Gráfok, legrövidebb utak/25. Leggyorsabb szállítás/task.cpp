/*
Megoldás lényege:
Minden pályaszakasz hossza pozitív, ezért a legrövidebb utat Dijkstra-algoritmussal kereshetjük. A csúcsokhoz két értéket tárolunk: a V-től eddig vezető legrövidebb út hosszát, és az ilyen utakon elérhető legnagyobb "szűk keresztmetszetet", vagyis az út legkisebb teherbírású szakaszát. A prioritási sort úgy rendezzük, hogy előbb a kisebb hossz, azonos hossz esetén a nagyobb teherbírás kerüljön előre, így minden csúcs a lexikografikusan legjobb címkét kapja. Az előzőket csak szigorú javításnál írjuk felül, és W-ből visszafelé haladva kapjuk a kiírandó utat. Az időigény O(M log N), ami az N ≤ 10 000, M ≤ 100 000 bemenetre a 0,1 mp-es időlimitbe belefér.
*/
/*
Hint 1: || A legrövidebb út hossza a Dijkstra-algoritmussal kiszámítható, de egyenlő hosszú utak között a teherbíráson is kell választani: ilyenkor a legkisebb szakasz teherbírását kell maximalizálni. ||
Hint 2: || Csúcsonként a távolság mellett tárold az eddig vezető út legkisebb teherbírását is. Két címke közül az a jobb, amelyiknek kisebb a távolsága, azonos távolságnál pedig nagyobb a teherbírása. ||
Hint 3: || Egy él bejárásakor az új teherbírás a régi és az él teherbírásának minimuma. Az út pontjait a W csúcsból az előzőkön visszafelé haladva rakhatod össze. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    // (szomszéd, hossz, teherbírás)
    vector<vector<array<int, 3>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, h, t;
        cin >> a >> b >> h >> t;
        adj[a].push_back({b, h, t});
        adj[b].push_back({a, h, t});
    }
    int v, w;
    cin >> v >> w;

    const int INF = INT_MAX;
    vector<int> dist(n + 1, INF), cap(n + 1, 0), prev(n + 1, 0);
    // (távolság, -teherbírás, csúcs): a kisebb elem kerül előre
    using Item = tuple<int, int, int>;
    priority_queue<Item, vector<Item>, greater<Item>> pq;

    dist[v] = 0;
    cap[v] = INF;
    pq.push({0, -INF, v});
    while (!pq.empty()) {
        auto [d, negc, x] = pq.top();
        pq.pop();
        if (d != dist[x] || -negc != cap[x]) continue;
        for (auto [y, h, t] : adj[x]) {
            int nd = d + h;
            int nc = min(cap[x], t);
            if (nd < dist[y] || (nd == dist[y] && nc > cap[y])) {
                dist[y] = nd;
                cap[y] = nc;
                prev[y] = x;
                pq.push({nd, -nc, y});
            }
        }
    }

    vector<int> path;
    for (int x = w; x != v; x = prev[x]) path.push_back(x);
    path.push_back(v);
    reverse(path.begin(), path.end());

    cout << dist[w] << ' ' << cap[w] << '\n';
    for (size_t i = 0; i < path.size(); i++) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}
