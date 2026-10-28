/*
Megoldás lényege:
Két szélességi bejárást (BFS) végzünk az irányított gráfon: az egyiket Ádám városából (A), a másikat Éva városából (E) indítjuk, így minden város távolságát megkapjuk mindkettejük számára. Egy X város akkor jó, ha mindketten el tudnak oda jutni. A feltétel szerint először azt kell minimalizálni, hogy Évának mennyit kell utaznia, ezen belül Ádám távolságát, végül a sorszám szerint választunk, így a legkisebb sorszámú városhoz jutunk. A kiválasztott városba az A-ból és az E-ből induló BFS-fák szülőmutatóin visszafelé lépve kapjuk meg az utakat. A két BFS és a kiválasztás O(N+M) időben fut.
*/
/*
Hint 1: || Két szélességi bejárás kell: az egyik Ádám kezdővárosából, a másik Éva kezdővárosából indul. Így minden városra megkapod, hogy mindkettőjüknek hány út kell oda. ||
Hint 2: || A jó város kiválasztásánál a rendezési sorrend: először Éva távolsága legyen minimális, utána Ádámé, végül a kisebb sorszám. Az utat a BFS-ben tárolt szülőkön visszafelé lépve kapod meg a célvárostól a kezdőig, majd megfordítod. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Szélességi bejárás a forrásból: távolságok és BFS-szülők.
void bfs(int src, const vector<vector<int>>& g, vector<int>& dist, vector<int>& par) {
    dist.assign(g.size(), -1);
    par.assign(g.size(), 0);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
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

// Út a forrásból a célba: a szülőkön visszafelé lépünk, majd megfordítjuk.
vector<int> buildPath(int src, int dst, const vector<int>& par) {
    vector<int> path;
    for (int v = dst;; v = par[v]) {
        path.push_back(v);
        if (v == src) break;
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, e;
    cin >> n >> m >> a >> e;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    vector<int> dA, pA, dE, pE;
    bfs(a, g, dA, pA);
    bfs(e, g, dE, pE);

    // Éva távolsága szerint, majd Ádámé szerint keresünk; döntetlennél a kisebb sorszám marad.
    int best = -1;
    for (int x = 1; x <= n; x++) {
        if (dA[x] < 0 || dE[x] < 0) continue;
        if (best == -1 || dE[x] < dE[best] || (dE[x] == dE[best] && dA[x] < dA[best])) best = x;
    }

    if (best == -1) {
        cout << 0 << '\n';
        return 0;
    }

    cout << best << ' ' << dA[best] << ' ' << dE[best] << '\n';

    vector<int> pathA = buildPath(a, best, pA);
    for (size_t i = 0; i < pathA.size(); i++) {
        cout << pathA[i] << (i + 1 < pathA.size() ? ' ' : '\n');
    }

    vector<int> pathE = buildPath(e, best, pE);
    for (size_t i = 0; i < pathE.size(); i++) {
        cout << pathE[i] << (i + 1 < pathE.size() ? ' ' : '\n');
    }
    return 0;
}
