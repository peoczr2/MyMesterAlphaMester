/*
Megoldás lényege:
Akkor és csak akkor van szétválasztó egyenes, ha a fehér és a fekete burok különbségének (W - B) konvex burkában az origó nem
belső pont. Ezt a különbséghalmazt a két burok éleinek rendezett irányaiból álló Minkowski-összeggel számoljuk, egész számokkal,
pontosan. Ha az origó a különbség-burok belsejében van, nincs megoldás. Különben a szétválasztó egyenes normálisa a különbség-burok
origóból húzott érintőinek vagy az origót tartalmazó élének normálisa, ezért csak O(N+M) jelölt van. Minden jelöltre O(N+M)
ellenőrzéssel nézzük, hogy a fehér pontok legnagyobb vetülete nem nagyobb a fekete pontok legkisebbénél (vagy fordítva), és a
találat egyenese átmegy egy fehér ponton. Idő: O((N+M) log(N+M)).
*/
/*
Hint 1: || Akkor van szétválasztó egyenes, ha a fehér és fekete pontok burkainak különbségében (W - B) az origó nem belső pont. Ezt a különbség konvex burkával lehet eldönteni. ||
Hint 2: || A különbség burkának élei a két burok éleinek irányaiból adódnak, így a rendezett élekből egyszerűen kiszámolható a Minkowski-összeg. Az origó helyzetéből csak néhány normálvektor-jelölt marad. ||
Hint 3: || Egy n normálisú egyenes akkor jó, ha a fehér pontok n szerinti legnagyobb vetülete nem nagyobb a fekete pontok legkisebbénél (vagy fordítva). Minden jelöltet O(N+M) alatt ellenőrizz, és a találat egyenese menjen át egy fehér ponton. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
};

static Pt operator+(const Pt& a, const Pt& b) { return {a.x + b.x, a.y + b.y}; }
static Pt operator-(const Pt& a, const Pt& b) { return {a.x - b.x, a.y - b.y}; }
static Pt operator-(const Pt& a) { return {-a.x, -a.y}; }

static __int128 cross128(const Pt& a, const Pt& b) {
    return (__int128)a.x * b.y - (__int128)a.y * b.x;
}

static int sgn128(__int128 v) { return (v > 0) - (v < 0); }

// Pontok szigorúan konvex, óramutató-ellentétes (CCW) burka, kollineáris pontok nélkül.
static vector<Pt> convexHull(vector<Pt> pts) {
    sort(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    pts.erase(unique(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
        return a.x == b.x && a.y == b.y;
    }), pts.end());
    if (pts.size() <= 2) return pts;

    vector<Pt> h(2 * pts.size());
    size_t k = 0;
    for (size_t i = 0; i < pts.size(); ++i) {
        while (k >= 2 && cross128(h[k - 1] - h[k - 2], pts[i] - h[k - 2]) <= 0) --k;
        h[k++] = pts[i];
    }
    for (size_t i = pts.size() - 1, t = k + 1; i > 0; --i) {
        while (k >= t && cross128(h[k - 1] - h[k - 2], pts[i - 1] - h[k - 2]) <= 0) --k;
        h[k++] = pts[i - 1];
    }
    h.resize(k - 1);
    return h;
}

// Legalsó (y, majd x szerint legkisebb) pont.
static Pt lowestLeft(const vector<Pt>& v) {
    Pt best = v[0];
    for (const auto& p : v) {
        if (p.y < best.y || (p.y == best.y && p.x < best.x)) best = p;
    }
    return best;
}

// Az élvektor félsíkja a polárszög szerinti rendezéshez: [0, pi) -> 0, [pi, 2pi) -> 1.
static int halfOf(const Pt& v) {
    return (v.y > 0 || (v.y == 0 && v.x > 0)) ? 0 : 1;
}

// P (+) Q Minkowski-összeg: az éleket polárszög szerint összefésüljük a legalsó pontoktól kezdve.
static vector<Pt> minkowskiSum(const vector<Pt>& P, const vector<Pt>& Q) {
    vector<Pt> edges;
    auto addEdges = [&](const vector<Pt>& H) {
        int m = (int)H.size();
        if (m < 2) return;
        for (int i = 0; i < m; ++i) edges.push_back(H[(i + 1) % m] - H[i]);
    };
    addEdges(P);
    addEdges(Q);
    sort(edges.begin(), edges.end(), [](const Pt& a, const Pt& b) {
        int ha = halfOf(a), hb = halfOf(b);
        if (ha != hb) return ha < hb;
        return cross128(a, b) > 0;
    });

    Pt cur = lowestLeft(P) + lowestLeft(Q);
    vector<Pt> pts{cur};
    for (const auto& e : edges) {
        cur = cur + e;
        pts.push_back(cur);
    }
    return convexHull(pts);
}

// Ha van olyan egyenes n normálissal, amely a fehér pontokat az egyik, a feketéket a másik zárt félsíkba teszi,
// visszaadja A-t: egy fehér pont az egyenesen.
static bool separatedBy(const vector<Pt>& W, const vector<Pt>& B, const Pt& n, Pt& A) {
    auto dot = [&](const Pt& p) { return n.x * p.x + n.y * p.y; };
    long long wMax = LLONG_MIN, wMin = LLONG_MAX, bMax = LLONG_MIN, bMin = LLONG_MAX;
    Pt wArgMax{0, 0}, wArgMin{0, 0};
    for (const auto& w : W) {
        long long v = dot(w);
        if (v > wMax) {
            wMax = v;
            wArgMax = w;
        }
        if (v < wMin) {
            wMin = v;
            wArgMin = w;
        }
    }
    for (const auto& b : B) {
        long long v = dot(b);
        bMax = max(bMax, v);
        bMin = min(bMin, v);
    }
    if (wMax <= bMin) {
        A = wArgMax;
        return true;
    }
    if (wMin >= bMax) {
        A = wArgMin;
        return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    if (!(cin >> m >> n)) return 0;
    vector<Pt> white(m), black(n);
    for (int i = 0; i < m; ++i) cin >> white[i].x >> white[i].y;
    for (int i = 0; i < n; ++i) cin >> black[i].x >> black[i].y;

    vector<Pt> hw = convexHull(white);
    vector<Pt> hb = convexHull(black);
    for (auto& p : hb) p = -p;
    vector<Pt> D = minkowskiSum(hw, hb);
    int k = (int)D.size();

    // Az origó helyzete D-hez képest: a jelölt normálisok listája.
    vector<Pt> cands;
    auto perp = [](const Pt& d) { return Pt{d.y, -d.x}; };
    if (k >= 3) {
        bool inside = true;
        for (int i = 0; i < k; ++i) {
            if (sgn128(cross128(D[i], D[(i + 1) % k])) <= 0) inside = false;
        }
        if (inside) {
            cout << "0 0 0 0\n";
            return 0;
        }
        for (int i = 0; i < k; ++i) {
            const Pt& a = D[i];
            const Pt& b = D[(i + 1) % k];
            const Pt& prev = D[(i + k - 1) % k];
            if (sgn128(cross128(a, b)) == 0) {
                cands.push_back(perp(b - a));
                cands.push_back(-perp(b - a));
            }
            int s1 = sgn128(cross128(prev, a)), s2 = sgn128(cross128(a, b));
            if (s1 != 0 && s2 != 0 && s1 != s2) {
                cands.push_back(perp(a));
                cands.push_back(-perp(a));
            }
        }
    } else if (k == 2) {
        Pt d = D[1] - D[0];
        for (const Pt& c : {perp(d), perp(D[0]), perp(D[1])}) {
            cands.push_back(c);
            cands.push_back(-c);
        }
    } else if (D[0].x == 0 && D[0].y == 0) {
        // Egyetlen közös pont: bármelyik rajta átmenő egyenes megfelel.
        cands.push_back(Pt{1, 0});
        cands.push_back(Pt{0, 1});
    } else {
        cands.push_back(-D[0]);
    }

    for (const Pt& nrm : cands) {
        if (nrm.x == 0 && nrm.y == 0) continue;
        Pt A{0, 0};
        if (!separatedBy(white, black, nrm, A)) continue;
        long long g = std::gcd(llabs(nrm.x), llabs(nrm.y));
        Pt dir{nrm.y / g, -nrm.x / g};
        cout << A.x << ' ' << A.y << ' ' << A.x + dir.x << ' ' << A.y + dir.y << '\n';
        return 0;
    }

    cout << "0 0 0 0\n";
    return 0;
}
