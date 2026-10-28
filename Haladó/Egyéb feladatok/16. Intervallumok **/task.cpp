/*
Megoldás lényege:
A B ember főnöke az A embernek, ha B intervalluma benne van A intervallumában, vagyis B kezdete nem kisebb és vége nem nagyobb.
Minden intervallumra tehát azt kell megszámolni, hány másik intervallum tartalmazza. Az intervallumokat kezdőpont szerint rendezzük
(azonos kezdőpontnál a nagyobb végpont előbb), majd fordított sorrendben dolgozzuk fel. Így a már beszúrt intervallumok kezdete
nem kisebb az aktuálisénál, és a tartalmazottakat csak a végpontjuk alapján kell megszámolni: egy Fenwick-fa a végpontok
rangjait tartja nyilván. Az egyforma intervallumok kölcsönösen tartalmazzák egymást, ezért a futamon belül előttük álló
azonos példányokat külön hozzáadjuk. Az időigény O(N log N).
*/
/*
Hint 1: || Az A ember főnöke B-nek, ha B intervalluma benne van A-éban. Ez kétdimenziós feltétel: minden intervallumra azt kell megszámolni, hány másiknak nagyobb vagy egyenlő a kezdete és kisebb vagy egyenlő a vége. ||
Hint 2: || Rendezd az intervallumokat kezdőpont szerint, azonos kezdőpontnál a nagyobb végponttal előbb. Ezután fordított sorrendben haladj, és a már beszúrt végpontokat tartsd Fenwick-fában a rangjuk szerint: a lekérdezés a végpontok prefixösszege. ||
Hint 3: || Egyforma intervallumok esetén mindkét ember tartalmazza a másikat, a Fenwick-fás lekérdezés viszont csak a később beszúrtakat látja. Ezt úgy pótold, hogy a futamon belül megszámolod az előtte álló azonos intervallumokat. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Gyors beolvasás: a bemenet nagy lehet, ezért blokkonként olvasunk.
static char ibuf[1 << 16];
static size_t ipos = 0, ilen = 0;

static inline int gc() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return static_cast<unsigned char>(ibuf[ipos++]);
}

static inline int readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9')) c = gc();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

struct Interval {
    int a, b, id;
};

int main() {
    int n = readInt();
    vector<Interval> v(n);
    for (int i = 0; i < n; ++i) {
        v[i].a = readInt();
        v[i].b = readInt();
        v[i].id = i + 1;
    }

    // Kezdőpont szerint növekvően, azonos kezdőpontnál a nagyobb végpont előbb (a bemenet már ilyen,
    // de ha nem lenne, rendezzük).
    auto cmp = [](const Interval& x, const Interval& y) {
        if (x.a != y.a) return x.a < y.a;
        return x.b > y.b;
    };
    if (!is_sorted(v.begin(), v.end(), cmp)) sort(v.begin(), v.end(), cmp);

    // A végpontok rangja: (végpont, pozíció) párok rendezése után a különböző végpontok sorszáma.
    vector<unsigned long long> keys(n);
    for (int i = 0; i < n; ++i)
        keys[i] = (static_cast<unsigned long long>(v[i].b) << 20) | static_cast<unsigned>(i);
    sort(keys.begin(), keys.end());
    vector<int> rk(n);
    int m = 0;
    long long prev_b = -1;
    for (int t = 0; t < n; ++t) {
        long long b = static_cast<long long>(keys[t] >> 20);
        int idx = static_cast<int>(keys[t] & ((1ULL << 20) - 1));
        if (b != prev_b) {
            ++m;
            prev_b = b;
        }
        rk[idx] = m;
    }

    // Azonos intervallumok futamon belül: hány azonos előzi meg az adott elemet.
    vector<int> same_before(n, 0);
    for (int i = 1; i < n; ++i)
        if (v[i].a == v[i - 1].a && v[i].b == v[i - 1].b)
            same_before[i] = same_before[i - 1] + 1;

    // Fordított sorrendben: a már beszúrt elemek a sorrendben utánunk álló intervallumok.
    vector<int> bit(m + 1, 0);
    int best = -1, best_id = 0;
    for (int k = n - 1; k >= 0; --k) {
        int r = rk[k];
        int s = 0;
        for (int i = r; i > 0; i -= i & -i) s += bit[i];
        int cnt = s + same_before[k];
        for (int i = r; i <= m; i += i & -i) bit[i]++;
        if (cnt > best || (cnt == best && v[k].id < best_id)) {
            best = cnt;
            best_id = v[k].id;
        }
    }

    printf("%d %d\n", best, best_id);
    return 0;
}
