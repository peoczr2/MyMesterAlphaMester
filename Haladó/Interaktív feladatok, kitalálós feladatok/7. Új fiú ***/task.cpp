/*
Megoldás lényege: az új fiú minden kérdésre 0-t kap, két azonos csoportbeli tanuló viszont 1-et; így aki kapott legalább egy 1-es választ, az biztosan nem az új fiú.
Tanulókat először párokba állítjuk (N/2 kérdés): az 1-es párok tagjai azonnal igazoltak lesznek.
A 0-s párok tagjai különböző csoportban vannak (kivéve az új fiút), ezért két 0-s párt négyesével összevetve 3 kérdéssel mind a négy tanuló igazolható.
A maradék tanulókat már igazolt tanulókkal hasonlítjuk össze; ha valakit két különböző csoportbeli igazolt tanulóval is 0 köt össze, ő az új fiú.
Kis N-re (N <= 14) minden lehetséges (új fiú, csoportfelosztás) hipotézist nyilván tartunk, és mindig olyan kérdést teszünk fel, amely a hipotéziseket a legjobban felezi.
A megoldás csak akkor közöl eredményt, ha az összes megmaradt hipotézis ugyanazt az új fiút adja, így a válasz bizonyíthatóan helyes; a kérdések száma a 3N/2 korláton belül marad.
*/
/*
Hint 1: || Az új fiú minden kérdésre 0-t kap, az 1-es válasz viszont mindkét tanulóról bizonyítja, hogy nem ő az. Keress olyan kérdéseket, amelyek 1-es választ adnak. ||
Hint 2: || Párosítsd a tanulókat (1-2, 3-4, ...). Az 1-es párokat azonnal elfogadhatod. Két 0-s párt együtt vizsgálj: ha egyik sem az új fiú, a párok tagjai ellentétes csoportban vannak, így egy 1-es kérdéssel a másik pár tagjai is igazolhatók. ||
Hint 3: || Ha egy tanulóra már igazolt tanulóktól két különböző csoportban is 0 jön, akkor ő az új fiú. ||
*/
#include "valasz.h"
#include <bits/stdc++.h>
using namespace std;

