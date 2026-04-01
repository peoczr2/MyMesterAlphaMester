/*
Megoldás lényege:
Az F függvény egy irányított funkcionális gráfot ad, ahol minden csúcsból pontosan
egy él indul. Az ilyen gráfokban minden komponensben pontosan egy ciklus van.
Először indegreesöpréses topológiai kiszórással eltávolítjuk a cikluson kívüli
csúcsokat, így csak a ciklusok maradnak meg. Ezután a még megmaradt csúcsok között
bejárjuk a ciklusokat, és kiválasztjuk a legrövidebbet.
*/

#include <bits/stdc++.h>
using namespace std;

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
    for (int i = 1; i <= n; ++i) {
        if (indeg[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        alive[v] = 0;
        int to = f[v];
        if (--indeg[to] == 0) q.push(to);
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
        if (best.empty() || cyc.size() < best.size()) best = cyc;
    }

    cout << best.size() << '\n';
    for (int x : best) cout << x << ' ';
    cout << '\n';
    return 0;
}
