/*
Megoldás lényege:
Mélységi bejárást végzünk az 1-es kereszteződésből. Amikor egy még nem egyirányúsított utcán az A kereszteződésből a B-be halad az őrmester, az utca forgalma B-ből A felé lesz engedélyezve, így a visszaút ugyanezen az utcán mindig szabályos. Az új kereszteződésekhez vezető utcákat így oda-vissza járja be, tehát minden fa-él a gyermektől a szülő felé mutat. Az már bejárt, de még a bejárási úton lévő őseihez vezető utcát az ős oldaláról dolgozzuk fel, így az utca a leszármazottól az ős felé mutat. Ezért a forgalmi gráf körmentes, az 1-es kereszteződésből nem indul ki utca, és minden kereszteződésből el lehet jutni oda, tehát a bűnöző előbb-utóbb feltűnik. Minden utcát pontosan két lépésben járunk be, így az időigény O(N+M).
*/
/*
Hint 1: || Mélységi bejárást végezz az 1-es kereszteződésből, és minden utcát pontosan két lépésben jártass be: egyszer oda, majd vissza. ||
Hint 2: || Ha egy még nem bejárt utcán mész át A-ból B-be, az utca forgalmi iránya B-ből A felé lesz, így a visszaút ugyanezen az utcán mindig szabályos. Ez garantálja, hogy a szülőhöz vezető út visszafelé járható. ||
Hint 3: || Az már bejárt, de még a bejárási úton lévő őseidhez vezető utcát most ne járd be, hanem az ős oldaláról dolgozd fel, amikor a bejárása visszatér hozzá. Így minden utca a leszármazott felől az ős felé mutat, nem lesz kör, és 1 lesz az egyetlen nyelő. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<pair<int, int>>> adj;  // (szomszéd, utca azonosítója)
vector<char> usedEdge, visited, onStack;
vector<array<int, 3>> route;  // A B C

void dfs(int x) {
    onStack[x] = 1;
    for (auto [y, e] : adj[x]) {
        if (usedEdge[e]) continue;
        if (!visited[y]) {
            // még nem járt kereszteződés: oda és vissza
            usedEdge[e] = 1;
            visited[y] = 1;
            route.push_back({x, y, 1});
            dfs(y);
            route.push_back({y, x, 0});
        } else if (!onStack[y]) {
            // már befejezett leszármazott: az ős oldaláról, oda és vissza
            usedEdge[e] = 1;
            route.push_back({x, y, 1});
            route.push_back({y, x, 0});
        }
        // y a bejárási úton lévő ős: az utcát az ős oldaláról dolgozzuk fel később
    }
    onStack[x] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    adj.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }

    usedEdge.assign(m, 0);
    visited.assign(n + 1, 0);
    onStack.assign(n + 1, 0);
    visited[1] = 1;
    dfs(1);

    cout << route.size() << "\n";
    for (auto &r : route) cout << r[0] << ' ' << r[1] << ' ' << r[2] << "\n";
    return 0;
}
