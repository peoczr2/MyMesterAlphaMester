/*
Megoldás lényege:
Egy csúcs pontosan akkor van legalább egy irányított körben, ha erősen összefüggő komponensének legalább két csúcsa van, vagy ha van rajta hurokél. Ezeket a komponenseket egyetlen mélységi bejárással, Tarjan-algoritmussal kapjuk meg: minden csúcsnak van belépési sorszáma és low értéke, és ha a low egyezik a belépési sorszámmal, a verem tetejéről a komponens csúcsai levehetők. A komponensek méretét és a hurokéleket megvizsgálva adódik a kör-csúcsok halmaza. A kimenetben a csúcsokat a veremből való kivétel sorrendjében írjuk ki, mert a feladat szerint a sorrend tetszőleges. Az időigény O(N + M).
*/
/*
Hint 1: || Egy csúcs pontosan akkor van körben, ha ugyanabban az erősen összefüggő komponensben van vele egy másik csúcs, vagy ha van rajta hurokél. ||
Hint 2: || Tarjan-algoritmussal, egyetlen mélységi bejárással megkapod a komponenseket: a komponens gyökerénél a veremből vedd le a csúcsokat a gyökérig. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m, timerCnt = 0;
vector<vector<int>> adj;
vector<int> tin, low, stk;
vector<char> onStack;
vector<vector<int>> comps;

void dfs(int v) {
    tin[v] = low[v] = ++timerCnt;
    stk.push_back(v);
    onStack[v] = 1;
    for (int to : adj[v]) {
        if (!tin[to]) {
            dfs(to);
            low[v] = min(low[v], low[to]);
        } else if (onStack[to]) {
            low[v] = min(low[v], tin[to]);
        }
    }
    if (low[v] == tin[v]) {
        vector<int> comp;
        int x;
        do {
            x = stk.back();
            stk.pop_back();
            onStack[x] = 0;
            comp.push_back(x);
        } while (x != v);
        comps.push_back(comp);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    adj.assign(n + 1, vector<int>());
    vector<char> selfLoop(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        if (u == v) selfLoop[u] = 1;
    }
    tin.assign(n + 1, 0);
    low.assign(n + 1, 0);
    onStack.assign(n + 1, 0);
    for (int v = 1; v <= n; ++v)
        if (!tin[v]) dfs(v);

    vector<int> ans;
    for (auto &comp : comps) {
        if (comp.size() >= 2) {
            for (int x : comp) ans.push_back(x);
        } else if (selfLoop[comp[0]]) {
            ans.push_back(comp[0]);
        }
    }

    cout << ans.size() << '\n';
    for (size_t i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}
