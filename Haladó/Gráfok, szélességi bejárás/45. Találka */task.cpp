/*
Megoldás lényege:
A járatok egy irányított gráfot alkotnak, és mindegyik járat egy napot tart, így a találkozás ideje a járatok
száma. Szélességi bejárással kiszámoljuk, hányadik napra ér el Rómeó (A-ból) és Júlia (B-ből) minden várost.
Egy X városban akkor találkozhatnak a legkorábban, ha a későbbi érkezésük minimális, vagyis a max(dA, dB)
értéket minimalizáljuk. A korábban érkező megvárhatja a másikat. Az útvonalakat a bejárás szülő-tömbjéből
rakjuk vissza. Az időigény O(N + M).
*/
/*
Hint 1: || Mivel minden járat ugyanabban az időpontban indul és egy napot tart, az idő a járatok számával egyezik: szélességi bejárással kell kiszámolnod, hány járat kell Rómeónak és Júliának minden városba. ||
Hint 2: || Egy X városban akkor találkoznak, ha mindketten odaértek: a találkozás ideje a két távolság nagyobbika, ezért keresd azt a várost, ahol ez a legkisebb. Az útvonalakat a bejárás előző csúcsaiból állítsd vissza X-ből visszafelé. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Szélességi bejárás: távolságok és az előző csúcsok (szülők)
void bfs(int s, const vector<vector<int>> &g, vector<int> &dist, vector<int> &par) {
    dist.assign(g.size(), -1);
    par.assign(g.size(), -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                par[v] = u;
                q.push(v);
            }
        }
    }
}

// Út a bejárás forrásától t-ig a szülő-tömb alapján
vector<int> pathTo(int t, const vector<int> &par) {
    vector<int> p;
    for (int v = t; v != -1; v = par[v]) p.push_back(v);
    reverse(p.begin(), p.end());
    return p;
}

void printPath(const vector<int> &p) {
    for (size_t i = 0; i < p.size(); i++) {
        if (i) cout << ' ';
        cout << p[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int k, v;
        cin >> k >> v;
        g[k].push_back(v);
    }

    vector<int> da, pa, db, pb;
    bfs(a, g, da, pa);
    bfs(b, g, db, pb);

    int best = -1, bestT = INT_MAX;
    for (int x = 1; x <= n; x++) {
        if (da[x] < 0 || db[x] < 0) continue;
        int t = max(da[x], db[x]);
        if (t < bestT) {
            bestT = t;
            best = x;
        }
    }

    if (best == -1) {
        cout << -1 << "\n\n\n";
        return 0;
    }

    cout << bestT << ' ' << best << '\n';
    printPath(pathTo(best, pa));
    printPath(pathTo(best, pb));
    return 0;
}
