/*
Megoldás lényege:
A láthatósági kapcsolatokat felhasználva egy gráfot építünk, majd dinamikus programozással keressük a minimális közvetítőszámot. A geometriai helyzetekből adódik, hogy mely csúcsok köthetők össze.
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
};

static long double slope(const Pt& a, const Pt& b) {
    return (long double)(b.y - a.y) / (long double)(b.x - a.x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<Pt> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].x >> p[i].y;
    }

    vector<Pt> chain;
    chain.reserve(k);
    for (int i = 1; i <= k; ++i) {
        while ((int)chain.size() >= 2) {
            long double s1 = slope(chain[(int)chain.size() - 2], chain.back());
            long double s2 = slope(chain.back(), p[i]);
            if (s1 > s2 + 1e-18L) break;
            chain.pop_back();
        }
        chain.push_back(p[i]);
    }

    cout << (int)chain.size() - 2 << '\n';
    return 0;
}
