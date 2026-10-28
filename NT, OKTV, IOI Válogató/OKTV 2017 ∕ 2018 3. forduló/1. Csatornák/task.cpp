/*
Megoldás lényege:
A legszélesebb út szélessége az út legszűkebb csatornájának maximuma. Ezt úgy kapjuk meg, hogy a csatornákat szélesség szerint csökkenő sorrendben egy unió-find (DSU) struktúrába kötjük, és azt az élt keressük, amelynél A és B először kerül egy komponensbe: ennek szélessége lesz a W. Minden W-nél nem keskenyebb csatornából álló gráfban van A-B út, és ezen az élhalmazon minden út szélessége legalább W, így a legkevesebb csatornát tartalmazó optimális út ebből a részgráfból BFS-sel kapható meg. Az időigény a rendezés miatt O(M log M).
*/
/*
Hint 1: || Egy út szélessége a rajta lévő legkeskenyebb csatorna. Keresd azt az utat, amelynek a legszűkebb pontja a lehető legnagyobb. ||
Hint 2: || Rendezd a csatornákat szélesség szerint csökkenően, és egyesével add őket egy DSU-hoz. Az az él, amelynél A és B először kerül egy halmazba, adja a W szélességet. ||
Hint 3: || A második kérdéshez a W-nél nem keskenyebb összes csatornából építs gráfot (nem csak a W-t lezáró élt), és ebben egy egyszerű BFS-sel számold ki az A-tól B-ig vezető legrövidebb út élszámát. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> par;

int findp(int x) {
    while (par[x] != x) {
        par[x] = par[par[x]];
        x = par[x];
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<int> eu(m), ev(m), ew(m);
    for (int i = 0; i < m; i++) cin >> eu[i] >> ev[i] >> ew[i];

    // 1. lépés: a legszélesebb út szélessége
    vector<int> order(m);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) { return ew[i] > ew[j]; });

    par.resize(n + 1);
    iota(par.begin(), par.end(), 0);
    int W = 0;
    for (int id : order) {
        int ru = findp(eu[id]), rv = findp(ev[id]);
        if (ru != rv) par[ru] = rv;
        if (findp(a) == findp(b)) {
            W = ew[id];
            break;
        }
    }

    // 2. lépés: legkevesebb csatorna a W-nél nem keskenyebb csatornákon
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        if (ew[i] >= W) {
            g[eu[i]].push_back(ev[i]);
            g[ev[i]].push_back(eu[i]);
        }
    }
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[a] = 0;
    q.push(a);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dist[v] < 0) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    cout << W << '\n' << dist[b] << '\n';
    return 0;
}
