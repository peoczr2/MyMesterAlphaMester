/*
Megoldási ötlet:
A számok tetszőleges sokszor felhasználhatók, ezért a feladat egy végtelen pénzérmés elérhetőségvizsgálat. Ha az összes számot leosztjuk
az összesük legnagyobb közös osztójával, akkor csak az marad kérdés, hogy egy adott maradékosztályban mi a legkisebb elérhető szám.

Legyen m a legkisebb megadott szám. A maradékosztályokat modulo m vizsgáljuk, és Dijkstra-val kiszámítjuk minden maradékhoz a legkisebb
előállítható értéket. Egy b szám pontosan akkor állítható elő, ha osztható a gcd-vel, és a redukált maradékosztályában a kiszámított
minimum nem nagyobb nála.
*/
/*
Hint 1: || A gcd már önmagában sok kérdést eldönt: ami nem osztható vele, az biztosan nem állítható elő. ||
Hint 2: || Elég a legkisebb szám modulo osztályait vizsgálni. ||
Hint 3: || Minden maradékhoz a legkisebb elérhető összeg után már ugyanaz a maradék bármennyi plusz legkisebb számmal újra előállítható. ||
*/

#include <bits/stdc++.h>
using namespace std;

static const long long INF = (1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<long long> a(n), b(m);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];

    long long g = 0;
    for (long long x : a) g = gcd(g, x);

    for (long long& x : a) x /= g;
    long long mod = *min_element(a.begin(), a.end());

    vector<long long> dist(mod, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dist[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [curDist, rem] = pq.top();
        pq.pop();
        if (curDist != dist[rem]) continue;
        for (long long x : a) {
            int nrem = static_cast<int>((rem + x) % mod);
            long long ndist = curDist + x;
            if (ndist < dist[nrem]) {
                dist[nrem] = ndist;
                pq.push({ndist, nrem});
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        long long x = b[i];
        int ok = 0;
        if (x % g == 0) {
            long long y = x / g;
            ok = (dist[y % mod] <= y);
        }
        if (i) cout << ' ';
        cout << ok;
    }
    cout << '\n';
    return 0;
}