/*
Megoldás lényege:
Ha a torony az x. épület után áll, akkor az i. épület (i ≤ x) akkor fogja a jelet, ha a torony magasabb nála, és közötte és a torony között minden épület alacsonyabb nála. Ez azt jelenti, hogy i az x-ig terjedő prefixum monoton veremének eleme, vagyis i ≤ x < nxt_i, ahol nxt_i az i-től jobbra első, nála nem alacsonyabb épület indexe. Egy H magasságú torony tehát a h_i < H feltételt teljesítő épületek közül azokat fogja, amelyek intervalluma tartalmazza x-et. Minden épülethez így egy [i, nxt_i - 1] intervallum tartozik, a válasz pedig a lefedettség maximuma a torony lehetséges helyein. A lekérdezéseket H szerint növekvően dolgozzuk fel, az épületek intervallumait ilyen sorrendben egy szakaszfába (tartomány +1, globális maximum) tesszük. A teljes futási idő O((N + K) log N), a memória O(N).
*/
/*
Hint 1: || Egy x helyen álló torony mely épületeket éri el? Az i. épület akkor látszik, ha a közte és a torony közötti összes épületnél magasabb, és a torony magasabb nála. ||
Hint 2: || Minden i épülethez tartozik egy x-tartomány, ahol látszik: ez i-nél kezdődik, és addig tart, amíg jobbra először nem talál nála nem alacsonyabb épületet. Ezek a tartományok egy monoton verem segítségével számolhatók ki. ||
Hint 3: || Rendezd a torony magasságait és az épületeket magasság szerint. A toronynál alacsonyabb épületek tartományait egymás után add hozzá egy szakaszfához, amely tartományra +1-et tud adni és a globális maximumot adja. Így minden lekérdezés egy kiolvasás. ||
*/
#include <bits/stdc++.h>
using namespace std;

static char ibuf[1 << 16];
static size_t ipos = 0, ilen = 0;

static inline int gc() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}

static inline long long readLL() {
    int c = gc();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == -1) return 0;
        c = gc();
    }
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = gc();
    }
    long long x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return neg ? -x : x;
}

// nem rekurzív szakaszfa a 0..N pozíciókon: t a v részfájának maximuma,
// d a v részfájára ráírt, még a gyerekekig le nem vitt növelés
struct Node {
    int t, d;
};
static int SZ;
static vector<Node> nd;

static inline void applyNode(int p) {
    nd[p].t += 1;
    if (p < SZ) nd[p].d += 1;
}

static inline void rebuild(int p) {
    while (p > 1) {
        p >>= 1;
        nd[p].t = max(nd[2 * p].t, nd[2 * p + 1].t) + nd[p].d;
    }
}

// +1 a [l, r] zárt intervallumra
static void rangeInc(int l, int r) {
    int lo = l + SZ, hi = r + 1 + SZ;
    int l0 = lo, r0 = hi - 1;
    while (lo < hi) {
        if (lo & 1) applyNode(lo++);
        if (hi & 1) applyNode(--hi);
        lo >>= 1;
        hi >>= 1;
    }
    rebuild(l0);
    rebuild(r0);
}

int main() {
    int N = (int)readLL();
    int K = (int)readLL();

    vector<int> h(N + 2, 0);
    for (int i = 1; i <= N; ++i) h[i] = (int)readLL();
    vector<long long> th(K);
    for (int k = 0; k < K; ++k) th[k] = readLL();

    // nxt[i]: az i-től jobbra első, nála nem alacsonyabb épület indexe (vagy N+1)
    vector<int> nxt(N + 2, N + 1);
    {
        vector<int> st;
        st.reserve(N);
        for (int i = N; i >= 1; --i) {
            while (!st.empty() && h[st.back()] < h[i]) st.pop_back();
            nxt[i] = st.empty() ? N + 1 : st.back();
            st.push_back(i);
        }
    }

    // épületek magasság szerint rendezve (magasság << 20 | index)
    vector<long long> bkey(N);
    for (int i = 1; i <= N; ++i) bkey[i - 1] = ((long long)h[i] << 20) | i;
    sort(bkey.begin(), bkey.end());

    // a lekérdezések magasság szerint rendezve (magasság << 17 | sorszám)
    vector<long long> qkey(K);
    for (int k = 0; k < K; ++k) qkey[k] = (th[k] << 17) | k;
    sort(qkey.begin(), qkey.end());

    SZ = 1;
    while (SZ < N + 1) SZ <<= 1;
    nd.assign(2 * SZ, Node{0, 0});

    vector<int> ans(K, 0);
    size_t p = 0;
    for (int k = 0; k < K; ++k) {
        long long H = qkey[k] >> 17;
        int qi = (int)(qkey[k] & ((1 << 17) - 1));
        while (p < (size_t)N && (bkey[p] >> 20) < H) {
            int i = (int)(bkey[p] & ((1 << 20) - 1));
            rangeInc(i, nxt[i] - 1);
            ++p;
        }
        ans[qi] = nd[1].t;
    }

    string out;
    out.reserve((size_t)K * 8);
    for (int k = 0; k < K; ++k) {
        if (k) out.push_back(' ');
        out += to_string(ans[k]);
    }
    out.push_back('\n');
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
