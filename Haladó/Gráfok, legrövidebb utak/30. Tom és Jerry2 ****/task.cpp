/*
Megoldás lényege:
Tom akkor kapja el Jerryt biztosan, ha van olyan csomópont X, amelyet Jerry minden, a lyukba vezető útján érint, és Tom hamarabb (vagy egyszerre) ér oda, mint Jerry. Az X elválasztó csúcs a Jerry-kezdőponttól az egérlyukig vezető utakat metszi, ezért a blokk-vágópont-fa (az egérlyukból gyökerezve) felső részén található. Tom távolságát BFS-sel számoljuk a 2 szélességű éleken, az egérlyukat kihagyva. Jerry távolsága egy X csúcshoz a Jerry-kezdőpont blokkjában lévő rövid utakból adódik: egy blokkon belül a felső csúcstól mért távolságokat BFS-sel kapjuk meg, és így az út hosszai összeadhatók. A lekérdezésekhez a szülő-láncon egy előre számolt minimumot tartunk nyilván. Az időigény O(N + M + DB).
*/
/*
Hint 1: || Melyik csomópontokon kell Jerrynek mindenképpen átmennie, ha az egérlyukba akar jutni? Ezek az elválasztó (vágó) csúcsok, és a Jerry-kezdőponttól az egérlyukig vezető úton találhatók. ||
Hint 2: || Egy X csúcsra Tom akkor ér oda előbb, ha a Tom-távolsága (csak 2 szélességű élen, az egérlyukat kihagyva) nem nagyobb, mint Jerry távolsága X-ig. Jerry távolságát érdemes a blokkokra bontott gráfban számolni: a blokkon belül a felső csúcstól mért távolságok összeadhatók. ||
Hint 3: || Egy Jerry-kezdőpontra elég az egérlyuk felé először elérhető vágópontokat vizsgálni egy láncban, ahol a lánc előre számolt prefix-összegekkel és minimumokkal kiértékelhető. Egy X csúcs kulcsa a Tom-távolság és az X-ig vezető lánc összege; ennek minimumát szülő-láncon haladva tartsd nyilván. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

int n, m, t, db, e;
vector<int> eu, ev, ew;           // élek végpontjai és szélessége
vector<vector<int>> adj;          // csúcsonként az élek sorszámai
vector<int> disc, low_, treeChild, order_, estk;
int timer_ = 0;
vector<int> P, up;               // P[v]: v tartalmazó blokkjának felső csúcsa, up[v]: v és P[v] távolsága ebben a blokkban
vector<vector<int>> ladj;        // blokkon belüli szomszédság (ideiglenes)
vector<int> bd;                  // blokkon belüli BFS-távolság (ideiglenes)

// Egy blokk feldolgozása: a felső csúcstól BFS-sel megkapjuk a távolságokat a blokkon belül.
void processBlock(int top, const vector<int>& block) {
    for (int id : block) {
        ladj[eu[id]].push_back(ev[id]);
        ladj[ev[id]].push_back(eu[id]);
    }
    queue<int> q;
    bd[top] = 0;
    q.push(top);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int y : ladj[x])
            if (bd[y] < 0) {
                bd[y] = bd[x] + 1;
                q.push(y);
            }
    }
    for (int id : block) {
        int c = treeChild[id];
        if (c != -1) {
            P[c] = top;
            up[c] = bd[c];
        }
    }
    for (int id : block) {
        for (int x : {eu[id], ev[id]}) {
            ladj[x].clear();
            bd[x] = -1;
        }
    }
}

// Tarjan-féle DFS, a gyökér az egérlyuk. Az élverem segítségével a blokkokat kapjuk meg.
void dfs(int u, int pe) {
    disc[u] = low_[u] = ++timer_;
    order_.push_back(u);
    for (int id : adj[u]) {
        if (id == pe) continue;
        int v = eu[id] ^ ev[id] ^ u;
        if (disc[v] == 0) {
            estk.push_back(id);
            treeChild[id] = v;
            dfs(v, id);
            low_[u] = min(low_[u], low_[v]);
            if (low_[v] >= disc[u]) {
                vector<int> block;
                int x;
                do {
                    x = estk.back();
                    estk.pop_back();
                    block.push_back(x);
                } while (x != id);
                processBlock(u, block);
            }
        } else if (disc[v] < disc[u]) {
            estk.push_back(id);
            low_[u] = min(low_[u], disc[v]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> t >> db >> e;
    eu.resize(m);
    ev.resize(m);
    ew.resize(m);
    adj.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        cin >> eu[i] >> ev[i] >> ew[i];
        adj[eu[i]].push_back(i);
        adj[ev[i]].push_back(i);
    }
    vector<int> js(db);
    for (int &j : js) cin >> j;

    // Tom távolsága: csak 2 szélességű élen halad, az egérlyukba nem léphet.
    vector<int> dT(n + 1, INF);
    if (t != e) {
        queue<int> q;
        dT[t] = 0;
        q.push(t);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int id : adj[x]) {
                if (ew[id] != 2) continue;
                int y = eu[id] ^ ev[id] ^ x;
                if (y == e || dT[y] != INF) continue;
                dT[y] = dT[x] + 1;
                q.push(y);
            }
        }
    }

    disc.assign(n + 1, 0);
    low_.assign(n + 1, 0);
    treeChild.assign(m, -1);
    P.assign(n + 1, -1);
    up.assign(n + 1, 0);
    ladj.assign(n + 1, {});
    bd.assign(n + 1, -1);
    dfs(e, -1);

    // W(v): a v-ből az egérlyukig vezető lánc blokkjainak távolságainak összege.
    // best[v]: a v és ősei (az egérlyukat kivéve) közül a legkisebb kulcs és annak csúcsa,
    // ahol a kulcs = Tom távolsága + W(X).
    vector<int> wsum(n + 1, 0), best(n + 1, INF), bestNode(n + 1, 0);
    for (int v : order_) {
        if (v == e) continue;
        int p = P[v];
        wsum[v] = up[v] + wsum[p];
        int key = dT[v] >= INF ? INF : dT[v] + wsum[v];
        best[v] = best[p];
        bestNode[v] = bestNode[p];
        if (key < best[v]) {
            best[v] = key;
            bestNode[v] = v;
        }
    }

    for (int j : js) {
        int ans = 0;
        if (j != e && disc[j] != 0) {
            int x1 = P[j];
            // Jerry távolsága x1-hez: up[j]; d_J(X) = aJ - W(X), ahol aJ = up[j] + W(x1).
            int aJ = up[j] + wsum[x1];
            if (best[x1] <= aJ) ans = bestNode[x1];
        }
        cout << ans << '\n';
    }
    return 0;
}
