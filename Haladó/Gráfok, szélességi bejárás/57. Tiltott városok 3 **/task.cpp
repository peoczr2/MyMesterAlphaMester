/*
Megoldás lényege:
Két szélességi bejárást végzünk: az egyiket Ádám A városából, amely nem léphet be a saját tiltott városaira,
a másikat Éva E városából, az ő tiltott városaival. Így minden városra megkapjuk, hány út kell Ádámnak (dA),
illetve Évának (dE) odajutni; ha valamelyikük nem éri el, az a város nem jöhet szóba. Egy X városban akkor
találkozhatnak, ha mindketten odaértek, vagyis a találkozás ideje max(dA, dE), mert a korábban érkező megvárja
a másikat. Ezt az értéket minimalizáljuk, döntetlennél a kisebb sorszámú várost írjuk ki. Ha nincs ilyen város,
0 a válasz. Az időigény O(N + M).
*/
/*
Hint 1: || Két külön szélességi bejárást végezz: az egyiket Ádám városából, a másikat Éva városából. Egy ember a neki tiltott várost egyszerűen ki sem nyitja a bejárásban. ||
Hint 2: || Egy X városban akkor találkoznak, ha mindketten odaértek, és a találkozás ideje a két távolság nagyobbika. Olyan várost keress, ahol ez az érték a legkisebb, és a sorrendet az 1-től N-ig tartó végigmenéssel döntsd el. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Szélességi bejárás a start városból: a tiltott városokat nem lépi be, a nem elérhető városok távolsága -1
vector<int> bejaras(int start, int n, const vector<vector<int>> &g, const vector<bool> &tiltott) {
    vector<int> dist(n + 1, -1);
    if (tiltott[start]) return dist;
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dist[v] == -1 && !tiltott[v]) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
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
        g[v].push_back(u);
    }

    vector<bool> tiltottA(n + 1, false), tiltottE(n + 1, false);

    int ta;
    cin >> ta;
    for (int i = 0; i < ta; i++) {
        int x;
        cin >> x;
        tiltottA[x] = true;
    }

    int te;
    cin >> te;
    for (int i = 0; i < te; i++) {
        int x;
        cin >> x;
        tiltottE[x] = true;
    }

    vector<int> dA = bejaras(a, n, g, tiltottA);
    vector<int> dE = bejaras(e, n, g, tiltottE);

    int legjobbVaros = 0, legjobbIdo = INT_MAX;
    for (int x = 1; x <= n; x++) {
        if (dA[x] < 0 || dE[x] < 0) continue;
        int ido = max(dA[x], dE[x]);
        if (ido < legjobbIdo) {
            legjobbIdo = ido;
            legjobbVaros = x;
        }
    }

    cout << legjobbVaros << '\n';
    return 0;
}
