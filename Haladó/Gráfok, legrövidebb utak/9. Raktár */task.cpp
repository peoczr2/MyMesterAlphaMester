/*
Megoldás lényege:
A városok fát alkotnak, és két város közötti távolság az élek száma. Egy U-ból V-be szállított D mennyiség költsége D·t(U,V),
így a raktár költsége: Σ w(u)·t(u,raktár), ahol w(u) az u városban gyártott alkatrészek száma.
Gyökerezzük a fát az 1-es városban, és számoljuk ki minden részfa súlyösszegét (S), valamint a gyökérből mért teljes költséget.
Ha a gyökeret egy gyerekére helyezzük át, a gyerek részfájába eső csúcsok 1-gyel közelebb, a többiek 1-gyel távolabb kerülnek,
így a költség változása T − 2·S_gyerek, ahol T az összes súly. Egyetlen bejárással minden csúcs költsége kiszámítható;
a legkisebb költségű csúcsok közül a legkisebb sorszámút kell kiírni. A futás O(N).
*/
/*
Hint 1: || Rögzíts egy gyökércsúcsot, és számold ki a gyökérből minden városba mutató távolságot: a költség a súly és a távolság szorzatainak összege. ||
Hint 2: || Gyökércsere a szomszédos gyerekre: a gyerek részfájában lévő súly 1-gyel közelebb, a többi 1-gyel távolabb kerül. A költség változása így a teljes súly és a gyerek részfájának súlya alapján adódik. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> w(n + 1);
    long long total = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        total += w[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Bejárás a gyökérből (1): sorrend, szülő, mélység.
    vector<int> order, parent(n + 1, 0);
    vector<long long> depth(n + 1, 0);
    vector<char> seen(n + 1, 0);
    order.reserve(n);
    order.push_back(1);
    seen[1] = 1;
    for (size_t h = 0; h < order.size(); ++h) {
        int u = order[h];
        for (int v : adj[u]) {
            if (!seen[v]) {
                seen[v] = 1;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                order.push_back(v);
            }
        }
    }

    // Részfák súlyösszege: a bejárási sorrend fordítottjában a gyerekek a szülőbe adódnak.
    vector<long long> sub(w);
    for (int h = n - 1; h > 0; --h) {
        int u = order[h];
        sub[parent[u]] += sub[u];
    }

    // Költség a gyökérben, majd gyerekről gyerekre (szülőből) az áthelyezés szerint.
    long long rootCost = 0;
    for (int i = 1; i <= n; ++i) {
        rootCost += w[i] * depth[i];
    }
    vector<long long> cost(n + 1, 0);
    cost[1] = rootCost;
    for (int h = 1; h < n; ++h) {
        int u = order[h];
        cost[u] = cost[parent[u]] + total - 2 * sub[u];
    }

    // A legkisebb költség; egyenlőségnél a kisebb sorszám marad.
    int best = 1;
    for (int i = 2; i <= n; ++i) {
        if (cost[i] < cost[best]) best = i;
    }

    cout << cost[best] << '\n' << best << '\n';
    return 0;
}
