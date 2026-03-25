/*
Megoldás lényege:
Legyen O egy szélső pont (legalacsonyabb y, majd x). Az O-ból induló irányokat tekintjük.
Minden irányból csak az O-hoz legközelebbi pont számíthat egy üres háromszögben oldalpontnak,
mert a távolabbi, kollineáris pontok az O-hoz közelebbiig tartó szakaszon kívül esnek.

1) Pontokat irány szerint csoportosítjuk (normalizált vektor: (dx/g, dy/g)),
   és irányonként a legközelebbi pontot tartjuk meg.
2) Ezeket az irányokat körszög szerint rendezzük O körül.
3) Két szomszédos irány pontja U,V esetén az OUV háromszög belsejében nincs más pont:
   nem létezik köztes irány. Ezért bármely nem degenerált szomszédos pár jó.

Idő: O(N log N)
*/

#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
    int id;
};

static long long cross(long long ax, long long ay, long long bx, long long by) {
    __int128 v = (__int128)ax * by - (__int128)ay * bx;
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<Pt> p(N);
    for (int i = 0; i < N; ++i) {
        cin >> p[i].x >> p[i].y;
        p[i].id = i + 1;
    }

    int o = 0;
    for (int i = 1; i < N; ++i) {
        if (p[i].y < p[o].y || (p[i].y == p[o].y && p[i].x < p[o].x)) o = i;
    }

    unordered_map<long long, pair<long long, int>> best; // key -> (dist2, index)
    best.reserve(2 * N + 16);

    auto dirKey = [](long long dx, long long dy) {
        // dx,dy már relatívak, normalizálás után tároljuk.
        return (dx << 32) ^ (unsigned int)dy;
    };

    for (int i = 0; i < N; ++i) {
        if (i == o) continue;
        long long dx = p[i].x - p[o].x;
        long long dy = p[i].y - p[o].y;
        long long g = std::gcd(llabs(dx), llabs(dy));
        dx /= g;
        dy /= g;
        long long d2 = (p[i].x - p[o].x) * (p[i].x - p[o].x) +
                       (p[i].y - p[o].y) * (p[i].y - p[o].y);
        long long k = dirKey(dx, dy);
        auto it = best.find(k);
        if (it == best.end() || d2 < it->second.first) best[k] = {d2, i};
    }

    vector<int> cand;
    cand.reserve(best.size());
    for (auto& kv : best) cand.push_back(kv.second.second);

    auto upper = [&](int i) {
        long long dx = p[i].x - p[o].x;
        long long dy = p[i].y - p[o].y;
        return (dy > 0) || (dy == 0 && dx > 0);
    };

    sort(cand.begin(), cand.end(), [&](int i, int j) {
        bool ui = upper(i), uj = upper(j);
        if (ui != uj) return ui > uj;
        long long c = cross(p[i].x - p[o].x, p[i].y - p[o].y,
                            p[j].x - p[o].x, p[j].y - p[o].y);
        if (c != 0) return c > 0;
        long long di = (p[i].x - p[o].x) * (p[i].x - p[o].x) +
                       (p[i].y - p[o].y) * (p[i].y - p[o].y);
        long long dj = (p[j].x - p[o].x) * (p[j].x - p[o].x) +
                       (p[j].y - p[o].y) * (p[j].y - p[o].y);
        return di < dj;
    });

    int m = (int)cand.size();
    for (int i = 0; i < m; ++i) {
        int u = cand[i];
        int v = cand[(i + 1) % m];
        long long c = cross(p[u].x - p[o].x, p[u].y - p[o].y,
                            p[v].x - p[o].x, p[v].y - p[o].y);
        if (c == 0) continue;
        if (c < 0) swap(u, v);
        cout << p[o].id << ' ' << p[u].id << ' ' << p[v].id << '\n';
        return 0;
    }

    // A feladatfeltételek mellett nem jutunk ide.
    cout << "1 2 3\n";
    return 0;
}
