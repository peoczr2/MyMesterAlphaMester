/*
Megoldás lényege:
A kormány eljárását követjük. Először Dijkstra-algoritmussal megkeressük a főváros (F) és a legnépesebb város (L) közötti
legolcsóbb utat, és ennek szakaszait megépítjük. Ha így még kevesebb mint K másik várost érünk el, akkor az építési ajánlatokat
költség szerint rendezzük, és minden lépésben azt az első ajánlatot építjük meg, amely már elért városból egy még el nem ért
városba vezet (ez a Prim-algoritmus minimális költségű bővítése), amíg legalább K másik város el nem érhető.
Az egyenlő költségű ajánlatok közötti választást a rendezés sorrendje dönti el. Az idő O(M log M + K·M), ami N ≤ 1000,
M ≤ 10 000 és K ≤ 1000 mellett a 0,1 mp-es korláton belül marad, mert a bővítés lépésenként korán kilép.
*/
/*
Hint 1: || A kormány eljárása két lépésből áll: előbb egy legolcsóbb utat épít F és L között, utána mindig a legolcsóbb olyan szakaszt, amely már elért városból új városba vezet. ||
Hint 2: || Az első lépéshez Dijkstra-algoritmus kell; a szülőtömbből visszakövetve megkapod az F-L út szakaszait, és ezek költsége adja az első részt. ||
Hint 3: || A második lépés a Prim-algoritmushoz hasonló: az építési ajánlatokat rendezd költség szerint, majd minden lépésben keresd meg az első olyan ajánlatot, amelynek pontosan az egyik végpontja már el van érve. ||
Hint 4: || Számold az elért, F-en kívüli városokat, és addig bővíts, amíg ez el nem éri a K-t; a kiírásban az F-L út szakaszai az L felől visszafelé szerepeljenek, utána a bővítés szakaszai a megépítés sorrendjében. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Offer {
    int a, b;
    long long c;
};

int main() {
    int n, k, f, l;
    cin >> n >> k >> f >> l;
    int m;
    cin >> m;
    vector<Offer> offers(m);
    for (auto& o : offers) cin >> o.a >> o.b >> o.c;

    // 1. Legolcsóbb út F és L között (Dijkstra)
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (const Offer& o : offers) {
        adj[o.a].push_back({o.b, o.c});
        adj[o.b].push_back({o.a, o.c});
    }
    const long long INF = LLONG_MAX / 4;
    vector<long long> d(n + 1, INF);
    vector<int> par(n + 1, 0);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    d[f] = 0;
    pq.push({0, f});
    while (!pq.empty()) {
        auto [du, u] = pq.top();
        pq.pop();
        if (du > d[u]) continue;
        for (auto [v, c] : adj[u]) {
            if (du + c < d[v]) {
                d[v] = du + c;
                par[v] = u;
                pq.push({d[v], v});
            }
        }
    }

    vector<bool> inR(n + 1, false); // már vasúttal elért városok
    inR[f] = true;
    long long total = 0;
    vector<pair<int, int>> pathEdges; // F-től L felé
    int prev = f;
    vector<int> chain;
    for (int v = l; v != f; v = par[v]) chain.push_back(v);
    reverse(chain.begin(), chain.end());
    for (int v : chain) {
        total += d[v] - d[prev];
        pathEdges.push_back({prev, v});
        inR[v] = true;
        prev = v;
    }
    int cnt = (int)chain.size(); // F-en kívül elért városok száma

    // 2. Bővítés: költség szerint rendezett ajánlatok, minden lépésben az első átmenő
    vector<Offer> sorted = offers;
    sort(sorted.begin(), sorted.end(), [](const Offer& x, const Offer& y) { return x.c < y.c; });
    vector<pair<int, int>> growth;
    while (cnt < k) {
        bool found = false;
        for (const Offer& o : sorted) {
            if (inR[o.a] != inR[o.b]) {
                int u = inR[o.a] ? o.a : o.b;
                int v = inR[o.a] ? o.b : o.a;
                inR[v] = true;
                total += o.c;
                growth.push_back({u, v});
                cnt++;
                found = true;
                break;
            }
        }
        if (!found) break;
    }

    cout << total << "\n";
    cout << pathEdges.size() + growth.size() << "\n";
    for (int i = (int)pathEdges.size() - 1; i >= 0; i--) cout << pathEdges[i].first << ' ' << pathEdges[i].second << "\n";
    for (auto [u, v] : growth) cout << u << ' ' << v << "\n";
    return 0;
}
