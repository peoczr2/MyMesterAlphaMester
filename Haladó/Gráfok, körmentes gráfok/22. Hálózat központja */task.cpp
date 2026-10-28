/*
Megoldás lényege:
Fában egy csúcs excentricitása (a többi csúcstól mért legnagyobb távolság) az átmérő két végpontja,
a és b alapján kiszámolható: ecc(v) = max(d(a,v), d(b,v)). Ennek oka, hogy fában minden csúcsnak
a legtávolabbi csúcsa az átmérő valamelyik végpontja. Ezért elég három BFS-t futtatni: az 1-ből kiindulva
megkeressük a és b végpontot, majd a-ból és b-ből megkapjuk a két távolságtáblázatot. A minimális
excentricitású csúcs lesz a központ; döntetlen esetén (a két központ) a kisebb sorszámút írjuk ki.
Az idő O(N), ami a 20 000 csúcsú fára a 0,1 másodperces korlátba is belefér.
*/
/*
Hint 1: || Fában bármely csúcs legtávolabbi csúcsa egy legnagyobb távolságú (átmérő-) pár valamelyik tagja. Keress ilyen párt két BFS-sel. ||
Hint 2: || Ha a és b az átmérő végpontjai, akkor egy v csúcs excentricitása max(d(a,v), d(b,v)). Ezt az 1-ből, a-ból és b-ből induló BFS-ekkel kiszámolhatod. ||
Hint 3: || A keresett csúcs az excentricitás szerint minimális; ha több ilyen van, a kisebb sorszámút írd ki. A BFS-ek lineáris időben futnak, így a korlát nem jelent gondot. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> bfs(int src, const vector<vector<int>> &g, int n) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
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
    return dist;
}

int farthest(const vector<int> &dist, int n) {
    int best = 1;
    for (int v = 1; v <= n; v++) {
        if (dist[v] > dist[best]) best = v;
    }
    return best;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int a = farthest(bfs(1, g, n), n);
    vector<int> da = bfs(a, g, n);
    int b = farthest(da, n);
    vector<int> db = bfs(b, g, n);

    int center = 1, bestEcc = INT_MAX;
    for (int v = 1; v <= n; v++) {
        int ecc = max(da[v], db[v]);
        if (ecc < bestEcc) {
            bestEcc = ecc;
            center = v;
        }
    }

    cout << center << "\n";
    return 0;
}
