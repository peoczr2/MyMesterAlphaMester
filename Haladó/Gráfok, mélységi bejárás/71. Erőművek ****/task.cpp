/*
Megoldás lényege: két vezeték lebontása után pontosan három összefüggő rész kell legyen, ezért csak két híd jöhet szóba.
A hidakat mélységi bejárással keressük, a nem híd élek mentén összevont csúcsokból fát kapunk, ahol a csúcs súlya a benne lévő városok áramigényének összege.
Két hidat törölve három rész keletkezik: vagy az egyik híd a másik alatt van (egymásba ágyazott eset), vagy a két híd független (diszjunkt eset).
Rögzített híd esetén a kiegyensúlyozottság csak attól függ, mennyire van a másik híd oldalának súlya a fél összeghez közel, ezért a legjobb társ mindig ez a legközelebbi érték.
Ezt a legközelebbi értéket, és az adott intervallumba eső értékek számát merge sort fával kérdezzük le, először a minimumot, majd a darabszámot.
Az időigény O(N + M + B log^2 B), ahol B a hidak száma.
*/
/*
Hint 1: || Két lebontott vezeték után pontosan három összefüggő rész kell legyen, ezért mindkét lebontott vezetéknek hídnak kell lennie. A hidakat mélységi bejárással (low-link) találhatod meg. ||
Hint 2: || Ha a nem híd éleket mentén összevonod a csúcsokat, egy fát kapsz. Egy csúcs súlya a benne lévő városok áramigényének összege, egy híd egyik oldalának súlya pedig a mögötte lévő részfa összege. ||
Hint 3: || Két híd törlésekor a három rész vagy egymásba ágyazott részfákból, vagy két független részfából és a maradékból áll. Rögzített híd esetén a másik híd részfa-összegének a feléhez legközelebb álló érték adja a legjobb egyensúlyt. ||
Hint 4: || A hidakat Euler-bejárás (tin/tout) sorrendjében tárold, és merge sort fát építs rájuk. A beágyazott esethez egy tartomány, a diszjunkt esethez két tartomány kell, a legközelebbi érték és a darabszám is ilyen lekérdezéssel számolható. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Összefésülő fa: a 2^k hosszú, egymás utáni blokkokban rendezett listák.
// Tartományra a legközelebbi értéket és az intervallumba eső értékek számát O(log^2 n) alatt adja.
struct MergeSortTree {
    int n = 0;
    vector<vector<ll>> lv;

    void build(const vector<ll>& a) {
        n = (int)a.size();
        lv.assign(1, a);
        for (int k = 1; (1 << k) <= n; ++k) {
            int len = 1 << k, half = len >> 1;
            vector<ll> cur(n);
            const vector<ll>& prev = lv[k - 1];
            for (int s = 0; s + len <= n; s += len)
                merge(prev.begin() + s, prev.begin() + s + half,
                      prev.begin() + s + half, prev.begin() + s + len,
                      cur.begin() + s);
            lv.push_back(move(cur));
        }
    }

    // A [l, r) tartományban max min(x, D - x); -1, ha a tartomány üres.
    ll bestHalf(int l, int r, ll D) const {
        ll key = (D + 1) / 2, best = -1;
        for (int k = 0; l < r; ++k, l >>= 1, r >>= 1) {
            if (l & 1) { probe(k, l << k, key, D, best); ++l; }
            if (r & 1) { --r; probe(k, r << k, key, D, best); }
        }
        return best;
    }

    // A [l, r) tartományban hány x esik a [lo, hi] intervallumba.
    ll countIn(int l, int r, ll lo, ll hi) const {
        if (lo > hi) return 0;
        ll res = 0;
        for (int k = 0; l < r; ++k, l >>= 1, r >>= 1) {
            if (l & 1) { res += cntBlock(k, l << k, lo, hi); ++l; }
            if (r & 1) { --r; res += cntBlock(k, r << k, lo, hi); }
        }
        return res;
    }

private:
    void probe(int k, int s, ll key, ll D, ll& best) const {
        const vector<ll>& arr = lv[k];
        auto b = arr.begin() + s, e = b + (1 << k);
        auto it = lower_bound(b, e, key);
        if (it != e) best = max(best, min(*it, D - *it));
        if (it != b) best = max(best, min(*(it - 1), D - *(it - 1)));
    }

    ll cntBlock(int k, int s, ll lo, ll hi) const {
        const vector<ll>& arr = lv[k];
        auto b = arr.begin() + s, e = b + (1 << k);
        return upper_bound(b, e, hi) - lower_bound(b, e, lo);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<ll> a(N + 1);
    ll S = 0;
    for (int i = 1; i <= N; ++i) {
        cin >> a[i];
        S += a[i];
    }
    vector<int> eu(M), ev(M);
    vector<vector<pair<int, int>>> g(N + 1);  // (szomszéd, élazonosító)
    for (int i = 0; i < M; ++i) {
        cin >> eu[i] >> ev[i];
        g[eu[i]].push_back({ev[i], i});
        g[ev[i]].push_back({eu[i], i});
    }

    // 1. Hidak keresése (iteratív mélységi bejárás, low-link, élazonosítóval)
    vector<int> tin(N + 1, 0), low(N + 1, 0), pe(N + 1, -1), it(N + 1, 0);
    vector<char> isBridge(M, 0);
    int timer = 0;
    for (int s = 1; s <= N; ++s) {
        if (tin[s]) continue;
        vector<int> st = {s};
        tin[s] = low[s] = ++timer;
        while (!st.empty()) {
            int u = st.back();
            if (it[u] < (int)g[u].size()) {
                auto [v, id] = g[u][it[u]++];
                if (id == pe[u]) continue;
                if (tin[v]) {
                    low[u] = min(low[u], tin[v]);
                } else {
                    tin[v] = low[v] = ++timer;
                    pe[v] = id;
                    st.push_back(v);
                }
            } else {
                st.pop_back();
                if (pe[u] != -1) {
                    int id = pe[u];
                    int p = (eu[id] == u) ? ev[id] : eu[id];
                    low[p] = min(low[p], low[u]);
                    if (low[u] > tin[p]) isBridge[id] = 1;
                }
            }
        }
    }

    // 2. Kétszeresen összefüggő komponensek és súlyaik
    vector<int> comp(N + 1, -1);
    int K = 0;
    for (int s = 1; s <= N; ++s) {
        if (comp[s] != -1) continue;
        vector<int> st = {s};
        comp[s] = K;
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            for (auto [v, id] : g[u]) {
                if (isBridge[id] || comp[v] != -1) continue;
                comp[v] = K;
                st.push_back(v);
            }
        }
        ++K;
    }
    vector<ll> wc(K, 0);
    for (int v = 1; v <= N; ++v) wc[comp[v]] += a[v];

    // 3. Hídfa: csúcsok a komponensek, élek a hidak
    vector<vector<pair<int, int>>> tg(K);
    vector<int> bridges;
    for (int i = 0; i < M; ++i) {
        if (!isBridge[i]) continue;
        bridges.push_back(i);
        int cu = comp[eu[i]], cv = comp[ev[i]];
        tg[cu].push_back({cv, i});
        tg[cv].push_back({cu, i});
    }
    int B = (int)bridges.size();
    if (B < 2) {
        cout << -1 << "\n";
        return 0;
    }

    // Gyökérből bejárás: preorder, részfa-összegek, Euler-intervallumok
    vector<int> par(K, -1), parBridge(K, -1), pre;
    pre.reserve(K);
    vector<char> seen(K, 0);
    {
        vector<int> st = {0};
        seen[0] = 1;
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            pre.push_back(u);
            for (auto [v, id] : tg[u]) {
                if (seen[v]) continue;
                seen[v] = 1;
                par[v] = u;
                parBridge[v] = id;
                st.push_back(v);
            }
        }
    }
    vector<int> ttin(K), tsz(K, 1);
    vector<ll> W(K, 0);
    for (int i = 0; i < K; ++i) ttin[pre[i]] = i;
    for (int i = K - 1; i >= 0; --i) {
        int u = pre[i];
        W[u] += wc[u];
        if (par[u] != -1) {
            W[par[u]] += W[u];
            tsz[par[u]] += tsz[u];
        }
    }

    // Minden híd: a gyerek csúcsának részfa-összege és Euler-intervalluma
    vector<ll> ex(B);
    vector<int> eti(B), eto(B);
    for (int k = 0; k < B; ++k) {
        int id = bridges[k];
        int cu = comp[eu[id]], cv = comp[ev[id]];
        int c = (parBridge[cu] == id) ? cu : cv;
        ex[k] = W[c];
        eti[k] = ttin[c];
        eto[k] = ttin[c] + tsz[c] - 1;
    }

    // Tin szerinti sorrend (beágyazott tartomány és "jobbra" tartomány)
    vector<int> ord1(B);
    iota(ord1.begin(), ord1.end(), 0);
    sort(ord1.begin(), ord1.end(), [&](int x, int y) { return eti[x] < eti[y]; });
    vector<int> pos1(B), T1(B);
    vector<ll> X1(B);
    for (int i = 0; i < B; ++i) {
        pos1[ord1[i]] = i;
        T1[i] = eti[ord1[i]];
        X1[i] = ex[ord1[i]];
    }

    // Tout szerinti sorrend ("balra" tartomány: a már lezárult részfák)
    vector<int> ord2(B);
    iota(ord2.begin(), ord2.end(), 0);
    sort(ord2.begin(), ord2.end(), [&](int x, int y) { return eto[x] < eto[y]; });
    vector<int> T2(B);
    vector<ll> X2(B);
    for (int i = 0; i < B; ++i) {
        T2[i] = eto[ord2[i]];
        X2[i] = ex[ord2[i]];
    }

    MergeSortTree t1, t2;
    t1.build(X1);
    t2.build(X2);

    // R_e: az e utáni (tin szerint) edge-ek kezdete; K_e: az e előtt lezárult részfák száma
    vector<int> Rr(B), Kk(B);
    for (int e = 0; e < B; ++e) {
        Rr[e] = (int)(upper_bound(T1.begin(), T1.end(), eto[e]) - T1.begin());
        Kk[e] = (int)(lower_bound(T2.begin(), T2.end(), eti[e]) - T2.begin());
    }

    // h(q; D, c): három rész {q, D - q, c} legnagyobb és legkisebb értékének különbsége, q <= D/2.
    // q-ban nemnövekvő, ezért mindig a legnagyobb q a legjobb.
    auto hval = [](ll q, ll D, ll c) { return max(D - q, c) - min(q, c); };

    // 1. menet: a minimális kiegyensúlyozottság
    const ll NONE = LLONG_MAX;
    ll G = NONE;
    for (int e = 0; e < B; ++e) {
        ll xe = ex[e], rest = S - xe;
        int p = pos1[e], R = Rr[e], Ke = Kk[e];
        // beágyazott: f az e alatt van, a három rész {q, xe - q, S - xe}
        ll q = t1.bestHalf(p + 1, R, xe);
        if (q >= 0) G = min(G, hval(q, xe, rest));
        // diszjunkt: f nem e alatt és nem e felett van, a három rész {xe, q, rest - q}
        ll qd = max(t1.bestHalf(R, B, rest), t2.bestHalf(0, Ke, rest));
        if (qd >= 0) G = min(G, hval(qd, rest, xe));
    }

    // 2. menet: hány pár éri el G-t
    auto minQ = [&](ll D, ll c) -> ll {  // legkisebb q in [0, D/2], amire hval <= G; -1 ha nincs
        ll hi = D / 2;
        if (hval(hi, D, c) > G) return -1;
        ll lo = 0;
        while (lo < hi) {
            ll mid = lo + (hi - lo) / 2;
            if (hval(mid, D, c) <= G) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    };
    ll cntNest = 0, cntDisTwice = 0;
    for (int e = 0; e < B; ++e) {
        ll xe = ex[e], rest = S - xe;
        int p = pos1[e], R = Rr[e], Ke = Kk[e];
        ll qs = minQ(xe, rest);
        if (qs >= 0) cntNest += t1.countIn(p + 1, R, qs, xe - qs);
        ll qd = minQ(rest, xe);
        if (qd >= 0) cntDisTwice += t1.countIn(R, B, qd, rest - qd) + t2.countIn(0, Ke, qd, rest - qd);
    }
    // a diszjunkt párokat mindkét hídnál megszámoltuk
    ll total = cntNest + cntDisTwice / 2;

    cout << G << "\n" << total << "\n";
    return 0;
}
