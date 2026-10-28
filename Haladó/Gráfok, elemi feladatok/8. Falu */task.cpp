/*
Megoldás lényege:
A zsákfalvak a pontosan egy úttal rendelkező települések, a legtöbb út a fokszámok maximuma.
A harmadik kérdésben a távolság a legrövidebb út hossza, ezért minden település kiindulópontjából
Dijkstra-algoritmussal kiszámoljuk a távolságokat. A nem szomszédos párok közül a legkisebb
távolságút választjuk; egyenlőség esetén a sorszámokban lexikografikusan kisebb pár nyer, mivel
a kezdőcsúcsokat és a végpontokat is növekvő sorrendben vizsgáljuk. Az időigény O(N·M log M),
N ≤ 1000 és M ≤ 10000 mellett elfogadható.
*/
/*
Hint 1: || A zsákfalvak száma egyszerű: azokat a településeket kell megszámolnod, amelyekhez pontosan egy út vezet. A legtöbb utat a fokszámok maximuma adja. ||
Hint 2: || A két legközelebbi, nem szomszédos település távolsága a legrövidebb út hossza, ezért minden kezdőcsúcsból futtass Dijkstra-algoritmust; N legfeljebb 1000. ||
Hint 3: || Csak azokat a párokat vedd figyelembe, amelyek között nincs közvetlen út, és tartsd meg a legkisebb távolságút; egyenlőségnél a lexikografikusan kisebb párt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, long long>>> g(n + 1);
    vector<vector<char>> szomszed(n + 1, vector<char>(n + 1, 0));
    vector<int> fok(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
        szomszed[u][v] = szomszed[v][u] = 1;
        fok[u]++;
        fok[v]++;
    }

    // A: zsákfalvak száma
    int zsakfalvak = 0;
    for (int v = 1; v <= n; v++)
        if (fok[v] == 1) zsakfalvak++;

    // B: a legtöbb úttal rendelkező települések közül a legkisebb sorszámú
    int maxFok = 0;
    for (int v = 1; v <= n; v++) maxFok = max(maxFok, fok[v]);
    int legtobbUt = 1;
    for (int v = 1; v <= n; v++)
        if (fok[v] == maxFok) {
            legtobbUt = v;
            break;
        }

    // C: legközelebbi nem szomszédos pár, Dijkstra minden kezdőcsúcsból
    const long long INF = LLONG_MAX / 4;
    long long legkisebb = INF;
    int pu = -1, pv = -1;
    vector<long long> dist(n + 1);
    for (int s = 1; s <= n; s++) {
        fill(dist.begin(), dist.end(), INF);
        dist[s] = 0;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        pq.push({0, s});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > legkisebb) break;
            if (d != dist[u]) continue;
            for (auto [v, w] : g[u]) {
                if (d + w < dist[v]) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }
        for (int t = s + 1; t <= n; t++) {
            if (szomszed[s][t] || dist[t] >= INF) continue;
            if (dist[t] < legkisebb) {
                legkisebb = dist[t];
                pu = s;
                pv = t;
            }
        }
    }

    cout << zsakfalvak << '\n' << legtobbUt << '\n' << pu << ' ' << pv << '\n';
    return 0;
}
