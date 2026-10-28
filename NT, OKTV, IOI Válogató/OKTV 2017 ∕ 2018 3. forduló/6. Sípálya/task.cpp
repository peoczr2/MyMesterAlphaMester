/*
Megoldás lényege:
Az ellenőrök az 1-es pontból (start) az N-esbe (cél) tartó utak, és minden pályaszakaszt legalább egy útnak át kell fognia. Ez alsó korlátos minimális folyam feladat: a forrás az 1-es pont, a nyelő az N-es, minden élen legalább 1 egység folyjon. A pálya gráfja körmentes, mert az élek mindig lefelé mutatnak, ezért minden egész folyam felbontható utakra, és minden út egy ellenőrnek felel meg. A minimumot úgy kapjuk, hogy először megengedett folyamot keresünk egy szuperforrással és szupernyelővel (az N-ből 1-be mutató éllel zárva a kört), majd az N-ből 1-be irányuló maximális folyammal csökkentjük a folyam értékét, az élek alsó korlátját nem sértve. A maximális folyamot push-relabel módszerrel számoljuk, mert az utak hossza akár N is lehet, és az út-alapú módszerek ilyenkor túl lassúak.
*/
/*
Hint 1: || Az ellenőrök útjai az 1-es pontból az N-esbe vezetnek, és minden pályaszakaszt legalább egyszer be kell járniuk. Keress olyan folyamot, amelyben minden élen legalább 1 egység folyik, és a folyam értéke a lehető legkisebb. ||
Hint 2: || Először minden élre küldj előre 1 egységet. Így minden csúcsnak lesz egyenlege: a bejövő élek számából levonva a kimenő élek számát. A pozitív egyenlegű csúcsokat egy szuperforrásból, a negatívakat egy szupernyelőbe kösd, az N-ből 1-be mutató éllel együtt. ||
Hint 3: || A szuperforrásból a szupernyelőbe menő maximális folyam pótolja a hiányt, így megengedett folyamot kapsz. Ezután töröld az N-ből 1-be mutató élt, és az N-ből 1-be keress maximális folyamot a maradék hálózatban. A kezdeti folyamértékből ezt a visszavont mennyiséget vond le. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

// Push-relabel maximális folyam (FIFO sorral, globális címkefrissítéssel).
// Minden hívás a hálózat aktuális maradék kapacitásain indul.
struct MaxFlow {
    struct Edge {
        int to, rev, cap;
    };
    int n;
    vector<vector<Edge>> g;
    vector<long long> ex;
    vector<int> h, cur;

    explicit MaxFlow(int nodes) : n(nodes), g(nodes), ex(nodes), h(nodes), cur(nodes) {}

    // Visszaadja az él indexét a g[u] listában.
    int addEdge(int u, int v, int cap) {
        g[u].push_back({v, (int)g[v].size(), cap});
        g[v].push_back({u, (int)g[u].size() - 1, 0});
        return (int)g[u].size() - 1;
    }

    // Távolság a nyelőtől (BFS a maradék hálózat fordítottján). A nyelőhöz nem elérhető
    // csúcsok címkéje n, a forrás címkéje n.
    void globalRelabel(int s, int t) {
        fill(h.begin(), h.end(), n);
        h[t] = 0;
        queue<int> q;
        q.push(t);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (const Edge& e : g[x]) {
                int y = e.to;
                if (y != s && h[y] == n && g[y][e.rev].cap > 0) {
                    h[y] = h[x] + 1;
                    q.push(y);
                }
            }
        }
        h[s] = n;
    }

    long long maxflow(int s, int t) {
        fill(ex.begin(), ex.end(), 0);
        globalRelabel(s, t);
        fill(cur.begin(), cur.end(), 0);

        vector<char> inq(n, 0);
        queue<int> act;
        for (Edge& e : g[s]) {
            if (e.cap <= 0) continue;
            int d = e.cap;
            e.cap -= d;
            g[e.to][e.rev].cap += d;
            ex[e.to] += d;
            ex[s] -= d;
            if (e.to != s && e.to != t && !inq[e.to]) {
                inq[e.to] = 1;
                act.push(e.to);
            }
        }

        int relabels = 0;
        while (!act.empty()) {
            int v = act.front();
            act.pop();
            inq[v] = 0;
            while (ex[v] > 0) {
                if (cur[v] == (int)g[v].size()) {
                    // Átcímkézés: a legkisebb olyan szomszéd címkéje, amelyre van maradék él, plusz 1.
                    int best = 2 * n;
                    for (const Edge& e : g[v]) {
                        if (e.cap > 0) best = min(best, h[e.to] + 1);
                    }
                    h[v] = best;
                    cur[v] = 0;
                    ++relabels;
                } else {
                    Edge& e = g[v][cur[v]];
                    if (e.cap > 0 && h[v] == h[e.to] + 1) {
                        int d = (int)min(ex[v], (long long)e.cap);
                        e.cap -= d;
                        g[e.to][e.rev].cap += d;
                        ex[v] -= d;
                        ex[e.to] += d;
                        if (e.to != s && e.to != t && !inq[e.to]) {
                            inq[e.to] = 1;
                            act.push(e.to);
                        }
                    } else {
                        ++cur[v];
                    }
                }
            }
            if (relabels > n) {
                // Időnként a címkéket újraszámoljuk a nyelőtől.
                globalRelabel(s, t);
                fill(cur.begin(), cur.end(), 0);
                relabels = 0;
            }
        }
        return ex[t];
    }

    // Kiüríti az élek mindkét irányát a csúcs összes élén (a csúcs kikerül a hálózatból).
    void detach(int v) {
        for (Edge& e : g[v]) {
            e.cap = 0;
            g[e.to][e.rev].cap = 0;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    if (n == 1) {
        // Nincs pályaszakasz, nincs mit bejárni.
        cout << 0 << "\n";
        return 0;
    }

    const int s = 0, t = n - 1;
    const int SS = n, TT = n + 1;
    MaxFlow mf(n + 2);
    vector<long long> excess(n, 0);

    for (int i = 0; i < n - 1; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int v;
            cin >> v;
            --v;
            // Az él alsó korlátja 1: 1 egységet előre küldünk, a többi (INF - 1) szabad.
            mf.addEdge(i, v, INF);
            excess[v] += 1;
            excess[i] -= 1;
        }
    }

    // Cirkuláció: az N-ből 1-be mutató él.
    int backIdx = mf.addEdge(t, s, INF);

    for (int v = 0; v < n; ++v) {
        if (excess[v] > 0) {
            mf.addEdge(SS, v, (int)excess[v]);
        } else if (excess[v] < 0) {
            mf.addEdge(v, TT, (int)(-excess[v]));
        }
    }
    mf.maxflow(SS, TT);
    mf.detach(SS);
    mf.detach(TT);

    // A megengedett folyam értéke: az N->1 élen átfolyó mennyiség.
    long long feasible = INF - mf.g[t][backIdx].cap;

    // Az N->1 élt eltávolítjuk, majd az N-ből 1-be visszafelé csökkentjük a folyamot.
    int revIdx = mf.g[t][backIdx].rev;
    mf.g[t][backIdx].cap = 0;
    mf.g[s][revIdx].cap = 0;
    long long reduce = mf.maxflow(t, s);

    cout << feasible - reduce << "\n";
    return 0;
}
