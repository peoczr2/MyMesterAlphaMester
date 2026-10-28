/*
Megoldás lényege:
A bolygók és a dimenziókapuk együtt egy fát adnak (D+1 másolat, minden szomszédos réteg között pontosan egy kapu),
a játék pedig Undirected Vertex Geography: Ágnes akkor nyer, ha a kezdőcsúcs (P_1^0) minden maximális párosításban
benne van. Egy gyökerezett fában egy csúcs "szabad" (0), ha nincs olyan gyereke, amely szabad; különben "fedett" (1).
Ez mohó, alulról felfelé számítható, és a gyökér fedettsége adja a döntést. A rétegek kapuinak N^2 választása
egy 2x2-es átmeneti mátrixot ad, amelyet D-1-edik hatványra emelünk (D <= 10^18). A mátrix elemei a fa három
számából adódnak: hány csúcs fedett, és hány (csúcs, kiegészítő csúcs) pár tesz egy csúcsot fedetté. Ezeket
rerootolással, O(N)-ben számoljuk ki.
*/
/*
Hint 1: || Ágnes akkor nyer, ha P_1^0 minden maximális párosításban benne van. A fára ezt a levelektől felfelé haladó mohó párosítással döntheted el: egy csúcs akkor fedett, ha van szabad gyereke. ||
Hint 2: || Egy réteg átmenete csak két számot viszi tovább: mennyi csúcs fedett a rétegben, és hány (belépő csúcs, kapu-csúcs) pár tesz a belépő csúcsot fedetté, ha a kapu másik oldalán szabad gyerek van. Ebből 2x2-es mátrix lesz, amit D-1-edik hatványra kell emelni. ||
Hint 3: || A fenti számokat minden csúcsra és minden élre rerootolással kapod meg: egy részfa szabad gyerekeinek száma és mérete elég ahhoz, hogy a részfa minden csúcsának állapotát és a „kapu nélküli” eseteket összesítsd. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const ll MOD = 1000000007LL;

struct Val {
    int typ;   // 0: szabad, 1: fedett
    int sz;    // részfa mérete
    int L;     // #{a a részfában, a != gyökér: a gyökér nem fedett (a nélkül)}
    int K;     // #{a a részfában, a != gyökér: a gyökér fedett (a nélkül)}
};

static vector<int> off, nbr, rev_, par;
static vector<Val> down_, up_;

// A q csúcs p-edik szomszédjának értéke: val(q -> w), w részfája q felől nézve.
static inline const Val &valAt(int q, int p) {
    int w = nbr[p];
    if (w == par[q]) return up_[q];
    return down_[w];
}

// Összevonás: f szabad gyerek, S méretösszeg, Lsum az L-ek összege, cfv az egyetlen szabad gyerek (ha f == 1).
static Val combine(ll f, ll S, ll Lsum, const Val *cfv) {
    Val r;
    ll K;
    if (f >= 2) K = S;
    else if (f == 1) K = (S - cfv->sz) + cfv->L;
    else K = Lsum;
    r.typ = (f >= 1) ? 1 : 0;
    r.sz = (int)(S + 1);
    r.K = (int)K;
    r.L = (int)(S - K);
    return r;
}

typedef array<ll, 4> Mat;

static ll mulmod(ll a, ll b) { return (ll)((__int128)a * b % MOD); }

static Mat matmul(const Mat &A, const Mat &B) {
    Mat R;
    R[0] = (mulmod(A[0], B[0]) + mulmod(A[1], B[2])) % MOD;
    R[1] = (mulmod(A[0], B[1]) + mulmod(A[1], B[3])) % MOD;
    R[2] = (mulmod(A[2], B[0]) + mulmod(A[3], B[2])) % MOD;
    R[3] = (mulmod(A[2], B[1]) + mulmod(A[3], B[3])) % MOD;
    return R;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ull D;
    cin >> n >> D;
    int m = n - 1;
    vector<int> eu(m), ev(m);
    vector<int> deg(n, 0);
    for (int i = 0; i < m; i++) {
        cin >> eu[i] >> ev[i];
        eu[i]--; ev[i]--;
        deg[eu[i]]++; deg[ev[i]]++;
    }
    off.assign(n + 1, 0);
    for (int v = 0; v < n; v++) off[v + 1] = off[v] + deg[v];
    nbr.assign(2 * m, 0);
    rev_.assign(2 * m, 0);
    {
        vector<int> fill(off.begin(), off.end() - 1);
        for (int i = 0; i < m; i++) {
            int pu = fill[eu[i]]++;
            int pv = fill[ev[i]]++;
            nbr[pu] = ev[i];
            nbr[pv] = eu[i];
            rev_[pu] = pv;
            rev_[pv] = pu;
        }
    }

    // BFS a 0. csúcsból
    par.assign(n, -1);
    vector<int> order;
    order.reserve(n);
    vector<char> vis(n, 0);
    order.push_back(0);
    vis[0] = 1;
    for (size_t h = 0; h < order.size(); h++) {
        int v = order[h];
        for (int p = off[v]; p < off[v + 1]; p++) {
            int u = nbr[p];
            if (!vis[u]) {
                vis[u] = 1;
                par[u] = v;
                order.push_back(u);
            }
        }
    }

    down_.assign(n, Val{0, 0, 0, 0});
    up_.assign(n, Val{0, 0, 0, 0});

    // Alulról felfelé: down_[p] = val(par(p) -> p)
    for (int h = n - 1; h >= 1; h--) {
        int p = order[h];
        ll f = 0, S = 0, Lsum = 0;
        int cf = -1;
        for (int q = off[p]; q < off[p + 1]; q++) {
            int u = nbr[q];
            if (u == par[p]) continue;
            const Val &c = down_[u];
            if (c.typ == 0) { f++; cf = u; }
            S += c.sz;
            Lsum += c.L;
        }
        Val cfv{0, 0, 0, 0};
        if (f == 1) cfv = down_[cf];
        down_[p] = combine(f, S, Lsum, &cfv);
    }

    // Felülről lefelé: up_[c] = val(c -> par(c)) minden c gyermekre.
    for (int h = 0; h < n; h++) {
        int q = order[h];
        ll Ftot = 0, Stot = 0, Ltot = 0;
        int fa = -1, fb = -1;  // legfeljebb két szabad szomszéd pozíciója a nbr tömbben
        for (int p = off[q]; p < off[q + 1]; p++) {
            const Val &v = valAt(q, p);
            if (v.typ == 0) {
                Ftot++;
                if (fa < 0) fa = p;
                else if (fb < 0) fb = p;
            }
            Stot += v.sz;
            Ltot += v.L;
        }
        for (int p = off[q]; p < off[q + 1]; p++) {
            int c = nbr[p];
            if (c == par[q]) continue;
            const Val &vc = down_[c];
            ll f = Ftot - (vc.typ == 0 ? 1 : 0);
            ll S = Stot - vc.sz;
            ll Lsum = Ltot - vc.L;
            Val cfv{0, 0, 0, 0};
            if (f == 1) {
                // az egyetlen szabad szomszéd, amely nem c (f == 1 esetén a két tárolt pozíció egyike ilyen)
                int pick = (fa >= 0 && fa != p) ? fa : fb;
                cfv = valAt(q, pick);
            }
            up_[c] = combine(f, S, Lsum, &cfv);
        }
    }

    // Gpos[p] = G(v -> y), ahol y = a p pozíció tulajdonosa, v = nbr[p]
    vector<int> Gpos(2 * m, 0);
    for (int y = 0; y < n; y++) {
        ll Htot = 0;
        int xc = 0, f0 = -1, f1 = -1;
        for (int p = off[y]; p < off[y + 1]; p++) {
            const Val &v = valAt(y, p);
            Htot += 1 + v.K;
            if (v.typ == 0) {
                xc++;
                if (f0 < 0) f0 = p;
                else if (f1 < 0) f1 = p;
            }
        }
        for (int p = off[y]; p < off[y + 1]; p++) {
            ll Hp = 1 + valAt(y, p).K;
            ll g;
            if (xc >= 3) g = 0;
            else if (xc == 2) {
                if (p == f0) g = 1 + valAt(y, f1).K;
                else if (p == f1) g = 1 + valAt(y, f0).K;
                else g = 0;
            } else if (xc == 1) {
                if (p == f0) g = Htot - Hp;
                else g = 1 + valAt(y, f0).K;
            } else {
                g = Htot - Hp;
            }
            Gpos[p] = (int)g;
        }
    }

    // cnt(v) = #{a != v : v fedett T - a-ban}
    ll N = n;
    ll sumCnt = 0;
    ll cntRoot = 0;
    ll c = 0;   // |Cov(T)|
    ll c1 = 0;  // [1. csúcs (0) fedett T-ben]
    for (int v = 0; v < n; v++) {
        int xc = 0, xp = -1;
        for (int p = off[v]; p < off[v + 1]; p++) {
            if (valAt(v, p).typ == 0) { xc++; xp = p; }
        }
        if (xc >= 1) c++;
        ll cnt = 0;
        if (xc >= 2) {
            cnt = N - 1;
        } else if (xc == 1) {
            ll sz = valAt(v, xp).sz;
            ll G = Gpos[rev_[xp]];
            cnt = (N - 1 - sz) + G;
        } else {
            for (int p = off[v]; p < off[v + 1]; p++) cnt += Gpos[rev_[p]];
        }
        sumCnt += cnt;
        if (v == 0) {
            cntRoot = cnt;
            c1 = (xc >= 1) ? 1 : 0;
        }
    }

    ll Ktot = N + sumCnt;       // Σ_a |Cov(T + ℓ_a) ∩ V|
    ll P = 1 + cntRoot;         // #{a : 1 ∈ Cov(T + ℓ_a)}

    // Átmeneti mátrix: sor y (a belső csúcs típusa), oszlop z (a kiegészítő gyerek típusa)
    Mat base = {
        ((N * N - Ktot) % MOD + MOD) % MOD,
        (N * (N - c)) % MOD,
        Ktot % MOD,
        (N * c) % MOD
    };
    Mat res = {1, 0, 0, 1};
    ull e = D - 1;
    while (e > 0) {
        if (e & 1ULL) res = matmul(res, base);
        base = matmul(base, base);
        e >>= 1;
    }
    // W_D = (N - c, c), W_1 = res * W_D
    ll wd0 = (N - c) % MOD, wd1 = c % MOD;
    ll w10 = (mulmod(res[0], wd0) + mulmod(res[1], wd1)) % MOD;
    ll w11 = (mulmod(res[2], wd0) + mulmod(res[3], wd1)) % MOD;

    ll ans = (mulmod(N % MOD, mulmod(c1, w11)) + mulmod(P % MOD, w10)) % MOD;
    cout << ans << "\n";
    return 0;
}
