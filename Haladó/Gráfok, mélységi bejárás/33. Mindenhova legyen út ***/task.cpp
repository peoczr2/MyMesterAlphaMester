/*
Megoldás lényege:
A gráf erősen összefüggő komponenseit Tarjan-algoritmussal határozzuk meg, iteratívan, majd a komponensekből álló kondenzált gráfot vizsgáljuk. Egy komponens forrás, ha nincs bele él más komponensből; ilyen komponensbe kívülről nem lehet eljutni, ezért minden forrásnak kell egy új bejövő él, kivéve azt, amelyikben az r pont van. Így K legalább (a források száma − 1). Ez elérhető: r-t egy forrásból választjuk, a többi forrás egy-egy pontját pedig láncba fűzzük (r → s1 → s2 → …), így r minden komponensbe eljut, mert a kondenzált gráf minden komponense valamelyik forrásból elérhető. Az időigény O(N + M).
*/
/*
Hint 1: || Egy komponensbe, amelybe nem vezet él másik komponensből, kívülről nem lehet eljutni. Ezért az ilyen komponensek mindegyikéhez kell új bejövő él, kivéve azt, amelyikben r van. ||
Hint 2: || Az erősen összefüggő komponenseket Tarjan-algoritmussal keresd meg, majd nézd meg, melyik komponensbe nem fut be él másik komponensből. A szükséges új élek száma ezek számánál eggyel kevesebb. ||
Hint 3: || Válassz r-t az egyik ilyen komponensből, a többi ilyen komponens egy-egy pontját pedig fűzd láncba: az előző pont (kezdetben r) és a következő komponens pontja közé vegyél fel új élt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    vector<pair<int, int>> edges(m);
    for (auto &[u, v] : edges) {
        cin >> u >> v;
        g[u].push_back(v);
    }

    // Tarjan-algoritmus, iteratív változatban; a komponensek a befejezés sorrendjében kapnak sorszámot
    vector<int> idx(n + 1, 0), low(n + 1, 0), it(n + 1, 0), comp(n + 1, -1);
    vector<char> onStack(n + 1, 0);
    vector<int> stk;
    int timer = 0, compCnt = 0;
    for (int s = 1; s <= n; ++s) {
        if (idx[s]) continue;
        vector<int> call{s};
        idx[s] = low[s] = ++timer;
        stk.push_back(s);
        onStack[s] = 1;
        while (!call.empty()) {
            int v = call.back();
            if (it[v] < (int)g[v].size()) {
                int w = g[v][it[v]++];
                if (!idx[w]) {
                    idx[w] = low[w] = ++timer;
                    stk.push_back(w);
                    onStack[w] = 1;
                    call.push_back(w);
                } else if (onStack[w]) {
                    low[v] = min(low[v], idx[w]);
                }
            } else {
                call.pop_back();
                if (!call.empty()) low[call.back()] = min(low[call.back()], low[v]);
                if (low[v] == idx[v]) {
                    int w;
                    do {
                        w = stk.back();
                        stk.pop_back();
                        onStack[w] = 0;
                        comp[w] = compCnt;
                    } while (w != v);
                    ++compCnt;
                }
            }
        }
    }

    // Forrás komponens: nincs bele él másik komponensből
    vector<char> hasIn(compCnt, 0);
    for (auto [u, v] : edges)
        if (comp[u] != comp[v]) hasIn[comp[v]] = 1;

    vector<int> rep(compCnt, INT_MAX);
    for (int v = 1; v <= n; ++v) rep[comp[v]] = min(rep[comp[v]], v);

    // A forrásokat a befejezés sorrendjének fordítottjában dolgozzuk fel
    vector<int> sources;
    for (int c = compCnt - 1; c >= 0; --c)
        if (!hasIn[c]) sources.push_back(c);

    // r az első forrás; a többi forrás egy-egy pontját láncba fűzzük r-ből kiindulva
    int r = rep[sources[0]];
    vector<pair<int, int>> added;
    int prev = r;
    for (size_t i = 1; i < sources.size(); ++i) {
        int x = rep[sources[i]];
        added.push_back({prev, x});
        prev = x;
    }

    cout << added.size() << "\n" << r << "\n";
    for (auto [a, b] : added) cout << a << ' ' << b << "\n";
    return 0;
}
