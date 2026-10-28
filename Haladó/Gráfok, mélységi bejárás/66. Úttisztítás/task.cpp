/*
Megoldás lényege:
Minden út két végpontja közül pontosan az egyikhez kerül, és minden városhoz legfeljebb egy út. Ha egy összefüggő komponens fa (az utak száma a városok számánál eggyel kisebb), pontosan egy város marad üresen, és a gyökérből nézve minden út a távolabbi végpontjához kerül; így a kijelölések száma a városok száma. Egy él költsége az összegben a két oldal méretével súlyozva szerepel, mert a gyökér helyétől függ, melyik végponthoz kerül. Ha a komponens körös (az utak száma a városokéval egyenlő), a körön kívüli utak levelektől indulva egyértelműen rendelődnek, a kört pedig két irányban lehet bejárni, így 2 kijelölés van. A komponensek (darabszám, összeg) párjait összevonva kapjuk a végeredményt, az időigény O(N + M).
*/
/*
Hint 1: || Minden városhoz legfeljebb egy út kerülhet, ezért ha egy komponensben az utak száma a városokéval egyenlő, akkor minden város pontosan egy utat kap, és a fa-eset egy városa üresen marad. ||
Hint 2: || Fa komponensben a kijelölt üres város gyökérnek tekinthető: minden él a gyökértől távolabbi végpontjához kerül, így minden lehetséges üres város egy kijelölést ad. ||
Hint 3: || Egy él költsége a kapott végponttól függ (a^2 * b). Fánál minden élt a két oldal részfa-méreteivel szorozva szerepeltethetsz; körös komponensben a körön kívüli éleket levélről indulva lehámozhatod, a körélekre pedig a két irány összege a * b * (a + b). ||
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

// Az x városhoz rendelt y-beli él költsége: x^2 * y, modulo MOD.
long long cost(long long x, long long y) {
    return (x * x % MOD) * y % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> ea(m), eb(m);
    vector<vector<pair<int, int>>> adj(n + 1);  // (szomszéd, élazonosító)
    vector<int> deg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        cin >> ea[i] >> eb[i];
        adj[ea[i]].push_back({eb[i], i});
        adj[eb[i]].push_back({ea[i], i});
        ++deg[ea[i]];
        ++deg[eb[i]];
    }

    // Komponensek BFS-sel; a BFS-sorrend és a szülők a fa-számításhoz kellenek.
    vector<int> comp(n + 1, -1), par(n + 1, 0), sz(n + 1, 1);
    vector<vector<int>> order;
    for (int s = 1; s <= n; ++s) {
        if (comp[s] != -1) continue;
        int id = order.size();
        vector<int> q{s};
        comp[s] = id;
        for (size_t h = 0; h < q.size(); ++h) {
            int v = q[h];
            for (auto &pr : adj[v]) {
                int w = pr.first;
                if (comp[w] == -1) {
                    comp[w] = id;
                    par[w] = v;
                    q.push_back(w);
                }
            }
        }
        order.push_back(q);
    }
    int C = order.size();
    vector<long long> vcnt(C), ecnt(C, 0);
    for (int c = 0; c < C; ++c) vcnt[c] = order[c].size();
    for (int i = 0; i < m; ++i) ecnt[comp[ea[i]]]++;

    // Körös komponensek: a levél-lehámozással a körön kívüli élek egyértelműen kiosztódnak.
    vector<char> usedE(m, 0), removed(n + 1, 0);
    vector<long long> forced(C, 0), cyc(C, 0);
    vector<int> d = deg;
    queue<int> lf;
    for (int v = 1; v <= n; ++v)
        if (ecnt[comp[v]] == vcnt[comp[v]] && d[v] == 1) lf.push(v);
    while (!lf.empty()) {
        int u = lf.front();
        lf.pop();
        if (removed[u] || d[u] != 1) continue;
        for (auto &pr : adj[u]) {
            int w = pr.first, e = pr.second;
            if (usedE[e]) continue;
            usedE[e] = 1;
            removed[u] = 1;
            forced[comp[u]] = (forced[comp[u]] + cost(u, w)) % MOD;
            d[u] = 0;
            if (--d[w] == 1) lf.push(w);
            break;
        }
    }
    for (int i = 0; i < m; ++i) {
        int c = comp[ea[i]];
        if (ecnt[c] == vcnt[c] && !usedE[i]) {
            long long a = ea[i], b = eb[i];
            cyc[c] = (cyc[c] + (a * b % MOD) * ((a + b) % MOD)) % MOD;
        }
    }

    vector<long long> cntC(C, 0), sumC(C, 0);
    for (int c = 0; c < C; ++c) {
        if (ecnt[c] == vcnt[c]) {
            // körös komponens: a kör 2 irányban, a körön kívüli élek fixek
            cntC[c] = 2;
            sumC[c] = (2 * forced[c] + cyc[c]) % MOD;
        } else {
            // fa komponens: a gyökérrel (üres város) az élek egyértelműek
            auto &q = order[c];
            for (int h = (int)q.size() - 1; h >= 1; --h) sz[par[q[h]]] += sz[q[h]];
            long long V = q.size(), S = 0;
            for (int h = 1; h < (int)q.size(); ++h) {
                long long ch = q[h], p = par[q[h]], s = sz[q[h]];
                S = (S + (V - s) * cost(ch, p) % MOD + s * cost(p, ch) % MOD) % MOD;
            }
            cntC[c] = V % MOD;
            sumC[c] = S;
        }
    }

    // Komponensek egyesítése: (C, S) és (c, s) -> (C*c, S*c + s*C).
    long long TC = 1, TS = 0;
    for (int c = 0; c < C; ++c) {
        TS = (TS * cntC[c] % MOD + sumC[c] * TC % MOD) % MOD;
        TC = TC * cntC[c] % MOD;
    }
    cout << TS << '\n';
    return 0;
}
