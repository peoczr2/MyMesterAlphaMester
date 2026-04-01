/*
Megoldás lényege:
A számok az A1 legkisebb elem szerinti maradékkal írhatók le. Egy adott maradékosztály
összes előállítható száma egy aritmetikai sorozatot alkot, amelynek legkisebb eleme
meghatározható a maradékosztályok gráfján futtatott legrövidebb úttal.

Először kivesszük az összes szám közös osztóját, mert csak annak többszörösei
állíthatók elő. Ezután a csúcsok a 0..A1-1 maradékok, és minden Ai egy élként
értelmezhető: r-ből (r+Ai) mod A1 maradékba jutunk Ai költséggel. Dijkstra megadja
minden maradék minimális előállítható értékét. Egy B lekérdezésre a legkisebb
előállítható C úgy adódik, hogy a megfelelő maradéknál a kapott minimális értéket
felfelé kerekítjük A1 többszörösére.
*/

#include <bits/stdc++.h>
using namespace std;

static long long gcdll(long long a, long long b) {
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> a(n);
    long long g = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        g = gcdll(g, a[i]);
    }

    int m;
    cin >> m;
    vector<long long> b(m);
    for (int i = 0; i < m; ++i) cin >> b[i];

    for (long long &x : a) x /= g;
    for (long long &x : b) x = (x + g - 1) / g;

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    int mod = (int)a[0];
    if (mod == 1) {
        for (int i = 0; i < m; ++i) {
            if (i) cout << ' ';
            cout << b[i] * g;
        }
        cout << '\n';
        return 0;
    }

    vector<int> coins;
    coins.reserve(a.size());
    for (long long x : a) coins.push_back((int)x);

    const long long INF = (1LL << 62);
    vector<long long> dist(mod, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dist[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d != dist[v]) continue;
        for (int c : coins) {
            int to = (v + c) % mod;
            long long nd = d + c;
            if (nd < dist[to]) {
                dist[to] = nd;
                pq.push({nd, to});
            }
        }
    }

    for (int qi = 0; qi < m; ++qi) {
        long long target = b[qi];
        long long best = INF;
        for (int r = 0; r < mod; ++r) {
            long long x = dist[r];
            if (x == INF) continue;
            if (x < target) {
                long long k = (target - x + mod - 1) / mod;
                x += k * mod;
            }
            best = min(best, x);
        }
        if (qi) cout << ' ';
        cout << best * g;
    }
    cout << '\n';
    return 0;
}