/*
Megoldás lényege:
A megfelelő B,C pontok a többi fa konvex burkának egymást követő csúcsai között
találhatók. Ha a hullél vonalán A és az új facsemete P is a külső oldalon van, és
P szigorúan benne van az A-B-C háromszögben, akkor a háromszög üres.

Ezért elég az A-t kivéve a pontok konvex burkát megépíteni, majd a határoló éleket
végignézni.

Idő: O(N log N)
*/

#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
    int id;
};

static long long crossVal(const Pt& a, const Pt& b, const Pt& c) {
    __int128 v = (__int128)(b.x - a.x) * (c.y - a.y) - (__int128)(b.y - a.y) * (c.x - a.x);
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

static bool insideStrict(const Pt& a, const Pt& b, const Pt& c, const Pt& p) {
    long long c1 = crossVal(a, b, p);
    long long c2 = crossVal(b, c, p);
    long long c3 = crossVal(c, a, p);
    return (c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0);
}

static vector<Pt> convexHullBoundary(vector<Pt> pts) {
    sort(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.id < b.id;
    });

    vector<Pt> lower, upper;
    lower.reserve(pts.size());
    upper.reserve(pts.size());

    for (const Pt& p : pts) {
        while (lower.size() >= 2 && crossVal(lower[lower.size() - 2], lower.back(), p) < 0) {
            lower.pop_back();
        }
        lower.push_back(p);
    }

    for (int i = (int)pts.size() - 1; i >= 0; --i) {
        const Pt& p = pts[i];
        while (upper.size() >= 2 && crossVal(upper[upper.size() - 2], upper.back(), p) < 0) {
            upper.pop_back();
        }
        upper.push_back(p);
    }

    vector<Pt> hull;
    hull.reserve(lower.size() + upper.size());
    for (const Pt& p : lower) hull.push_back(p);
    for (int i = 1; i + 1 < (int)upper.size(); ++i) hull.push_back(upper[i]);

    vector<Pt> boundary;
    boundary.reserve(hull.size());
    for (const Pt& p : hull) {
        if (boundary.empty() || boundary.back().x != p.x || boundary.back().y != p.y || boundary.back().id != p.id) {
            boundary.push_back(p);
        }
    }
    if (boundary.size() >= 2) {
        const Pt& a = boundary.front();
        const Pt& b = boundary.back();
        if (a.x == b.x && a.y == b.y && a.id == b.id) boundary.pop_back();
    }
    return boundary;
}

static long long polygonOrientation(const vector<Pt>& poly) {
    __int128 sum = 0;
    for (int i = 0; i < (int)poly.size(); ++i) {
        const Pt& a = poly[i];
        const Pt& b = poly[(i + 1) % (int)poly.size()];
        sum += (__int128)a.x * b.y - (__int128)a.y * b.x;
    }
    if (sum > 0) return 1;
    if (sum < 0) return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, A;
    if (!(cin >> N >> A)) return 0;

    Pt P;
    cin >> P.x >> P.y;

    vector<Pt> pts(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].id = i;
    }

    Pt a = pts[A];
    vector<Pt> others;
    others.reserve(N - 1);
    for (int i = 1; i <= N; ++i) {
        if (i != A) others.push_back(pts[i]);
    }

    vector<Pt> hull = convexHullBoundary(others);
    if (hull.size() < 2) {
        cout << "0 0\n";
        return 0;
    }

    long long hullOrient = polygonOrientation(hull);
    if (hullOrient == 0) {
        cout << "0 0\n";
        return 0;
    }

    for (int i = 0; i < (int)hull.size(); ++i) {
        const Pt& b = hull[i];
        const Pt& c = hull[(i + 1) % (int)hull.size()];
        if (crossVal(b, c, a) * hullOrient < 0 && crossVal(b, c, P) * hullOrient < 0 && insideStrict(a, b, c, P)) {
            if (crossVal(a, b, c) < 0) {
                cout << c.id << ' ' << b.id << '\n';
            } else {
                cout << b.id << ' ' << c.id << '\n';
            }
            return 0;
        }
    }

    cout << "0 0\n";
    return 0;
}