/*
Megoldás lényege:
A négyzetek vagy téglalapok fedését, metszését vagy optimális kiválasztását kell kezelni. A számítás a geometriai átfedések pontos vizsgálatára épül.
*/
#include <bits/stdc++.h>
using namespace std;

struct Square {
    long long x, y, l;
};

static bool hitRay(const Square& s, long double ux, long double uy, long double& t) {
    long double t1 = (long double)s.x / ux;
    long double t2 = (long double)(s.x + s.l) / ux;
    long double t3 = (long double)s.y / uy;
    long double t4 = (long double)(s.y + s.l) / uy;
    long double enter = max(min(t1, t2), min(t3, t4));
    long double exit = min(max(t1, t2), max(t3, t4));
    if (enter <= exit) {
        t = enter;
        return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<Square> sq(n);
    for (int i = 0; i < n; ++i) cin >> sq[i].x >> sq[i].y >> sq[i].l;

    vector<long double> angles;
    angles.reserve(4 * n);
    const long double PI = acosl(-1.0L);
    for (const auto& s : sq) {
        long double x1 = (long double)s.x;
        long double x2 = (long double)(s.x + s.l);
        long double y1 = (long double)s.y;
        long double y2 = (long double)(s.y + s.l);
        angles.push_back(atan2l(y1, x1));
        angles.push_back(atan2l(y1, x2));
        angles.push_back(atan2l(y2, x1));
        angles.push_back(atan2l(y2, x2));
    }

    sort(angles.begin(), angles.end());
    angles.erase(unique(angles.begin(), angles.end(), [](long double a, long double b) {
        return fabsl(a - b) < 1e-18L;
    }), angles.end());

    vector<char> visible(n, 0);

    auto sample = [&](long double ang) {
        long double ux = cosl(ang);
        long double uy = sinl(ang);
        int best = -1;
        long double bestT = numeric_limits<long double>::infinity();
        for (int i = 0; i < n; ++i) {
            long double t;
            if (!hitRay(sq[i], ux, uy, t)) continue;
            if (t < bestT) {
                bestT = t;
                best = i;
            }
        }
        if (best != -1) visible[best] = 1;
    };

    if (angles.empty()) {
        cout << 0 << '\n';
        return 0;
    }

    sample(max(angles.front() * 0.5L, 1e-12L));
    for (int i = 0; i + 1 < (int)angles.size(); ++i) {
        sample((angles[i] + angles[i + 1]) * 0.5L);
    }
    sample((angles.back() + PI * 0.5L) * 0.5L);

    int answer = 0;
    for (char v : visible) answer += v;
    cout << answer << '\n';
    return 0;
}