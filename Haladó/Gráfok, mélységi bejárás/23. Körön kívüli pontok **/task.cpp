/*
Megoldás lényege:
Egy csúcs pontosan akkor nincs benne körben, ha minden hozzá csatlakozó éle híd. Egy él akkor híd, ha az elhagyásával a komponense ketté esik, és a hidakat egyetlen mélységi bejárással határozzuk meg: minden csúcsnak van belépési sorszáma (tin), és a low értéke a részfájából visszaugorva elérhető legkisebb belépési sorszám. A (szülő, gyerek) él akkor híd, ha a gyerek low értéke nagyobb a szülő belépési sorszámánál. Ezután minden csúcsra megnézzük, van-e rajta nem híd él; ha van, a csúcs kör része, ha nincs (az izolált csúcsok is ide tartoznak), akkor a válaszban szerepel. A kimenet a csúcsok növekvő sorrendben. Az időigény O(N + M).
*/
/*
Hint 1: || Egy csúcs akkor van körben, ha van rajta olyan él, amely nem híd, hiszen a kör minden éle nem híd. Először a hidakat keresd meg. ||
Hint 2: || Mélységi bejárásban egy (szülő, gyerek) él akkor híd, ha a gyerek részfájából nem lehet a szülőnél korábbi csúcsra visszaugrani. Ezt a belépési sorszámok (tin) és a low értékek összehasonlításával ellenőrizheted. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m, timerCnt = 0;
vector<vector<pair<int, int>>> adj;  // (szomszéd, élsorszám)
vector<int> tin, low;
vector<char> isBridge;

void dfs(int v, int parentEdge) {
    tin[v] = low[v] = ++timerCnt;
    for (auto [to, id] : adj[v]) {
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    vector<int> eu(m), ev(m);
    adj.assign(n + 1, vector<pair<int, int>>());
    for (int i = 0; i < m; ++i) {
        cin >> eu[i] >> ev[i];
        adj[eu[i]].push_back({ev[i], i});
        adj[ev[i]].push_back({eu[i], i});
    }

    tin.assign(n + 1, 0);
    low.assign(n + 1, 0);
    isBridge.assign(m, 0);
    for (int v = 1; v <= n; ++v)
        if (!tin[v]) dfs(v, -1);

    vector<char> onCycle(n + 1, 0);
    for (int i = 0; i < m; ++i)
        if (!isBridge[i]) onCycle[eu[i]] = onCycle[ev[i]] = 1;

    vector<int> ans;
    for (int v = 1; v <= n; ++v)
        if (!onCycle[v]) ans.push_back(v);

    cout << ans.size() << '\n';
    for (size_t i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}
