/*
Megoldás lényege:
A kiválasztott A fa körül szög szerint rendezzük a többi fát. Ha van megoldás, akkor P
szigorúan beleesik valamely két egymást követő sugár által kifeszített háromszögbe.
Minden ilyen szomszédos párra teszteljük, hogy az A-B-C háromszög szigorúan tartalmazza-e
az új facsemetét. Ha igen, a szomszédos sorrend miatt a háromszög üres is lesz.

Idő: O(N log N)
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

static bool insideStrict(const Pt& a, const Pt& b, const Pt& c, const Pt& p) {
    long long c1 = cross(a, b, p);
    long long c2 = cross(b, c, p);
    long long c3 = cross(c, a, p);
    bool pos = (c1 > 0 && c2 > 0 && c3 > 0);
    bool neg = (c1 < 0 && c2 < 0 && c3 < 0);
    return pos || neg;
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

    auto half = [&](const Pt& q) {
        long long dx = q.x - a.x;
        long long dy = q.y - a.y;
        return (dy > 0) || (dy == 0 && dx > 0);
    };

    sort(others.begin(), others.end(), [&](const Pt& lhs, const Pt& rhs) {
        bool hl = half(lhs), hr = half(rhs);
        if (hl != hr) return hl > hr;
        long long c = cross(a, lhs, rhs);
        if (c != 0) return c > 0;
        __int128 dl = (__int128)(lhs.x - a.x) * (lhs.x - a.x) + (__int128)(lhs.y - a.y) * (lhs.y - a.y);
        __int128 dr = (__int128)(rhs.x - a.x) * (rhs.x - a.x) + (__int128)(rhs.y - a.y) * (rhs.y - a.y);
        return dl < dr;
    });

    int m = (int)others.size();
    for (int i = 0; i < m; ++i) {
        const Pt& b = others[i];
        const Pt& c = others[(i + 1) % m];
        if (insideStrict(a, b, c, P)) {
            if (cross(a, b, c) < 0) {
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
