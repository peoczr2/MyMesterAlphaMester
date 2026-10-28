/*
Megoldás lényege:
Egy csomópont akkor marad elérhető, ha bármely egyetlen vonal kiesése után is van hozzá út a központból. Ez pontosan azt jelenti, hogy a csomópont és a központ ugyanabban a kétélű-összefüggő komponensben van, vagyis nincs olyan híd (vonal), amely elválasztaná őket. A komponenseket egyetlen mélységi bejárással kapjuk meg (Tarjan-algoritmus): a csúcsokat egy verembe tesszük, és ha egy v csúcs befejezésekor low[v] == tin[v], akkor v és a verem tetején álló, még nem lezárt csúcsok egy komponenst alkotnak. A kimenetbe a központ komponensének csúcsait a bejárás sorrendjében írjuk (a sorrend a feladat szerint tetszőleges). A bemenetet gyorsan, fread-del olvassuk, mert 10^6 élnél a cin az időlimitet is megközelítené. Az időigény O(N + M), a memóriaigény O(N + M).
*/
/*
Hint 1: || Egy csomópont pontosan akkor jó, ha a központtal két élen diszjunkt út köti össze. Keresd azokat az éleket (hidakat), amelyek törlése kettévágja a központ komponensét. ||
Hint 2: || Egyetlen mélységi bejárás elég. Minden csúcshoz tárolj egy tin (bejárási sorszám) és egy low (a visszaélekkel elérhető legkisebb tin) értéket. Egy (szülő, gyerek) él akkor híd, ha low[gyerek] > tin[szülő]; ilyenkor a gyerekből induló részt a veremből le lehet vágni. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Gyors beolvasás a standard bemenetről (fread): M = 10^6 élnél a cin az időlimit felét is elvinné.
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

    int n, m, k;
    readInt(n);
    readInt(m);
    readInt(k);
    vector<int> eu(m), ev(m), start(n + 2, 0);
    for (int i = 0; i < m; ++i) {
        readInt(eu[i]);
        readInt(ev[i]);
        ++start[eu[i] + 1];
        ++start[ev[i] + 1];
    }
    // start[v]: a v csúcs szomszédainak kezdőindexe az adj tömbben
    for (int v = 1; v <= n + 1; ++v) start[v] += start[v - 1];

    vector<int> adj(2 * (size_t)m), pos(start.begin(), start.end());
    for (int i = 0; i < m; ++i) {
        adj[pos[eu[i]]++] = ev[i];
        adj[pos[ev[i]]++] = eu[i];
    }

    vector<int> tin(n + 1, -1), low(n + 1, 0), par(n + 1, 0), it(n + 1, 0), comp(n + 1, -1);
    vector<int> order, stk, call;
    order.reserve(n);
    int timer = 0, cid = 0;

    auto enter = [&](int v, int p) {
        tin[v] = low[v] = timer++;
        par[v] = p;
        it[v] = start[v + 1];  // a szomszédokat fordított sorrendben járjuk be
        order.push_back(v);
        stk.push_back(v);
        call.push_back(v);
    };

    enter(k, 0);
    while (!call.empty()) {
        int v = call.back();
        if (it[v] > start[v]) {
            int to = adj[--it[v]];
            if (to == par[v]) continue;  // a szülő felé vezető él (nincs többszörös él)
            if (tin[to] != -1) {
                low[v] = min(low[v], tin[to]);
            } else {
                enter(to, v);
            }
        } else {
            call.pop_back();
            if (low[v] == tin[v]) {
                // v és a verem tetején álló csúcsok egy kétélű-összefüggő komponenst alkotnak
                int w;
                do {
                    w = stk.back();
                    stk.pop_back();
                    comp[w] = cid;
                } while (w != v);
                ++cid;
            }
            if (!call.empty()) low[call.back()] = min(low[call.back()], low[v]);
        }
    }

    vector<int> ans;
    for (int w : order)
        if (comp[w] == comp[k]) ans.push_back(w);

    cout << ans.size() << '\n';
    for (size_t i = 0; i < ans.size(); ++i)
        cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
    return 0;
}
