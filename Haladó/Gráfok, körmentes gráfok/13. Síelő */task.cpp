/*
Megoldás lényege:
Minden út kisebb sorszámú csomópontból nagyobb felé halad (A < B), ezért az 1..N sorrend topologikus, és a pályák hosszát
egyetlen, sorszám szerint előrefelé haladó dinamikus programozással lehet kiszámolni. Minden csomóponthoz nyilvántartjuk a
hozzá vezető legrövidebb és leghosszabb pálya hosszát, valamint a hozzá tartozó legkisebb kezdőpont sorszámát. A kezdőpontok
(amelyekbe nem vezet él) hossza 0. Egy él (a, b, h) feldolgozásakor a b csomópont értékét frissítjük az a értékéből h-val
növelve. A végpontok (amelyekből nem vezet él, de van bemenő élük) közül a (hossz, kezdőpont, végpont) rendezés szerinti
legkisebb adja a legrövidebb, a leghosszabb pályát pedig a (-hossz, kezdőpont, végpont) szerint kapjuk meg, így a holtversenyeknél
a minimális sorszámú pálya kerül a kimenetbe. Az időigény O(N + M).
*/
/*
Hint 1: || Mivel minden út kisebb sorszámú csomópontból nagyobb felé megy, a csomópontokat sorszámuk szerint feldolgozva már
mindig ismert, hogy az adott csomópontba vezető utak mind feldolgozottak. ||
Hint 2: || Minden csomópontra tartsd nyilván a hozzá vezető legrövidebb és leghosszabb út hosszát, és a hozzá tartozó legkisebb
kezdőpontot; a kezdőpontok (bemenő él nélküli csomópontok) hossza 0, a végpontok (kimenő él nélküli csomópontok) közül válogass. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, long long>>> out(n + 1);
    vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int a, b;
        long long h;
        cin >> a >> b >> h;
        out[a].push_back({b, h});
        ++indeg[b];
        ++outdeg[a];
    }

    // lo[v], loStart[v]: a v-be vezető legrövidebb pálya hossza és legkisebb kezdőpontja.
    // hi[v], hiStart[v]: ugyanez a leghosszabb pályára.
    const long long INF = LLONG_MAX;
    vector<long long> lo(n + 1, INF), hi(n + 1, -1);
    vector<int> loStart(n + 1, 0), hiStart(n + 1, 0);
    for (int v = 1; v <= n; ++v) {
        if (indeg[v] == 0) {
            lo[v] = 0;
            hi[v] = 0;
            loStart[v] = v;
            hiStart[v] = v;
        }
    }

    // A sorszám szerinti bejárás topologikus, így v értéke már végleges, amikor kiterjesztjük az éleit.
    for (int v = 1; v <= n; ++v) {
        for (const auto& [w, h] : out[v]) {
            long long nl = lo[v] + h;
            if (nl < lo[w] || (nl == lo[w] && loStart[v] < loStart[w])) {
                lo[w] = nl;
                loStart[w] = loStart[v];
            }
            long long nh = hi[v] + h;
            if (nh > hi[w] || (nh == hi[w] && hiStart[v] < hiStart[w])) {
                hi[w] = nh;
                hiStart[w] = hiStart[v];
            }
        }
    }

    // Egy pálya: (hossz, kezdőpont, végpont). A legkisebb rendezett elem adja a választ.
    tuple<long long, int, int> bestMin(LLONG_MAX, 0, 0), bestMax(LLONG_MAX, 0, 0);
    for (int t = 1; t <= n; ++t) {
        if (indeg[t] == 0 || outdeg[t] != 0) {
            continue;
        }
        bestMin = min(bestMin, make_tuple(lo[t], loStart[t], t));
        bestMax = min(bestMax, make_tuple(-hi[t], hiStart[t], t));
    }

    cout << get<0>(bestMin) << ' ' << get<1>(bestMin) << ' ' << get<2>(bestMin) << '\n';
    cout << -get<0>(bestMax) << ' ' << get<1>(bestMax) << ' ' << get<2>(bestMax) << '\n';
    return 0;
}
