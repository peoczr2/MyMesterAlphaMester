/*
Megoldás lényege:
Az épületek külső oldalainak összhossza az egyesített alakzat kerülete. A vízszintes éleket x szerinti söpréssel számoljuk: egy x-szeletben a lefedett y-szakaszok számát szegmensfával tartjuk nyilván, és a szelet szélességével szorozva 2-vel adjuk hozzá. A függőleges éleket ugyanígy kapjuk, ha a tengelyeket felcseréljük és y szerint söpörünk. Mindkét söprés O(N log N), az összidő is ennyi.
*/
/*
Hint 1: || Az egyesített alakzat kerülete tengelyek szerint szétválasztható: a vízszintes és a függőleges élek összhosszát külön-külön számold. ||
Hint 2: || Két egymást követő esemény között a lefedettség állandó, így egy x-szeletben a vízszintes élek összhossza 2 · (lefedett y-szakaszok száma) · szélesség. ||
Hint 3: || A szegmensfa csomópontjában tárold a lefedett hosszt, a lefedett szakaszok számát és a két szélének lefedettségét; két gyerek összevonásakor a határon összeérő szakaszok egynek számítanak. ||
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Rect {
    int x1, y1, x2, y2;
};

struct Ev {
    int x;
    int l, r;  // az y-elemi intervallumok [l, r) indexei
    int d;
};

struct Node {
    int cover;  // a csomópontra közvetlenül ráfeszülő téglalapok száma
    int len;    // a csomópont lefedett hossza
    int segs;   // a lefedett futamok száma
    int flags;  // bit0: bal szél lefedett, bit1: jobb szél lefedett
};

static vector<int> ys;
static vector<int> full;  // a csomópont teljes hossza (kitöltetlen levelek: 0)
static vector<Node> st;
static int sz;  // 2-hatvány >= elemi intervallumok száma

static inline void pull(int p) {
    Node& nd = st[p];
    if (nd.cover > 0) {
        nd.len = full[p];
        nd.segs = 1;
        nd.flags = 3;
        return;
    }
    if (p >= sz) {
        nd.len = 0;
        nd.segs = 0;
        nd.flags = 0;
        return;
    }
    const Node& a = st[p << 1];
    const Node& b = st[(p << 1) | 1];
    nd.len = a.len + b.len;
    nd.segs = a.segs + b.segs - (((a.flags >> 1) & 1) && (b.flags & 1) ? 1 : 0);
    nd.flags = (a.flags & 1) | (b.flags & 2);
}

// [l, r) elemi intervallum lefedése d-vel (alulról felfelé, rekurzió nélkül).
static void update(int l, int r, int d) {
    l += sz;
    r += sz;
    int l0 = l, r0 = r - 1;
    while (l < r) {
        if (l & 1) {
            st[l].cover += d;
            pull(l);
            ++l;
        }
        if (r & 1) {
            --r;
            st[r].cover += d;
            pull(r);
        }
        l >>= 1;
        r >>= 1;
    }
    for (int i = l0 >> 1; i >= 1; i >>= 1) pull(i);
    for (int i = r0 >> 1; i >= 1; i >>= 1) pull(i);
}

// Egy irányú söprés: az x-szerinti szeletekben a lefedett y-futamok száma
// adja a vízszintes élek összhosszát (2 * futamok * dx).
static ll sweepHorizontal(const vector<Rect>& R) {
    ys.clear();
    ys.reserve(2 * R.size());
    for (const auto& r : R) {
        ys.push_back(r.y1);
        ys.push_back(r.y2);
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int n = (int)ys.size() - 1;  // elemi y-intervallumok száma
    if (n <= 0) return 0;

    vector<Ev> ev;
    ev.reserve(2 * R.size());
    for (const auto& r : R) {
        int l = (int)(lower_bound(ys.begin(), ys.end(), r.y1) - ys.begin());
        int rr = (int)(lower_bound(ys.begin(), ys.end(), r.y2) - ys.begin());
        ev.push_back({r.x1, l, rr, +1});
        ev.push_back({r.x2, l, rr, -1});
    }
    sort(ev.begin(), ev.end(), [](const Ev& a, const Ev& b) { return a.x < b.x; });

    sz = 1;
    while (sz < n) sz <<= 1;
    full.assign(2 * sz, 0);
    for (int i = 0; i < n; ++i) full[sz + i] = ys[i + 1] - ys[i];
    for (int i = sz - 1; i >= 1; --i) full[i] = full[2 * i] + full[2 * i + 1];
    st.assign(2 * sz, Node{0, 0, 0, 0});

    ll res = 0;
    size_t i = 0;
    ll prevX = ev[0].x;
    while (i < ev.size()) {
        ll x = ev[i].x;
        ll dx = x - prevX;
        if (dx > 0) {
            res += 2LL * st[1].segs * dx;
            prevX = x;
        }
        while (i < ev.size() && ev[i].x == x) {
            update(ev[i].l, ev[i].r, ev[i].d);
            ++i;
        }
    }
    return res;
}

static char buf[1 << 23];

int main() {
    size_t len_in = fread(buf, 1, sizeof(buf) - 1, stdin);
    buf[len_in] = 0;
    char* p = buf;
    auto readInt = [&]() -> int {
        while (*p && (*p < '0' || *p > '9') && *p != '-') ++p;
        bool neg = false;
        if (*p == '-') {
            neg = true;
            ++p;
        }
        int v = 0;
        while (*p >= '0' && *p <= '9') {
            v = v * 10 + (*p - '0');
            ++p;
        }
        return neg ? -v : v;
    };

    int N = readInt();
    vector<Rect> R(N);
    for (auto& r : R) {
        r.x1 = readInt();
        r.y1 = readInt();
        r.x2 = readInt();
        r.y2 = readInt();
    }

    // Vízszintes élek: x-szerinti söprés; függőleges élek: ugyanez a tengelyek
    // felcserélésével (y-szerinti söprés).
    ll perimeter = sweepHorizontal(R);
    for (auto& r : R) {
        swap(r.x1, r.y1);
        swap(r.x2, r.y2);
    }
    perimeter += sweepHorizontal(R);

    printf("%lld\n", perimeter);
    return 0;
}
