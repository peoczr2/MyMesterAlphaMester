/*
Megoldás lényege:
A városokat csúcsoknak, a csíkokat éleknek tekintjük. A repülések irányát nem ismerjük, így bármely irányítást választhatunk: egy városba pontosan akkor juthatunk vissza, ha rajta áthalad egy kör a gráfban, vagyis van rajta nem híd él.
Párhuzamos élek (két város között két csík) is alkotnak kört, ezért ezeket is így kell kezelni.
A hidakat mélységi bejárással (Tarjan-módszer) keressük: egy fa-él akkor híd, ha a gyerek csúcsából a szülőnél feljebb (vagy a szülővel azonos magasságba) nem lehet visszaélen jutni.
A hidak nélküli éleken lévő csúcsokat megjelöljük, a többi város (ahova nem juthatunk vissza) számát írjuk ki. Az idő O(N + M).
*/
/*
Hint 1: || A repülések irányát tetszőlegesen választhatjuk, így egy városba akkor juthatsz vissza, ha a városon át van zárt kör a csíkok gráfjában. ||
Hint 2: || Egy csík pontosan akkor van kör része, ha az eltávolítása nem szakítja szét az összefüggő részét (vagyis nem híd). Az ilyen csíkok végpontjai azok a városok, ahová vissza lehet jutni. ||
Hint 3: || Mélységi bejárásban számold a csúcsok bejárási sorszámát és a visszaélen elérhető legkisebb sorszámot; ha egy gyerek nem jut feljebb a szülőjénél, a szülő-gyerek él híd. Két párhuzamos él esetén az éleket azonosítóval különböztesd meg, ne a szülő csúcsával. ||
*/
#include <bits/stdc++.h>
using namespace std;

int timer_ = 0;
vector<vector<pair<int, int>>> g; // (szomszéd, élazonosító)
vector<int> tin, low;
vector<char> isBridge;

void dfs(int v, int parentEdge) {
    tin[v] = low[v] = ++timer_;
    for (auto [to, id] : g[v]) {
        if (id == parentEdge) continue;
        if (tin[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, id);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) isBridge[id] = 1;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    g.assign(n + 1, {});
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        edges[i] = {a, b};
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }

    tin.assign(n + 1, 0);
    low.assign(n + 1, 0);
    isBridge.assign(m, 0);
    for (int v = 1; v <= n; v++)
        if (!tin[v]) dfs(v, -1);

    vector<char> onCycle(n + 1, 0);
    for (int i = 0; i < m; i++) {
        if (!isBridge[i]) {
            onCycle[edges[i].first] = 1;
            onCycle[edges[i].second] = 1;
        }
    }

    int cnt = 0;
    for (int v = 1; v <= n; v++)
        if (!onCycle[v]) cnt++;
    cout << cnt << '\n';
    return 0;
}
