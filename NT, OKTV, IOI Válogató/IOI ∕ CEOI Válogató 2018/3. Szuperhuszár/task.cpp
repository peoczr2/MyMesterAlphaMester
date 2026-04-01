/*
Megoldás lényege:
A második játékos akkor tud biztosan visszamenni az origóba, ha a megengedett
lépések additív monoidja valójában csoporttá záródik. Ez pontosan akkor teljesül,
ha a lépések iránya nem fér bele egy zárt félsíkba úgy, hogy közben ne legyenek
mind egy egyenesben.

Geometriailag ez két esetet jelent:
1. Ha minden lépés egy egyenesre esik, akkor kell, hogy mindkét ellentétes irány
   jelen legyen.
2. Egyébként a lépések szögei között ne legyen 180 foknál nagyobb hézag, vagyis
   az origó legyen a vektorok konvex burkának belsejében.

Az ellenőrzéshez az irányokat szög szerint rendezzük, és megkeressük a legnagyobb
szomszédos szögkülönbséget.
*/

#include <bits/stdc++.h>
using namespace std;

struct Vec {
    long long x, y;
};

static long long cross(const Vec& a, const Vec& b) {
    return a.x * b.y - a.y * b.x;
}

static long long dot(const Vec& a, const Vec& b) {
    return a.x * b.x + a.y * b.y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    if (!(cin >> k)) return 0;

    while (k--) {
        int l;
        cin >> l;
        vector<Vec> v(l);
        for (int i = 0; i < l; ++i) cin >> v[i].x >> v[i].y;

        int first = -1;
        for (int i = 0; i < l; ++i) {
            if (v[i].x != 0 || v[i].y != 0) {
                first = i;
                break;
            }
        }

        if (first == -1) {
            cout << "IGEN\n";
            continue;
        }

        bool colinear = true;
        for (int i = 0; i < l; ++i) {
            if (cross(v[first], v[i]) != 0) {
                colinear = false;
                break;
            }
        }

        bool ok = false;
        if (colinear) {
            bool pos = false, neg = false;
            for (const auto& p : v) {
                long long d = dot(v[first], p);
                if (d > 0) pos = true;
                if (d < 0) neg = true;
            }
            ok = pos && neg;
        } else {
            sort(v.begin(), v.end(), [](const Vec& a, const Vec& b) {
                bool ha = (a.y > 0) || (a.y == 0 && a.x > 0);
                bool hb = (b.y > 0) || (b.y == 0 && b.x > 0);
                if (ha != hb) return ha > hb;
                long long c = cross(a, b);
                if (c != 0) return c > 0;
                long long da = a.x * a.x + a.y * a.y;
                long long db = b.x * b.x + b.y * b.y;
                return da < db;
            });

            vector<long double> ang;
            ang.reserve(l);
            for (const auto& p : v) ang.push_back(atan2l((long double)p.y, (long double)p.x));
            sort(ang.begin(), ang.end());
            long double bestGap = 0;
            for (int i = 0; i < l; ++i) {
                long double cur = ang[(i + 1) % l] - ang[i];
                if (i + 1 == l) cur += 2.0L * acosl(-1.0L);
                bestGap = max(bestGap, cur);
            }
            ok = bestGap < acosl(-1.0L) - 1e-15L;
        }

        cout << (ok ? "IGEN" : "NEM") << '\n';
    }

    return 0;
}