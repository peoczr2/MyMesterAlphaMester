/*
Megoldás lényege:
Tom csak a 2-es szélességű utakon mozoghat, így minden csomópontba legkorábban d(v) lépés alatt ér el; ezt egy
szélességi bejárással számoljuk ki a 2-es élekből. Jerry akkor biztonságos, ha minden csomópontba, ahová érkezik,
a saját érkezési idejénél (a lépések számánál) később Tom még nem érhet el, vagyis k < d(v). Ezért minden v
csomópontra kiszámoljuk L(v)-t: a legkésőbbi időpontot, amikor Jerry még lehet v-ben úgy, hogy onnan el tud jutni
az egérlyukhoz. Az egérlyukból L(E) = d(E) - 1, és L(v) = min(d(v) - 1, max L(w) - 1), ahol w a szomszédok. Ezt a
legnagyobb értékű csomópontból kiindulva, Dijkstra-szerű prioritásos sorral számoljuk, mert az érték minden élen
csökken. Egy K kezdőhelyre a válasz IGEN, ha L(K) ≥ 0. Az időigény O((N + M) log N) és a P lekérdezés O(1).
*/
/*
Hint 1: || Tom távolságát csak a 2-es szélességű utakon mérd: egy szélességi bejárás megadja, hány lépés kell neki minden csomóponthoz. Jerry csak akkor lehet egy csomópontban, ha ahhoz hamarabb ér, mint Tom. ||
Hint 2: || Fordítva gondolkodj: az egérlyuktól indulva számold ki minden csomópontra a legkésőbbi időt, amikor Jerry még ott lehet és el tud jutni a lyukhoz. Ez az érték a lyuknál Tom-távolság mínusz 1, és szomszédról szomszédra eggyel csökken. ||
Hint 3: || Mivel az érték minden lépésnél csökken, a csomópontokat mindig a nagyobb értékűtől a kisebb felé dolgozd fel egy maximum-prioritásos sorral (Dijkstra-szerűen). Végül egy K kezdőhelyre elég megnézni, hogy az értéke nem negatív-e. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, tom, p, hole;
    cin >> n >> m >> tom >> p >> hole;

    const int INF = 1000000000;
    vector<vector<int>> adj(n + 1), tomAdj(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b, s;
        cin >> a >> b >> s;
        adj[a].push_back(b);
        adj[b].push_back(a);
        if (s == 2) {
            tomAdj[a].push_back(b);
            tomAdj[b].push_back(a);
        }
    }

    // d[v]: Tom legrövidebb ideje v-ig (csak a 2-es szélességű utakon)
    vector<int> d(n + 1, INF);
    queue<int> q;
    d[tom] = 0;
    q.push(tom);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int w : tomAdj[u]) {
            if (d[w] == INF) {
                d[w] = d[u] + 1;
                q.push(w);
            }
        }
    }

    // L[v]: legkésőbbi idő, amikor Jerry még v-ben lehet, és onnan eléri az egérlyukat (-1 / negatív: nem jó)
    vector<int> L(n + 1, -INF);
    vector<char> done(n + 1, 0);
    priority_queue<pair<int, int>> pq;
    L[hole] = d[hole] - 1;
    if (L[hole] >= 0) pq.push({L[hole], hole});

    while (!pq.empty()) {
        auto [val, u] = pq.top();
        pq.pop();
        if (done[u]) continue;
        done[u] = 1;
        for (int w : adj[u]) {
            if (done[w]) continue;
            int cand = min(d[w] - 1, val - 1);
            if (cand >= 0 && cand > L[w]) {
                L[w] = cand;
                pq.push({cand, w});
            }
        }
    }

    for (int i = 0; i < p; ++i) {
        int k;
        cin >> k;
        cout << (L[k] >= 0 ? "IGEN" : "NEM") << '\n';
    }
    return 0;
}
