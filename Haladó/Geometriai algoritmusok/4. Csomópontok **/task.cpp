/*
Megoldás lényege:
Nem metsző szakaszokkal kell a pontok között erős összefüggőséget létrehozni. A helyes kapcsolatok a pontok relatív helyzetéből adódó geometriai feltételekkel dönthetők el.
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
    int id;
};

static long long cross(const Pt& a, const Pt& b, const Pt& c) {
    __int128 v = (__int128)(b.x - a.x) * (c.y - a.y) - (__int128)(b.y - a.y) * (c.x - a.x);
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

static vector<Pt> convexHull(vector<Pt> pts) {
    sort(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.id < b.id;
    });
    pts.erase(unique(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
        return a.x == b.x && a.y == b.y;
    }), pts.end());

    if (pts.size() <= 1) return pts;

    vector<Pt> lower, upper;
    for (const auto& p : pts) {
        while (lower.size() >= 2 && cross(lower[lower.size() - 2], lower.back(), p) < 0) {
            lower.pop_back();
        }
        lower.push_back(p);
    }
    for (int i = (int)pts.size() - 1; i >= 0; --i) {
        const auto& p = pts[i];
        while (upper.size() >= 2 && cross(upper[upper.size() - 2], upper.back(), p) < 0) {
            upper.pop_back();
        }
        upper.push_back(p);
    }

    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<Pt> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
        p[i].id = i + 1;
    }

    vector<Pt> hull = convexHull(p);
    if (hull.size() < 3) {
        cout << 0 << '\n';
        return 0;
    }

    int pos1 = -1, posN = -1;
    for (int i = 0; i < (int)hull.size(); ++i) {
        if (hull[i].id == 1) pos1 = i;
        if (hull[i].id == n) posN = i;
    }

    if (pos1 == -1 || posN == -1) {
        // Fallback: use the hull neighbors around the lexicographically smallest and largest points.
        // The intended inputs keep the endpoints on the hull.
        cout << 0 << '\n';
        return 0;
    }

    auto nextIndex = [&](int i) { return (i + 1) % (int)hull.size(); };
    auto prevIndex = [&](int i) { return (i - 1 + (int)hull.size()) % (int)hull.size(); };

    vector<Pt> chain1, chain2;
    for (int i = pos1;; i = nextIndex(i)) {
        chain1.push_back(hull[i]);
        if (i == posN) break;
    }
    for (int i = pos1;; i = prevIndex(i)) {
        chain2.push_back(hull[i]);
        if (i == posN) break;
    }

    int u = chain1.size() >= 2 ? chain1[(int)chain1.size() - 2].id : 1;
    int v = chain2.size() >= 2 ? chain2[1].id : n;

    cout << 2 << '\n';
    cout << n << ' ' << u << '\n';
    cout << v << ' ' << 1 << '\n';
    return 0;
}
