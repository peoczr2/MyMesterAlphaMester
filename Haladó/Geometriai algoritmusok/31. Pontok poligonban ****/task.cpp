/*
Megoldás lényege:
Több pontra kell gyorsan eldönteni, hogy a sokszög belsejében vannak-e. Erre logaritmikus vagy lineáris point-in-polygon tesztet használunk.
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
};

static bool insidePolygon(const vector<Pt>& poly, const Pt& p) {
    bool inside = false;
    int n = (int)poly.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        const Pt& a = poly[j];
        const Pt& b = poly[i];
        bool straddles = (a.y > p.y) != (b.y > p.y);
        if (!straddles) continue;
        long double xIntersect = (long double)a.x + (long double)(b.x - a.x) * (long double)(p.y - a.y) /
                                 (long double)(b.y - a.y);
        if (xIntersect > (long double)p.x) inside = !inside;
    }
    return inside;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Pt> pts(n + 1);
    for (int i = 1; i <= n; ++i) cin >> pts[i].x >> pts[i].y;

    vector<int> mark(n + 1, 0);
    vector<int> polyIds;
    polyIds.reserve(n);

    while (m--) {
        int k;
        cin >> k;
        vector<int> ids(k);
        vector<Pt> poly(k);
        for (int i = 0; i < k; ++i) {
            cin >> ids[i];
            poly[i] = pts[ids[i]];
            mark[ids[i]] = 1;
        }

        int answer = 0;
        for (int i = 1; i <= n; ++i) {
            if (mark[i]) continue;
            if (insidePolygon(poly, pts[i])) ++answer;
        }

        cout << answer << '\n';

        for (int id : ids) mark[id] = 0;
    }

    return 0;
}