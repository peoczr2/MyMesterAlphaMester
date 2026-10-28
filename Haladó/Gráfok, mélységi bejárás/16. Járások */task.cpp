/*
Megoldás lényege:
Az utak a mintapélda ábrája szerint kétirányúak, a távolság pedig a legrövidebb úton levő élek száma. Minden járásközpontból szélességi bejárással (BFS) kiszámoljuk a távolságokat az összes településig, és minden településhez tároljuk az eddig talált legkisebb távolságot és a hozzá tartozó központ sorszámát. A központokat növekvő sorrendben dolgozzuk fel, ezért egyenlő távolságnál a kisebb sorszámú központ marad meg, mert csak szigorúan kisebb távolság írja felül. Végül minden központhoz megszámoljuk a hozzá rendelt településeket, és ezeket a központok sorrendjében írjuk ki. Az időigény O(M·(N+K)), ami legfeljebb 1000·(1000+10000) lépés.
*/
/*
Hint 1: || Minden falu ahhoz a központhoz tartozik, amelyhez legközelebb van. Ezért minden központból ki kell számolnod a többi település távolságát, és csak a legkisebb távolságot kell megtartanod. ||
Hint 2: || A távolság az élek száma, ezért szélességi bejárás (BFS) adja a legrövidebb távolságot, és az utak kétirányúak: mindkét végpontból lehet lépni rajtuk. A központokat növekvő sorrendben véve az egyenlő távolságnál a kisebb sorszám marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> centers(m);
    for (int &c : centers) cin >> c;

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < k; ++i) {
        int a, b;
        if (!(cin >> a >> b)) break;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> bestDist(n + 1, -1), bestCenter(n + 1, -1);
    for (int i = 0; i < m; ++i) {
        vector<int> dist(n + 1, -1);
        queue<int> q;
        dist[centers[i]] = 0;
        q.push(centers[i]);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : g[v]) {
                if (dist[u] < 0) {
                    dist[u] = dist[v] + 1;
                    q.push(u);
                }
            }
        }
        for (int v = 1; v <= n; ++v) {
            if (dist[v] < 0) continue;
            if (bestCenter[v] < 0 || dist[v] < bestDist[v]) {
                bestDist[v] = dist[v];
                bestCenter[v] = i;
            }
        }
    }

    vector<int> cnt(m, 0);
    for (int v = 1; v <= n; ++v)
        if (bestCenter[v] >= 0) ++cnt[bestCenter[v]];

    for (int i = 0; i < m; ++i) cout << cnt[i] << "\n";
    return 0;
}
