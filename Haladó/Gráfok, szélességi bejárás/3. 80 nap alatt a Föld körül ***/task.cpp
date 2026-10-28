/*
Megoldás lényege:
A kiinduló városba visszatérő út akkor kerüli meg a Földet, ha a hosszúsági fokok szerinti elmozdulás összege ±360 fok, vagyis a fordulatszám nem nulla. Minden járat hosszúsági változását a rövidebb irányban mérjük: a dátumvonal nyugati irányú átlépése −1, keleti irányú átlépése +1 fordulatot ad. Az állapot ezért a (város, fordulatszám) pár, és ezen Dijkstra-algoritmussal keressük a legrövidebb időt a kiindulási városból a kiindulási városba úgy, hogy a fordulatszám végül nem nulla. A fordulatszámot ±(2N+2)-re korlátozzuk, így az állapotok száma N·(4N+5), és az algoritmus ezen belül fut.
*/
/*
Hint 1: || Egy járat hosszúsági változását a rövidebb irányban kell venni: ha a két város hosszúsági különbsége 180 foknál nagyobb, a járat a dátumvonalon át, a másik irányban halad. ||
Hint 2: || A visszaérkezéskor a teljes hosszúsági elmozdulás legyen ±360 fok; ezt úgy követheted nyomon, hogy a fordulatszámot az állapotban tárolod, és minden járatnál a dátumvonal-átlépés szerint módosítod. ||
Hint 3: || Az állapot (város, fordulatszám); Dijkstra-algoritmussal az (kiindulás, 0) állapotból indulj, és az első olyan állapot, ahol a város a kiindulási város és a fordulatszám nem nulla, adja a legkevesebb napot. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int turn;      // a fordulatszám változása: -1, 0 vagy +1
    long long days;
};

int main() {
    int n, m, s;
    cin >> n >> m >> s;

    vector<long long> lon(n + 1);
    for (int i = 1; i <= n; ++i) {
        long long latitude;
        cin >> lon[i] >> latitude;
    }

    vector<vector<Edge>> g(n + 1);
    for (int k = 0; k < m; ++k) {
        int u, v;
        long long t;
        cin >> u >> v >> t;
        long long d = lon[v] - lon[u];
        int turn = 0;
        if (d > 180) turn = -1;         // nyugati irányban lépi át a dátumvonalat
        else if (d <= -180) turn = 1;   // keleti irányban lépi át
        g[u].push_back({v, turn, t});
    }

    const int K = 2 * n + 2;            // a fordulatszám korlátja
    const int W = 2 * K + 1;
    auto id = [&](int v, int w) { return v * W + (w + K); };
    const long long INF = LLONG_MAX / 4;

    vector<long long> dist((n + 1) * W, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[id(s, 0)] = 0;
    pq.push({0, id(s, 0)});

    long long answer = -1;
    while (!pq.empty()) {
        auto [d, cur] = pq.top();
        pq.pop();
        if (d != dist[cur]) continue;

        int v = cur / W;
        int w = cur % W - K;
        if (v == s && w != 0) {
            answer = d;
            break;
        }
        for (const Edge& e : g[v]) {
            int nw = w + e.turn;
            if (nw < -K || nw > K) continue;
            int nid = id(e.to, nw);
            if (d + e.days < dist[nid]) {
                dist[nid] = d + e.days;
                pq.push({dist[nid], nid});
            }
        }
    }

    cout << answer << "\n";
    return 0;
}