namespace {

int N;
vector<int> cnt, par;
vector<unsigned char> rel;
vector<char> cert;
vector<pair<int,int>> zeros;
unordered_map<long long,int> memo;
bool useMemo = false;

long long keyOf(int a, int b) {
    if (a > b) swap(a, b);
    return (long long)a * 2000003LL + b;
}

int ask(int a, int b) {
    long long k = 0;
    if (useMemo) {
        k = keyOf(a, b);
        auto it = memo.find(k);
        if (it != memo.end()) return it->second;
    }
    cnt[a]++;
    cnt[b]++;
    int r = Barat(a, b);
    if (useMemo) memo[k] = r;
    if (r == 0) zeros.push_back({a, b});
    return r;
}

int findRoot(int v, int &p) {
    int r = v, acc = 0;
    while (par[r] != r) { acc ^= rel[r]; r = par[r]; }
    int cur = v, cp = acc;
    while (par[cur] != cur) {
        int nxt = par[cur];
        int nrel = cp ^ rel[cur];
        par[cur] = r;
        rel[cur] = (unsigned char)cp;
        cur = nxt;
        cp = nrel;
    }
    p = acc;
    return r;
}

// parity(a) xor parity(b) == d
void unite(int a, int b, int d) {
    int pa, pb;
    int ra = findRoot(a, pa), rb = findRoot(b, pb);
    if (ra == rb) return;
    par[rb] = ra;
    rel[rb] = (unsigned char)(pa ^ pb ^ d);
}

int findBothRoot() {
    vector<int> mk(N + 1, 0);
    for (int v = 1; v <= N; ++v) if (cert[v]) { int p; int r = findRoot(v, p); mk[r] |= 1 << p; }
    for (int v = 1; v <= N; ++v) if (cert[v]) { int p; int r = findRoot(v, p); if (mk[r] == 3) return r; }
    return -1;
}

// Ha nincs bizonyitott ket, kulonbozo csoportu tanulo: letrehozzuk.
void establishHubs() {
    vector<int> S;
    for (int v = 1; v <= N; ++v) if (cert[v]) S.push_back(v);
    // F1: bizonyitott tanulok egymas utani parjai kulonbozo komponensekbol
    for (size_t i = 0; i + 1 < S.size(); ++i) {
        int a = S[i], b = S[i + 1], pa, pb;
        if (findRoot(a, pa) == findRoot(b, pb)) continue;
        int r = ask(a, b);
        unite(a, b, r == 1 ? 0 : 1);
        if (r == 0) return;
    }
    // F2: minden bizonyitott tanulo azonos csoport (L). A tobbi nem-uj-fiu a masik csoport (B).
    S.clear();
    vector<int> U;
    for (int v = 1; v <= N; ++v) (cert[v] ? S : U).push_back(v);
    if (S.empty()) {
        bool found = false;
        for (size_t i = 0; i < U.size() && !found; ++i)
            for (size_t j = i + 1; j < U.size() && !found; ++j)
                if (ask(U[i], U[j]) == 1) {
                    cert[U[i]] = cert[U[j]] = 1;
                    unite(U[i], U[j], 0);
                    S = {U[i], U[j]};
                    found = true;
                }
        if (!found) return;
        U.clear();
        for (int v = 1; v <= N; ++v) if (!cert[v]) U.push_back(v);
    }
    size_t sp = 0;  // a kovetkezo hasznalhato horgony
    auto anchor = [&]() -> int {
        while (sp < S.size() && cnt[S[sp]] >= 5) ++sp;
        return sp < S.size() ? S[sp] : -1;
    };
    vector<int> Bc;  // B-tagok es az uj fiu jelolt
    for (int u : U) {
        if (cert[u]) continue;
        int s = anchor();
        if (s < 0) return;
        if (ask(u, s) == 1) { cert[u] = 1; unite(u, s, 0); S.push_back(u); }
        else Bc.push_back(u);
    }
    if (Bc.size() < 2) return;
    int b1 = Bc[0], b2 = Bc[1];
    int s = anchor();
    if (s < 0) return;
    if (ask(b1, b2) == 1) {
        cert[b1] = cert[b2] = 1; unite(b1, b2, 0); unite(b1, s, 1);
        return;
    }
    if (Bc.size() >= 3) {
        int b3 = Bc[2];
        if (ask(b1, b3) == 1) {
            cert[b1] = cert[b3] = 1; unite(b1, b3, 0); unite(b1, s, 1);
            return;
        }
        // b1 nem lehet B-tag: b1 az uj fiu, b2 es b3 bizonyosan B
        if (ask(b2, b3) == 1) {
            cert[b2] = cert[b3] = 1; unite(b2, b3, 0); unite(b2, s, 1);
        }
    }
}

// Kis N (<=14): hipotezisteres mohó megoldo. Hipotezis = (uj fiu c, A csoport bitmaszk).
void solveSmall(int n) {
    struct H { int c; unsigned A; };
    vector<H> cur;
    for (int c = 1; c <= n; ++c) {
        vector<int> ov;
        for (int v = 1; v <= n; ++v) if (v != c) ov.push_back(v);
        int m1 = (int)ov.size();
        for (unsigned t = 0; t < (1u << (m1 - 1)); ++t) {
            unsigned m = (t << 1) | 1u;  // ov[0] mindig A: a csoportcsere-szimmetria miatt
            int a = __builtin_popcount(m);
            if (a < 2 || m1 - a < 2) continue;
            unsigned A = 0;
            for (int i = 0; i < m1; ++i) if (m >> i & 1) A |= 1u << (ov[i] - 1);
            cur.push_back({c, A});
        }
    }
    vector<int> cn(n + 1, 0);
    auto answer = [](const H &h, int x, int y) -> int {
        if (x == h.c || y == h.c) return 0;
        return ((h.A >> (x - 1)) & 1) == ((h.A >> (y - 1)) & 1);
    };
    for (;;) {
        bool uniq = true;
        for (const H &h : cur) if (h.c != cur[0].c) { uniq = false; break; }
        if (uniq) Megoldas(cur[0].c);
        int bx = -1, by = -1;
        for (int pass = 0; pass < 3 && bx < 0; ++pass) {
        const int lim = pass == 0 ? 4 : (pass == 1 ? 5 : 1000000);
        size_t best = (size_t)-1;
        int bdeg = 1 << 30;
        for (int x = 1; x <= n; ++x) for (int y = x + 1; y <= n; ++y) {
            if (cn[x] >= lim || cn[y] >= lim) continue;
            size_t n1 = 0;
            for (const H &h : cur) n1 += answer(h, x, y);
            size_t n0 = cur.size() - n1;
            if (n1 == 0 || n0 == 0) continue;
            size_t sc = max(n1, n0);
            int deg = cn[x] + cn[y];
            if (sc < best || (sc == best && deg < bdeg)) { best = sc; bdeg = deg; bx = x; by = y; }
        }
        }
        if (bx < 0) Megoldas(cur[0].c);
        int r = Barat(bx, by);
        cn[bx]++;
        cn[by]++;
        vector<H> nxt;
        nxt.reserve(cur.size());
        for (const H &h : cur) if (answer(h, bx, by) == r) nxt.push_back(h);
        cur.swap(nxt);
    }
}

// Maradek (bizonyitatlan) tanulok feloldasa. Hipotezis: melyik maradek az uj fiu,
// es a tobbi maradek melyik csoportba tartozik. Ismert csoportu horgonyokat hasznalunk.
// Csak akkor valaszolunk, ha az osszes megmarado hipotezis ugyanazt az uj fiut adja.
void resolveResidual(const vector<int> &R, const vector<int> &lab) {
    int m = (int)R.size();
    vector<int> idx(N + 1, -1);
    for (int i = 0; i < m; ++i) idx[R[i]] = i;
    struct Cons { int i, j, L; };  // j >= 0: R-R par; j < 0: R-horgony par, L a horgony csoportja
    vector<Cons> cons;
    for (auto &z : zeros) {
        int a = z.first, b = z.second;
        int ia = idx[a], ib = idx[b];
        if (ia >= 0 && ib >= 0) cons.push_back({ia, ib, -1});
        else if (ia >= 0 && lab[b] >= 0) cons.push_back({ia, -1, lab[b]});
        else if (ib >= 0 && lab[a] >= 0) cons.push_back({ib, -1, lab[a]});
    }
    struct Hy { int ci; unsigned mask; };
    auto lbl = [](const Hy &h, int i) -> int { return i == h.ci ? 2 : (int)((h.mask >> i) & 1u); };
    vector<Hy> alive;
    for (int ci = 0; ci < m; ++ci)
        for (unsigned mk = 0; mk < (1u << m); ++mk) {
            if ((mk >> ci) & 1u) continue;
            Hy h{ci, mk};
            bool ok = true;
            for (const Cons &c : cons) {
                int li = lbl(h, c.i);
                if (li == 2) continue;
                if (c.j >= 0) {
                    int lj = lbl(h, c.j);
                    if (lj != 2 && lj == li) { ok = false; break; }
                } else if (li == c.L) { ok = false; break; }
            }
            if (ok) alive.push_back(h);
        }
    for (;;) {
        int c0 = -1;
        bool uniq = true;
        for (const Hy &h : alive) {
            if (c0 < 0) c0 = h.ci;
            else if (h.ci != c0) { uniq = false; break; }
        }
        if (uniq && c0 >= 0) Megoldas(R[c0]);
        if (alive.empty()) Megoldas(R[0]);
        // Elso korben a 5-os korlatot betartjuk; ha nincs informativ kerdes, a korlat nelkul keresunk.
        int bestType = -1, bi = -1, bj = -1, bL = -1;
        int hub[2] = {-1, -1};
        for (int pass = 0; pass < 3 && bestType < 0; ++pass) {
            const int lim = pass == 0 ? 4 : (pass == 1 ? 5 : 1000000);
            hub[0] = hub[1] = -1;
            for (int v = 1; v <= N; ++v)
                if (cert[v] && lab[v] >= 0 && cnt[v] < lim && hub[lab[v]] < 0) hub[lab[v]] = v;
            size_t best = (size_t)-1;
            for (int i = 0; i < m; ++i) {
                if (cnt[R[i]] >= lim) continue;
                for (int L = 0; L < 2; ++L) {
                    if (hub[L] < 0) continue;
                    size_t n1 = 0;
                    for (const Hy &h : alive) {
                        int li = lbl(h, i);
                        if (li != 2 && li == L) ++n1;
                    }
                    size_t n0 = alive.size() - n1;
                    if (n1 == 0 || n0 == 0) continue;
                    size_t sc = max(n1, n0);
                    if (sc < best) { best = sc; bestType = 0; bi = i; bL = L; }
                }
            }
            for (int i = 0; i < m; ++i) {
                if (cnt[R[i]] >= lim) continue;
                for (int j = i + 1; j < m; ++j) {
                    if (cnt[R[j]] >= lim) continue;
                    size_t n1 = 0;
                    for (const Hy &h : alive) {
                        int li = lbl(h, i), lj = lbl(h, j);
                        if (li != 2 && lj != 2 && li == lj) ++n1;
                    }
                    size_t n0 = alive.size() - n1;
                    if (n1 == 0 || n0 == 0) continue;
                    size_t sc = max(n1, n0);
                    if (sc < best) { best = sc; bestType = 1; bi = i; bj = j; }
                }
            }
        }
        if (bestType < 0) Megoldas(R[alive[0].ci]);
        int r;
        vector<Hy> nxt;
        nxt.reserve(alive.size());
        if (bestType == 0) {
            r = Barat(R[bi], hub[bL]);
            cnt[R[bi]]++;
            cnt[hub[bL]]++;
            for (const Hy &h : alive) {
                int li = lbl(h, bi);
                int a = (li != 2 && li == bL) ? 1 : 0;
                if (a == r) nxt.push_back(h);
            }
        } else {
            r = Barat(R[bi], R[bj]);
            cnt[R[bi]]++;
            cnt[R[bj]]++;
            for (const Hy &h : alive) {
                int li = lbl(h, bi), lj = lbl(h, bj);
                int a = (li != 2 && lj != 2 && li == lj) ? 1 : 0;
                if (a == r) nxt.push_back(h);
            }
        }
        alive.swap(nxt);
    }
}

}  // namespace

