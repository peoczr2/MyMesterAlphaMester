/*
Megoldás lényege:
Egy kijelölés minden úthoz egy végpontot rendel úgy, hogy minden városhoz legfeljebb egy út tartozik. A gráf komponensei függetlenek, ezért a kijelölések száma komponensenként szorzódik, a költségösszeg pedig Σ_c (c költségösszege) · Π_{d≠c} (d darabszáma). Egy fa-komponensben (V csúcs, V-1 él) a kijelölések száma V, mert a szabad csúcs bárhol lehet, és az él mindig a gyökértől távolabbi végpontra kerül; egy él (A,B) így a két oldal méretével súlyozva járul hozzá. Egy körös komponensben (V csúcs, V él) a körélek két irány lehetséges, így a darabszám 2; a körből kiindulva a fa-élek mindkét irányban a távoli végpontra kerülnek. A részfa-méreteket a levelek sorban történő eltávolításával (leveles lehúzással) kapjuk meg egy menetben. Modulo 1 000 000 007 az osztás inverzzel oldható meg, mert a darabszámok kicsik. Az idő O(N + M).
*/
/*
Hint 1: || Komponensenként érdemes gondolkodni. Fa esetén a kijelölések száma a csúcsok száma, mert a szabad város bárhol lehet; egy körös komponensben csak a kör két irányítása lehetséges. ||
Hint 2: || A kijelölések száma komponensenként szorzódik, a költségösszeg pedig: Σ_c (c komponens költségösszege) · (a többi komponens kijelöléseinek száma). Egy élnél elég tudni, hány kijelölésben kerül az egyik vagy a másik végpontra. ||
Hint 3: || Fa-komponensben a levelekből kiindulva, sorban távolítsd el a fokszám-1 csúcsokat: így minden élhez megkapod a távoli végpont oldalán lévő részfa méretét, ami az él súlya. Körös komponensben a visszamaradó éleknél a körélek mindkét irányt egyszer adja, a levélekkel eltávolított élek pedig kétszer számítanak. ||
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

long long pw(long long b, long long e) {
    long long r = 1;
    b %= MOD;
    while (e > 0) {
        if (e & 1) r = r * b % MOD;
        b = b * b % MOD;
        e >>= 1;
    }
    return r;
}

// a * a * b modulo MOD
long long costOf(long long a, long long b) {
    return (a * a % MOD) * (b % MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> ea(m), eb(m), deg(n + 1, 0);
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<int> dsu(n + 1);
    iota(dsu.begin(), dsu.end(), 0);
    auto findr = [&](int x) {
        while (dsu[x] != x) { dsu[x] = dsu[dsu[x]]; x = dsu[x]; }
        return x;
    };
    for (int i = 0; i < m; ++i) {
        cin >> ea[i] >> eb[i];
        adj[ea[i]].push_back({eb[i], i});
        adj[eb[i]].push_back({ea[i], i});
        deg[ea[i]]++; deg[eb[i]]++;
        int ra = findr(ea[i]), rb = findr(eb[i]);
        if (ra != rb) dsu[ra] = rb;
    }

    vector<int> vcnt(n + 1, 0), ecnt(n + 1, 0);
    for (int v = 1; v <= n; ++v) vcnt[findr(v)]++;
    for (int i = 0; i < m; ++i) ecnt[findr(ea[i])]++;

    // leveles lehúzás: minden fa-él távoli végpontja és a távoli oldal mérete
    vector<char> removed(m, 0);
    vector<long long> sz(n + 1, 1);
    vector<int> farV(m, 0), nearV(m, 0);
    vector<long long> farSz(m, 0);
    queue<int> q;
    for (int v = 1; v <= n; ++v) if (deg[v] == 1) q.push(v);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        if (deg[v] != 1) continue;
        int e = -1, u = -1;
        for (auto [w, id] : adj[v]) if (!removed[id]) { e = id; u = w; break; }
        removed[e] = 1;
        deg[v] = 0;
        deg[u]--;
        sz[u] += sz[v];
        farV[e] = v; nearV[e] = u; farSz[e] = sz[v];
        if (deg[u] == 1) q.push(u);
    }

    // komponensenkénti darabszám: fánál V, körösnél 2
    vector<long long> sumc(n + 1, 0), cnt(n + 1, 1);
    for (int v = 1; v <= n; ++v) {
        if (findr(v) != v) continue;
        int V = vcnt[v], E = ecnt[v];
        cnt[v] = (E == V) ? 2 : V;
    }
    for (int i = 0; i < m; ++i) {
        int r = findr(ea[i]);
        int V = vcnt[r], E = ecnt[r];
        if (removed[i]) {
            long long far = farV[i], near = nearV[i], fs = farSz[i];
            if (E == V - 1) {
                // fa: a távoli végpontra (V - fs) kijelölés és a közeli végpontra fs kijelölés jut
                sumc[r] = (sumc[r] + (long long)(V - fs) % MOD * costOf(far, near)) % MOD;
                sumc[r] = (sumc[r] + fs % MOD * costOf(near, far)) % MOD;
            } else {
                // körös komponens: a távoli végpontra mindkét körirányban kerül
                sumc[r] = (sumc[r] + 2 * costOf(far, near)) % MOD;
            }
        } else {
            // körél: a két irányban egyszer-egyszer kerül az egyik végpontra
            sumc[r] = (sumc[r] + costOf(ea[i], eb[i]) + costOf(eb[i], ea[i])) % MOD;
        }
    }

    long long P = 1;
    for (int v = 1; v <= n; ++v) if (findr(v) == v) P = P * cnt[v] % MOD;
    long long ans = 0;
    for (int v = 1; v <= n; ++v) {
        if (findr(v) != v) continue;
        long long others = P * pw(cnt[v], MOD - 2) % MOD;
        ans = (ans + sumc[v] * others) % MOD;
    }
    cout << ans << '\n';
    return 0;
}
