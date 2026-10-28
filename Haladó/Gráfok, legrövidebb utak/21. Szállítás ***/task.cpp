/*
Megoldás lényege:
A feladat két részből áll. Először a legnagyobb átvihető súlyt keressük: az utakat csökkenő teherbírás szerint adjuk hozzá
egy uniós-keresős (DSU) szerkezethez, és amikor A és B egy komponensbe kerül, az épp hozzáadott út teherbírása a keresett W maximum.
Másodszor csak a legalább W teherbírású utakon keresünk szélességi bejárással (BFS) A-ból B-be legkevesebb élből álló utat,
ami egyben a legkevesebb városon átmenő út. Egy ilyen út minden éle legalább W, és mivel W maximális, a szűk keresztmetszet pontosan W.
Az idő O(M log M), ami M ≤ 100 000 mellett bőven belefér a 0,8 mp-es korlátba.
*/
/*
Hint 1: || Két részre bontható a feladat: előbb a legnagyobb lehetséges teherbírást kell megtalálni, utána a legkevesebb városon átvezető utat a már megengedett utakon. ||
Hint 2: || Ha az utakat csökkenő teherbírás szerint adod hozzá egy uniós-keresős (DSU) szerkezethez, akkor abban a pillanatban, amikor A és B egy komponensbe kerül, az utoljára hozzáadott út teherbírása a keresett maximum. ||
Hint 3: || Ezután csak a legalább ekkora teherbírású utakat tartsd meg, és szélességi bejárással (BFS) keress A-ból B-be legkevesebb élből álló utat; a szülőtömb visszakövetésével kapod a városok sorrendjét. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;
    explicit DSU(int n) : p(n + 1), sz(n + 1, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) {
        while (p[x] != x) {
            p[x] = p[p[x]];
            x = p[x];
        }
        return x;
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
    }
};

struct Road {
    int x, y, t;
};

int main() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<Road> roads(m);
    for (auto& r : roads) cin >> r.x >> r.y >> r.t;
    // A minta első sorában előfordul, hogy a N kisebb a legnagyobb városszámnál: ezért a valódi méretet az adatokból vesszük.
    for (const Road& r : roads) n = max({n, r.x, r.y});
    n = max({n, a, b});

    // 1. Legnagyobb átvihető súly: az utak csökkenő teherbírás szerinti hozzáadása
    vector<Road> sorted = roads;
    sort(sorted.begin(), sorted.end(), [](const Road& p, const Road& q) { return p.t > q.t; });
    DSU dsu(n);
    int best = 0;
    for (const Road& r : sorted) {
        dsu.unite(r.x, r.y);
        if (dsu.find(a) == dsu.find(b)) {
            best = r.t;
            break;
        }
    }
    if (best == 0) {
        cout << 0 << "\n" << 0 << "\n";
        return 0;
    }

    // 2. Legkevesebb városon át: BFS a best-nél nem kisebb teherbírású utakon
    vector<vector<int>> adj(n + 1);
    for (const Road& r : roads) {
        if (r.t >= best) {
            adj[r.x].push_back(r.y);
            adj[r.y].push_back(r.x);
        }
    }
    vector<int> par(n + 1, -1), dist(n + 1, -1);
    queue<int> q;
    dist[a] = 0;
    q.push(a);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] < 0) {
                dist[v] = dist[u] + 1;
                par[v] = u;
                q.push(v);
            }
        }
    }

    vector<int> path;
    for (int v = b; v != a; v = par[v]) path.push_back(v);
    path.push_back(a);
    reverse(path.begin(), path.end());

    cout << best << "\n";
    cout << path.size() - 2; // A-t és B-t nem számoljuk
    for (size_t i = 1; i + 1 < path.size(); i++) cout << ' ' << path[i];
    cout << "\n";
    return 0;
}
