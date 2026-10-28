/*
Megoldás lényege:
Két vezeték törlése pontosan akkor ad három összefüggő részt (három erőművet), ha mindkét törölt vezeték híd. A hidakat a DFS-fa élei közül a low-érték dönti el, és egy híd alatti rész a DFS-fa részfája. Két híd esetén a három rész összege a két részfa összegéből és a teljes összegből adódik, attól függően, hogy a két híd egymás alatt van-e. Egy rögzített részhez tartozó kiegyensúlyozottsági érték a másik két rész összegének felétől való eltéréssel szigorúan nő, ezért minden hídhoz elég a legközelebbi megengedett párt megkeresni. A megengedett hidak halmazát a DFS-sorrend intervallumai adják, a tartományokon végzett érték szerinti rang- és k-adik-elem lekérdezéseket hullámmátrix (bitenként felbontott sorozat) támogatja, így minden lekérdezés logaritmikus. Az értéket a minimumot adó párok darabszámából adjuk meg, a nem egymás alatti párokat mindkét végükről kétszer számoljuk. Az összidő O(N log N).
*/
/*
Hint 1: || Két vezetéket törölve pontosan akkor lesz három összefüggő rész, ha mindkét törölt vezeték híd. A hidakat a DFS-fa élei közül a low-értékek alapján lehet kiválasztani. ||
Hint 2: || Egy híd egyik oldala a DFS-fa részfája. Két híd esetén a három rész összege a két részfa összegéből és a teljes összegből adódik, attól függően, hogy az egyik híd a másik alatt van-e. ||
Hint 3: || Egy rögzített híd mellett a másik híd akkor ad jó kiegyensúlyozást, ha a részfa összege a rögzített részhez és a teljes összeg felének különbségéhez közel van. A legközelebbi elemet érték szerinti bináris bontású szerkezettel (hullámmátrixszal) érdemes keresni. ||
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
    if (c == '-') { neg = true; c = gc(); }
    long long x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return neg ? -x : x;
}

const long long INF = LLONG_MAX / 4;

static vector<long long> Wv;   // a 2 * részösszegek rendezett, egyedi értékei
static int MV = 0;             // Wv mérete

// Hullámmátrix: egy egész sorozat bitenkénti felbontása, tartományokra (l, r) rang- és k-adik lekérdezés
struct WaveBlock {
    unsigned long long b;   // 64 bit a szintben
    int pre;                // az előző blokkok egyeseinek száma
};

struct WaveMatrix {
    int n = 0, L = 1, words = 0;
    vector<WaveBlock> blk;  // blk[lev * words + i]
    vector<int> Z;

    void build(const vector<int> &seq, int sigma) {
        n = (int)seq.size();
        L = 1;
        while ((1LL << L) <= sigma) L++;
        words = n / 64 + 2;
        blk.assign((size_t)L * words, WaveBlock{0ULL, 0});
        Z.assign(L, 0);
        vector<int> cur = seq, nxt(n);
        for (int lev = L - 1; lev >= 0; lev--) {
            WaveBlock *B = &blk[(size_t)lev * words];
            int zc = 0;
            for (int i = 0; i < n; i++) {
                if ((cur[i] >> lev) & 1) B[i >> 6].b |= 1ULL << (i & 63);
                else zc++;
            }
            int acc = 0;
            for (int w = 0; w < words; w++) {
                B[w].pre = acc;
                acc += __builtin_popcountll(B[w].b);
            }
            Z[lev] = zc;
            int zi = 0, oi = zc;
            for (int i = 0; i < n; i++) {
                if ((cur[i] >> lev) & 1) nxt[oi++] = cur[i];
                else nxt[zi++] = cur[i];
            }
            swap(cur, nxt);
        }
    }

    inline int rank1(int lev, int pos) const {
        const WaveBlock &B = blk[(size_t)lev * words + (pos >> 6)];
        return B.pre + __builtin_popcountll(B.b & ((1ULL << (pos & 63)) - 1));
    }

    // a [l, r) tartományban az x-nél kisebb értékek száma
    int countLess(int l, int r, int x) const {
        int res = 0;
        for (int lev = L - 1; lev >= 0; lev--) {
            int l1 = rank1(lev, l), r1 = rank1(lev, r);
            int l0 = l - l1, r0 = r - r1;
            if ((x >> lev) & 1) {
                res += r0 - l0;
                l = Z[lev] + l1;
                r = Z[lev] + r1;
            } else {
                l = l0;
                r = r0;
            }
        }
        return res;
    }

    // a [l, r) tartomány k-adik (0-alapú) legkisebb értéke
    int kth(int l, int r, int k) const {
        int res = 0;
        for (int lev = L - 1; lev >= 0; lev--) {
            int l1 = rank1(lev, l), r1 = rank1(lev, r);
            int l0 = l - l1, r0 = r - r1;
            int zeros = r0 - l0;
            if (k < zeros) {
                l = l0;
                r = r0;
            } else {
                k -= zeros;
                res |= 1 << lev;
                l = Z[lev] + l1;
                r = Z[lev] + r1;
            }
        }
        return res;
    }

    // a [l, r) tartomány ka-adik és kb-edik (0-alapú) legkisebb értéke egy bejárásban;
    // ha a két keresési út egybeesik, a rangokat közösen használja
    void kth2(int l, int r, int ka, int kb, int &va, int &vb) const {
        int resA = 0, resB = 0;
        int la = l, ra = r, lq = l, rq = r;
        for (int lev = L - 1; lev >= 0; lev--) {
            int la1 = rank1(lev, la), ra1 = rank1(lev, ra);
            int lq1, rq1;
            if (lq == la && rq == ra) { lq1 = la1; rq1 = ra1; }
            else { lq1 = rank1(lev, lq); rq1 = rank1(lev, rq); }
            int zerosA = (ra - ra1) - (la - la1);
            int zerosB = (rq - rq1) - (lq - lq1);
            if (ka < zerosA) {
                la = la - la1;
                ra = ra - ra1;
            } else {
                ka -= zerosA;
                resA |= 1 << lev;
                la = Z[lev] + la1;
                ra = Z[lev] + ra1;
            }
            if (kb < zerosB) {
                lq = lq - lq1;
                rq = rq - rq1;
            } else {
                kb -= zerosB;
                resB |= 1 << lev;
                lq = Z[lev] + lq1;
                rq = Z[lev] + rq1;
            }
        }
        va = resA;
        vb = resB;
    }
};

// a [l, r) tartomány értékei közül P-hez legközelebbi; bestW / bestD frissül, ha jobb
// lb: Wv-ben P első előfordulása (>= P), eq: P megtalálható-e Wv-ben
static void nearest(const WaveMatrix &wm, int l, int r, long long P, int lb, bool eq,
                    long long &bestW, long long &bestD) {
    int total = r - l;
    if (total <= 0) return;
    int cb = wm.countLess(l, r, lb);                  // értékek < P
    int cl = eq ? wm.countLess(l, r, lb + 1) : cb;    // értékek <= P
    int pr = cl > 0 ? cl - 1 : -1;                    // legnagyobb érték <= P rangja
    int sr = cb < total ? cb : -1;                    // legkisebb érték >= P rangja
    int vp = -1, vs = -1;
    if (pr >= 0 && sr >= 0) wm.kth2(l, r, pr, sr, vp, vs);
    else if (pr >= 0) vp = wm.kth(l, r, pr);
    else if (sr >= 0) vs = wm.kth(l, r, sr);
    if (vp >= 0) {
        long long d = P - Wv[vp];
        if (d < bestD) { bestD = d; bestW = Wv[vp]; }
    }
    if (vs >= 0) {
        long long d = Wv[vs] - P;
        if (d < bestD) { bestD = d; bestW = Wv[vs]; }
    }
}

// hány eleme van a [l, r) tartománynak pontosan w értékkel
static long long exactCount(const WaveMatrix &wm, int l, int r, long long w) {
    int id = (int)(lower_bound(Wv.begin(), Wv.end(), w) - Wv.begin());
    if (id >= MV || Wv[id] != w) return 0;
    return (long long)wm.countLess(l, r, id + 1) - wm.countLess(l, r, id);
}

int main() {
    int n = (int)readLL();
    int m = (int)readLL();
    vector<long long> a(n + 1, 0);
    for (int i = 1; i <= n; i++) a[i] = readLL();
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int e = 0; e < m; e++) {
        int u = (int)readLL(), v = (int)readLL();
        adj[u].push_back({v, e});
        adj[v].push_back({u, e});
    }

    // iteratív DFS az 1. városból
    vector<int> tin(n + 1, -1), tout(n + 1, -1), low(n + 1, 0), par(n + 1, 0), parE(n + 1, -1), it(n + 1, 0);
    vector<int> order;
    order.reserve(n);
    int timer = 0;
    vector<int> st;
    st.push_back(1);
    tin[1] = low[1] = timer++;
    order.push_back(1);
    while (!st.empty()) {
        int v = st.back();
        if (it[v] < (int)adj[v].size()) {
            int to = adj[v][it[v]].first, id = adj[v][it[v]].second;
            it[v]++;
            if (id == parE[v]) continue;
            if (tin[to] == -1) {
                tin[to] = low[to] = timer++;
                par[to] = v;
                parE[to] = id;
                order.push_back(to);
                st.push_back(to);
            } else {
                low[v] = min(low[v], tin[to]);
            }
        } else {
            st.pop_back();
            tout[v] = timer - 1;
            if (v != 1) low[par[v]] = min(low[par[v]], low[v]);
        }
    }

    // részfa-összegek
    vector<long long> sub(n + 1, 0);
    for (int v : order) sub[v] = a[v];
    for (int i = (int)order.size() - 1; i >= 1; i--) sub[par[order[i]]] += sub[order[i]];
    long long T = sub[1];

    // hidak: a DFS-fa azon élei, amelyekre low[c] > tin[szülő]; a c-hez tartozó részfa a híd egyik oldala
    vector<int> ord;
    for (int v : order) if (v != 1 && low[v] > tin[par[v]]) ord.push_back(v);
    int k = (int)ord.size();
    if (k < 2) { printf("-1\n"); return 0; }

    // cntTin[t]: a t-nél nem nagyobb tin-ű hidak száma (a részfa végének határa)
    // cntTout[t]: a t-nél kisebb tout-ú hidak száma (nem ős, már lezárult hidak)
    vector<int> cntTin(n + 1, 0), cntTout(n + 1, 0);
    for (int j = 0; j < k; j++) {
        cntTin[tin[ord[j]]]++;
        cntTout[tout[ord[j]] + 1]++;
    }
    for (int t = 1; t <= n; t++) {
        cntTin[t] += cntTin[t - 1];
        cntTout[t] += cntTout[t - 1];
    }
    vector<int> byT(k);
    iota(byT.begin(), byT.end(), 0);
    sort(byT.begin(), byT.end(), [&](int x, int y) { return tout[ord[x]] < tout[ord[y]]; });

    vector<long long> wRaw(k);
    for (int j = 0; j < k; j++) wRaw[j] = 2 * sub[ord[j]];
    Wv = wRaw;
    sort(Wv.begin(), Wv.end());
    Wv.erase(unique(Wv.begin(), Wv.end()), Wv.end());
    MV = (int)Wv.size();
    vector<int> cw(k);
    for (int j = 0; j < k; j++) cw[j] = (int)(lower_bound(Wv.begin(), Wv.end(), wRaw[j]) - Wv.begin());

    // wmTin: a hidak értékei tin szerint; wmTout: a hidak értékei tout szerint
    vector<int> seqTin(k), seqTout(k);
    for (int i = 0; i < k; i++) {
        seqTin[i] = cw[i];
        seqTout[i] = cw[byT[i]];
    }
    WaveMatrix wmTin, wmTout;
    wmTin.build(seqTin, MV);
    wmTout.build(seqTout, MV);

    vector<long long> valA(k, INF), valB(k, INF), dA(k, INF), dB(k, INF);
    vector<int> pos2v(k), c1v(k);
    for (int j = 0; j < k; j++) {
        int c = ord[j];
        long long x = sub[c];
        // a c alatti hidak tin-pozíciója: (j, pos2) ; a tin > tout_c hidak: [pos2, k)
        int pos2 = cntTin[tout[c]];
        // a tout < tin_c hidak (nem ős, már lezárult): tout-sorrend prefixe [0, c1)
        int c1 = cntTout[tin[c]];
        pos2v[j] = pos2;
        c1v[j] = c1;

        // A: nem egymás alatti pár, rögzített rész x, a másik kettő y és T-x-y
        {
            long long P = T - x, bw = 0, bd = INF;
            int lb = (int)(lower_bound(Wv.begin(), Wv.end(), P) - Wv.begin());
            bool eq = lb < MV && Wv[lb] == P;
            nearest(wmTout, 0, c1, P, lb, eq, bw, bd);
            nearest(wmTin, pos2, k, P, lb, eq, bw, bd);
            if (bd < INF) {
                long long y = bw / 2, z = T - x - y;
                valA[j] = max({x, y, z}) - min({x, y, z});
                dA[j] = bd;
            }
        }
        // B: a c alatti híd y, a rész x-y, a rész T-x
        {
            long long P = x, bw = 0, bd = INF;
            int lb = (int)(lower_bound(Wv.begin(), Wv.end(), P) - Wv.begin());
            bool eq = lb < MV && Wv[lb] == P;
            nearest(wmTin, j + 1, pos2, P, lb, eq, bw, bd);
            if (bd < INF) {
                long long y = bw / 2, z = x - y, w = T - x;
                valB[j] = max({y, z, w}) - min({y, z, w});
                dB[j] = bd;
            }
        }
    }

    long long D = INF;
    for (int j = 0; j < k; j++) D = min(D, min(valA[j], valB[j]));

    long long cntA = 0, cntB = 0;
    for (int j = 0; j < k; j++) {
        int c = ord[j];
        long long x = sub[c];
        long long P = T - x;
        if (valA[j] == D) {
            long long d = dA[j];
            int pos2 = pos2v[j], c1 = c1v[j];
            vector<long long> ws = {P - d};
            if (d > 0) ws.push_back(P + d);
            for (long long w : ws) {
                cntA += exactCount(wmTout, 0, c1, w) + exactCount(wmTin, pos2, k, w);
            }
        }
        if (valB[j] == D) {
            long long d = dB[j];
            int pos2 = pos2v[j];
            vector<long long> ws = {x - d};
            if (d > 0) ws.push_back(x + d);
            for (long long w : ws) {
                cntB += exactCount(wmTin, j + 1, pos2, w);
            }
        }
    }
    // a nem egymás alatti párokat mindkét végükről számoltuk
    long long total = cntA / 2 + cntB;
    printf("%lld\n%lld\n", D, total);
    return 0;
}