int main() {
    N = GetN();
    if (N <= 14) { solveSmall(N); return 0; }
    useMemo = (N <= 4096);
    cnt.assign(N + 1, 0);
    cert.assign(N + 1, 0);
    rel.assign(N + 1, 0);
    par.resize(N + 1);
    for (int i = 0; i <= N; ++i) par[i] = i;

    // 1. kor: egymas melletti parok
    vector<pair<int,int>> Z;
    for (int i = 1; i + 1 <= N; i += 2) {
        if (ask(i, i + 1) == 1) { cert[i] = cert[i + 1] = 1; unite(i, i + 1, 0); }
        else Z.push_back({i, i + 1});
    }
    // 2. kor: 0-s parok kettesevel
    for (size_t k = 0; k + 1 < Z.size(); k += 2) {
        int x = Z[k].first, y = Z[k].second, u = Z[k + 1].first, w = Z[k + 1].second;
        if (ask(x, u) == 1) {
            cert[x] = cert[u] = 1; unite(x, u, 0);
            if (ask(y, w) == 1) { cert[y] = cert[w] = 1; unite(y, w, 0); }
        } else {
            if (ask(y, u) == 1) { cert[y] = cert[u] = 1; unite(y, u, 0); }
            if (ask(x, w) == 1) { cert[x] = cert[w] = 1; unite(x, w, 0); }
        }
    }
    vector<pair<int,int>>().swap(Z);
    for (auto &z : zeros) if (cert[z.first] && cert[z.second]) unite(z.first, z.second, 1);

    // 3. kor: maradekok feloldasa kimerito hipotezis-kereses segitsegevel
    if (findBothRoot() < 0) establishHubs();
    int R0 = findBothRoot();
    vector<int> lab(N + 1, -1);
    if (R0 >= 0)
        for (int v = 1; v <= N; ++v)
            if (cert[v]) { int p; if (findRoot(v, p) == R0) lab[v] = p; }
    vector<int> R;
    for (int v = 1; v <= N; ++v) if (!cert[v]) R.push_back(v);
    resolveResidual(R, lab);
    return 0;
}
