/*
Megoldás lényege:
A P pontot kivesszük a gráfból, majd P minden szomszédjából egyszerre indítunk szélességi bejárást, így minden pont a hozzá legközelebbi szomszédjához (a saját "gyökeréhez") kerül.
Ha egy él két olyan pontot köt össze, amelyek különböző gyökerekhez tartoznak, akkor a két gyökérbe vezető BFS-utak, az él és a P pont együtt egy P-n átmenő kört adnak, amelynek hossza d[u]+d[v]+3.
A legrövidebb P-n átmenő kör ilyen élek közül a legkisebb értéket adja: a legjobb kör két szomszédja között van olyan él, ahol a gyökér változik, így ez az érték nem lehet nagyobb a valódi optimumnál.
A teljes megoldás O(N+M) időben fut, ami a 0.1 mp-es időlimithez elég.
A kört a szülőpointerek visszafelé követésével rakjuk össze P-ből indulva.
*/
/*
Hint 1: || Ha a P pontot kihagyjuk a gráfból, a P-n átmenő kör két éle P két különböző szomszédjához fut, és a két szomszéd között egy P-t nem használó úton kell eljutni. ||
Hint 2: || Indíts egyszerre szélességi bejárást P összes szomszédjából, és jegyezd meg minden pontról, melyik szomszédtól érted el. Ha két szomszédos pont különböző kiindulási szomszédhoz tartozik, az él és a két gyökérbe vezető út körré áll össze P-n át. ||
Hint 3: || Az ilyen éleken a d[u]+d[v]+3 értékek minimuma adja a választ, ahol d a BFS-távolság. A kör pontjait a szülőpointerekkel, visszafelé összegyűjtve kapod meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, p;
    cin >> n >> m >> p;

    vector<vector<int>> adj(n + 1);
    vector<pair<int, int>> edges;
    edges.reserve(m);
    vector<char> isNbr(n + 1, 0);
    vector<int> nbrs;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u == p || v == p) {
            int other = (u == p) ? v : u;
            if (!isNbr[other]) {
                isNbr[other] = 1;
                nbrs.push_back(other);
            }
            continue;
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({u, v});
    }

    // Többforrású BFS: P szomszédjai a kiindulási pontok (gyökerek).
    vector<int> dist(n + 1, -1), label(n + 1, -1), par(n + 1, 0);
    queue<int> q;
    for (int a : nbrs) {
        dist[a] = 0;
        label[a] = a;
        par[a] = 0;
        q.push(a);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                label[v] = label[u];
                par[v] = u;
                q.push(v);
            }
        }
    }

    // Olyan él keresése, amely két különböző gyökér területét köti össze.
    long long best = LLONG_MAX;
    int bu = -1, bv = -1;
    for (const auto &e : edges) {
        int u = e.first, v = e.second;
        if (dist[u] < 0 || dist[v] < 0) continue;
        if (label[u] == label[v]) continue;
        long long cand = (long long)dist[u] + dist[v] + 3;
        if (cand < best) {
            best = cand;
            bu = u;
            bv = v;
        }
    }

    if (bu == -1) {
        cout << -1 << '\n';
        return 0;
    }

    // Kör: P, a gyökértől bu-ig, majd bv-től a másik gyökérig.
    vector<int> A, B;
    for (int x = bu; x != 0; x = par[x]) A.push_back(x);
    for (int x = bv; x != 0; x = par[x]) B.push_back(x);
    reverse(A.begin(), A.end());

    vector<int> cyc;
    cyc.push_back(p);
    for (int x : A) cyc.push_back(x);
    for (int x : B) cyc.push_back(x);

    cout << cyc.size() << '\n';
    for (size_t i = 0; i < cyc.size(); i++) {
        if (i) cout << ' ';
        cout << cyc[i];
    }
    cout << '\n';
    return 0;
}
