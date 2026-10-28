/*
Megoldás lényege:
X(p) a p Zeckendorf-alakjából számolható: a legkisebb tagtól felfelé minden tag vagy megmarad, vagy két kisebb tagra bomlik, és az átmenetek csak a szomszédos tagok távolságától függenek, így X(p) egy 2×2-es mátrixok szorzata. Egy Fibonacci-szám hozzáadásakor a prefixösszeg Zeckendorf-alakja csak O(1)-szer (amortizáltan) változik, ha a tagokat 2-esével követő indexek futamaiban tároljuk. A futamokhoz tartozó mátrixokat szegmensfa tartja, így minden k-ra a válasz a teljes szorzatból adódik, az időigény O(n log n).
*/
/*
Hint 1: || Egy szám Fibonacci-felbontásainak száma csak a Zeckendorf-alakjától függ: a nem szomszédos indexű tagok távolságai határozzák meg, hogy egy tag megmarad-e, vagy két kisebb tagra bomlik. ||
Hint 2: || A prefixösszegek Zeckendorf-alakját futamokban (2-esével követő indexek) tárold: egy Fibonacci-szám hozzáadása csak néhány futamot érint, így a változások száma lépésenként állandó (amortizáltan). ||
Hint 3: || Minden futamhoz tartozzon egy 2×2-es mátrix, amely az előző futam végétől mért távolságból és a futam hosszából számolódik; ezeket a kezdőpont szerinti sorrendben szegmensfában szorozd össze, és a megváltozott futamoknál csak a leveleket és azok rákövetkezőjét frissítsd. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const ull MOD = 1000000007ULL;

// 2x2 matrix with residues mod MOD
struct Mat {
    uint32_t a, b, c, d;
};

static inline Mat mul(const Mat& x, const Mat& y) {
    Mat r;
    r.a = (uint32_t)(((ull)x.a * y.a + (ull)x.b * y.c) % MOD);
    r.b = (uint32_t)(((ull)x.a * y.b + (ull)x.b * y.d) % MOD);
    r.c = (uint32_t)(((ull)x.c * y.a + (ull)x.d * y.c) % MOD);
    r.d = (uint32_t)(((ull)x.c * y.b + (ull)x.d * y.d) % MOD);
    return r;
}

const Mat IDENT = {1, 0, 0, 1};

// A Zeckendorf representation is a set of indices >= 2 (f_2 = 1, f_3 = 2, ...)
// without two neighbouring indices. It is stored as maximal runs: the run (s, e)
// means the indices s, s+2, ..., e. Runs start at least 3 apart.
// The runs are kept in a blocked sorted list.
struct Run { ll s, e; };
struct Pos { int bi, bj; bool ok() const { return bi >= 0; } };
const Pos NONE = {-1, -1};
const size_t BLOCK = 64;
vector<vector<Run>> blocks;
vector<ll> touched;   // starts of runs changed during the current addition

// firsts[i] = start of the first run of block i (kept in sync; used by the branch-free search)
vector<ll> firsts;

// last run whose start is <= x (branch-free binary searches)
static inline Pos locate(ll x) {
    size_t nb = firsts.size();
    if (nb == 0 || firsts[0] > x) return {-1, -1};
    // last block whose first start is <= x
    const ll* fb = firsts.data();
    size_t len = nb;
    while (len > 1) {
        size_t half = len / 2;
        fb = (fb[half] <= x) ? fb + half : fb;
        len -= half;
    }
    int bi = (int)(fb - firsts.data());
    // last run in that block whose start is <= x
    const Run* base = blocks[bi].data();
    size_t blen = blocks[bi].size();
    while (blen > 1) {
        size_t half = blen / 2;
        base = (base[half].s <= x) ? base + half : base;
        blen -= half;
    }
    return {bi, (int)(base - blocks[bi].data())};
}
static inline Pos nextPos(Pos p) {
    if (p.bj + 1 < (int)blocks[p.bi].size()) return {p.bi, p.bj + 1};
    if (p.bi + 1 < (int)blocks.size()) return {p.bi + 1, 0};
    return NONE;
}
static inline Pos prevPos(Pos p) {
    if (p.bj > 0) return {p.bi, p.bj - 1};
    if (p.bi > 0) return {p.bi - 1, (int)blocks[p.bi - 1].size() - 1};
    return NONE;
}
static inline Run& at(Pos p) { return blocks[p.bi][p.bj]; }

void insertRun(ll s, ll e) {
    touched.push_back(s);
    if (blocks.empty()) {
        blocks.push_back(vector<Run>(1, Run{s, e}));
        firsts.push_back(s);
        return;
    }
    Pos p = locate(s);
    int bi = p.ok() ? p.bi : 0;
    int idx = p.ok() ? p.bj + 1 : 0;
    blocks[bi].insert(blocks[bi].begin() + idx, Run{s, e});
    firsts[bi] = blocks[bi][0].s;
    if (blocks[bi].size() > 2 * BLOCK) {
        vector<Run> second(blocks[bi].begin() + BLOCK, blocks[bi].end());
        blocks[bi].resize(BLOCK);
        blocks.insert(blocks.begin() + bi + 1, second);
        firsts.insert(firsts.begin() + bi + 1, second[0].s);
    }
}
void eraseRun(ll s) {
    touched.push_back(s);
    Pos p = locate(s);
    blocks[p.bi].erase(blocks[p.bi].begin() + p.bj);
    if (blocks[p.bi].empty()) {
        blocks.erase(blocks.begin() + p.bi);
        firsts.erase(firsts.begin() + p.bi);
    } else {
        firsts[p.bi] = blocks[p.bi][0].s;
    }
}
void setEnd(ll s, ll e) {
    touched.push_back(s);
    at(locate(s)).e = e;
}

// Only the last two runs starting at or before x+2 can contain a one in [x-2, x+2].
struct Nb { Pos c, c2; };
static inline Nb neighbourhood(ll x) {
    Nb r;
    r.c = locate(x + 2);
    r.c2 = r.c.ok() ? prevPos(r.c) : NONE;
    return r;
}
// run containing y (y in [x-2, x+2]), or NONE
static inline Pos inNb(const Nb& nb, ll y) {
    if (y < 2) return NONE;
    if (nb.c.ok()) {
        const Run& r = at(nb.c);
        if (r.s <= y && y <= r.e && (y - r.s) % 2 == 0) return nb.c;
    }
    if (nb.c2.ok()) {
        const Run& r = at(nb.c2);
        if (r.s <= y && y <= r.e && (y - r.s) % 2 == 0) return nb.c2;
    }
    return NONE;
}

// Adds f_m to the represented number. Each pending value is handled by one of four rules:
//  a) x is a one:          2 f_x = f_{x+1} + f_{x-2}
//  b) x+1 is a one:        f_x + (f_{x+1} + f_{x+3} + ... + f_e) = f_{e+1}
//  c) x-1 is a one:        f_{x-1} + f_x = f_{x+1}
//  d) otherwise insert x.
void addFib(ll m0) {
    static vector<ll> pending;   // reused between calls
    pending.clear();
    pending.push_back(m0);
    while (!pending.empty()) {
        ll x = pending.back();
        pending.pop_back();
        if (x < 2) {
            if (x == 1) x = 2;   // f_1 = f_2 = 1
            else continue;       // f_0 = 0
        }
        Nb nb = neighbourhood(x);
        Pos px = inNb(nb, x);
        if (px.ok()) {                                    // rule a
            ll s = at(px).s, e = at(px).e;
            eraseRun(s);
            if (x + 2 <= e) insertRun(x + 2, e);
            if (s <= x - 2) insertRun(s + 1, x - 1);
            pending.push_back(s - 2);
            pending.push_back(x + 1);
            continue;
        }
        Pos p1 = inNb(nb, x + 1);
        if (p1.ok()) {                                    // rule b
            ll s = at(p1).s, e = at(p1).e;
            eraseRun(s);
            if (s <= x - 1) insertRun(s, x - 1);
            pending.push_back(e + 1);
            continue;
        }
        Pos pm = inNb(nb, x - 1);
        if (pm.ok()) {                                    // rule c
            ll s = at(pm).s, e = at(pm).e;
            eraseRun(s);
            if (s <= x - 3) insertRun(s, x - 3);
            if (x + 1 <= e) insertRun(x + 1, e);
            pending.push_back(x + 1);
            continue;
        }
        // rule d: x-1, x, x+1 are not ones
        Pos L = inNb(nb, x - 2), R = inNb(nb, x + 2);
        if (L.ok() && R.ok()) {
            ll sl = at(L).s, er = at(R).e;
            eraseRun(x + 2);
            setEnd(sl, er);
        } else if (L.ok()) {
            setEnd(at(L).s, x);
        } else if (R.ok()) {
            ll er = at(R).e;
            eraseRun(x + 2);
            insertRun(x, er);
        } else {
            insertRun(x, x);
        }
    }
}

// Matrix of a run (s..e) as a leaf of the product. State is a row vector (x, y):
// the first run contributes T = [[1, q], [0, 0]] with q = s/2 - 1; any later run contributes
// G(d) = [[1, a], [1, b]] with d = s - (previous end): d even -> a = d/2-1, b = d/2;
// d odd -> a = b = (d-1)/2. Inside a run consecutive ones differ by 2: G(2)^(L-1) = [[1,0],[L-1,1]].
Mat leafOf(ll s, ll e, bool hasPrev, ll prevEnd) {
    ll len = (e - s) / 2 + 1;
    Mat first;
    if (!hasPrev) {
        first = {1, (uint32_t)((s / 2 - 1) % (ll)MOD), 0, 0};
    } else {
        ll d = s - prevEnd;
        if (d % 2 == 0) first = {1, (uint32_t)((d / 2 - 1) % (ll)MOD), 1, (uint32_t)((d / 2) % (ll)MOD)};
        else {
            uint32_t h = (uint32_t)(((d - 1) / 2) % (ll)MOD);
            first = {1, h, 1, h};
        }
    }
    Mat tail = {1, 0, (uint32_t)((len - 1) % (ll)MOD), 1};
    return mul(first, tail);
}

struct Event { int id; Mat m; };   // leaf of the run-start key with this id becomes m (identity if the run is gone)
struct Dirty { ll key; Pos p; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // Pass 1: maintain the runs, record every changed leaf.
    vector<Event> events;
    events.reserve((size_t)n * 3 + 16);
    vector<size_t> stepEnd(n);
    vector<Dirty> dirty;
    unordered_map<ll, int> keyId;
    keyId.reserve(1 << 18);
    vector<ll> keyOf;
    keyOf.reserve(1 << 18);
    for (int t = 0; t < n; t++) {
        touched.clear();
        addFib(a[t] + 1);                 // Fib(a) = f_{a+1}
        dirty.clear();
        for (ll k : touched) {            // changed run and its successor need new leaves
            Pos p = locate(k);
            Pos self = (p.ok() && at(p).s == k) ? p : NONE;
            dirty.push_back({k, self});
            Pos succ = p.ok() ? nextPos(p) : (blocks.empty() ? NONE : Pos{0, 0});
            if (succ.ok()) dirty.push_back({at(succ).s, succ});
        }
        sort(dirty.begin(), dirty.end(), [](const Dirty& x, const Dirty& y) { return x.key < y.key; });
        size_t m = 0;
        for (size_t i = 0; i < dirty.size(); i++) {
            if (m > 0 && dirty[m - 1].key == dirty[i].key) continue;
            dirty[m++] = dirty[i];
        }
        dirty.resize(m);
        for (const Dirty& d : dirty) {
            int id;
            auto f = keyId.find(d.key);
            if (f != keyId.end()) id = f->second;
            else {
                id = (int)keyOf.size();
                keyId.emplace(d.key, id);
                keyOf.push_back(d.key);
            }
            if (!d.p.ok()) {
                events.push_back({id, IDENT});
            } else {
                Pos pr = prevPos(d.p);
                events.push_back({id, leafOf(at(d.p).s, at(d.p).e, pr.ok(), pr.ok() ? at(pr).e : 0)});
            }
        }
        stepEnd[t] = events.size();
    }

    // Pass 2: segment tree over the run starts in increasing order; the root is the product.
    size_t K = keyOf.size();
    vector<pair<ll, int>> byKey(K);
    for (size_t i = 0; i < K; i++) byKey[i] = {keyOf[i], (int)i};
    sort(byKey.begin(), byKey.end());
    vector<int> rank(K);
    for (size_t i = 0; i < K; i++) rank[byKey[i].second] = (int)i;
    size_t P = 1;
    while (P < K) P <<= 1;
    vector<Mat> tree(2 * P, IDENT);

    string out;
    out.reserve((size_t)n * 11);
    vector<size_t> changed, next;
    size_t ev = 0;
    for (int t = 0; t < n; t++) {
        changed.clear();
        for (; ev < stepEnd[t]; ev++) {
            size_t pos = P + (size_t)rank[events[ev].id];
            tree[pos] = events[ev].m;
            changed.push_back(pos >> 1);
        }
        // recompute each affected ancestor once per level
        while (!changed.empty()) {
            sort(changed.begin(), changed.end());
            changed.erase(unique(changed.begin(), changed.end()), changed.end());
            next.clear();
            for (size_t v : changed) {
                if (v == 0) continue;
                tree[v] = mul(tree[2 * v], tree[2 * v + 1]);
                next.push_back(v >> 1);
            }
            changed.swap(next);
        }
        // X(p_t) = (1,0) * product * (1,1)^T
        ull R = ((ull)tree[1].a + tree[1].b) % MOD;
        char tmp[24];
        int tl = 0;
        do { tmp[tl++] = (char)('0' + R % 10); R /= 10; } while (R);
        while (tl) out.push_back(tmp[--tl]);
        out.push_back('\n');
    }
    cout << out;
    return 0;
}
