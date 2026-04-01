/*
Megoldás lényege:
Az egyenesek lefedési vagy szeparációs szerepét vizsgáljuk geometriai rendezéssel. A döntés a pontok oldalviszonyain és a tartóegyeneseken alapul.
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
};

struct Line {
    Pt a, b;
};

static long long cross(const Pt& a, const Pt& b, const Pt& c) {
    __int128 v = (__int128)(b.x - a.x) * (c.y - a.y) - (__int128)(b.y - a.y) * (c.x - a.x);
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

static bool onLine(const Line& line, const Pt& p) {
    return cross(line.a, line.b, p) == 0;
}

static Line lineThrough(const Pt& a, const Pt& b) {
    return {a, b};
}

static Line arbitraryLineThrough(const Pt& p) {
    return {p, {p.x + 1, p.y}};
}

static vector<Pt> dedupe(vector<Pt> pts) {
    sort(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    pts.erase(unique(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
        return a.x == b.x && a.y == b.y;
    }), pts.end());
    return pts;
}

static bool solveTwoLines(const vector<Pt>& pts, Line& l1, Line& l2) {
    int m = (int)pts.size();
    if (m == 0) {
        l1 = {{0, 0}, {1, 0}};
        l2 = l1;
        return true;
    }
    if (m == 1) {
        l1 = arbitraryLineThrough(pts[0]);
        l2 = l1;
        return true;
    }
    if (m == 2) {
        l1 = lineThrough(pts[0], pts[1]);
        l2 = l1;
        return true;
    }

    int lim = min(3, m);
    for (int i = 0; i < lim; ++i) {
        for (int j = i + 1; j < lim; ++j) {
            Line cand = lineThrough(pts[i], pts[j]);
            vector<Pt> rest;
            for (const auto& p : pts) {
                if (!onLine(cand, p)) rest.push_back(p);
            }
            bool collinear = true;
            if ((int)rest.size() >= 2) {
                for (int k = 2; k < (int)rest.size(); ++k) {
                    if (cross(rest[0], rest[1], rest[k]) != 0) {
                        collinear = false;
                        break;
                    }
                }
            }
            if (collinear) {
                l1 = cand;
                if (rest.empty()) l2 = cand;
                else if (rest.size() == 1) l2 = arbitraryLineThrough(rest[0]);
                else l2 = lineThrough(rest[0], rest[1]);
                return true;
            }
        }
    }
    return false;
}

static bool solveThreeLines(const vector<Pt>& pts, array<Line, 3>& ans) {
    int m = (int)pts.size();
    if (m == 0) {
        ans = {arbitraryLineThrough({0, 0}), arbitraryLineThrough({0, 0}), arbitraryLineThrough({0, 0})};
        return true;
    }
    if (m <= 3) {
        for (int i = 0; i < 3; ++i) {
            ans[i] = arbitraryLineThrough(pts[min(i, m - 1)]);
        }
        return true;
    }

    int lim = min(4, m);
    for (int i = 0; i < lim; ++i) {
        for (int j = i + 1; j < lim; ++j) {
            Line first = lineThrough(pts[i], pts[j]);
            vector<Pt> rest;
            for (const auto& p : pts) {
                if (!onLine(first, p)) rest.push_back(p);
            }
            Line second, third;
            if (solveTwoLines(rest, second, third)) {
                ans[0] = first;
                ans[1] = second;
                ans[2] = third;
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<Pt> pts(n);
    for (int i = 0; i < n; ++i) cin >> pts[i].x >> pts[i].y;
    pts = dedupe(pts);

    array<Line, 3> ans;
    if (!solveThreeLines(pts, ans)) {
        cout << "0 0 0 0\n";
        return 0;
    }

    for (int i = 0; i < 3; ++i) {
        cout << ans[i].a.x << ' ' << ans[i].a.y << ' ' << ans[i].b.x << ' ' << ans[i].b.y << '\n';
    }

    return 0;
}
