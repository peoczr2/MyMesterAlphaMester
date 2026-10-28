/*
Megoldás lényege:
A számokat az A1 szerinti maradékosztályokba soroljuk. Minden r maradékosztályban van egy legkisebb
előállítható szám, legyen d_r. A lépéseket az A2 és A3 hozzáadása adja: egy maradékról a másikra
lépve a hozzáadott szám a költség, így d_r legrövidebb úttal (Dijkstra-algoritmussal) számolható ki,
A1 csomóponttal. Az r maradékú előállítható számok pontosan a d_r + k*A1 alakú számok (k >= 0),
mert A1 tetszőleges számszor hozzáadható. Egy B-hez minden maradékosztályban megkeressük az első,
B-nél nem kisebb ilyen számot, és ezek közül a legkisebbet válaszoljuk. Egy lekérdezés O(A1) időben fut.
*/
/*
Hint 1: || Nézd meg, hogy az előállítható számok maradéka A1 szerint hogyan változik, ha A2-t vagy A3-at adunk hozzá. ||
Hint 2: || Minden A1 szerinti maradékosztályban van egy legkisebb előállítható szám. Ezt a legrövidebb út (Dijkstra) módszerével számold ki, ahol a lépés A2 vagy A3 hozzáadása. ||
Hint 3: || Egy maradékosztály előállítható számai a legkisebb számtól kezdve A1 többszörösével követik egymást. B-hez maradékosztályonként keresd meg az első B-nél nem kisebb számot, és a legkisebbet vedd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a1, a2, a3;
    cin >> a1 >> a2 >> a3;
    int m;
    cin >> m;
    vector<long long> b(m);
    for (auto& x : b) cin >> x;

    const long long INF = LLONG_MAX / 4;
    int k = (int)a1;
    vector<long long> dist(k, INF);  // dist[r]: legkisebb előállítható szám, amely r maradékú
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, r] = pq.top();
        pq.pop();
        if (d != dist[r]) continue;
        for (long long step : {a2, a3}) {
            int nr = (int)((r + step) % a1);
            long long nd = d + step;
            if (nd < dist[nr]) {
                dist[nr] = nd;
                pq.push({nd, nr});
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        long long best = INF;
        for (int r = 0; r < k; ++r) {
            if (dist[r] >= INF) continue;
            long long c;
            if (dist[r] >= b[i]) {
                c = dist[r];
            } else {
                long long t = (b[i] - dist[r] + a1 - 1) / a1;
                c = dist[r] + t * a1;
            }
            best = min(best, c);
        }
        cout << best << (i + 1 < m ? ' ' : '\n');
    }
    return 0;
}
