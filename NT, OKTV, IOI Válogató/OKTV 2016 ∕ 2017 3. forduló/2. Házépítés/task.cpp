/*
Megoldás lényege:
A és B közé eső munkák száma adja a napok számát. Azok a munkák, amelyeket A előtt kell elvégezni
(A elődei), nem kerülhetnek A és B közé, ugyanígy B után kötelező munkák (B utódai) sem. Minden
más munka beillesztható A és B közé. Az elődöket A-ból visszafelé, az utódokat B-ből előre
haladó bejárással (DFS) kapjuk meg. A sorrendet topologikus rendezéssel (Kahn-algoritmus) építjük:
mindig a legkisebb csoportba tartozó elvégezhető munkát vesszük, így a sorrend: A elődei, A,
a köztes munkák, B, B utódai. A válasz N - 2 - (A elődeinek száma) - (B utódainak száma).
Az időigény O((N + M) log N).
*/
/*
Hint 1: || Gondold végig, mely munkákat nem lehet A és B közé tenni: azokat, amelyeket A előtt kötelező elvégezni, és azokat, amelyek B után kötelezően jönnek. ||
Hint 2: || Az A-ból visszafelé, illetve a B-ből előre haladó bejárás megadja ezeket a munkákat; a többi munka mind A és B közé tehető. ||
Hint 3: || Topologikus rendezésnél a sorban elvégezhető munkák közül mindig a csoportszám szerint legkisebbet választod (a csoportszám: 0 A elődei, 1 A, 2 köztes, 3 B, 4 B utódai). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<vector<int>> g(n + 1), rg(n + 1);  // g: előre, rg: visszafelé
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;  // x munkát y előtt kell elvégezni
        g[x].push_back(y);
        rg[y].push_back(x);
        ++indeg[y];
    }

    // Bejárás egy kezdőpontból az adott élirányban
    auto reach = [&](int start, const vector<vector<int>>& adj) {
        vector<char> seen(n + 1, 0);
        vector<int> st{start};
        seen[start] = 1;
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            for (int v : adj[u]) {
                if (!seen[v]) {
                    seen[v] = 1;
                    st.push_back(v);
                }
            }
        }
        return seen;
    };
    vector<char> before = reach(a, rg);  // A és elődei
    vector<char> after = reach(b, g);    // B és utódai

    // Csoportok: 0 = A elődei, 1 = A, 2 = köztes, 3 = B, 4 = B utódai
    vector<int> grp(n + 1, 2);
    for (int v = 1; v <= n; ++v) {
        if (before[v] && v != a) grp[v] = 0;
        else if (after[v] && v != b) grp[v] = 4;
    }
    grp[a] = 1;
    grp[b] = 3;

    // Topologikus rendezés: a legkisebb csoportú elvégezhető munka következik
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int v = 1; v <= n; ++v) {
        if (indeg[v] == 0) pq.push({grp[v], -v});
    }
    vector<int> order;
    order.reserve(n);
    while (!pq.empty()) {
        int u = -pq.top().second;
        pq.pop();
        order.push_back(u);
        for (int v : g[u]) {
            if (--indeg[v] == 0) pq.push({grp[v], -v});
        }
    }

    int between = 0;
    for (int v = 1; v <= n; ++v) {
        if (grp[v] == 2) ++between;
    }

    cout << between << '\n';
    for (int i = 0; i < n; ++i) {
        cout << order[i] << (i + 1 < n ? ' ' : '\n');
    }
    return 0;
}
