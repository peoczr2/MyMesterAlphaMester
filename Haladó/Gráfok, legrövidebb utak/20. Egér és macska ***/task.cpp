/*
Megoldás lényege:
A macska legkorábbi érkezési idejét (dc) minden pontba Dijkstra-algoritmussal számoljuk ki, a macska kezdőpontjából indulva.
Az egér keresése is Dijkstra, de az egér csak olyan pontba léphet be t időpontban, ahol a macska ideje (dc) szigorúan nagyobb t-nél,
mert egyenlő vagy korábbi érkezésnél a macska már elkapná az egeret. A korábbi biztonságos érkezés mindig előnyösebb,
ezért a Dijkstra minden pontba az egér legkorábbi biztonságos érkezését adja meg. Az első elért egérlyukat (olyan pont, ahonnan
nincs kimenő él) választjuk, és a szülőtömbön keresztül visszaállítjuk az utat. Az idő O(M log N), ami N ≤ 200 és M ≤ 10 000 mellett
messze belefér a 0,1 mp-es korlátba.
*/
/*
Hint 1: || A macska távolságait egy szokásos legrövidebb út kereséssel kiszámíthatod, az egér útját is hasonlóan kell keresni, de csak akkor léphet egy pontba, ha ott még nem várja a macska. ||
Hint 2: || Legyen dc[P] a macska legkorábbi érkezési ideje P-be, dm[P] pedig az egér ideje a megtett úton. Az egér csak akkor léphet P-be, ha dm[P] < dc[P], mert egyenlőségnél a macska már elkapná. ||
Hint 3: || Egérlyuk az a pont, ahonnan nincs kimenő él. Az egér keresésénél az első ilyen pontot, amit kiemelsz a prioritási sorból, válaszd, az utat a szülőtömbből fordított sorrendben állítsd vissza, és a kezdőpont is kerüljön a kiírásba. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, ic, ie; // a macska és az egér ideje az élen
};

int main() {
    int n, m;
    cin >> n >> m;
    int a, b; // a macska és az egér kezdőpontja
    cin >> a >> b;

    vector<vector<Edge>> adj(n + 1);
    vector<int> outdeg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int k, v, ic, ie;
        cin >> k >> v >> ic >> ie;
        adj[k].push_back({v, ic, ie});
        outdeg[k]++;
    }

    const long long INF = LLONG_MAX / 4;
    using State = pair<long long, int>;

    // A macska legkorábbi érkezési ideje minden pontba
    vector<long long> dc(n + 1, INF);
    priority_queue<State, vector<State>, greater<State>> pq;
    dc[a] = 0;
    pq.push({0, a});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dc[u]) continue;
        for (const Edge& e : adj[u]) {
            if (d + e.ic < dc[e.to]) {
                dc[e.to] = d + e.ic;
                pq.push({dc[e.to], e.to});
            }
        }
    }

    // Az egér legkorábbi biztonságos érkezési ideje minden pontba
    vector<long long> dm(n + 1, INF);
    vector<int> par(n + 1, 0);
    dm[b] = 0;
    pq.push({0, b});
    int hole = 0;
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dm[u]) continue;
        if (outdeg[u] == 0) { // egérlyuk: az első kiemelt ilyen pont a legkorábbi
            hole = u;
            break;
        }
        for (const Edge& e : adj[u]) {
            long long nd = d + e.ie;
            if (nd < dc[e.to] && nd < dm[e.to]) {
                dm[e.to] = nd;
                par[e.to] = u;
                pq.push({nd, e.to});
            }
        }
    }

    if (hole == 0) {
        cout << 0 << "\n";
        return 0;
    }

    vector<int> path;
    for (int v = hole;; v = par[v]) {
        path.push_back(v);
        if (v == b) break;
    }
    reverse(path.begin(), path.end());
    for (size_t i = 0; i < path.size(); i++) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << "\n";
    return 0;
}
