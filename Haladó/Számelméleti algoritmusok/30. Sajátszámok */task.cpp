/*
 * A self-number keresése. Elég az M körüli generáló jelöltek vizsgálata.
 
Hint 1: || Egy X szám generátora csak kevéssel lehet kisebb X-nél, mert legfeljebb a számjegyösszeggel térhet el. ||
Hint 2: || Nem kell 1-től M-ig mindent vizsgálni: elég az M körüli szűk tartományban megnézni, hogy előáll-e `n + számjegyösszeg(n)` alakban. ||
*/

#include "../common.hpp"

static long long gen(long long n) {
    long long s = 0, t = n;
    while (t) {
        s += t % 10;
        t /= 10;
    }
    return n + s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long m;
    cin >> m;
    unordered_set<long long> generated;
    long long start = max(1LL, m - 200);
    for (long long n = start; n <= m; ++n) {
        long long x = gen(n);
        if (x <= m) generated.insert(x);
    }
    for (long long x = m; x >= 1 && x >= m - 200; --x) {
        if (!generated.count(x)) {
            cout << x << '\n';
            return 0;
        }
    }
    cout << m << '\n';
    return 0;
}
