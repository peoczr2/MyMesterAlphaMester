/*
Megoldás lényege:
Az R központból mélységi bejárást (DFS) végzünk, és minden csúcshoz kiszámoljuk a bejárási sorszámát (tin) és a low értékét. Egy fa-él (p, c) híd, ha low[c] > tin[p]: ilyenkor a c részfájából nem lehet a p-nél korábban bejárt csúcsba visszajutni. Egy csúcsba pontosan akkor vezet egyetlen út R-ből, ha az R-től odáig vezető fa-úton minden él híd, mert egy nem híd él benne van egy körben, és a körön keresztül második út is vezet. A csúcsokat a bejárási sorrendben haladva egy logikai jelzéssel vezetjük végig: egy csúcs jó, ha a szülője jó és a hozzá vezető él híd. Az időigény O(N+M), amit a 10^6 él beolvasása dominál.
*/
/*
Hint 1: || Egy csúcsba akkor vezet csak egy út, ha az úton minden él híd. Ha egy él benne van körben, a körön megkerülve második út vezet a csúcsba. ||
Hint 2: || Mélységi bejárásnál a (p, c) fa-él akkor híd, ha a c részfájából nem érhető el p-nél korábban bejárt csúcs. Ezt a low[c] > tin[p] feltétel adja, ahol low[c] a c részfájából elérhető legkisebb bejárási sorszám. ||
Hint 3: || A bejárási sorrendben haladva egy csúcs jó, ha a szülője jó és a hozzá vezető él híd. Az R-től különböző jó csúcsokat kell megszámolni és kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m, r;
vector<int> startIdx, adj, tin, low, par, order_;
int timer_ = 0;

void dfs(int v, int p) {
    tin[v] = low[v] = ++timer_;
    par[v] = p;
    order_.push_back(v);
    for (int i = startIdx[v]; i < startIdx[v + 1]; ++i) {
        int to = adj[i];
        if (to == p) continue;  // nincs párhuzamos él, így a szülőt egyszerűen kihagyhatjuk
        if (tin[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> r;
    vector<int> eu(m), ev(m);
    startIdx.assign(n + 2, 0);
    for (int i = 0; i < m; ++i) {
        cin >> eu[i] >> ev[i];
        startIdx[eu[i] + 1]++;
        startIdx[ev[i] + 1]++;
    }
    for (int v = 1; v <= n + 1; ++v) startIdx[v] += startIdx[v - 1];

    adj.assign(2 * m, 0);
    vector<int> pos(startIdx);
    for (int i = 0; i < m; ++i) {
        adj[pos[eu[i]]++] = ev[i];
        adj[pos[ev[i]]++] = eu[i];
    }

    tin.assign(n + 1, 0);
    low.assign(n + 1, 0);
    par.assign(n + 1, 0);
    dfs(r, 0);

    vector<char> good(n + 1, 0);
    good[r] = 1;
    vector<int> ans;
    for (size_t idx = 1; idx < order_.size(); ++idx) {  // order_[0] = r, a szülő mindig előbb van
        int v = order_[idx];
        int p = par[v];
        if (good[p] && low[v] > tin[p]) good[v] = 1;
        if (good[v]) ans.push_back(v);
    }
    sort(ans.begin(), ans.end());

    cout << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); ++i) cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
    if (ans.empty()) cout << "\n";
    return 0;
}
