/*
Megoldás lényege:
A keresett útvonal a kiindulási városon (K) átmenő legrövidebb kör, amelynek legalább három csúcsa van, hiszen K mellett legalább két másik várost kell érintenie. Először szélességi bejárással K-ból minden város távolságát megkapjuk, és minden várost azzal az első lépéssel címkézünk meg, amellyel K-ból elérhető (ez az ág). Ha egy (u, v) busz két olyan várost köt össze, amelyek különböző ágon vannak, akkor K-ból u-n és v-n át visszatérhetünk K-ba egy egyszerű körön, amelynek hossza dist[u] + dist[v] + 1. A legrövidebb K-n átmenő kör ilyen élből adódik, ezért elég minden élt megnézni, és a legkisebb hosszút választani. Az útvonalat a két BFS-fa-út összefűzésével írjuk ki. Az időigény O(N + M).
*/
/*
Hint 1: || Keresd a legrövidebb kört, amely a kiindulási városon megy át. Hány várost kell érintenie úgy, hogy legalább két másik várost is érintsen? ||
Hint 2: || K-ból indított szélességi bejárás megadja a távolságokat. Minden városhoz jegyezd fel azt is, hogy K melyik szomszédján keresztül érhető el. ||
Hint 3: || Ha egy busz két olyan várost köt össze, amelyek K különböző szomszédjain keresztül érhetők el, az egy K-n átmenő körhöz vezet. A kör hossza a két távolság összege plusz egy. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // BFS K-ból: dist = távolság, par = BFS-fa szülője, branch = K melyik szomszédján át érhető el
    vector<int> dist(n + 1, -1), par(n + 1, 0), branch(n + 1, 0);
    queue<int> q;
    dist[k] = 0;
    q.push(k);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            par[v] = u;
            branch[v] = (u == k) ? v : branch[u];
            q.push(v);
        }
    }

    // A legrövidebb K-n átmenő kör: olyan (u, v) él, amely két különböző ágat köt össze
    int bestLen = INT_MAX, bu = -1, bv = -1;
    for (int u = 1; u <= n; ++u) {
        if (u == k || dist[u] == -1) continue;
        for (int v : adj[u]) {
            if (v == k || dist[v] == -1 || branch[u] == branch[v]) continue;
            int len = dist[u] + dist[v] + 1;
            if (len < bestLen) {
                bestLen = len;
                bu = u;
                bv = v;
            }
        }
    }

    if (bu == -1) {
        cout << 0 << '\n';
        return 0;
    }

    // K ... bu út, utána bv ... (K melletti csúcs) út visszafelé
    vector<int> route;
    for (int x = bu;; x = par[x]) {
        route.push_back(x);
        if (x == k) break;
    }
    reverse(route.begin(), route.end());
    for (int x = bv; x != k; x = par[x]) route.push_back(x);

    cout << route.size() << '\n';
    for (size_t i = 0; i < route.size(); ++i) {
        if (i) cout << ' ';
        cout << route[i];
    }
    cout << '\n';
    return 0;
}
