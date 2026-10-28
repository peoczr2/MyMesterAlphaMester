/*
Megoldás lényege:
Csak a q-ból látszó pontok lehetnek csúcsok: irányonként a legközelebbi pont, mert a távolabbi pont a q-ból a belsejébe esne. Két csúcs (a,b) között a (q,a,b) háromszögben nem lehet más pont. Ha a-ból kiindulva szögrendben végigmegyünk a pontokon, b akkor jó, ha (b-a) iránya nagyobb minden korábbi (k-a) iránynál, vagyis b a prefix-maximum. Ezt egy futással, keresztszorzattal lehet eldönteni, így minden a-ra O(N) munka kell. Ezután olyan a,b,c,d négyes kell, ahol minden él jó és minden csúcsnál balra fordul az út: ekkor a négyszög konvex, q a belsejében van, és nincs más pont benne. Időigény: O(N^2) a teljes keresésre (a 0,1 másodperces limit nagy N-re nem teljesül).
*/
/*
Hint 1: || Csak a q-ból látszó pontokat érdemes vizsgálni: irányonként a legközelebbi pont lehet csúcs, a távolabbiak mindig a belsejébe kerülnének. ||
Hint 2: || Két csúcs (a,b) között a (q,a,b) háromszögben nem lehet más pont. Szögrendben haladva az a-ból nézett irányok prefix-maximumai (rekordjai) pontosan a jó b-k; ezt egy futással, vektoros keresztszorzattal lehet eldönteni. ||
Hint 3: || Építsd fel minden a pontra a jó b-k listáját, majd keress 4-ciklust a jó élekben úgy, hogy minden csúcsnál balra forduljon az út; a q belsejében-lét az élek 180 foknál kisebb szögéből következik. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

static char ibuf[1 << 16];
static size_t ipos = 0, ilen = 0;
static inline int gc() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}
static inline ll readLL() {
    int c = gc();
    while (c != '-' && (c < '0' || c > '9')) c = gc();
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = gc();
    }
    ll r = 0;
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = gc();
    }
    return neg ? -r : r;
}

struct Vec {
    ll x, y;
};
static inline ll crs(const Vec& a, const Vec& b) { return a.x * b.y - a.y * b.x; }
static inline ll ori(const Vec& p, const Vec& q, const Vec& r) {
    return crs({q.x - p.x, q.y - p.y}, {r.x - p.x, r.y - p.y});
}

struct Ent {
    ll kx, ky, dist;
    ll dx, dy;
    int idx;
};

int main() {
    int K = (int)readLL();
    string out;
    while (K--) {
        int n = (int)readLL();
        ll qx = readLL(), qy = readLL();
        vector<ll> X(n), Y(n);
        for (int i = 0; i < n; i++) {
            X[i] = readLL();
            Y[i] = readLL();
        }

        bool zero = false;
        vector<Ent> es;
        es.reserve(n);
        for (int i = 0; i < n; i++) {
            ll dx = X[i] - qx, dy = Y[i] - qy;
            if (dx == 0 && dy == 0) {
                zero = true;
                break;
            }
            ll g = std::gcd(llabs(dx), llabs(dy));
            es.push_back({dx / g, dy / g, dx * dx + dy * dy, dx, dy, i});
        }

        // Irányonként a legközelebbi pont; azonos pontok (duplikált koordináta) nem lehetnek csúcsok.
        vector<Vec> P;
        vector<int> orig;
        vector<char> cand;
        if (!zero) {
            sort(es.begin(), es.end(), [](const Ent& a, const Ent& b) {
                if (a.kx != b.kx) return a.kx < b.kx;
                if (a.ky != b.ky) return a.ky < b.ky;
                return a.dist < b.dist;
            });
            for (size_t i = 0; i < es.size();) {
                size_t j = i;
                while (j < es.size() && es[j].kx == es[i].kx && es[j].ky == es[i].ky) j++;
                bool dup = (i + 1 < j && es[i + 1].dist == es[i].dist);
                P.push_back({es[i].dx, es[i].dy});
                orig.push_back(es[i].idx);
                cand.push_back(dup ? 0 : 1);
                i = j;
            }
        }

        int m = (int)P.size();
        bool found = false;
        int ra = 0, rb = 0, rc = 0, rd = 0;
        if (!zero && m >= 4) {
            // Szögrendezés (óramutató-ellenes), a félsíkos összehasonlítással.
            vector<int> ord(m);
            iota(ord.begin(), ord.end(), 0);
            auto half = [&](const Vec& v) { return (v.y < 0 || (v.y == 0 && v.x < 0)) ? 1 : 0; };
            sort(ord.begin(), ord.end(), [&](int i, int j) {
                int hi = half(P[i]), hj = half(P[j]);
                if (hi != hj) return hi < hj;
                return crs(P[i], P[j]) > 0;
            });
            {
                vector<Vec> P2(m);
                vector<int> O2(m);
                vector<char> C2(m);
                for (int i = 0; i < m; i++) {
                    P2[i] = P[ord[i]];
                    O2[i] = orig[ord[i]];
                    C2[i] = cand[ord[i]];
                }
                P = P2;
                orig = O2;
                cand = C2;
            }

            // R[a]: a-ból jó élek, eltolásként (b - a mod m), növekvő sorrendben.
            vector<vector<int>> R(m);
            vector<char> done(m, 0);
            auto ensureRow = [&](int a) {
                if (done[a]) return;
                done[a] = 1;
                bool has = false;
                Vec M{0, 0};
                for (int step = 1; step < m; step++) {
                    int b = a + step;
                    if (b >= m) b -= m;
                    if (crs(P[a], P[b]) <= 0) break;  // a és b közti szög >= 180 fok
                    Vec d{P[b].x - P[a].x, P[b].y - P[a].y};
                    if (!has || crs(M, d) > 0) {
                        if (cand[b]) R[a].push_back(step);
                        M = d;
                        has = true;
                    }
                }
            };
            auto hasEdge = [&](int d, int a) -> bool {
                int need = a - d;
                if (need < 0) need += m;
                return binary_search(R[d].begin(), R[d].end(), need);
            };

            for (int a = 0; a < m && !found; a++) {
                if (!cand[a]) continue;
                ensureRow(a);
                for (int sb : R[a]) {
                    if (found) break;
                    int b = a + sb;
                    if (b >= m) b -= m;
                    ensureRow(b);
                    for (int sc : R[b]) {
                        if (found) break;
                        int c = b + sc;
                        if (c >= m) c -= m;
                        if (ori(P[a], P[b], P[c]) <= 0) continue;
                        ensureRow(c);
                        for (int sd : R[c]) {
                            int d = c + sd;
                            if (d >= m) d -= m;
                            if (ori(P[b], P[c], P[d]) <= 0) continue;
                            if (ori(P[c], P[d], P[a]) <= 0) continue;
                            if (ori(P[d], P[a], P[b]) <= 0) continue;
                            ensureRow(d);
                            if (hasEdge(d, a)) {
                                found = true;
                                ra = a;
                                rb = b;
                                rc = c;
                                rd = d;
                                break;
                            }
                        }
                    }
                }
            }
        }

        if (found) {
            out += to_string(orig[ra] + 1) + " " + to_string(orig[rb] + 1) + " " + to_string(orig[rc] + 1) + " " +
                   to_string(orig[rd] + 1) + "\n";
        } else {
            out += "0 0 0 0\n";
        }
    }
    fputs(out.c_str(), stdout);
    return 0;
}
