/*
Megoldás lényege:
A keresett háromszögnek tartalmaznia kell a kijelölt pontot, de más pontot nem. Ezért a kijelölt pont körül szögsorrendet használunk, és csak az egymást követő irányokból álló üres háromszögeket vizsgáljuk.
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

static long long dist2(const Pt& a, const Pt& b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    Pt q;
    if (!(cin >> n >> q.x >> q.y)) return 0;

    vector<Pt> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].x >> p[i].y;
        p[i].id = i;
    }

    int o = 1;
    for (int i = 2; i <= n; ++i) {
        if (p[i].y < p[o].y || (p[i].y == p[o].y && p[i].x < p[o].x)) o = i;
    }

    map<pair<long long, long long>, Pt> best;
    for (int i = 1; i <= n; ++i) {
        if (i == o) continue;
        long long dx = p[i].x - p[o].x;
        long long dy = p[i].y - p[o].y;
        long long g = std::gcd(llabs(dx), llabs(dy));
        dx /= g;
        dy /= g;
        pair<long long, long long> key{dx, dy};
        auto it = best.find(key);
        if (it == best.end() || dist2(p[i], p[o]) < dist2(it->second, p[o])) {
            best[key] = p[i];
        }
    }

    vector<Pt> cand;
    cand.reserve(best.size());
    for (auto& kv : best) cand.push_back(kv.second);

    auto upper = [&](const Pt& a) {
        long long dx = a.x - p[o].x;
        long long dy = a.y - p[o].y;
        return (dy > 0) || (dy == 0 && dx > 0);
    };

    sort(cand.begin(), cand.end(), [&](const Pt& a, const Pt& b) {
        bool ua = upper(a), ub = upper(b);
        if (ua != ub) return ua > ub;
        int c = orient(p[o], a, b);
        if (c != 0) return c > 0;
        return dist2(a, p[o]) < dist2(b, p[o]);
    });

    auto inside = [&](const Pt& a, const Pt& b) {
        int s1 = orient(p[o], a, b);
        int s2 = orient(a, b, q);
        int s3 = orient(b, p[o], q);
        int s4 = orient(p[o], a, q);
        if (s1 == 0) return false;
        if (s1 > 0) return s2 >= 0 && s3 >= 0 && s4 >= 0;
        return s2 <= 0 && s3 <= 0 && s4 <= 0;
    };

    int m = (int)cand.size();
    for (int i = 0; i < m; ++i) {
        Pt a = cand[i];
        Pt b = cand[(i + 1) % m];
        if (orient(p[o], a, b) < 0) swap(a, b);
        if (inside(a, b)) {
            cout << p[o].id << ' ' << a.id << ' ' << b.id << '\n';
            return 0;
        }
    }

    cout << "0 0 0\n";
    return 0;
}
