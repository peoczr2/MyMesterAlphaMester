/*
Megoldás lényege:
Kiválasztunk néhány szélső pontot jelölt csúcsnak, majd a csúcs körüli szögsorrendben
keressük meg a három egymást követő irányt, amelyek a jelölt csúccsal együtt szigorúan
konvex négyszöget adnak. Az azonos sugárirányban lévő távolabbi pontok nem lehetnek
határcsúcsok, ezért irányonként csak a legközelebbit tartjuk meg.

A szögsorrendben egymást követő három sugárból képzett négyszög üres marad, mert más
pont nem eshet közéjük a körüljárási sorrendben.

Idő: O(C * N log N), ahol C állandó számú jelölt csúcs.
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

static vector<int> convexHull(const vector<Pt>& pts) {
    vector<int> ord(pts.size());
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        if (pts[i].x != pts[j].x) return pts[i].x < pts[j].x;
        if (pts[i].y != pts[j].y) return pts[i].y < pts[j].y;
        return pts[i].id < pts[j].id;
    });

    vector<int> lower, upper;
    for (int idx : ord) {
        while ((int)lower.size() >= 2 && orient(pts[lower[(int)lower.size() - 2]], pts[lower.back()], pts[idx]) <= 0) {
            lower.pop_back();
        }
        lower.push_back(idx);
    }
    for (int k = (int)ord.size() - 1; k >= 0; --k) {
        int idx = ord[k];
        while ((int)upper.size() >= 2 && orient(pts[upper[(int)upper.size() - 2]], pts[upper.back()], pts[idx]) <= 0) {
            upper.pop_back();
        }
        upper.push_back(idx);
    }

    if (!lower.empty()) lower.pop_back();
    if (!upper.empty()) upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

static bool tryPivot(const vector<Pt>& pts, int pivotIdx, array<int, 4>& ans) {
    const Pt& pivot = pts[pivotIdx];

    vector<Pt> others;
    others.reserve(pts.size() - 1);
    for (int i = 0; i < (int)pts.size(); ++i) {
        if (i != pivotIdx) others.push_back(pts[i]);
    }

    sort(others.begin(), others.end(), [&](const Pt& a, const Pt& b) {
        long long ax = a.x - pivot.x;
        long long ay = a.y - pivot.y;
        long long bx = b.x - pivot.x;
        long long by = b.y - pivot.y;
        bool ua = (ay > 0) || (ay == 0 && ax > 0);
        bool ub = (by > 0) || (by == 0 && bx > 0);
        if (ua != ub) return ua > ub;
        __int128 cr = (__int128)ax * by - (__int128)ay * bx;
        if (cr != 0) return cr > 0;
        __int128 da = (__int128)ax * ax + (__int128)ay * ay;
        __int128 db = (__int128)bx * bx + (__int128)by * by;
        return da < db;
    });

    vector<Pt> uniq;
    uniq.reserve(others.size());
    for (const auto& p : others) {
        if (!uniq.empty() && orient(pivot, uniq.back(), p) == 0) continue;
        uniq.push_back(p);
    }

    int m = (int)uniq.size();
    if (m < 3) return false;

    auto good = [&](const Pt& a, const Pt& b, const Pt& c) {
        return orient(pivot, a, b) > 0 && orient(a, b, c) > 0 && orient(b, c, pivot) > 0;
    };

    for (int i = 0; i < m; ++i) {
        const Pt& a = uniq[i];
        const Pt& b = uniq[(i + 1) % m];
        const Pt& c = uniq[(i + 2) % m];
        if (good(a, b, c)) {
            ans = {pivot.id, a.id, b.id, c.id};
            return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    if (!(cin >> K)) return 0;

    while (K--) {
        int N;
        cin >> N;

        vector<Pt> pts(N);
        for (int i = 0; i < N; ++i) {
            cin >> pts[i].x >> pts[i].y;
            pts[i].id = i + 1;
        }

        if (N < 4) {
            cout << "0 0 0 0\n";
            continue;
        }

        vector<int> hull = convexHull(pts);
        if ((int)hull.size() < 4) {
            cout << "0 0 0 0\n";
            continue;
        }

        vector<int> cand;
        auto add = [&](int idx) {
            if (idx < 0 || idx >= N) return;
            for (int x : cand) if (x == idx) return;
            cand.push_back(idx);
        };

        auto addExtreme = [&](auto getter) {
            int best = 0;
            for (int i = 1; i < N; ++i) {
                if (getter(i, best)) best = i;
            }
            add(best);
        };

        addExtreme([&](int i, int j) { return pts[i].y < pts[j].y || (pts[i].y == pts[j].y && pts[i].x < pts[j].x); });
        addExtreme([&](int i, int j) { return pts[i].y > pts[j].y || (pts[i].y == pts[j].y && pts[i].x < pts[j].x); });
        addExtreme([&](int i, int j) { return pts[i].x < pts[j].x || (pts[i].x == pts[j].x && pts[i].y < pts[j].y); });
        addExtreme([&](int i, int j) { return pts[i].x > pts[j].x || (pts[i].x == pts[j].x && pts[i].y < pts[j].y); });
        addExtreme([&](int i, int j) { return pts[i].x + pts[i].y < pts[j].x + pts[j].y; });
        addExtreme([&](int i, int j) { return pts[i].x + pts[i].y > pts[j].x + pts[j].y; });
        addExtreme([&](int i, int j) { return pts[i].x - pts[i].y < pts[j].x - pts[j].y; });
        addExtreme([&](int i, int j) { return pts[i].x - pts[i].y > pts[j].x - pts[j].y; });

        for (int idx : hull) add(idx);

        array<int, 4> ans{};
        bool found = false;
        for (int idx : cand) {
            if (tryPivot(pts, idx, ans)) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "0 0 0 0\n";
        } else {
            cout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << ' ' << ans[3] << '\n';
        }
    }

    return 0;
}