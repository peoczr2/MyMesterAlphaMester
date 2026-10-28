/*
Megoldás lényege:
A külső oldalak összhossza az épületek egyesítésének (unió) kerülete, mert az érintkező falak nem tartoznak a külső oldalakhoz. A kerületet vízszintes és függőleges részre bontjuk. A vízszintes éleket x szerinti sweep-pel számoljuk: két esemény közötti vékony x-sávban a lefedett, összefüggő y-szakaszok száma adja a felső és alsó élek számát, így a sáv szélességével szorozva 2 · szakaszszám · szélesség a hozzájárulás. A függőleges éleket ugyanígy kapjuk, az x és y szerepét felcserélve. A lefedettséget szakaszfa tartja nyilván, ezért az idő O(N log N).
*/
/*
Hint 1: || Az épületek külső oldalai az egyesített alakzat határának részei. Érdemes a határt vízszintes és függőleges szakaszokra bontva külön összeadni. ||
Hint 2: || Vízszintes élek hosszát x szerinti sweep adja: minden két egymás utáni x-esemény közötti sávban számold meg, hány összefüggő y-szakasz van lefedve. Egy ilyen szakasz két vízszintes élt ad, a sáv szélességével. ||
Hint 3: || A lefedett y-szakaszokat szakaszfával tartsd nyilván, amelyben minden csúcs megmondja, hány lefedett összefüggő szakasz van a részfájában. Függőleges élekhez ugyanezt végezd el y szerinti sweep-pel. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Event {
    int x;
    int l, r;  // az érintett elemi y-szakaszok zárt intervalluma
    int delta;
    bool operator<(const Event& other) const {
        return x < other.x;
    }
};

// info: a lefedett összefüggő szakaszok száma (alsó 30 bit), a bal szél (30. bit) és a jobb szél (31. bit) lefedettsége.
static const unsigned LBIT = 1u << 30, RBIT = 1u << 31, SMASK = LBIT - 1;

struct Node {
    int cover = 0;
    unsigned info = 0;
};

// Rekurzió nélküli szakaszfa az elemi y-szakaszokon. A lefedettséget nem toljuk le, ezért minden
// módosítás után a megváltozott csúcsok felmenő útvonalát újraszámoljuk.
struct SegTree {
    int P;
    vector<Node> st;

    explicit SegTree(int leaves) {
        P = 1;
        while (P < max(1, leaves)) P <<= 1;
        st.assign(2 * P, Node{});
    }

    void pull(int p) {
        Node& v = st[p];
        if (v.cover > 0) {
            v.info = 1u | LBIT | RBIT;
        } else if (p >= P) {
            v.info = 0;
        } else {
            unsigned L = st[2 * p].info, R = st[2 * p + 1].info;
            unsigned joined = ((L & RBIT) && (R & LBIT)) ? 1u : 0u;
            unsigned segs = (L & SMASK) + (R & SMASK) - joined;
            v.info = segs | (L & LBIT) | (R & RBIT);
        }
    }

    // Az elemi szakaszok [l, r] zárt intervallumának lefedettségét módosítja.
    void addRange(int l, int r, int delta) {
        int lo = l + P, hi = r + P + 1;
        int leftLeaf = lo, rightLeaf = hi - 1;
        for (; lo < hi; lo >>= 1, hi >>= 1) {
            if (lo & 1) {
                st[lo].cover += delta;
                pull(lo);
                ++lo;
            }
            if (hi & 1) {
                --hi;
                st[hi].cover += delta;
                pull(hi);
            }
        }
        for (int a = leftLeaf >> 1, b = rightLeaf >> 1; a >= 1; a >>= 1, b >>= 1) {
            pull(a);
            if (b != a) pull(b);
        }
    }

    int segmentCount() const { return (int)(st[1].info & SMASK); }
};

// A téglalapok határának "vízszintes" éleinek összhossza: a sweep-tengely (a) mentén haladva
// minden sávban 2 * (lefedett összefüggő szakaszok száma) * (sáv szélessége).
// A rects elemei: {x1, y1, x2, y2}; a = 0 esetén x a sweep-tengely, a = 1 esetén y.
static long long sweepEdges(const vector<array<long long, 4>>& rects, int a) {
    const int b = 1 - a;
    const int m = (int)rects.size();

    // A merőleges tengely (b) értékeinek rangsorolása: egyenlő értékek azonos sorszámot kapnak.
    vector<pair<int, int>> keys;
    keys.reserve(2 * m);
    for (int i = 0; i < m; ++i) {
        keys.push_back({(int)rects[i][b], 2 * i});
        keys.push_back({(int)rects[i][b + 2], 2 * i + 1});
    }
    sort(keys.begin(), keys.end());
    vector<int> rank(2 * m);
    int distinct = 0;
    for (size_t k = 0; k < keys.size(); ++k) {
        if (k == 0 || keys[k].first != keys[k - 1].first) ++distinct;
        rank[keys[k].second] = distinct - 1;
    }

    // Egy téglalap a [rank(lo), rank(hi)-1] elemi szakaszokat fedi.
    vector<Event> ev;
    ev.reserve(2 * m);
    for (int i = 0; i < m; ++i) {
        int l = rank[2 * i], r = rank[2 * i + 1] - 1;
        if (l > r) continue;
        ev.push_back({(int)rects[i][a], l, r, +1});
        ev.push_back({(int)rects[i][a + 2], l, r, -1});
    }
    if (ev.empty()) return 0;
    sort(ev.begin(), ev.end());

    SegTree st(distinct - 1);

    long long total = 0;
    long long prevX = ev[0].x;
    size_t i = 0;
    while (i < ev.size()) {
        long long x = ev[i].x;
        long long dx = x - prevX;
        if (dx > 0) {
            total += 2LL * st.segmentCount() * dx;
            prevX = x;
        }
        while (i < ev.size() && ev[i].x == x) {
            st.addRange(ev[i].l, ev[i].r, ev[i].delta);
            ++i;
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<array<long long, 4>> rects(N);
    for (auto& r : rects) cin >> r[0] >> r[1] >> r[2] >> r[3];

    // Az unió kerülete = vízszintes élek (x szerinti sweep) + függőleges élek (y szerinti sweep).
    // A közös falak (érintkező épületek) nem a külső oldalhoz tartoznak, így az unió határát adjuk meg.
    cout << sweepEdges(rects, 0) + sweepEdges(rects, 1) << '\n';
    return 0;
}
