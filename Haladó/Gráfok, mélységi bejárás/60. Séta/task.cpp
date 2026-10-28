/*
Megoldás lényege:
Ha egy erősen összefüggő részbe (ahol bármely kereszteződésből bármelyik másikba el lehet jutni) egyszer belépünk, a benne lévő összes kereszteződést be tudjuk járni, és onnan bármelyik kivezető utcán kiléphetünk. Ezért nem a csúcsokat, hanem az erősen összefüggő komponenseket kell figyelembe venni: a feladat a komponensek körmentes gráfjában (DAG) az A komponensből a B komponensbe vezető olyan út keresése, amelyen a komponensek méretének összege a legnagyobb. Az erősen összefüggő komponenseket iteratív Tarjan-algoritmussal találjuk meg (így nincs mélyrekurzió), a komponensek ilyenkor fordított topologikus sorrendben keletkeznek, ezért a DP-t a fordított sorrendben végezzük. Az időigény O(N+M).
*/
/*
Hint 1: || Ha egy erősen összefüggő részbe egyszer belépünk, onnan bármely csúcsba el lehet jutni, és onnan vissza is. Ezért a részben lévő összes kereszteződést érinthetjük, így komponenseket kell számolnunk, nem csúcsokat. ||
Hint 2: || Az erősen összefüggő komponensek Tarjan-algoritmussal találhatók meg. A komponensek közötti élek körmentes gráfot adnak, egy komponens súlya a benne lévő csúcsok száma. ||
Hint 3: || Topologikus sorrendben haladva tartsd nyilván minden komponensre a sétából eddig elérhető legnagyobb súlyösszeget, de csak az A komponensből elérhető komponensekből terjeszd tovább az értéket. A B komponens értéke adja a választ. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<int> eu(m), ev(m), start(n + 2, 0);
    for (int i = 0; i < m; ++i) {
        cin >> eu[i] >> ev[i];
        start[eu[i] + 1]++;
    }
    for (int v = 1; v <= n + 1; ++v) start[v] += start[v - 1];
    vector<int> adj(m);
    {
        vector<int> pos(start);
        for (int i = 0; i < m; ++i) adj[pos[eu[i]]++] = ev[i];
    }

    // Tarjan-algoritmus iteratívan. A komponensek befejezési sorrendben keletkeznek,
    // az order vektorban a csúcsok komponensenként, egymás után szerepelnek.
    vector<int> idx(n + 1, 0), low(n + 1, 0), comp(n + 1, -1), it(n + 1, 0);
    vector<char> onStack(n + 1, 0);
    vector<int> stk, call, order;
    int timer = 0, compCnt = 0;
    for (int s = 1; s <= n; ++s) {
        if (idx[s]) continue;
        idx[s] = low[s] = ++timer;
        it[s] = start[s];
        stk.push_back(s);
        onStack[s] = 1;
        call.push_back(s);
        while (!call.empty()) {
            int v = call.back();
            if (it[v] < start[v + 1]) {
                int to = adj[it[v]++];
                if (!idx[to]) {
                    idx[to] = low[to] = ++timer;
                    it[to] = start[to];
                    stk.push_back(to);
                    onStack[to] = 1;
                    call.push_back(to);
                } else if (onStack[to]) {
                    low[v] = min(low[v], idx[to]);
                }
            } else {
                if (low[v] == idx[v]) {
                    while (true) {
                        int w = stk.back();
                        stk.pop_back();
                        onStack[w] = 0;
                        comp[w] = compCnt;
                        order.push_back(w);
                        if (w == v) break;
                    }
                    ++compCnt;
                }
                call.pop_back();
                if (!call.empty()) low[call.back()] = min(low[call.back()], low[v]);
            }
        }
    }

    vector<int> sz(compCnt, 0);
    for (int v = 1; v <= n; ++v) sz[comp[v]]++;

    // dp[c]: az A-ból a c komponensbe vezető utakon a komponensek méretének legnagyobb összege
    vector<int> dp(compCnt, -1);
    dp[comp[a]] = sz[comp[a]];
    // A komponensek topologikus sorrendje: a befejezési sorrend fordítottja
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        int cu = comp[u];
        if (dp[cu] < 0) continue;
        for (int e = start[u]; e < start[u + 1]; ++e) {
            int cv = comp[adj[e]];
            if (cv != cu) dp[cv] = max(dp[cv], dp[cu] + sz[cv]);
        }
    }

    cout << dp[comp[b]] << '\n';
    return 0;
}
