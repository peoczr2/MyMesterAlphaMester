/*
Megoldás lényege:
Két ponthalmaz lineáris szeparálhatóságát kell eldönteni. Ez a konvex burkok és egy elválasztó egyenes létezésének klasszikus geometriai kérdése.
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
};

static __int128 cross128(const Pt& a, const Pt& b, const Pt& c) {
    return (__int128)(b.x - a.x) * (c.y - a.y) - (__int128)(b.y - a.y) * (c.x - a.x);
}

static __int128 dot128(const Pt& a, const Pt& b) {
    return (__int128)a.x * b.x + (__int128)a.y * b.y;
}

static Pt operator+(const Pt& a, const Pt& b) { return {a.x + b.x, a.y + b.y}; }
static Pt operator-(const Pt& a, const Pt& b) { return {a.x - b.x, a.y - b.y}; }

static vector<Pt> convexHull(vector<Pt> pts) {
    sort(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    pts.erase(unique(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
        return a.x == b.x && a.y == b.y;
    }), pts.end());

    if (pts.size() <= 1) return pts;

    vector<Pt> lower, upper;
    for (const auto& p : pts) {
        while (lower.size() >= 2 && cross128(lower[lower.size() - 2], lower.back(), p) <= 0) lower.pop_back();
        lower.push_back(p);
    }
    for (int i = (int)pts.size() - 1; i >= 0; --i) {
        const auto& p = pts[i];
        while (upper.size() >= 2 && cross128(upper[upper.size() - 2], upper.back(), p) <= 0) upper.pop_back();
        upper.push_back(p);
    }

    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

static int sgn(__int128 v) {
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

static int idxLowest(const vector<Pt>& poly) {
    int idx = 0;
    for (int i = 1; i < (int)poly.size(); ++i) {
        if (poly[i].y < poly[idx].y || (poly[i].y == poly[idx].y && poly[i].x < poly[idx].x)) idx = i;
    }
    return idx;
}

static vector<Pt> minkowskiSum(vector<Pt> a, vector<Pt> b) {
    if (a.empty()) return b;
    if (b.empty()) return a;

    if (a.size() == 1) {
        for (auto& p : b) p = p + a[0];
        return b;
    }
    if (b.size() == 1) {
        for (auto& p : a) p = p + b[0];
        return a;
    }

    int ia = idxLowest(a);
    int ib = idxLowest(b);
    rotate(a.begin(), a.begin() + ia, a.end());
    rotate(b.begin(), b.begin() + ib, b.end());
    a.push_back(a[0]);
    a.push_back(a[1]);
    b.push_back(b[0]);
    b.push_back(b[1]);

    vector<Pt> res;
    res.push_back(a[0] + b[0]);
    size_t i = 0, j = 0;
    while (i + 1 < a.size() - 1 || j + 1 < b.size() - 1) {
        Pt ea = a[i + 1] - a[i];
        Pt eb = b[j + 1] - b[j];
        int cr = sgn((__int128)ea.x * eb.y - (__int128)ea.y * eb.x);
        if (j + 1 == b.size() - 1 || (i + 1 < a.size() - 1 && cr >= 0)) {
            ++i;
        }
        if (i + 1 == a.size() - 1 || (j + 1 < b.size() - 1 && cr <= 0)) {
            ++j;
        }
        res.push_back(a[i] + b[j]);
    }
    return convexHull(res);
}

static bool pointOnSegment(const Pt& a, const Pt& b, const Pt& p) {
    if (cross128(a, b, p) != 0) return false;
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

static bool originInsideOrOn(const vector<Pt>& poly) {
    if (poly.empty()) return false;
    if (poly.size() == 1) return poly[0].x == 0 && poly[0].y == 0;
    if (poly.size() == 2) return pointOnSegment(poly[0], poly[1], {0, 0});
    for (int i = 0; i < (int)poly.size(); ++i) {
        if (cross128(poly[i], poly[(i + 1) % poly.size()], {0, 0}) < 0) return false;
    }
    return true;
}

struct Candidate {
    bool valid = false;
    Pt n{};
    long double dist2 = numeric_limits<long double>::infinity();
    bool onEdge = false;
    int edgeIdx = -1;
    Pt proj{};
};

static Candidate closestOnPolygon(const vector<Pt>& poly) {
    Candidate best;
    int m = (int)poly.size();
    if (m == 0) return best;
    if (m == 1) {
        best.valid = true;
        best.proj = poly[0];
        best.dist2 = (long double)poly[0].x * poly[0].x + (long double)poly[0].y * poly[0].y;
        best.n = poly[0];
        return best;
    }
    auto upd = [&](const Candidate& cand) {
        if (!cand.valid) return;
        if (cand.dist2 < best.dist2) best = cand;
    };

    for (int i = 0; i < m; ++i) {
        Pt a = poly[i], b = poly[(i + 1) % m];
        Pt d = b - a;
        __int128 len2 = dot128(d, d);
        __int128 tnum = -dot128(a, d);
        Candidate cand;
        cand.valid = true;
        if (len2 == 0) {
            cand.proj = a;
            cand.dist2 = (long double)a.x * a.x + (long double)a.y * a.y;
            cand.n = a;
            cand.edgeIdx = i;
            cand.onEdge = false;
            upd(cand);
            continue;
        }
        if (0 <= tnum && tnum <= len2) {
            long double t = (long double)tnum / (long double)len2;
            long double px = (long double)a.x + t * (long double)d.x;
            long double py = (long double)a.y + t * (long double)d.y;
            cand.proj = {(long long)llround(px), (long long)llround(py)};
            cand.dist2 = px * px + py * py;
            cand.n = {d.y, -d.x};
            cand.onEdge = true;
            cand.edgeIdx = i;
            upd(cand);
        } else {
            long double da = (long double)a.x * a.x + (long double)a.y * a.y;
            cand.proj = a;
            cand.dist2 = da;
            cand.n = a;
            cand.onEdge = false;
            cand.edgeIdx = i;
            upd(cand);

            if (i == m - 1) {
                Candidate cand2;
                cand2.valid = true;
                cand2.proj = b;
                cand2.dist2 = (long double)b.x * b.x + (long double)b.y * b.y;
                cand2.n = b;
                cand2.onEdge = false;
                cand2.edgeIdx = i;
                upd(cand2);
            }
        }
    }
    return best;
}

static bool solveLineNormal(const vector<Pt>& white, const vector<Pt>& black, Pt n, long long& c) {
    __int128 wMax = numeric_limits<long long>::min();
    __int128 wMin = numeric_limits<long long>::max();
    __int128 bMax = numeric_limits<long long>::min();
    __int128 bMin = numeric_limits<long long>::max();
    for (const auto& p : white) {
        __int128 v = dot128(n, p);
        wMax = max(wMax, v);
        wMin = min(wMin, v);
    }
    for (const auto& p : black) {
        __int128 v = dot128(n, p);
        bMax = max(bMax, v);
        bMin = min(bMin, v);
    }
    if (wMax <= bMin) {
        c = (long long)wMax;
        return true;
    }
    if (bMax <= wMin) {
        c = (long long)bMax;
        return true;
    }
    return false;
}

static long long extgcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = (a >= 0 ? 1 : -1);
        y = 0;
        return llabs(a);
    }
    long long x1, y1;
    long long g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

static pair<Pt, Pt> twoPointsOnLine(long long a, long long b, long long c) {
    long long x0, y0;
    long long g = extgcd(a, b, x0, y0);
    if (g == 0) return {{0, 0}, {1, 0}};
    long long mult = c / g;
    x0 *= mult;
    y0 *= mult;
    Pt p1{x0, y0};
    Pt p2{x0 + b / g, y0 - a / g};
    return {p1, p2};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    if (!(cin >> m >> n)) return 0;
    vector<Pt> white(m), black(n);
    for (int i = 0; i < m; ++i) cin >> white[i].x >> white[i].y;
    for (int i = 0; i < n; ++i) cin >> black[i].x >> black[i].y;

    auto hw = convexHull(white);
    auto hb = convexHull(black);

    if (hw.empty() || hb.empty()) {
        cout << "0 0 0 0\n";
        return 0;
    }

    for (auto& p : hb) {
        p.x = -p.x;
        p.y = -p.y;
    }
    auto diff = minkowskiSum(hw, hb);

    if (diff.size() == 1 && diff[0].x == 0 && diff[0].y == 0) {
        cout << "0 0 0 0\n";
        return 0;
    }

    if (originInsideOrOn(diff)) {
        bool strictInside = true;
        if (diff.size() <= 2) strictInside = false;
        else {
            for (int i = 0; i < (int)diff.size(); ++i) {
                if (cross128(diff[i], diff[(i + 1) % diff.size()], {0, 0}) <= 0) {
                    strictInside = false;
                    break;
                }
            }
        }
        if (strictInside) {
            cout << "0 0 0 0\n";
            return 0;
        }
    }

    Candidate cand = closestOnPolygon(diff);
    if (!cand.valid) {
        cout << "0 0 0 0\n";
        return 0;
    }

    Pt nvec = cand.n;
    if (nvec.x == 0 && nvec.y == 0) {
        // Origin coincides with a vertex of the Minkowski difference.
        // Use the sum of the incident edge normals if possible.
        int idx = -1;
        for (int i = 0; i < (int)diff.size(); ++i) {
            if (diff[i].x == 0 && diff[i].y == 0) {
                idx = i;
                break;
            }
        }
        if (idx == -1) {
            cout << "0 0 0 0\n";
            return 0;
        }
        Pt e1{0, 0}, e2{0, 0};
        if (diff.size() >= 2) {
            Pt pprev = diff[(idx - 1 + (int)diff.size()) % (int)diff.size()];
            Pt pnext = diff[(idx + 1) % (int)diff.size()];
            Pt d1 = diff[idx] - pprev;
            Pt d2 = pnext - diff[idx];
            e1 = {d1.y, -d1.x};
            e2 = {d2.y, -d2.x};
            nvec = {e1.x + e2.x, e1.y + e2.y};
            if (nvec.x == 0 && nvec.y == 0) nvec = e1.x || e1.y ? e1 : e2;
        }
    }

    long long c = 0;
    if (!solveLineNormal(white, black, nvec, c)) {
        // Try the opposite orientation.
        nvec.x = -nvec.x;
        nvec.y = -nvec.y;
        if (!solveLineNormal(white, black, nvec, c)) {
            cout << "0 0 0 0\n";
            return 0;
        }
    }

    auto [a, b] = twoPointsOnLine(nvec.x, nvec.y, c);
    cout << a.x << ' ' << a.y << ' ' << b.x << ' ' << b.y << '\n';
    return 0;
}