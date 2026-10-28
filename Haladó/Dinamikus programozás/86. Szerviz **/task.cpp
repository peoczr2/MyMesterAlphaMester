/*
Megoldás lényege:
Az offline k-szerver probléma egyenesen: minden csapat útvonala az általa kiszolgált igények időrendi sorozata, az összköltség pedig az útvonalak mentén a szomszédos helyek távolságainak összege. Ez minimális költségű folyam: egy folyamegység egy csapat útvonala, és minden igényt pontosan egy útvonal érint. Az optimumot csapatonkénti javítással kapjuk: először egyetlen csapat (az első igényhez legközelebbi) szolgál ki mindent, majd minden lépésben a legolcsóbb javító út szerint egy újabb csapatot vonunk be, amíg a javítás költsége nem negatív (a költség a csapatok számának konvex függvénye). A javító út lopáslánc: az új csapat átvesz egy igényt (és az útvonalon utána következőket), annak előző gazdája egy másik útvonalból vesz át igényt, és így tovább; az utolsó gazda lemond az útvonala hátralévő részéről. A legolcsóbb láncot Dijkstra-val keressük potenciálokkal. A gráf sűrű (minden korábbi elem minden későbbi igényhez köthető a távolsággal), ezért az éleket nem tároljuk: az elemeket idő szerint felezzük (CDQ), minden szinten hely szerint rendezett láncot kapunk, ahol a bal fél a forrás, a jobb fél a cél, a távolság két félegyenes-címkével (E − x, illetve E + x) kezelhető, és egy lusta címkés szegmensfa adja a legkisebb kulcsú célt. Időigény: O(M · N · log²N), memória O(N log N).
*/
/*
Hint 1: || Minden csapat útvonala az általa kiszolgált igények időrendi sorozata (az elején a csapat kezdőhelye), az összköltség ezek szomszédos helyeinek távolságösszege. Ez minimális költségű folyam: egy folyamegység egy csapat útvonala, az (előző elem → igény) él költsége a két hely távolsága, és minden igényt pontosan egy útvonal tartalmaz. ||
Hint 2: || Növeld a folyamot csapatonként: kezdetben egyetlen csapat (az első igényhez legközelebbi) szolgál ki mindent, majd mindig a legolcsóbb javító útnak megfelelően egy újabb csapatot vonsz be, és megállsz, amikor a javítás költsége nem negatív. A javító út lopáslánc: az új csapat átvesz egy igényt (az útvonalon utána következőkkel együtt), annak előző gazdája egy másik útvonalból vesz át egy igényt, és így tovább; az utolsó gazda lemond az útvonala maradékáról. Egy lépés költsége: új él mínusz törölt él. ||
Hint 3: || A javító utat Dijkstra-val keresd potenciálokkal (az előző keresés távolságaival), mert negatív élek is vannak. A csúcsok az igények; egy igényből (miután elvetted az előző gazdájától) minden későbbi igény felé megy él, a költség a távolság. Ezt az O(N²) élt ne tárold: oszd fel az elemeket idő szerint (CDQ); egy csomópontban a bal fél a forrás, a jobb fél a cél, és hely szerint rendezve a költség két félegyenes: E − x_forrás (jobbra lévő célhoz) és E + x_forrás (balra lévőhöz). Egy csomópont láncához szegmensfát tarts: a forrás tartományokra ad minimum-címkét (lusta módon, a címkében a forrás azonosítójával), a levelek a még le nem zárt célok, a gyökér adja a legkisebb kulcsú célt; a láncok legjobbjait közös prioritási sor kezeli. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = LLONG_MAX / 4, INFH = INF / 2;

// Elemek: 1..M a csapatok (idő 0), M+1..M+N az igények időrendben. X[i] az i. elem helye.
int K, M, N, L, LV;
vector<ll> X;

// ---- 1. Idő szerinti felezés (CDQ): minden szinten a csomópont elemei hely szerint rendezve ----
vector<vector<int>> seqL, whereL, loL, hiL;     // rendezett sorrend, hely a szinten, a csomópont szélei
vector<vector<char>> leftL;                     // a csomópont bal (forrás) vagy jobb (cél) felében van-e
void build(int lo, int hi, int lv) {
    if (lo == hi) {
        seqL[lv][lo - 1] = lo; whereL[lv][lo] = lo - 1; loL[lv][lo - 1] = hiL[lv][lo - 1] = lo - 1;
        return;
    }
    int mid = (lo + hi) / 2;
    build(lo, mid, lv + 1); build(mid + 1, hi, lv + 1);
    merge(seqL[lv + 1].begin() + lo - 1, seqL[lv + 1].begin() + mid, seqL[lv + 1].begin() + mid, seqL[lv + 1].begin() + hi,
          seqL[lv].begin() + lo - 1, [](int a, int b) { return X[a] < X[b]; });
    for (int g = lo - 1; g < hi; g++) {
        int k = seqL[lv][g];
        whereL[lv][k] = g; loL[lv][g] = lo - 1; hiL[lv][g] = hi - 1; leftL[lv][g] = (k <= mid);
    }
}

// ---- 2. Szegmensfa lusta címkékkel egy lánchoz ----
// Egy cél kulcsa min(tu + a, td + b), ahol a = X - pi, b = -X - pi a cél saját értéke (pi: potenciál),
// tu / td pedig a forrásoktól kapott címke (E - x_forrás, illetve E + x_forrás); su / sd a címkét adó forrás.
struct Node { ll a, b, tu, td, best; int su, sd; };
ll UB;      // a T csúcs kulcsának felső korlátja: ennél nagyobb kulcsok már nem számítanak
inline void apply(Node *t, int v, ll val, int src, int type) {
    ll z = val + (type == 0 ? t[v].a : t[v].b);
    if (z >= UB) return;
    if (type == 0) { if (val < t[v].tu) { t[v].tu = val; t[v].su = src; } }
    else { if (val < t[v].td) { t[v].td = val; t[v].sd = src; } }
    for (int u = v; u >= 1 && z < t[u].best; u >>= 1) t[u].best = z;
}
void rangeChmin(Node *t, int s, int l, int r, ll val, int type, int src) {      // [l, r] helyi indexek
    for (int lo = l + s, hi = r + s + 1; lo < hi; lo >>= 1, hi >>= 1) {
        if (lo & 1) apply(t, lo++, val, src, type);
        if (hi & 1) apply(t, --hi, val, src, type);
    }
}
void removeLeaf(Node *t, int s, int idx) {          // a lezárt cél kivétele a fából
    int v = s + idx;
    t[v].a = t[v].b = t[v].best = INF;
    for (v >>= 1; v >= 1; v >>= 1) {
        Node &n = t[v];
        ll na = min(t[2 * v].a, t[2 * v + 1].a), nb = min(t[2 * v].b, t[2 * v + 1].b);
        ll r = min(n.tu + na, n.td + nb);
        r = min(r, min(t[2 * v].best, t[2 * v + 1].best));
        if (na == n.a && nb == n.b && r == n.best) break;
        n.a = na; n.b = nb; n.best = r;
    }
}
int argmin(Node *t, int s, int &src) {              // a legkisebb kulcsú levél és a kulcsot adó forrás
    int v = 1;
    ll best = t[1].best;
    while (v < s) {
        Node &n = t[v];
        if (n.tu + n.a == best) { src = n.su; while (v < s) v = t[2 * v].a <= t[2 * v + 1].a ? 2 * v : 2 * v + 1; return v - s; }
        if (n.td + n.b == best) { src = n.sd; while (v < s) v = t[2 * v].b <= t[2 * v + 1].b ? 2 * v : 2 * v + 1; return v - s; }
        v = t[2 * v].best == best ? 2 * v : 2 * v + 1;
    }
    src = t[v].tu + t[v].a == best ? t[v].su : t[v].sd;
    return v - s;
}

int main() {
    if (scanf("%d %d %d", &K, &M, &N) != 3) return 0;
    vector<ll> P(K + 1);
    for (int c = 1; c <= K; c++) if (scanf("%lld", &P[c]) != 1) return 0;
    L = M + N;
    X.assign(L + 1, 0);
    for (int s = 1; s <= M; s++) { int c; if (scanf("%d", &c) != 1) return 0; X[s] = P[c]; }
    for (int k = 1; k <= N; k++) { int c; if (scanf("%d", &c) != 1) return 0; X[M + k] = P[c]; }
    ll range = *max_element(P.begin() + 1, P.end()) - *min_element(P.begin() + 1, P.end());
    ll BIG = (ll)(N + 1) * (range + 1);     // minden igény lefedésének "jutalma" (nagyobb bármely útköltségnél)

    LV = 2;
    for (int sz = L; sz > 1; sz = (sz + 1) / 2) LV++;
    seqL.assign(LV, vector<int>(L, 0)); whereL.assign(LV, vector<int>(L + 1, -1));
    loL.assign(LV, vector<int>(L, 0)); hiL.assign(LV, vector<int>(L, 0)); leftL.assign(LV, vector<char>(L, 0));
    build(1, L, 0);

    // láncok: minden szint minden legalább 2 elemű csomópontja; a fák egy közös tömbben vannak
    vector<int> chBase, chS, chLo, chLv;
    vector<vector<int>> chainAt(LV, vector<int>(L, -1));
    int total = 0;
    for (int lv = 0; lv < LV; lv++)
        for (int i = 0; i < L;) {
            if (seqL[lv][i] == 0) { i++; continue; }
            int lo = i, hi = hiL[lv][i], s = hi - lo + 1;
            i = hi + 1;
            if (s < 2) continue;
            for (int g = lo; g <= hi; g++) chainAt[lv][g] = chBase.size();
            chBase.push_back(total); chS.push_back(s); chLo.push_back(lo); chLv.push_back(lv);
            total += 2 * s;
        }
    int C = chBase.size();
    vector<Node> nodes(total);
    // minden elemhez: melyik láncokban szerepel forrásként (srcE) illetve célként (tgtE), és milyen helyi indexszel
    struct Ent { int ch, t; };
    vector<Ent> srcE, tgtE;
    vector<int> srcS(L + 2, 0), tgtS(L + 2, 0);
    for (int k = 1; k <= L; k++) {
        srcS[k] = srcE.size(); tgtS[k] = tgtE.size();
        for (int lv = 0; lv < LV; lv++) {
            int w = whereL[lv][k];
            if (w < 0 || chainAt[lv][w] < 0) continue;
            int ch = chainAt[lv][w];
            if (leftL[lv][w]) srcE.push_back({ch, w - chLo[ch]});
            else if (k > M) tgtE.push_back({ch, w - chLo[ch]});
        }
    }
    srcS[L + 1] = srcE.size(); tgtS[L + 1] = tgtE.size();

    // ---- 3. Kezdeti megoldás: egyetlen csapat (az első igényhez legközelebbi) kiszolgál mindent ----
    vector<int> pred(L + 1, 0), succ(L + 1, 0);     // pred[b]: b előző eleme (csapat vagy igény), succ[p]: a p utáni igény
    {
        int best = 1;
        for (int s = 2; s <= M; s++) if (llabs(X[s] - X[M + 1]) < llabs(X[best] - X[M + 1])) best = s;
        pred[M + 1] = best; succ[best] = M + 1;
        for (int k = 2; k <= N; k++) { pred[M + k] = M + k - 1; succ[M + k - 1] = M + k; }
    }
    // Kezdeti potenciálok: az egyetlen út a legolcsóbb S-T út (a -BIG élek miatt minden igényt érint)
    vector<ll> piIn(L + 1, 0), piOut(L + 1, 0);
    ll piT;
    {
        ll c = llabs(X[pred[M + 1]] - X[M + 1]);
        for (int k = 1; k <= N; k++) {
            if (k > 1) c += llabs(X[M + k] - X[M + k - 1]);
            piIn[M + k] = -(ll)(k - 1) * BIG + c; piOut[M + k] = -(ll)k * BIG + c;
        }
        piT = piOut[L];
    }
    int usedCnt = 1;
    vector<char> settled(L + 1, 0);
    vector<int> par(L + 1, 0);                      // a lezárt igény szülője: a kulcsot adó forrás
    vector<ll> dkey(L + 1), Eout(L + 1);
    vector<ll> pushedKey(C + 1, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    while (usedCnt < M) {
        // a fák felépítése az aktuális potenciálokkal
        for (int ch = 0; ch < C; ch++) {
            Node *t = &nodes[chBase[ch]];
            int s = chS[ch], lv = chLv[ch];
            for (int i = 0; i < s; i++) {
                int g = chLo[ch] + i, k = seqL[lv][g];
                Node &n = t[s + i];
                n.tu = n.td = n.best = INF; n.su = n.sd = 0;
                if (!leftL[lv][g] && k > M) { n.a = X[k] - piIn[k]; n.b = -X[k] - piIn[k]; }
                else n.a = n.b = INF;
            }
            for (int v = s - 1; v >= 1; v--) {
                Node &n = t[v];
                n.a = min(t[2 * v].a, t[2 * v + 1].a); n.b = min(t[2 * v].b, t[2 * v + 1].b);
                n.tu = n.td = n.best = INF; n.su = n.sd = 0;
            }
        }
        fill(settled.begin(), settled.end(), 0);
        fill(pushedKey.begin(), pushedKey.end(), INF);
        while (!pq.empty()) pq.pop();
        ll DT = INF; int parT = 0; UB = INF;
        auto chainBest = [&](int ch) { return nodes[chBase[ch] + 1].best; };
        auto schedule = [&](int ch) {               // a lánc legjobb jelöltjének (újra)beírása a sorba
            ll nb = chainBest(ch);
            if (nb < INFH && nb < pushedKey[ch]) { pushedKey[ch] = nb; pq.push({nb, ch}); }
        };
        // a p elem forrásként: E a p kimeneti távolsága; minden láncában két félegyenes-címkét kap
        auto addSource = [&](int p, ll E) {
            Eout[p] = E;
            ll vu = E - X[p], vd = E + X[p];
            for (int ei = srcS[p]; ei < srcS[p + 1]; ei++) {
                const Ent &e = srcE[ei];
                Node *t = &nodes[chBase[e.ch]];
                int s = chS[e.ch];
                bool ch = false;
                if (t[1].a < INFH && vu + t[1].a < UB) { rangeChmin(t, s, e.t, s - 1, vu, 0, p); ch = true; }
                if (t[1].b < INFH && vd + t[1].b < UB) { rangeChmin(t, s, 0, e.t, vd, 1, p); ch = true; }
                if (ch) schedule(e.ch);
            }
        };
        for (int s = 1; s <= M; s++) if (!succ[s]) addSource(s, 0);      // szabad csapatok: távolság 0
        bool reached = false; ll kappa = 0;
        while (!pq.empty()) {
            auto [key, ch] = pq.top(); pq.pop();
            if (ch == C) {                          // a T csúcs
                if (key != DT - piT) continue;
                reached = true; kappa = key; break;
            }
            if (key != pushedKey[ch]) continue;
            if (key != chainBest(ch)) {             // időközben törölt levél miatt elavult bejegyzés
                ll nb = chainBest(ch);
                pushedKey[ch] = nb < INFH ? nb : INF;
                if (nb < INFH) pq.push({nb, ch});
                continue;
            }
            Node *t = &nodes[chBase[ch]];
            int s = chS[ch], src;
            int idx = argmin(t, s, src);
            int j = seqL[chLv[ch]][chLo[ch] + idx];
            settled[j] = 1; dkey[j] = key; par[j] = src;
            ll D = key + piIn[j];                   // j (igazi) távolsága az új csapattól
            for (int ei = tgtS[j]; ei < tgtS[j + 1]; ei++) removeLeaf(&nodes[chBase[tgtE[ei].ch]], chS[tgtE[ei].ch], tgtE[ei].t);
            { ll nb = chainBest(ch); pushedKey[ch] = nb < INFH ? nb : INF; if (nb < INFH) pq.push({nb, ch}); }
            // j-t elvesszük az előző gazdájától (p); p innentől új igény felé mehet vagy ott véget ér az útja
            int p = pred[j];
            ll E = D - llabs(X[p] - X[j]);
            if (p > M && E < DT) { DT = E; parT = p; UB = DT - piT; pq.push({UB, C}); }
            addSource(p, E);
        }
        if (!reached || DT >= 0) break;
        // potenciálok frissítése (a le nem zárt csúcsok kappa-val nőnek)
        for (int k = M + 1; k <= L; k++) piIn[k] += settled[k] ? min(dkey[k], kappa) : kappa;
        for (int p = 1; p <= L; p++) {
            bool seen = succ[p] ? settled[succ[p]] : p <= M;
            piOut[p] += seen ? min(Eout[p] - piOut[p], kappa) : kappa;
        }
        piT += kappa;
        // a javító út alkalmazása: parT lemond az útvonaláról, minden érintett igény új előzője a címkét adó forrás
        vector<int> bl, oldp;
        for (int cur = parT;;) {
            int b = succ[cur];
            bl.push_back(b); oldp.push_back(cur);
            cur = par[b];
            if (cur <= M && !succ[cur]) break;      // szabad csapat: itt kezdődik az út
        }
        vector<int> newp(bl.size());
        for (size_t i = 0; i < bl.size(); i++) newp[i] = par[bl[i]];
        for (size_t i = 0; i < bl.size(); i++) succ[oldp[i]] = 0;
        for (size_t i = 0; i < bl.size(); i++) { succ[newp[i]] = bl[i]; pred[bl[i]] = newp[i]; }
        usedCnt++;
    }
    vector<int> teamOf(L + 1, 0);
    ll cost = 0;
    for (int k = M + 1; k <= L; k++) {
        teamOf[k] = pred[k] <= M ? pred[k] : teamOf[pred[k]];
        cost += llabs(X[pred[k]] - X[k]);
    }
    printf("%lld\n", cost);
    for (int k = 1; k <= N; k++) printf("%d%c", teamOf[M + k], k < N ? ' ' : '\n');
    return 0;
}
