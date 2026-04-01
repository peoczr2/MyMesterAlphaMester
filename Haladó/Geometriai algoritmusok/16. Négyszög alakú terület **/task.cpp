/*
Megoldás lényege:
A legalsó pont körül rendezett szögsorrendben keressük a megfelelő csúcsokat. Három egymást követő irányból olyan konvex négyszöget választunk, amelynek belsejében nincs más pont.
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

    int apex = 0;
    for (int i = 1; i < n; ++i) {
        if (pts[i].y < pts[apex].y || (pts[i].y == pts[apex].y && pts[i].x < pts[apex].x)) apex = i;
    }

    vector<Pt> others;
    others.reserve(n - 1);
    for (int i = 0; i < n; ++i) {
        if (i != apex) others.push_back(pts[i]);
    }

    sort(others.begin(), others.end(), [&](const Pt& a, const Pt& b) {
        int o = orient(pts[apex], a, b);
        if (o != 0) return o > 0;
        __int128 da = (__int128)(a.x - pts[apex].x) * (a.x - pts[apex].x) + (__int128)(a.y - pts[apex].y) * (a.y - pts[apex].y);
        __int128 db = (__int128)(b.x - pts[apex].x) * (b.x - pts[apex].x) + (__int128)(b.y - pts[apex].y) * (b.y - pts[apex].y);
        return da < db;
    });

    vector<Pt> uniq;
    uniq.reserve(others.size());
    for (const auto& p : others) {
        if (!uniq.empty() && orient(pts[apex], uniq.back(), p) == 0) continue;
        uniq.push_back(p);
    }

    if ((int)uniq.size() < 3) {
        cout << "0 0 0 0\n";
        return 0;
    }

    auto good = [&](const Pt& a, const Pt& b, const Pt& c) {
        return orient(pts[apex], a, b) > 0 && orient(a, b, c) > 0 && orient(b, c, pts[apex]) > 0;
    };

    for (int i = 0; i + 2 < (int)uniq.size(); ++i) {
        if (good(uniq[i], uniq[i + 1], uniq[i + 2])) {
            cout << pts[apex].id << ' ' << uniq[i].id << ' ' << uniq[i + 1].id << ' ' << uniq[i + 2].id << '\n';
            return 0;
        }
    }

    cout << "0 0 0 0\n";
    return 0;
}
