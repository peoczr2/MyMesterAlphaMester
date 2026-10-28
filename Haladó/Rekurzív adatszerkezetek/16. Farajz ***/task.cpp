/*
Megoldás lényege:
Minden csúcs pozíciója a két gyerekének számtani közepe, így a rajz a gyerekek
távolságából határozódik meg. Egy részfát szintenként a legbaloldalibb és a
legjobboldalibb pozíciójával (kontúrjával) jellemzünk. A két gyerekfát úgy toljuk
egymás mellé, hogy minden közös szinten a bal oldali részfa legjobboldalibb és a jobb
oldali részfa legbaloldalibb csúcsa legalább 2 távolságra legyen, a gyerekek távolsága
pedig ennek legkisebb lehetséges értéke. A teljes rajz szélessége a gyökér kontúrjának
szélessége. Az időigény O(N * h), ahol h a fa magassága.
*/
/*
Hint 1: || A csúcs pozíciója a két gyerek pozíciójának átlaga, így a gyerekek távolsága határozza meg a szülő helyét. ||
Hint 2: || Minden részfához szintenként el kell tárolni a legbaloldalibb és legjobboldalibb pozíciót, ezekből adódik a két részfa közötti minimális távolság. ||
Hint 3: || A két részfát úgy kell eltolni, hogy minden közös szinten a bal oldali részfa legjobboldalibb és a jobb oldali legbaloldalibb csúcsa legalább 2 távolságra legyen. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Egy részfa szintenkénti szélsőértékei a részfa gyökeréhez (0) képest.
struct Shape {
    vector<long double> lo, hi;
};

string s;
size_t p;

Shape build() {
    ++p; // a csúcs betűje
    if (p >= s.size() || s[p] != '(') {
        Shape leaf;
        leaf.lo.assign(1, 0.0L);
        leaf.hi.assign(1, 0.0L);
        return leaf;
    }
    ++p; // (
    Shape a = build();
    ++p; // ,
    Shape b = build();
    ++p; // )

    // A gyerekek távolsága D: minden közös szinten D >= 2 + a.hi - b.lo
    long double D = 2.0L;
    size_t common = min(a.lo.size(), b.lo.size());
    for (size_t d = 0; d < common; ++d) {
        D = max(D, 2.0L + a.hi[d] - b.lo[d]);
    }

    Shape r;
    r.lo.assign(1, 0.0L);
    r.hi.assign(1, 0.0L);
    size_t len = max(a.lo.size(), b.lo.size());
    for (size_t d = 0; d < len; ++d) {
        long double lo = numeric_limits<long double>::max();
        long double hi = -lo;
        if (d < a.lo.size()) {
            lo = min(lo, a.lo[d] - D / 2);
            hi = max(hi, a.hi[d] - D / 2);
        }
        if (d < b.lo.size()) {
            lo = min(lo, b.lo[d] + D / 2);
            hi = max(hi, b.hi[d] + D / 2);
        }
        r.lo.push_back(lo);
        r.hi.push_back(hi);
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    p = 0;
    Shape root = build();
    long double lo = *min_element(root.lo.begin(), root.lo.end());
    long double hi = *max_element(root.hi.begin(), root.hi.end());
    long long ans = (long long)ceill(hi - lo - 1e-9L);
    cout << ans << '\n';
    return 0;
}
