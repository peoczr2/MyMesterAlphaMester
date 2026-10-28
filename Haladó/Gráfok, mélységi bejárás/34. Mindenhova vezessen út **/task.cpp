/*
Megoldás lényege:
A gráf erősen összefüggő komponenseit Tarjan-algoritmussal határozzuk meg, iteratívan, majd a komponensekből álló kondenzált gráfot vizsgáljuk. Egy komponens nyelő, ha nincs belőle él másik komponensbe; ilyenből nem lehet kijutni, ezért minden nyelő komponensből kell egy új kimenő él, kivéve azt, amelyikben az R pont van. Így K legalább (a nyelők száma − 1). Ez elérhető: R-t egy nyelő komponensből választjuk, a többi nyelő komponens egy-egy pontjából pedig új élt húzunk az előző lánctagba (kezdetben R-be). Így minden komponens eljut R-be, mert a kondenzált gráf minden komponense valamelyik nyelőbe eljut. Az időigény O(N + M).
*/
/*
Hint 1: || Egy komponensből, amelyből nem vezet él másik komponensbe, nem lehet kijutni. Ezért minden ilyen komponensből kell egy új kimenő él, kivéve azt, amelyikben R van. ||
Hint 2: || Az erősen összefüggő komponenseket Tarjan-algoritmussal keresd meg, majd számold meg a kifelé élt nem tartalmazó komponenseket. Ha ezek száma s, a válasz s − 1; R-t az egyik ilyen komponensből válaszd, a többi komponens egy-egy pontjából pedig fűzz láncot R felé. ||
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

    // Nyelő komponens: nincs belőle él másik komponensbe
    vector<char> hasOut(compCnt, 0);
    for (auto [u, v] : edges)
        if (comp[u] != comp[v]) hasOut[comp[u]] = 1;

    vector<int> rep(compCnt, INT_MAX);
    for (int v = 1; v <= n; ++v) rep[comp[v]] = min(rep[comp[v]], v);

    // A nyelőket a befejezés sorrendjének fordítottjában dolgozzuk fel
    vector<int> sinks;
    for (int c = compCnt - 1; c >= 0; --c)
        if (!hasOut[c]) sinks.push_back(c);

    // R az első nyelő; a többi nyelő egy-egy pontjából új él vezet az előző lánctagba
    int R = rep[sinks[0]];
    vector<pair<int, int>> added;
    int prev = R;
    for (size_t i = 1; i < sinks.size(); ++i) {
        int x = rep[sinks[i]];
        added.push_back({x, prev});
        prev = x;
    }

    cout << added.size() << "\n" << R << "\n";
    for (auto [a, b] : added) cout << a << ' ' << b << "\n";
    return 0;
}
