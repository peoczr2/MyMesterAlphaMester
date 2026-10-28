/*
Megoldás lényege:
A kérdés: a központi csúcsból minden csúcsba vezető, legfeljebb K összköltségű úton mekkora a legnagyobb "szűk keresztmetszet" (az út éleinek legkisebb sebessége). Az éleket sebesség szerint csökkenő sorrendben vesszük hozzá a gráfhoz. Egy adott sebességküszöb t mellett a csak t-nél nem lassabb éleket használva minden csúcs legkisebb költségét egy Dijkstra-algoritmussal kapjuk meg, és nem kell minden t-re újraszámolni: a küszöb csökkentésekor új élek érkeznek, a távolságok csak csökkenhetnek, ezért elég a változott csúcsokból továbbterjeszteni. Egy csúcsnál az első olyan küszöb a válasz, amelynél a költsége már nem nagyobb K-nál, mert a küszöb csökkenésével a válasz nem romolhat. A K-nál nagyobb távolságokat nem terjesztjük tovább. Az időigény a változások számától függ, de a gyakorlatban az N ≤ 4000, M ≤ 50 000 bemenetre elég gyors.
*/
/*
Hint 1: || Fordítsd meg a kérdést: sebességküszöböt csökkentve minden csúcsnál azt keresd, mikor kerül először K összköltségen belülre. Így az éleket sebesség szerint csökkenő sorrendben vedd hozzá. ||
Hint 2: || Egy adott küszöbnél a csak megfelelő sebességű élekből számolt legkisebb költségű utak Dijkstra-algoritmussal kiszámíthatók. Új élek hozzáadásakor a távolságok már csak csökkennek, ezért elég a megváltozott csúcsokból folytatni a Dijkstrát. ||
Hint 3: || Ne számolj tovább olyan csúcsot, amelynek költsége már nagyobb K-nál, és a központi csúcsnak a válasza 0. Egy csúcsra az első olyan sebesség lesz a válasz, amelynél a költsége először K alá kerül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, c, k;
    cin >> n >> m >> c >> k;

    struct Edge {
        int u, v, cost, bw;
    };
    vector<Edge> es(m);
    // (szomszéd, él sorszáma)
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> es[i].u >> es[i].v >> es[i].cost >> es[i].bw;
        adj[es[i].u].push_back({es[i].v, i});
        adj[es[i].v].push_back({es[i].u, i});
    }

    // Élek sebesség szerint csökkenő sorrendben.
    vector<int> ord(m);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int x, int y) { return es[x].bw > es[y].bw; });

    const int INF = INT_MAX / 2;
    vector<int> dist(n + 1, INF), ans(n + 1, -1);
    dist[c] = 0;
    ans[c] = 0;

    using Item = pair<int, int>;  // (költség, csúcs)
    priority_queue<Item, vector<Item>, greater<Item>> pq;

    int i = 0;
    while (i < m) {
        int t = es[ord[i]].bw;  // az aktuális sebességküszöb
        // Az ugyanilyen sebességű élek hozzáadása.
        while (i < m && es[ord[i]].bw == t) {
            const Edge& e = es[ord[i]];
            i++;
            for (auto [x, y] : {make_pair(e.u, e.v), make_pair(e.v, e.u)}) {
                if (dist[x] < INF && dist[x] + e.cost <= k && dist[x] + e.cost < dist[y]) {
                    dist[y] = dist[x] + e.cost;
                    pq.push({dist[y], y});
                }
            }
        }
        // Dijkstra a már bekapcsolt élekre (sebesség >= t).
        while (!pq.empty()) {
            auto [d, x] = pq.top();
            pq.pop();
            if (d != dist[x]) continue;
            for (auto [y, idx] : adj[x]) {
                if (es[idx].bw < t) continue;
                int nd = d + es[idx].cost;
                if (nd <= k && nd < dist[y]) {
                    dist[y] = nd;
                    pq.push({nd, y});
                }
            }
        }
        // Az először K-n belülre kerülő csúcsok válasza ez a sebesség.
        for (int v = 1; v <= n; v++) {
            if (ans[v] == -1 && dist[v] <= k) ans[v] = t;
        }
    }

    for (int v = 1; v <= n; v++) cout << ans[v] << '\n';
    return 0;
}
