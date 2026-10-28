/*
Megoldás lényege:
Egy kézbesítés az idő-hely síkon egy szakasz: O idő alatt megy az egyik telephelyről a másikra. Két futár akkor
találkozik út közben, ha ellentétes irányba indult, és az indulásaik között kevesebb idő telt el, mint O; ekkor
a találkozás ideje (O + t1 + t2) / 2. Mindkét futár kézbesítései időben növekvő sorrendben vannak, ezért minden
kézbesítéshez a másik futár szóba jöhető indulásai egy összefüggő tartományt alkotnak, amelyet két mutatóval
(csúszó ablakkal) követünk. Így a párok O(N + M + K) időben előállíthatók, majd a párokat a találkozási idő
(azaz t1 + t2) szerint rendezve kiírjuk.
*/
/*
Hint 1: || Képzeld el a kézbesítést szakaszként az idő–hely síkon: O idő alatt megy át a másik telephelyre. Két futár akkor találkozhat út közben, ha ellentétes irányba indult, és az indulásaik között kevesebb idő telt el, mint O. ||
Hint 2: || Mindkét lista időben rendezett, ezért minden kézbesítésnél a másik futár szóba jöhető indulásai egy összefüggő tartományt adnak. Ezt két mutatóval követheted, így nem kell minden párt végigpróbálni. ||
Hint 3: || A találkozás ideje (O + t1 + t2) / 2, így a párokat elég t1 + t2 szerint rendezni, a darabszám pedig a talált párok száma. Az adatok int-ben is elférnek, mert az összeg legfeljebb 2·10^8. ||
*/
#include <bits/stdc++.h>
using namespace std;

static char ibuf[1 << 16];
static size_t ipos = 0, ilen = 0;

static inline int gc() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0)
            return -1;
    }
    return (unsigned char)ibuf[ipos++];
}

static inline long long readInt() {
    int c = gc();
    while (c != -1 && !(c >= '0' && c <= '9'))
        c = gc();
    long long x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

static inline char readSite() {
    int c = gc();
    while (c != -1 && c != 'A' && c != 'B')
        c = gc();
    return (char)c;
}

struct Delivery {
    int t;     // indulási idő
    int idx;   // a kézbesítés sorszáma (1-től)
    char site; // 'A' vagy 'B'
};

struct Meeting {
    int sum; // t1 + t2, ebből a találkozási idő monoton számítható
    int i, j;
};

static bool isSortedByTime(const vector<Delivery> &v) {
    for (size_t k = 1; k < v.size(); ++k)
        if (v[k - 1].t > v[k].t)
            return false;
    return true;
}

int main() {
    long long n = readInt();
    long long m = readInt();
    long long o = readInt();

    vector<Delivery> a(n), b(m);
    for (long long k = 0; k < n; ++k) {
        char s = readSite();
        long long t = readInt();
        a[k] = Delivery{(int)t, (int)(k + 1), s};
    }
    for (long long k = 0; k < m; ++k) {
        char s = readSite();
        long long t = readInt();
        b[k] = Delivery{(int)t, (int)(k + 1), s};
    }

    auto byTime = [](const Delivery &x, const Delivery &y) { return x.t < y.t; };
    if (!isSortedByTime(a))
        stable_sort(a.begin(), a.end(), byTime);
    if (!isSortedByTime(b))
        stable_sort(b.begin(), b.end(), byTime);

    vector<Meeting> res;
    size_t lo = 0; // az első olyan indulás a második futárnál, ahol t2 > t1 - O
    for (size_t i = 0; i < a.size(); ++i) {
        long long t1 = a[i].t;
        while (lo < b.size() && (long long)b[lo].t <= t1 - o)
            ++lo;
        for (size_t j = lo; j < b.size() && (long long)b[j].t < t1 + o; ++j) {
            if (a[i].site == b[j].site)
                continue; // ugyanabba az irányba haladnak, nem találkoznak
            res.push_back(Meeting{(int)(t1 + b[j].t), a[i].idx, b[j].idx});
        }
    }

    sort(res.begin(), res.end(), [](const Meeting &x, const Meeting &y) {
        if (x.sum != y.sum)
            return x.sum < y.sum;
        if (x.i != y.i)
            return x.i < y.i;
        return x.j < y.j;
    });

    string out = to_string(res.size()) + "\n";
    for (const Meeting &mt : res) {
        out += to_string(mt.i);
        out.push_back(' ');
        out += to_string(mt.j);
        out.push_back('\n');
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
