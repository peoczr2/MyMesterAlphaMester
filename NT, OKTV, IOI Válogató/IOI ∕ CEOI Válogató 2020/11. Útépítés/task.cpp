/*
Megoldás lényege:
Minden tervezett átlós út két kereszteződést köt össze: a '\' út a blokk bal felső és jobb alsó sarkát, a '/' út a jobb felső és bal alsó sarkát. A lakók feltétele szerint minden kereszteződéshez legfeljebb egy új út csatlakozhat, így a kérdés az, hogy a tervezett utak közül hány választható ki úgy, hogy a kereszteződések egyike se szerepeljen kettőnél több kiválasztott útban, vagyis maximális párosítást kell keresni a kereszteződések gráfjában. Ez a gráf páros: minden út sorszomszédos sarkokat köt össze, így a páros és a páratlan sorszámú sarkok két osztályt alkotnak. A maximális párosítást Hopcroft-Karp algoritmussal keressük, ami az (N+1)(M+1) csúcsú, legfeljebb NM élű gráfon O(E·√V) időben fut, és a 0,8 mp-es időlimitbe bőven belefér (a 200×200-as mintán 0,01 mp). A kimenetben a párosításba került utakat megtartjuk, a többi blokkba '.' kerül.
*/
/*
Hint 1: || Először azt gondold végig, hogy egy átlós út melyik két kereszteződést köti össze, és hogy két út mikor ütközik egy kereszteződésben. Ha egy kereszteződésbe legfeljebb egy új út futhat, akkor a feladat egy gráfon kiválasztandó élhalmaz. ||
Hint 2: || Rajzold fel a kereszteződéseket mint csúcsokat, az utakat mint éleket. Egy kereszteződésben legfeljebb egy kiválasztott él lehet, ez éppen a párosítás definíciója. Figyelj arra, hogy minden él sorról sorra lép, így a gráf páros: a páros és a páratlan sorszámú kereszteződések két osztály. ||
Hint 3: || A maximális párosítást kereshetted volna egyszerű keresőutas (Kuhn) módszerrel, de nagy rácsnál a Hopcroft-Karp algoritmus gyorsabb: a BFS megkeresi a rövid kiegészítő utakat, a DFS pedig ezeken végighalad. A kiválasztott éleket végül a blokkok karakterével írd ki, a többi helyre pont kerül. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const int INF = INT_MAX;

int N, M, V;
vector<vector<pair<int, int>>> adj;  // bal csúcs -> (jobb csúcs, cella indexe)
vector<int> matchL, matchR, matchCell, distv, itv;
vector<int> leftList;

bool bfs() {
    queue<int> q;
    bool found = false;
    for (int u : leftList) {
        if (matchL[u] == -1) {
            distv[u] = 0;
            q.push(u);
        } else {
            distv[u] = INF;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, cell] : adj[u]) {
            int w = matchR[v];
            if (w == -1) {
                found = true;
            } else if (distv[w] == INF) {
                distv[w] = distv[u] + 1;
                q.push(w);
            }
        }
    }
    return found;
}

bool dfs(int u) {
    for (int &i = itv[u]; i < (int)adj[u].size(); ++i) {
        auto [v, cell] = adj[u][i];
        int w = matchR[v];
        if (w == -1 || (distv[w] == distv[u] + 1 && dfs(w))) {
            matchL[u] = v;
            matchR[v] = u;
            matchCell[u] = cell;
            ++i;
            return true;
        }
    }
    distv[u] = INF;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    vector<string> g(N);
    for (auto &row : g) cin >> row;

    int C = M + 1;
    V = (N + 1) * C;
    adj.assign(V, {});
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) {
            int u, v;
            if (g[i][j] == '\\') {
                u = i * C + j;
                v = (i + 1) * C + (j + 1);
            } else if (g[i][j] == '/') {
                u = i * C + (j + 1);
                v = (i + 1) * C + j;
            } else {
                continue;
            }
            // a sorok paritása szerint: a páros sorú kereszteződés a bal oldal
            if (i % 2 != 0) swap(u, v);
            adj[u].push_back({v, i * M + j});
        }

    for (int r = 0; r <= N; r += 2)
        for (int c = 0; c <= M; ++c) leftList.push_back(r * C + c);

    matchL.assign(V, -1);
    matchR.assign(V, -1);
    matchCell.assign(V, -1);
    distv.assign(V, INF);
    itv.assign(V, 0);

    int result = 0;
    while (bfs()) {
        fill(itv.begin(), itv.end(), 0);
        for (int u : leftList)
            if (matchL[u] == -1 && dfs(u)) ++result;
    }

    vector<string> out(N, string(M, '.'));
    for (int u : leftList)
        if (matchL[u] != -1) {
            int cell = matchCell[u];
            out[cell / M][cell % M] = g[cell / M][cell % M];
        }

    cout << result << '\n';
    for (int i = 0; i < N; ++i) cout << out[i] << '\n';
    return 0;
}
