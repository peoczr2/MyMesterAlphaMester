/*
Megoldás lényege:
A gráfot erősen összefüggő komponensekre bontjuk (Tarjan). Ha egy komponens van, nincs teendő. Különben a komponensek közötti élek körmentes gráfot adnak, amelyben vannak forrás-komponensek (nincs bejövő él) és nyelő-komponensek (nincs kimenő él). Minden forrásba kell új bejövő él, minden nyelőből új kimenő él, ezért legalább max(források, nyelők) új él kell, és ennyi elég is. A forrásokból a nyelőkbe mutató elérési halmazokat bitsorozatban tároljuk. Egy (nyelő t, forrás s) párra, ha s nem éri el t-t, a t -> s él nem zár kört, így a források és nyelők száma eggyel csökken. Ha már minden maradék forrás eléri a maradék nyelőket, a párokat tetszőlegesen kötjük, és a végén a megmaradt egyetlen forrást vagy nyelőt a többivel kötjük össze. Az időigény O((N + M) + F·N·N/64), ahol F a forrás-komponensek száma.
*/
/*
Hint 1: || Először erősen összefüggő komponensekre bontsd a gráfot Tarjan-algoritmussal. Ha egyetlen komponens van, nincs teendő; különben a komponensek közti élek körmentes gráfot adnak. ||
Hint 2: || Egy új él egy nyelő-komponensből egy forrás-komponensbe vezet, így minden forrásnak és nyelőnek egy-egy új élre van szüksége. A minimum a források és a nyelők számának maximuma. ||
Hint 3: || Ha egy forrásból nem érhető el egy nyelő, a nyelőből a forrásba húzott él nem zár kört. Az elérhetőséget bitsorozatban tárold minden forrásra, és az új él hozzáadása után frissítsd azokat a forrásokat, amelyek elérik a nyelő kezdetét. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Gyors beolvasás (fread): M = 10^5 élnél is hasznos.
static char ibuf[1 << 16];
static size_t ilen = 0, ipos = 0;

inline int readChar() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}

inline void readInt(int &x) {
    int c = readChar();
    while (c != -1 && (c < '0' || c > '9')) c = readChar();
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = readChar();
    }
}

int main() {
    int n, m;
    readInt(n);
    readInt(m);
    vector<int> eu(m), ev(m), st(n + 2, 0);
    for (int e = 0; e < m; ++e) {
        readInt(eu[e]);
        readInt(ev[e]);
        ++st[eu[e] + 1];
    }
    for (int v = 1; v <= n + 1; ++v) st[v] += st[v - 1];
    vector<int> adj(m);
    {
        vector<int> pos(st.begin(), st.end());
        for (int e = 0; e < m; ++e) adj[pos[eu[e]]++] = ev[e];
    }

    // Tarjan-féle erősen összefüggő komponensek (iteratív).
    // A komponens-sorszámok fordított topologikus sorrendben keletkeznek: ha A -> B él van, id(B) < id(A).
    vector<int> idx(n + 1, -1), low(n + 1, 0), comp(n + 1, -1), it(n + 1, 0), stk, cs;
    vector<char> onStk(n + 1, 0);
    int timer = 0, C = 0;
    for (int s = 1; s <= n; ++s) {
        if (idx[s] != -1) continue;
        idx[s] = low[s] = timer++;
        it[s] = st[s];
        stk.push_back(s);
        onStk[s] = 1;
        cs.push_back(s);
        while (!cs.empty()) {
            int v = cs.back();
            if (it[v] < st[v + 1]) {
                int w = adj[it[v]++];
                if (idx[w] == -1) {
                    idx[w] = low[w] = timer++;
                    it[w] = st[w];
                    stk.push_back(w);
                    onStk[w] = 1;
                    cs.push_back(w);
                } else if (onStk[w]) {
                    low[v] = min(low[v], idx[w]);
                }
            } else {
                cs.pop_back();
                if (low[v] == idx[v]) {
                    while (true) {
                        int w = stk.back();
                        stk.pop_back();
                        onStk[w] = 0;
                        comp[w] = C;
                        if (w == v) break;
                    }
                    ++C;
                }
                if (!cs.empty()) low[cs.back()] = min(low[cs.back()], low[v]);
            }
        }
    }

    if (C == 1) {
        fputs("0\n", stdout);
        return 0;
    }

    vector<int> rep(C, -1);
    for (int v = 1; v <= n; ++v)
        if (rep[comp[v]] == -1) rep[comp[v]] = v;

    // Kondenzált élek: a komponensek közti élek (az önhurok nem számít).
    vector<int> outDeg(C, 0), inDeg(C, 0);
    vector<vector<int>> cadj(C);
    for (int e = 0; e < m; ++e) {
        int a = comp[eu[e]], b = comp[ev[e]];
        if (a != b) {
            ++outDeg[a];
            ++inDeg[b];
            cadj[a].push_back(b);
        }
    }

    // Nyelők (kimenő él nélkül) indexelése; sinkComp[i] a komponens.
    vector<int> sidx(C, -1), sinkComp;
    for (int c = 0; c < C; ++c)
        if (outDeg[c] == 0) {
            sidx[c] = (int)sinkComp.size();
            sinkComp.push_back(c);
        }
    const int Q = (int)sinkComp.size();
    const int W = (Q + 63) / 64;

    // Elérési halmazok: minden komponensből az elérhető nyelők bitsorozata (a 0..C-1 sorrendben, nyelőtől előre).
    vector<unsigned long long> reach((size_t)C * W, 0ULL);
    auto row = [&](int c) { return reach.data() + (size_t)c * W; };
    for (int c = 0; c < C; ++c) {
        unsigned long long *r = row(c);
        if (sidx[c] != -1) r[sidx[c] >> 6] |= 1ULL << (sidx[c] & 63);
        for (int d : cadj[c]) {
            const unsigned long long *rd = row(d);
            for (int w = 0; w < W; ++w) r[w] |= rd[w];
        }
    }

    vector<int> sources;
    for (int c = 0; c < C; ++c)
        if (inDeg[c] == 0) sources.push_back(c);

    vector<char> inX(C, 0);
    for (int s : sources) inX[s] = 1;
    vector<unsigned long long> aliveY(W, 0ULL);
    for (int i = 0; i < Q; ++i) aliveY[i >> 6] |= 1ULL << (i & 63);

    // Új élek: (tail komponens, head komponens): tail -> head.
    vector<pair<int, int>> arcs;

    // 1. menet: minden forrásra, ha van nem elérhető élő nyelő, egy ilyen párt kötünk össze.
    for (int s : sources) {
        int tIdx = -1;
        unsigned long long *rs = row(s);
        for (int w = 0; w < W; ++w) {
            unsigned long long z = ~rs[w] & aliveY[w];
            if (z) {
                tIdx = w * 64 + __builtin_ctzll(z);
                break;
            }
        }
        if (tIdx < 0) continue;  // s minden élő nyelőt elér; ez a későbbi menetekben sem változik
        int t = sinkComp[tIdx];
        arcs.push_back({t, s});
        // frissítés: minden megmaradt forrás, amely eléri t-t, elérni fogja s elérési halmazát is
        for (int x : sources) {
            if (!inX[x] || x == s) continue;
            unsigned long long *rx = row(x);
            if ((rx[tIdx >> 6] >> (tIdx & 63)) & 1ULL) {
                for (int w = 0; w < W; ++w) rx[w] |= rs[w];
            }
        }
        inX[s] = 0;
        aliveY[tIdx >> 6] &= ~(1ULL << (tIdx & 63));
    }

    // 2. menet: a maradék forrásokat és nyelőket párosítjuk, majd a maradékot egyetlen csomópontba kötjük.
    vector<int> Xr, Yr;
    for (int s : sources)
        if (inX[s]) Xr.push_back(s);
    for (int i = 0; i < Q; ++i)
        if ((aliveY[i >> 6] >> (i & 63)) & 1ULL) Yr.push_back(sinkComp[i]);
    while (Xr.size() >= 2 && Yr.size() >= 2) {
        int s = Xr.back();
        Xr.pop_back();
        int t = Yr.back();
        Yr.pop_back();
        arcs.push_back({t, s});
    }
    if (Xr.size() == 1) {
        int s0 = Xr[0];
        for (int t : Yr) arcs.push_back({t, s0});
    } else if (Yr.size() == 1) {
        int t0 = Yr[0];
        for (int s : Xr) arcs.push_back({t0, s});
    }

    string out;
    out.reserve(arcs.size() * 12 + 16);
    out += to_string(arcs.size());
    out += '\n';
    for (auto &a : arcs) {
        out += to_string(rep[a.first]);
        out += ' ';
        out += to_string(rep[a.second]);
        out += '\n';
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
