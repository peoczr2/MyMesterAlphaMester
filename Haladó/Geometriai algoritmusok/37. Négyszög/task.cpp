/*
Megoldás lényege:
Egy ponthalmaz akkor tartalmaz konvex négyszöget, ha a konvex burka legalább 4 csúcsból áll.
Ezért minden ponthalmazra elég a burkot kiszámítani, és a burkcsúcsok számát ellenőrizni.

Idő: O(N log N)
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        int N;
        cin >> N;
        vector<Pt> p(N);
        for (int i = 0; i < N; ++i) cin >> p[i].x >> p[i].y;

        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());

        if ((int)p.size() < 4) {
            cout << "NINCS\n";
            continue;
        }

        vector<Pt> hull;
        hull.reserve(p.size() * 2);

        for (const auto& pt : p) {
            while ((int)hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), pt) <= 0) {
                hull.pop_back();
            }
            hull.push_back(pt);
        }

        int lowerSize = (int)hull.size();
        for (int i = (int)p.size() - 2; i >= 0; --i) {
            while ((int)hull.size() > lowerSize && cross(hull[hull.size() - 2], hull.back(), p[i]) <= 0) {
                hull.pop_back();
            }
            hull.push_back(p[i]);
        }

        if (!hull.empty()) hull.pop_back();

        if ((int)hull.size() >= 4) cout << "VAN\n";
        else cout << "NINCS\n";
    }

    return 0;
}
