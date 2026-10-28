/*
Megoldás lényege: a kifejezés gráfjának élei a szomszédos karakterek között, és a zárójelpárok
(nyitó és záró zárójel) között futnak. A minimumot BFS adja (O(N)). A maximumot a zárójelpárok
beágyazási fájából számoljuk: minden zárójelpár egy kört alkot a közbeeső karakterekkel és a saját
élével, a közvetlenül beágyazott párok pedig a körön belüli "kitérők", amelyeknek a leghosszabb
útjait alulról felfelé összegezzük (prefixösszegek és bináris keresés segítségével). A két x
legmélyebb közös zárójelpárjában dől el, hogy a bolha melyik irányban járja be a kört, és a körből
kilépve a szülő kör másik oldalán haladhat tovább; ezt a "kerülő" hosszt fentről lefelé számoljuk.
Az időigény O(N log N).
*/
/*
Hint 1: || Először a minimumot gondold meg: a gráfban minden lépés egy él, így a legrövidebb út egy BFS-sel megkapható. A maximumhoz vedd észre, hogy minden zárójelpár egy kört zár be, és ezek a körök egymásba ágyazódnak. ||
Hint 2: || Építs fát a zárójelpárokból: egy pár gyerekei a közvetlenül benne lévő párok. Egy pár két végpontja között a bolha vagy a pár két zárójele közötti egyetlen élen megy át, vagy a hosszú úton, a gyerek-párokat is bejárva; a hosszú út leghosszabb hosszát a gyerekek értékeiből alulról felfelé kapod meg. ||
Hint 3: || Keresd meg a két x legmélyebb közös zárójelpárját (vagy a teljes kifejezést). Itt a két x által meghatározott végpontokból két irányba lehet indulni, és egy irány a szülő körének másik oldalán vezethet tovább. A tartományok összegzését prefixtömbbel és bináris kereséssel végezd. ||
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll NEG = LLONG_MIN / 4;

int n;
vector<int> NL, NR, par;
vector<vector<int>> ch, chL, chR;
vector<vector<ll>> psz, pdd;
vector<ll> D, XV;

// Az [a,b] szakasz leghosszabb útja: a csomópont kör-íve a gyerek-párok maximális
// útjaival (D), a gyerekek belsejét kihagyva.
ll between(int y, int a, int b) {
    int i = int(lower_bound(chL[y].begin(), chL[y].end(), a) - chL[y].begin());
    int j = int(upper_bound(chR[y].begin(), chR[y].end(), b) - chR[y].begin());
    ll sz = 0, dd = 0;
    if (j > i) {
        sz = psz[y][j] - psz[y][i];
        dd = pdd[y][j] - pdd[y][i];
    }
    return (ll)(b - a) - sz + dd;
}

void prep(int y) {
    chL[y].clear();
    chR[y].clear();
    psz[y].assign(1, 0);
    pdd[y].assign(1, 0);
    for (int c : ch[y]) {
        chL[y].push_back(NL[c]);
        chR[y].push_back(NR[c]);
        psz[y].push_back(psz[y].back() + (NR[c] - NL[c]));
        pdd[y].push_back(pdd[y].back() + D[c]);
    }
}

// A v-t zártan tartalmazó csomópontok láncolata a gyökértől a legmélyebbig.
vector<int> closedChain(int v) {
    vector<int> chain{0};
    int cur = 0;
    while (true) {
        int idx = int(upper_bound(chL[cur].begin(), chL[cur].end(), v) - chL[cur].begin()) - 1;
        if (idx >= 0 && NR[ch[cur][idx]] >= v) {
            cur = ch[cur][idx];
            chain.push_back(cur);
        } else {
            break;
        }
    }
    return chain;
}

// A cur csomópont azon gyereke, amely v-t nyíltan (belsőleg) tartalmazza; egyébként -1.
int strictChild(int cur, int v) {
    int idx = int(upper_bound(chL[cur].begin(), chL[cur].end(), v) - chL[cur].begin()) - 1;
    if (idx >= 0) {
        int c = ch[cur][idx];
        if (NL[c] < v && v < NR[c]) return c;
    }
    return -1;
}

// v-ből a cs kör bal, illetve jobb végpontjába vezető leghosszabb út (PL, PR).
pair<ll, ll> plPr(int v, int cs) {
    vector<int> seq{cs};
    while (true) {
        int d = strictChild(seq.back(), v);
        if (d < 0) break;
        seq.push_back(d);
    }
    int y = seq.back();
    ll PL = max(between(y, NL[y], v), between(y, v, NR[y]) + 1);
    ll PR = max(between(y, v, NR[y]), between(y, NL[y], v) + 1);
    for (int idx = (int)seq.size() - 2; idx >= 0; --idx) {
        int Y = seq[idx], Z = seq[idx + 1];
        ll nPL = max(PL + between(Y, NL[Y], NL[Z]), PR + between(Y, NR[Z], NR[Y]) + 1);
        ll nPR = max(PR + between(Y, NR[Z], NR[Y]), PL + between(Y, NL[Y], NL[Z]) + 1);
        PL = nPL;
        PR = nPR;
    }
    return {PL, PR};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nIn;
    string e;
    cin >> nIn >> e;
    n = (int)e.size();

    vector<int> match(n, -1);
    {
        vector<int> st;
        for (int i = 0; i < n; ++i) {
            if (e[i] == '(') {
                st.push_back(i);
            } else if (e[i] == ')') {
                int j = st.back();
                st.pop_back();
                match[i] = j;
                match[j] = i;
            }
        }
    }

    int s = -1, t = -1;
    for (int i = 0; i < n; ++i) {
        if (e[i] == 'x') {
            if (s < 0) s = i;
            else t = i;
        }
    }

    // Minimum: BFS a szomszédos karakterek és a zárójelpárok élein.
    ll minAns;
    {
        vector<int> dist(n, -1);
        queue<int> q;
        dist[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            auto relax = [&](int v) {
                if (v >= 0 && v < n && dist[v] < 0) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            };
            relax(u - 1);
            relax(u + 1);
            relax(match[u]);
        }
        minAns = dist[t];
    }

    // A zárójelpárok fája: 0 a gyökér (a teljes kifejezés), k >= 1 a k-adik zárójelpár.
    vector<int> L;
    for (int i = 0; i < n; ++i)
        if (e[i] == '(') L.push_back(i);
    int m = (int)L.size();
    NL.assign(m + 1, 0);
    NR.assign(m + 1, 0);
    NR[0] = n - 1;
    for (int k = 1; k <= m; ++k) {
        NL[k] = L[k - 1];
        NR[k] = match[L[k - 1]];
    }
    par.assign(m + 1, -1);
    ch.assign(m + 1, {});
    {
        vector<int> stk{0};
        for (int k = 1; k <= m; ++k) {
            while (stk.back() != 0 && NR[stk.back()] < NL[k]) stk.pop_back();
            par[k] = stk.back();
            ch[par[k]].push_back(k);
            stk.push_back(k);
        }
    }

    // D[k]: a k-adik pár bal és jobb végpontja közti leghosszabb út a saját körén belül.
    chL.assign(m + 1, {});
    chR.assign(m + 1, {});
    psz.assign(m + 1, {});
    pdd.assign(m + 1, {});
    D.assign(m + 1, 0);
    for (int k = m; k >= 1; --k) {
        prep(k);
        D[k] = between(k, NL[k], NR[k]);
    }
    prep(0);

    // XV[k]: a k-adik kör bal és jobb végpontja közti leghosszabb "kiugró" út (a kör éle, vagy
    // a szülő köréből kiinduló kerülő út). A gyökérnek nincs ilyen, ezért ott NEG.
    vector<ll> OUT(m + 1, NEG);
    for (int k = 1; k <= m; ++k) {
        int q = par[k];
        if (q != 0) {
            ll Xq = max<ll>(1, OUT[q]);
            OUT[k] = between(q, NL[q], NL[k]) + Xq + between(q, NR[k], NR[q]);
        }
    }
    XV.assign(m + 1, NEG);
    for (int k = 1; k <= m; ++k) XV[k] = max<ll>(1, OUT[k]);

    vector<int> cs = closedChain(s), ct = closedChain(t);
    int i = 0;
    while (i + 1 < (int)cs.size() && i + 1 < (int)ct.size() && cs[i + 1] == ct[i + 1]) ++i;
    int N = cs[i];
    int l = NL[N], r = NR[N];
    ll XN = XV[N];
    int Cs = strictChild(N, s), Ct = strictChild(N, t);

    ll best = NEG;
    if (Cs < 0 && Ct < 0) {
        best = max(best, between(N, s, t));
        if (XN > NEG) best = max(best, between(N, l, s) + XN + between(N, t, r));
    } else if (Cs < 0 || Ct < 0) {
        int v = s, w = t, G = Cs;
        if (Cs < 0) {
            v = t;
            w = s;
            G = Ct;
        }
        auto [PL, PR] = plPr(v, G);
        int lc = NL[G], rc = NR[G];
        if (w > rc) {
            best = max(best, PR + between(N, rc, w));
            if (XN > NEG) best = max(best, PL + between(N, l, lc) + XN + between(N, w, r));
        } else {
            best = max(best, PL + between(N, w, lc));
            if (XN > NEG) best = max(best, PR + between(N, rc, r) + XN + between(N, l, w));
        }
    } else {
        int sv = s, tv = t, A = Cs, B = Ct;
        if (NR[A] > NL[B]) {
            swap(sv, tv);
            swap(A, B);
        }
        auto [PLs, PRs] = plPr(sv, A);
        auto [PLt, PRt] = plPr(tv, B);
        best = max(best, PRs + between(N, NR[A], NL[B]) + PLt);
        if (XN > NEG) best = max(best, PLs + between(N, l, NL[A]) + XN + between(N, NR[B], r) + PRt);
    }

    cout << minAns << '\n' << best << '\n';
    return 0;
}
