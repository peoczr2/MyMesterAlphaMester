/*
Megoldás lényege:
Lokális keresést használunk. Kezdetben tetszőleges beosztás van (a sorszám paritása szerint). Ha egy résztvevőnek a saját csoportjában legalább két olyan társa van, akit nem kedvel, akkor átteszszük a másik csoportba. Mivel legfeljebb három nem kedvelés van egy résztvevőnél, az átrakás a csoportokon belüli nem kedvelési párok számát legalább eggyel csökkenti (a változás legalább 3 - 4 = -1). Így az eljárás véges lépés után véget ér, és akkor már senkinek sincs kettő vagy több azonos csoportbeli nem kedvelt társa. Az állapotokat egy számlálóval (hány azonos csoportbeli társa van) és egy veremmel követjük, így az összidő O(N + M), ahol M az élek száma, legfeljebb 1,5N.
*/
/*
Hint 1: || Kezdj egy tetszőleges beosztással, és keress olyan résztvevőt, akinek a saját csoportjában legalább két nem kedvelt társa van. ||
Hint 2: || Ha egy ilyen résztvevőt átteszel a másik csoportba, a csoportokon belüli nem kedvelési párok száma csökken. Ez abból látszik, hogy egy résztvevőnek legfeljebb három nem kedvelt társa van. ||
Hint 3: || Az átrakás után a szomszédok azonos csoportbeli számlálóját frissítsd, és ha valakinél kettő lesz, azt is tedd a keresendők közé. Ha nincs ilyen résztvevő, kész a beosztás. ||
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

int main() {
    int n = (int)readLL();
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; i++) {
        while (true) {
            int x = (int)readLL();
            if (x == 0) break;
            adj[i].push_back(x);
        }
    }

    vector<int> col(n + 1, 0), s(n + 1, 0);  // s[v]: a v csoportjában lévő nem kedvelt társak száma
    for (int v = 1; v <= n; v++) col[v] = v & 1;
    for (int v = 1; v <= n; v++)
        for (int u : adj[v])
            if (col[u] == col[v]) s[v]++;

    vector<int> stk;
    for (int v = 1; v <= n; v++)
        if (s[v] >= 2) stk.push_back(v);

    while (!stk.empty()) {
        int v = stk.back();
        stk.pop_back();
        if (s[v] < 2) continue;
        int deg = (int)adj[v].size();
        int old = col[v];
        col[v] ^= 1;
        s[v] = deg - s[v];  // az új csoportjában lévő azonos társak száma
        for (int u : adj[v]) {
            if (col[u] == old) {
                s[u]--;  // u és v korábban egy csoportban voltak, most már nem
            } else {
                s[u]++;  // most már egy csoportban vannak
                if (s[u] >= 2) stk.push_back(u);
            }
        }
    }

    vector<int> grp;
    for (int v = 1; v <= n; v++)
        if (col[v] == 1) grp.push_back(v);
    string out;
    out += to_string(grp.size());
    out += '\n';
    for (size_t i = 0; i < grp.size(); i++) {
        if (i) out += ' ';
        out += to_string(grp[i]);
    }
    out += '\n';
    fputs(out.c_str(), stdout);
    return 0;
}
