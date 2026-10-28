/*
Megoldás lényege:
Egy útvonal szélességét a rajta lévő legkeskenyebb csatorna szélessége adja. A
legszélesebb használható hajó szélességét úgy kapjuk meg, hogy a csatornákat
szélesség szerint csökkenő sorrendben egy uniós-keresés (DSU) struktúrába
vesszük. Abban a pillanatban, amikor A és B egy komponensbe kerül, az épp
hozzáadott csatorna szélessége a keresett érték. Ezen a szélességen csak azok a
csatornák használhatók, amelyek legalább ilyen szélesek, ezért a második kérdés
erre a részgráfra egy szélességi bejárással (BFS) válaszolható meg A-ból.
Az időigény O(M log M), a rendezés miatt.
*/
/*
Hint 1: || Rendezd a csatornákat szélesség szerint csökkenő sorrendbe, és közben figyeld meg, mikor lesz A és B összekötött. ||
Hint 2: || Az utolsó hozzáadott csatorna szélessége adja a maximális szélességet, és utána már csak az ennél szélesebb vagy egyforma széles csatornák között keress legrövidebb utat szélességi bejárással. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> par;

int findRoot(int v) {
    while (par[v] != v) {
        par[v] = par[par[v]];
        v = par[v];
    }
    return v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, b;
    cin >> n >> m >> a >> b;

    struct Edge {
        int x, y, w;
    };
    vector<Edge> edges(m);
    for (Edge &e : edges) cin >> e.x >> e.y >> e.w;

    sort(edges.begin(), edges.end(), [](const Edge &p, const Edge &q) { return p.w > q.w; });

    par.resize(n + 1);
    iota(par.begin(), par.end(), 0);

    int width = 0;
    for (const Edge &e : edges) {
        int rx = findRoot(e.x), ry = findRoot(e.y);
        if (rx != ry) par[rx] = ry;
        if (findRoot(a) == findRoot(b)) {
            width = e.w;
            break;
        }
    }

    vector<vector<int>> adj(n + 1);
    for (const Edge &e : edges) {
        if (e.w >= width) {
            adj[e.x].push_back(e.y);
            adj[e.y].push_back(e.x);
        }
    }

    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[a] = 0;
    q.push(a);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    cout << width << '\n' << dist[b] << '\n';
    return 0;
}
