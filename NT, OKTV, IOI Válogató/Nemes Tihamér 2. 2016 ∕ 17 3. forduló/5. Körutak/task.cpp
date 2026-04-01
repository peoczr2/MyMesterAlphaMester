#include <bits/stdc++.h>
using namespace std;

/*
    Egy csomópont akkor része valamilyen körnek, ha a 2-magban marad. Ezért a
    2-nél kisebb fokú csúcsokat sorban eltávolítjuk; ami megmarad, az mind rajta
    van legalább egy körön.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    vector<int> deg(n + 1);
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
        ++deg[x];
        ++deg[y];
    }

    queue<int> q;
    vector<char> alive(n + 1, 1);
    for (int i = 1; i <= n; ++i) if (deg[i] < 2) q.push(i);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (!alive[v]) continue;
        alive[v] = 0;
        for (int to : g[v]) {
            if (--deg[to] == 1) q.push(to);
        }
    }

    vector<int> ans;
    for (int i = 1; i <= n; ++i) if (!alive[i]) ans.push_back(i);
    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}