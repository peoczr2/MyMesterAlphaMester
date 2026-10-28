/*
Megoldás lényege:
A d(n) = n + (n számjegyeinek összege) függvény a legfeljebb 9 jegyű n-eknél legfeljebb 81-gyel nagyobb a számnál, így egy X szám generálója (olyan n, amelyre d(n) = X) csak az X - 81 és X - 1 közötti számok között lehet.
Ezért nem kell minden számot vizsgálni: az M-hez közeli n-ek (M - 200 és M között) d(n) értékeivel megjelöljük az előállítható számokat, és a legnagyobb olyan X ≤ M, amely nincs megjelölve, lesz a keresett self-szám.
Az ablak mérete bőven lefedi a szükséges tartományt az M - 119 és M közötti X-ekre, és 10^9-ig két egymás utáni self-szám távolsága legfeljebb 80, így az ablakban mindig van self-szám.
Mivel csak mintegy 200 számjegyösszeget számolunk, az időigény gyakorlatilag konstans.
*/
/*
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
