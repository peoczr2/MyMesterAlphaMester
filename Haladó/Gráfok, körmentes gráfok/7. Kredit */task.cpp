/*
Megoldás lényege:
Az előfeltételek irányított körmentes gráfot adnak, a tárgyakat topologikus sorrendben dolgozzuk fel. Minden tárgy
legkorábbi félévét (ES) az előfeltételeinek legkorábbi félévei határozzák meg: a tárgy legalább eggyel később vehető
fel, mint bármelyik előfeltétele. A minimális elvégzési idő a legkorábbi félévek maximuma. Ezután fordított
sorrendben kiszámoljuk minden tárgy legkésőbbi félévét (LS), ami a minimális idő betartásával még felvehető: ez a
rákövetkező tárgyak LS értékéből 1-gyel kevesebb minimuma, az utolsó tárgyaknál pedig a teljes félévszám. Pontosan
azok a tárgyak csak egy félévben vehetők fel, amelyekre ES = LS. Ezeket ábécé-sorrendben írjuk ki. Az időigény
O(N + M + N log N).
*/
/*
Hint 1: || Egy tárgy legkorábbi félévét az előfeltételei határozzák meg: ha az előfeltétel X. félévben van, a tárgy legkorábban az (X+1). félévben vehető fel. ||
Hint 2: || A minimális félévszám a legkorábbi félévek maximuma. Fordítva végigmenve minden tárgy legkésőbbi félévét a rákövetkező tárgyak legkésőbbi félévéből 1-gyel kevesebb minimumaként kapod meg, az utolsó tárgyaknál a teljes félévszám. ||
Hint 3: || Azok a tárgyak, ahol a legkorábbi és a legkésőbbi félév megegyezik, csak egy félévben vehetők fel. Ezeket std::sort-tal rendezve írd ki. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> name(n);
    map<string, int> id;
    for (int i = 0; i < n; ++i) {
        cin >> name[i];
        id[name[i]] = i;
    }

    // next[y]: azok a tárgyak, amelyeknek y az előfeltétele.
    vector<vector<int>> next(n);
    vector<int> indeg(n, 0);
    for (int i = 0; i < m; ++i) {
        string a, b;
        cin >> a >> b;
        int x = id[a], y = id[b];
        next[y].push_back(x);
        ++indeg[x];
    }

    // Topologikus sorrend (Kahn-algoritmus).
    vector<int> order;
    order.reserve(n);
    queue<int> ready;
    for (int v = 0; v < n; ++v) {
        if (indeg[v] == 0) ready.push(v);
    }
    while (!ready.empty()) {
        int u = ready.front();
        ready.pop();
        order.push_back(u);
        for (int v : next[u]) {
            if (--indeg[v] == 0) ready.push(v);
        }
    }

    // Legkorábbi félév (1-től számítva).
    vector<int> es(n, 1);
    for (int u : order) {
        for (int v : next[u]) {
            es[v] = max(es[v], es[u] + 1);
        }
    }
    int total = 0;
    for (int v = 0; v < n; ++v) {
        total = max(total, es[v]);
    }

    // Legkésőbbi félév, fordított sorrendben.
    vector<int> ls(n, total);
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int u = order[i];
        for (int v : next[u]) {
            ls[u] = min(ls[u], ls[v] - 1);
        }
    }

    vector<string> critical;
    for (int v = 0; v < n; ++v) {
        if (es[v] == ls[v]) critical.push_back(name[v]);
    }
    sort(critical.begin(), critical.end());

    cout << total << "\n";
    cout << critical.size() << "\n";
    for (const string &s : critical) {
        cout << s << "\n";
    }
    return 0;
}
