/*
Megoldás lényege:
Az éleket átviteli sebesség szerint csökkenő sorrendben adjuk hozzá, így az a sebesség, amelynél egy csúcs először érhető el legfeljebb K költséggel, pontosan a csúcs maximális átviteli sebessége. A jelenlegi gráfban tartjuk a központtól mért legolcsóbb távolságokat (csak a K-n belülieket), és új él hozzáadásakor a távolságok csak csökkenhetnek, ezért elég a javuló csúcsokból Dijkstra-szerűen terjeszteni. Az a csúcs, amely először kerül K-n belüli távolságra, megkapja az aktuális él sebességét. A futásidő fő költsége a távolságcsökkenések száma, amely a gyakorlatban kicsi, a memória O(N+M).
*/
/*
Hint 1: || Ha a vonalakat sebesség szerint csökkenő sorrendben veszed hozzá, mi történik akkor, amikor egy csúcs először elérhetővé válik K költséggel? Mit jelent ez a sebességre nézve? ||
Hint 2: || Tarts nyilván minden csúcsra a központtól mért legolcsóbb utat a már hozzáadott vonalakon, csak a K-n belülieket. Új vonal hozzáadásakor a távolság csak csökkenhet, és ez a végpontján keresztül terjed tovább, ezért elég onnan indítani a bejárást. ||
Hint 3: || Új él (u,v,a,b) után, ha dist[u]+a ≤ K és dist[u]+a < dist[v], állítsd be dist[v]-t, és prioritásos sorral (Dijkstra) járd be a javuló csúcsokat. Mindkét irányt nézd meg; amelyik csúcs először kerül K-n belülre, annak a válasz az aktuális él sebessége. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, c, k;
    cin >> n >> m >> c >> k;

    struct El {
        int u, v, a, b;
    };
    vector<El> el(m);
    for (El& e : el) cin >> e.u >> e.v >> e.a >> e.b;

    // sebesség szerint csökkenő sorrend
    stable_sort(el.begin(), el.end(), [](const El& x, const El& y) { return x.b > y.b; });

    const int INF = INT_MAX / 2;
    vector<int> dist(n + 1, INF), ans(n + 1, -1);
    vector<vector<pair<int, int>>> adj(n + 1);
    dist[c] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // a pq-ban lévő csúcsokból Dijkstra-szerű terjesztés; csak K-n belüli távolságot tárolunk
    auto spread = [&](int bw) {
        while (!pq.empty()) {
            auto [d, x] = pq.top();
            pq.pop();
            if (d != dist[x]) continue;
            for (auto [y, w] : adj[x]) {
                int nd = d + w;
                if (nd <= k && nd < dist[y]) {
                    dist[y] = nd;
                    if (ans[y] == -1) ans[y] = bw;
                    pq.push({nd, y});
                }
            }
        }
    };

    for (const El& e : el) {
        adj[e.u].push_back({e.v, e.a});
        adj[e.v].push_back({e.u, e.a});

        if (dist[e.u] + e.a <= k && dist[e.u] + e.a < dist[e.v]) {
            dist[e.v] = dist[e.u] + e.a;
            if (ans[e.v] == -1) ans[e.v] = e.b;
            pq.push({dist[e.v], e.v});
            spread(e.b);
        }
        if (dist[e.v] + e.a <= k && dist[e.v] + e.a < dist[e.u]) {
            dist[e.u] = dist[e.v] + e.a;
            if (ans[e.u] == -1) ans[e.u] = e.b;
            pq.push({dist[e.u], e.u});
            spread(e.b);
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (i == c)
            cout << 0 << '\n';
        else
            cout << ans[i] << '\n';
    }
    return 0;
}
