/*
Megoldás lényege:
Az alap poligonműveleteket használjuk: orientáció, terület, konvexitás és egyszerű metszésvizsgálatok. Ezekből áll össze a feladat teljes megoldása.
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
    int id;
};

static int orient(const Pt& a, const Pt& b, const Pt& c) {
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

    vector<Pt> lower, upper;
    for (const auto& p : pts) {
        while (lower.size() >= 2 && orient(lower[lower.size() - 2], lower.back(), p) <= 0) lower.pop_back();
        lower.push_back(p);
    }
    for (int i = (int)pts.size() - 1; i >= 0; --i) {
        const auto& p = pts[i];
        while (upper.size() >= 2 && orient(upper[upper.size() - 2], upper.back(), p) <= 0) upper.pop_back();
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

    vector<Pt> pts(n);
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].id = i + 1;
    }

    vector<Pt> hull = convexHull(pts);
    cout << hull.size() << '\n';
    for (int i = 0; i < (int)hull.size(); ++i) {
        int j = (i + 1) % (int)hull.size();
        cout << hull[i].id << ' ' << hull[j].id << '\n';
    }

    return 0;
}
