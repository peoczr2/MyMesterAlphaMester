/*
Megoldás lényege:
Két szélességi bejárást végzünk: az egyiket az A, a másikat a B raktár városából indítjuk, így minden
városhoz megkapjuk a két távolságot (dA és dB). Egy város A-ból (dA) vagy B-ből (dB) kaphatja az árut,
és pontosan N/2 városnak kell A-ból kapnia. Az összköltség felírható Σ dB + Σ (dA − dB) alakban, ahol
a második összegben az A-ból ellátott városok szerepelnek, ezért a dA − dB különbség szerint növekvően
rendezve az első N/2 város kapja az A raktárat. Ez a kiosztás a kényszer mellett is optimális, mert
bármely más N/2-es választás legalább ennyi költséget ad. Az időigény O(N log N + M), a költség 64 bites
egész (long long), a biztonság kedvéért.
*/
/*
Hint 1: || Két szélességi bejárást kell végezni: egyet az A, egyet a B városból indulva. Így minden városhoz tudod a két távolságot. ||
Hint 2: || A feltétel csak annyi, hogy pontosan N/2 várost látunk el A-ból. Írd fel az összköltséget úgy, hogy alapértelmezésben mindenki B-ből kapjon, és csak a különbséget kelljen hozzáadni. ||
Hint 3: || Az összköltség Σ dB + Σ (dA − dB), ahol a második összeg az A-ból ellátott városokon fut. Rendezd a városokat a dA − dB különbség szerint, és az első N/2 város kapja az A-t. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> bfsDist(int n, const vector<vector<int>>& adj, int src) {
    vector<int> d(n + 1, -1);
    queue<int> q;
    d[src] = 0;
    q.push(src);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (d[v] < 0) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> da = bfsDist(n, adj, a);
    vector<int> db = bfsDist(n, adj, b);

    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    stable_sort(order.begin(), order.end(), [&](int x, int y) {
        return da[x] - db[x] < da[y] - db[y];
    });

    long long cost = 0;
    for (int i = 1; i <= n; ++i) cost += db[i];
    vector<char> fromA(n + 1, 0);
    for (int i = 0; i < n / 2; ++i) {
        int c = order[i];
        fromA[c] = 1;
        cost += da[c] - db[c];
    }

    string res;
    for (int i = 1; i <= n; ++i) res += fromA[i] ? 'A' : 'B';
    cout << cost << '\n' << res << '\n';
    return 0;
}
