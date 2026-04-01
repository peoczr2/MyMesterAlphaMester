#include <bits/stdc++.h>
using namespace std;

/*
    A népszerűségi kör egy irányított gráf ciklusa. A legrövidebb útvonalakat
    nem kell keresni: elég az összes csúcsból eltávolítani a cikluson kívüli,
    bejövő él nélküli elemeket, majd a maradék ciklusok közül a leghosszabbat
    kiválasztani.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> f(n + 1), indeg(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> f[i];
        ++indeg[f[i]];
    }

    queue<int> q;
    vector<char> alive(n + 1, 1);
    for (int i = 1; i <= n; ++i) if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        alive[v] = 0;
        if (--indeg[f[v]] == 0) q.push(f[v]);
    }

    vector<char> vis(n + 1, 0);
    vector<int> best;
    for (int i = 1; i <= n; ++i) {
        if (!alive[i] || vis[i]) continue;
        vector<int> cyc;
        int v = i;
        while (!vis[v]) {
            vis[v] = 1;
            cyc.push_back(v);
            v = f[v];
        }
        if (cyc.size() > best.size()) best = cyc;
    }

    cout << best.size() << '\n';
    for (int i = 0; i < (int)best.size(); ++i) {
        if (i) cout << ' ';
        cout << best[i];
    }
    cout << '\n';
    return 0;
}