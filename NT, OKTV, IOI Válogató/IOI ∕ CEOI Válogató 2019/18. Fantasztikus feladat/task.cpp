/*
Megoldás lényege:
Két szám akkor nem relatív prím, ha van közös prímosztójuk, ezért egy ablak pontosan akkor hibás, ha van benne olyan prím, amellyel legalább két eleme osztható. Egy prímhez tartozó osztható helyek sorában elég a szomszédos (a,b) párokat nézni: ha egy ablakban két ilyen hely van, köztük szomszédos pár is az ablakban van. Egy (a,b) pár pontosan azokat az s kezdőpozíciójú ablakokat fedi le, amelyekre b−K+1 ≤ s ≤ a, így a hibás ablakok száma az intervallumok lefedettségéből adódik (cov[s] > 0). Egy módosításnál csak azok a prímek változnak, amelyek a régi és az új értéknek nem közös osztói: ezeknél legfeljebb néhány szomszédos pár intervallumát kell törölni vagy hozzáadni, mindegyik O(K) lépésben frissíthető. A kezdeti lefedettséget különbségtömbbel számoljuk ki. Időigény: egy módosítás O(ω·(K + log N)), ahol ω ≤ 6 az érték különböző prímosztóinak száma; memória O(MAXV + N).
*/
/*
Hint 1: || Két szám akkor nem relatív prím, ha van közös prímosztójuk. Ezért elég prímenként nézni, hány helyen osztható az adott prímmel: egy ablak akkor hibás, ha valamelyik prímből legalább kettő van benne. Melyik helyek közötti párok „fedik le” az ablakokat? ||
Hint 2: || Ha egy prímhez tartozó helyek sorrendben a_1 < a_2 < …, elég a szomszédos (a_i, a_{i+1}) párokat tekinteni, mert ha egy ablakban két osztható hely van, köztük szomszédos pár is benne van. Egy (a,b) pár az s kezdetű ablakokat fedi le, ha b−K+1 ≤ s ≤ a. ||
Hint 3: || Tarts nyilván minden ablakra, hány szomszédos pár fedi le (lefedettség), és a hibás ablakok száma az, ahol ez a szám pozitív. Egy módosításnál a régi érték prímjeinél a szomszédos párokat töröld, az újnál adj hozzá; a halmazban a lower_bound adja meg a szomszédokat. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 100000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // legkisebb prímosztó szita
    vector<int> spf(MAXV + 1, 0);
    for (int i = 2; i <= MAXV; ++i)
        if (spf[i] == 0)
            for (int j = i; j <= MAXV; j += i)
                if (spf[j] == 0) spf[j] = i;

    // pos[p]: a p prímmel osztható elemek helyei, rendezve
    vector<set<int>> pos(MAXV + 1);

    auto distinctPrimes = [&](int x, vector<int>& out) {
        out.clear();
        while (x > 1) {
            int p = spf[x];
            out.push_back(p);
            while (x % p == 0) x /= p;
        }
    };

    int t;
    cin >> t;
    while (t--) {
        int n, k, m;
        cin >> n >> k >> m;
        vector<int> v(n + 1);
        for (int i = 1; i <= n; ++i) cin >> v[i];
        int w = n - k + 1;  // ablakok száma; az s. ablak az [s, s+k-1] intervallum

        // cov[s]: hány szomszédos pár fedi le az s. ablakot; bad: a cov[s] > 0 ablakok száma
        vector<int> cov(w + 2, 0);
        int bad = 0;

        // a (a,b) szomszédos pár az s ablakokat fedi le, ha b-k+1 <= s <= a
        auto applyPair = [&](int a, int b, int d) {
            int lo = max(1, b - k + 1), hi = min(a, w);
            if (d > 0) {
                for (int s = lo; s <= hi; ++s) {
                    bad += (cov[s] == 0);
                    ++cov[s];
                }
            } else {
                for (int s = lo; s <= hi; ++s) {
                    --cov[s];
                    bad -= (cov[s] == 0);
                }
            }
        };

        vector<int> ps, ps2;
        for (int i = 1; i <= n; ++i) {
            distinctPrimes(v[i], ps);
            for (int p : ps) pos[p].insert(pos[p].end(), i);
        }
        auto contains = [](const vector<int>& vec, int p) {
            return find(vec.begin(), vec.end(), p) != vec.end();
        };

        // kezdeti lefedettség különbségtömbbel
        vector<int> diff(w + 2, 0);
        for (int p = 2; p <= MAXV; ++p) {
            const auto& S = pos[p];
            if (S.size() < 2) continue;
            for (auto it = S.begin(); next(it) != S.end(); ++it) {
                int a = *it, b = *next(it);
                int lo = max(1, b - k + 1), hi = min(a, w);
                if (lo <= hi) {
                    diff[lo]++;
                    diff[hi + 1]--;
                }
            }
        }
        int run = 0;
        for (int s = 1; s <= w; ++s) {
            run += diff[s];
            cov[s] = run;
            if (run > 0) ++bad;
        }

        // x helyet eltávolítjuk a régi érték prímjeinek halmazából
        auto removePos = [&](int p, int x) {
            auto& S = pos[p];
            auto it = S.find(x);
            bool hasPrev = it != S.begin();
            bool hasNext = next(it) != S.end();
            int pr = hasPrev ? *prev(it) : 0;
            int nx = hasNext ? *next(it) : 0;
            if (hasPrev) applyPair(pr, x, -1);
            if (hasNext) applyPair(x, nx, -1);
            if (hasPrev && hasNext) applyPair(pr, nx, +1);
            S.erase(it);
        };

        // x helyet beszúrjuk az új érték prímjeinek halmazába
        auto insertPos = [&](int p, int x) {
            auto& S = pos[p];
            auto it = S.lower_bound(x);
            bool hasPrev = it != S.begin();
            bool hasNext = it != S.end();
            int pr = hasPrev ? *prev(it) : 0;
            int nx = hasNext ? *it : 0;
            if (hasPrev && hasNext) applyPair(pr, nx, -1);
            if (hasPrev) applyPair(pr, x, +1);
            if (hasNext) applyPair(x, nx, +1);
            S.insert(it, x);
        };

        long long sum = 0;
        for (int i = 1; i <= n; ++i) sum += v[i];

        cout << bad;
        for (int q = 0; q < m; ++q) {
            int x, y;
            cin >> x >> y;
            // csak a prímosztók különbsége változik: a közös prímek halmaza érintetlen marad
            distinctPrimes(v[x], ps);
            distinctPrimes(y, ps2);
            for (int p : ps)
                if (!contains(ps2, p)) removePos(p, x);
            for (int p : ps2)
                if (!contains(ps, p)) insertPos(p, x);
            sum += y - v[x];
            v[x] = y;
            cout << ' ' << bad;
        }
        cout << ' ' << sum << '\n';

        for (int p = 2; p <= MAXV; ++p) pos[p].clear();
    }
    return 0;
}
