/*
Megoldás lényege:
Legyen d(v) a v-ből a B-be vezető legrövidebb út hossza (Dijkstra, B-ből indulva). Egy vonaton nem mehetünk távolabb B-től, mint ahol felszálltunk, tehát az u -> w lépés csak akkor megengedett, ha d(w) <= d(u). Az azonos d-értékű csúcsok között az élek mindkét irányban járhatók, ezért az ilyen éleken összekötött csúcsok egy csoportot alkotnak (DSU). Egy csoport minden csúcsa egy jegyen bejárható, ha a csoporton belül be tudunk jönni és ki tudunk menni a kívánt élen. A csoportok közötti átmenetek szigorúan csökkenő távolságúak, így a csoportok között egy irányított körmentes gráf van. Ezen a DP-vel (távolság szerinti növekvő sorrendben) a legnagyobb összsúlyú A-ból B-be vezető láncot kapjuk, ahol a csoport súlya a méret. Az időigény O((N + M) log N).
*/
/*
Hint 1: || Számold ki minden állomásra a B-től mért legrövidebb távolságot Dijkstra-algoritmussal. Vonaton csak olyan irányban léphetsz u-ról w-re, ahol w távolsága B-től nem nagyobb, mint u-é. ||
Hint 2: || Az azonos távolságú állomások között az élek mindkét irányban járhatók, így ezeket összevonhatod egy csoportba (DSU). A csoportok közötti lépések szigorúan csökkenő távolságúak, tehát a csoport-gráf körmentes. ||
Hint 3: || Csoportokra futtass DP-t a távolság szerinti növekvő sorrendben: f(C) = |C| + max f(C') azon C' csoportokra, amelyekbe C-ből szigorúan alacsonyabb távolságú él vezet; B csoportjának értéke 1. A válasz f(A csoportja), a lánc csoportjainak csúcsait kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

static vector<int> par;

int findRoot(int x) {
    while (par[x] != x) {
        par[x] = par[par[x]];
        x = par[x];
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, A, B;
    cin >> N >> M >> A >> B;
    vector<int> X(M), Y(M), T(M);
    vector<int> deg(N + 2, 0);
    for (int i = 0; i < M; i++) {
        cin >> X[i] >> Y[i] >> T[i];
        deg[X[i]]++;
        deg[Y[i]]++;
    }

    // Szomszédsági lista CSR formában.
    vector<int> start(N + 2, 0);
    for (int v = 1; v <= N; v++) start[v + 1] = start[v] + deg[v];
    vector<int> fill_(start.begin(), start.end());
    vector<int> adjTo(2 * M), adjW(2 * M);
    for (int i = 0; i < M; i++) {
        adjTo[fill_[X[i]]] = Y[i];
        adjW[fill_[X[i]]++] = T[i];
        adjTo[fill_[Y[i]]] = X[i];
        adjW[fill_[Y[i]]++] = T[i];
    }

    // d[v]: a v-ből B-be vezető legrövidebb út hossza.
    const long long INF = LLONG_MAX / 4;
    vector<long long> d(N + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    d[B] = 0;
    pq.push({0, B});
    while (!pq.empty()) {
        auto [dist, u] = pq.top();
        pq.pop();
        if (dist != d[u]) continue;
        for (int k = start[u]; k < start[u + 1]; k++) {
            int v = adjTo[k];
            long long nd = dist + adjW[k];
            if (nd < d[v]) {
                d[v] = nd;
                pq.push({nd, v});
            }
        }
    }

    // Azonos d-értékű csúcsok összevonása (az ilyen élek mindkét irányban járhatók).
    par.resize(N + 1);
    for (int v = 0; v <= N; v++) par[v] = v;
    for (int i = 0; i < M; i++) {
        int u = X[i], v = Y[i];
        if (d[u] < INF && d[u] == d[v]) {
            int ru = findRoot(u), rv = findRoot(v);
            if (ru != rv) par[ru] = rv;
        }
    }

    vector<int> comp(N + 1, 0);
    vector<vector<int>> members(N + 1);
    vector<int> roots;
    for (int v = 1; v <= N; v++) {
        if (d[v] >= INF) continue;
        comp[v] = findRoot(v);
        members[comp[v]].push_back(v);
    }
    for (int v = 1; v <= N; v++)
        if (d[v] < INF && comp[v] == v) roots.push_back(v);
    sort(roots.begin(), roots.end(), [&](int a, int b) { return d[a] < d[b]; });

    // DP a csoportok között: f(C) = |C| + max f(C'), ahol C'-be szigorúan kisebb távolságú él vezet.
    const int NONE = -1;
    vector<long long> f(N + 1, NONE);
    vector<int> nxt(N + 1, 0);
    int rootA = comp[A], rootB = comp[B];
    for (int r : roots) {
        if (r == rootB) {
            f[r] = (long long)members[r].size();
            continue;
        }
        long long best = NONE;
        int bestC = 0;
        for (int u : members[r]) {
            for (int k = start[u]; k < start[u + 1]; k++) {
                int v = adjTo[k];
                if (d[v] < d[u]) {
                    int c = comp[v];
                    if (f[c] > best) {
                        best = f[c];
                        bestC = c;
                    }
                }
            }
        }
        if (best != NONE) {
            f[r] = (long long)members[r].size() + best;
            nxt[r] = bestC;
        }
    }

    // A lánc csúcsainak összegyűjtése A csoportjától B-ig.
    vector<int> res;
    int r = rootA;
    while (r != rootB) {
        for (int v : members[r]) res.push_back(v);
        r = nxt[r];
    }
    for (int v : members[rootB]) res.push_back(v);
    sort(res.begin(), res.end());

    string out = to_string(res.size()) + "\n";
    for (size_t i = 0; i < res.size(); i++) {
        out += to_string(res[i]);
        out += (i + 1 == res.size() ? '\n' : ' ');
    }
    cout << out;
    return 0;
}
