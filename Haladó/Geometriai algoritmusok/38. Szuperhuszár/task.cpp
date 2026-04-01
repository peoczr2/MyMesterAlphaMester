/*
Megoldás lényege:
A második játékos akkor és csak akkor tud mindig visszajutni az origóba, ha a megengedett
lépések pozitív konvex burka tartalmazza az origót a relatív belsejében. Ez pontosan azt
jelenti, hogy az origó vagy a kétdimenziós konvex burok szigorú belsejében van, vagy a
kollineáris esetben a szakasz belsejében.

Idő: O(L log L) játékonként.
*/

#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
    bool operator<(const Pt& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    bool operator==(const Pt& other) const {
        return x == other.x && y == other.y;
    }
};

static long long cross(const Pt& a, const Pt& b, const Pt& c) {
    __int128 v = (__int128)(b.x - a.x) * (c.y - a.y) - (__int128)(b.y - a.y) * (c.x - a.x);
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

static __int128 dot(const Pt& a, const Pt& b) {
    return (__int128)a.x * b.x + (__int128)a.y * b.y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    if (!(cin >> K)) return 0;

    while (K--) {
        int L;
        cin >> L;
        vector<Pt> v(L);
        for (int i = 0; i < L; ++i) cin >> v[i].x >> v[i].y;

        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());

        if (v.size() == 1) {
            cout << "NEM\n";
            continue;
        }

        vector<Pt> h;
        h.reserve(v.size() * 2);
        for (const auto& p : v) {
            while (h.size() >= 2 && cross(h[h.size() - 2], h.back(), p) <= 0) h.pop_back();
            h.push_back(p);
        }
        size_t lower = h.size();
        for (int i = (int)v.size() - 2; i >= 0; --i) {
            while (h.size() > lower && cross(h[h.size() - 2], h.back(), v[i]) <= 0) h.pop_back();
            h.push_back(v[i]);
        }
        if (!h.empty()) h.pop_back();

        Pt O{0, 0};
        bool ok = false;

        if (h.size() == 2) {
            ok = (cross(h[0], h[1], O) == 0) &&
                 min(h[0].x, h[1].x) <= 0 && 0 <= max(h[0].x, h[1].x) &&
                 min(h[0].y, h[1].y) <= 0 && 0 <= max(h[0].y, h[1].y);
        } else if (h.size() >= 3) {
            bool allPos = true, allNeg = true;
            for (size_t i = 0; i < h.size(); ++i) {
                const Pt& a = h[i];
                const Pt& b = h[(i + 1) % h.size()];
                long long c = cross(a, b, O);
                if (c < 0) allPos = false;
                if (c > 0) allNeg = false;
            }
            ok = allPos || allNeg;
            if (ok) {
                bool strict = true;
                for (size_t i = 0; i < h.size(); ++i) {
                    const Pt& a = h[i];
                    const Pt& b = h[(i + 1) % h.size()];
                    long long c = cross(a, b, O);
                    if (c == 0) {
                        strict = false;
                        break;
                    }
                }
                ok = strict;
            }
        }

        cout << (ok ? "IGEN" : "NEM") << '\n';
    }

    return 0;
}
