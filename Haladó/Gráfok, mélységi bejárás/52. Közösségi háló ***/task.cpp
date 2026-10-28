/*
Megoldás lényege:
Minden tagra meg kell számolni, hány másik tagot ér el, és ebből a legkisebb értékű tagot kell kiírni. Az irányított gráf erősen összefüggő komponensei (Tarjan-algoritmus) körmentes gráfot adnak, és egy komponens elérési halmaza a saját tagjaiból és az utódkomponensek elérési halmazaiból áll össze. Ezeket a halmazokat bitsorozatban (bitset) tároljuk, az egyesítés VAGY művelet, és a komponenseket olyan sorrendben dolgozzuk fel, hogy az utódok már készen legyenek (a Tarjan-algoritmus komponenssorszáma ilyen). A kiírt szám a bitek száma eggyel csökkentve, mert a tag önmagát nem számolja. Az egyesítésnél kihagyjuk azokat az utódokat, amelyek már benne vannak az aktuális halmazban. A bemenetet fread-del olvassuk, mert 5·10^5 élnél a cin lassú. Az időigény O(M · N / 64), a memória O(N²/8), ami a 10 000 csúcsnál körülbelül 12 MB.
*/
/*
Hint 1: || Egy tag elérési száma azt mutatja, hány csúcsot ér el a bejelölések mentén. Mindegyikre külön bejárást futtatni túl lassú, ezért a közös részeket kell kihasználni. ||
Hint 2: || Az erősen összefüggő komponensek (Tarjan) után a komponensek között körmentes gráfot kapsz. Ha egy komponens elérési halmaza ismert, az ebből elérhető halmaz a saját tagjainak és az utódkomponensek halmazainak uniója. ||
Hint 3: || Az elérési halmazokat bitsorozatban tárold (bitset<10000>), és az uniót VAGY művelettel számold. Az utódkomponenseket mindig előbb dolgozd fel, majd a bitek számából kivonva az önmagadat megkapod a kívánt P értéket. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000;  // a csúcsok száma legfeljebb 10 000

// Gyors beolvasás a standard bemenetről (fread): M = 5·10^5 élnél a cin az időlimit nagy részét elviszi.
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    readInt(n);
    readInt(m);
    vector<int> ea(m), eb(m), start(n + 2, 0);
    for (int i = 0; i < m; ++i) {
        readInt(ea[i]);
        readInt(eb[i]);
        ++start[ea[i] + 1];
    }
    for (int v = 1; v <= n + 1; ++v) start[v] += start[v - 1];
    vector<int> adj(m), pos(start.begin(), start.end());
    for (int i = 0; i < m; ++i) adj[pos[ea[i]]++] = eb[i];

    // Tarjan-féle erősen összefüggő komponensek.
    // Egy komponens sorszáma kisebb, mint az általa elérhető komponenseké.
    vector<int> idx(n + 1, -1), low(n + 1, 0), it(n + 1, 0), comp(n + 1, -1);
    vector<char> onStack(n + 1, 0);
    vector<int> stk, call;
    int timer = 0, cc = 0;
    auto enter = [&](int v) {
        idx[v] = low[v] = timer++;
        it[v] = start[v];
        stk.push_back(v);
        onStack[v] = 1;
        call.push_back(v);
    };
    for (int s = 1; s <= n; ++s) {
        if (idx[s] != -1) continue;
        enter(s);
        while (!call.empty()) {
            int v = call.back();
            if (it[v] < start[v + 1]) {
                int to = adj[it[v]++];
                if (idx[to] == -1) {
                    enter(to);
                } else if (onStack[to]) {
                    low[v] = min(low[v], idx[to]);
                }
            } else {
                call.pop_back();
                if (low[v] == idx[v]) {
                    int w;
                    do {
                        w = stk.back();
                        stk.pop_back();
                        onStack[w] = 0;
                        comp[w] = cc;
                    } while (w != v);
                    ++cc;
                }
                if (!call.empty()) low[call.back()] = min(low[call.back()], low[v]);
            }
        }
    }

    vector<vector<int>> members(cc);
    for (int v = 1; v <= n; ++v) members[comp[v]].push_back(v);
    vector<int> rep(cc);  // a komponens egy tagja (bitindexként, eggyel csökkentve)
    for (int c = 0; c < cc; ++c) rep[c] = members[c][0] - 1;

    // reach[c]: a c komponensből elérhető csúcsok (a u csúcs a (u-1). bit).
    vector<bitset<MAXN>> reach(cc);
    for (int c = 0; c < cc; ++c) {
        for (int u : members[c]) {
            reach[c].set(u - 1);
            for (int e = start[u]; e < start[u + 1]; ++e) {
                int d = comp[adj[e]];
                // ha d egy tagja már elérhető, d teljes elérési halmaza már benne van: nem kell VAGY-olni
                if (d != c && !reach[c][rep[d]]) reach[c] |= reach[d];
            }
        }
    }

    // A legkevesebb másik tagot elérő tag (a legkisebb sorszámú a döntetlennél).
    int best = -1, bestV = -1;
    for (int v = 1; v <= n; ++v) {
        int val = (int)reach[comp[v]].count() - 1;
        if (best == -1 || val < best) {
            best = val;
            bestV = v;
        }
    }
    cout << best << ' ' << bestV << '\n';
    return 0;
}
