/*
Megoldás lényege:
Az út által létrehozott darabok száma: 1 + C, ahol C az útszakasz poligon-belsőben fekvő
összefüggő részeinek száma.

Ezért kiszámítjuk K határmetszési pontot az AB szakaszon:
1) élek belsejében történő (szigorú) metszések,
2) AB-re eső csúcspontok, de csak akkor számítanak metszésnek, ha a csúcs két szomszédja
   az AB egyenes két külön oldalán van (különben csak érintés).

Legyen K a valódi határ-átlépések száma az AB mentén (toggle események).
Ha az AB elején (A után közvetlenül) bent vagyunk, akkor C = 1 + K/2,
különben C = (K+1)/2.
Így a válasz: 1 + C.

Idő: O(N)
*/

#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
};

static long long orient(const Pt& a, const Pt& b, const Pt& c) {
    __int128 x1 = b.x - a.x;
    __int128 y1 = b.y - a.y;
    __int128 x2 = c.x - a.x;
    __int128 y2 = c.y - a.y;
    __int128 v = x1 * y2 - y1 * x2;
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}

static bool onSegment(const Pt& a, const Pt& b, const Pt& p) {
    if (orient(a, b, p) != 0) return false;
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<Pt> p(N);
    for (int i = 0; i < N; ++i) cin >> p[i].x >> p[i].y;

    Pt A, B;
    cin >> A.x >> A.y >> B.x >> B.y;

    vector<int> s(N);
    for (int i = 0; i < N; ++i) s[i] = (int)orient(A, B, p[i]); // side wrt AB line

    long long K = 0;

    // 1) Proper crossings in edge interiors.
    for (int i = 0; i < N; ++i) {
        const Pt& u = p[i];
        const Pt& v = p[(i + 1) % N];

        int su = s[i], sv = s[(i + 1) % N];
        if (su == 0 || sv == 0) continue;
        if (1LL * su * sv < 0) {
            long long o1 = orient(u, v, A);
            long long o2 = orient(u, v, B);
            if (o1 == 0 || o2 == 0 || 1LL * o1 * o2 <= 0) {
                ++K;
            }
        }
    }

    // 2) Crossings exactly at vertices on AB.
    vector<int> prevNZ(N, -1), nextNZ(N, -1);
    int last = -1;
    for (int t = 0; t < 2 * N; ++t) {
        int i = t % N;
        if (s[i] != 0) last = i;
        if (t >= N) prevNZ[i] = last;
    }
    last = -1;
    for (int t = 2 * N - 1; t >= 0; --t) {
        int i = t % N;
        if (s[i] != 0) last = i;
        if (t < N) nextNZ[i] = last;
    }

    for (int i = 0; i < N; ++i) {
        if (s[i] != 0) continue;
        if (!onSegment(A, B, p[i])) continue;
        int li = prevNZ[i], ri = nextNZ[i];
        if (li == -1 || ri == -1) continue;
        if (1LL * s[li] * s[ri] < 0) ++K;
    }

    // Determine whether just after A we are inside.
    long double tx = (long double)A.x + ((long double)B.x - (long double)A.x) * 1e-9L;
    long double ty = (long double)A.y + ((long double)B.y - (long double)A.y) * 1e-9L;

    bool startInside = false;
    for (int i = 0, j = N - 1; i < N; j = i++) {
        long double xi = (long double)p[i].x, yi = (long double)p[i].y;
        long double xj = (long double)p[j].x, yj = (long double)p[j].y;
        bool intersects = ((yi > ty) != (yj > ty)) &&
                          (tx < (xj - xi) * (ty - yi) / (yj - yi) + xi);
        if (intersects) startInside = !startInside;
    }

    long long components = startInside ? (1 + K / 2) : ((K + 1) / 2);
    cout << (1 + components) << '\n';
    return 0;
}
