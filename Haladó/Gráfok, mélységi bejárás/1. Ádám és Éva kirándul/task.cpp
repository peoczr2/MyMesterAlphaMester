/*
Megoldás lényege:
Akkor jó az útvonal, ha van két olyan egyszerű út, amelyek csak Évában találkoznak: az egyik Évától Ádámig, a másik Évától a kirándulási városig vezet. Ezt csúcskapacitásos maximális folyammal keressük: minden várost be- és kimeneti csúcsra bontunk, a csúcs kapacitása 1, így minden város legfeljebb egyszer kerülhet az útba. A forrásból Éva kimenetébe 2 egység folyam indul, a nyelő Ádám és a cél kimenetéből 1–1 egységet vesz fel. Ha a folyam értéke 2, a két útból az Ádám felé tartót megfordítva és az Évától a célig tartóhoz fűzve kapjuk a választ; különben 0. Az élek irányítatlanok, mindkét irányba felvesszük őket. A folyam két BFS-augmentálással O(N+M) időben kiszámítható.
*/
/*
Hint 1: || Két, Éván kívül diszjunkt utat kell találni Évából: egyet Ádám, egyet a kirándulási város felé. Az, hogy minden város legfeljebb egyszer szerepelhet, pontosan a csúcsok kapacitásának felel meg. ||
Hint 2: || Bontsd minden várost két csúcsra (belépés és kilépés, köztük 1 kapacitású él), az irányítatlan utakat mindkét irányban vedd fel, és Éva kilépő csúcsából küldj 2 egység folyamot a nyelőbe. Ádám és a cél kilépő csúcsa egy-egy egységet vesz fel. ||
Hint 3: || A két folyamútból azt, amelyik Ádámnál ér véget, fordítsd meg, és fűzd a másikhoz Éva csúcsánál. Ha a maximális folyam nem 2, nincs megoldás, és egyetlen 0-t kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Arc {
    int to, rev, cap, orig;
};

vector<vector<Arc>> g;

void addArc(int u, int v, int c) {
    g[u].push_back({v, (int)g[v].size(), c, c});
    g[v].push_back({u, (int)g[u].size() - 1, 0, 0});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int a, e, k;
    cin >> a >> e >> k;
    vector<pair<int, int>> edges(m);
    for (auto &p : edges) cin >> p.first >> p.second;

    // A v város belépő csúcsa 2v, kilépő csúcsa 2v+1; a forrás S, a nyelő T.
    int S = 2 * n + 2, T = 2 * n + 3;
    g.assign(2 * n + 4, {});
    auto inN = [](int v) { return 2 * v; };
    auto outN = [](int v) { return 2 * v + 1; };

    for (int v = 1; v <= n; ++v)
        if (v != e) addArc(inN(v), outN(v), 1);
    addArc(S, outN(e), 2);
    addArc(outN(a), T, 1);
    addArc(outN(k), T, 1);
    for (auto &[u, v] : edges) {
        if (v != e) addArc(outN(u), inN(v), 1);
        if (u != e) addArc(outN(v), inN(u), 1);
    }

    // Edmonds-Karp, legfeljebb 2 egységig.
    int flow = 0;
    while (flow < 2) {
        vector<int> pv(g.size(), -1), pe(g.size(), -1);
        vector<char> seen(g.size(), 0);
        queue<int> q;
        q.push(S);
        seen[S] = 1;
        while (!q.empty() && !seen[T]) {
            int x = q.front();
            q.pop();
            for (int i = 0; i < (int)g[x].size(); ++i) {
                const Arc &ar = g[x][i];
                if (ar.cap > 0 && !seen[ar.to]) {
                    seen[ar.to] = 1;
                    pv[ar.to] = x;
                    pe[ar.to] = i;
                    q.push(ar.to);
                }
            }
        }
        if (!seen[T]) break;
        int f = 2 - flow;
        for (int x = T; x != S; x = pv[x]) f = min(f, g[pv[x]][pe[x]].cap);
        for (int x = T; x != S; x = pv[x]) {
            Arc &ar = g[pv[x]][pe[x]];
            ar.cap -= f;
            g[x][ar.rev].cap += f;
        }
        flow += f;
    }

    if (flow < 2) {
        cout << 0 << "\n";
        return 0;
    }

    // A két folyamút visszafejtése Éva kilépő csúcsától: a csúcsok sorrendjét adja.
    // Az elfogyasztott éleket orig = 0-ra állítjuk, hogy a második út ne használja őket.
    auto walk = [&](int startNode) {
        vector<int> path = {e};
        int cur = startNode;
        while (cur != T) {
            if (cur % 2 == 0) {  // belépő csúcs: a belső él (kapacitás 1) mentén a kilépőbe
                cur += 1;
                continue;
            }
            int next = -1;
            for (auto &ar : g[cur]) {
                if (ar.orig > 0 && ar.cap == 0) {
                    ar.orig = 0;
                    next = ar.to;
                    break;
                }
            }
            if (next == -1) return vector<int>();
            if (next != T && next % 2 == 0) path.push_back(next / 2);
            cur = next;
        }
        return path;
    };

    vector<int> p1 = walk(outN(e));
    vector<int> p2 = walk(outN(e));
    if (p1.empty() || p2.empty()) {
        cout << 0 << "\n";
        return 0;
    }
    if (p1.back() != a) swap(p1, p2);  // p1 Ádámnál ér véget

    vector<int> ans(p1.rbegin(), p1.rend());  // Ádámtól Évához
    for (size_t i = 1; i < p2.size(); ++i) ans.push_back(p2[i]);  // Évától a célig

    for (size_t i = 0; i < ans.size(); ++i) cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
    return 0;
}
