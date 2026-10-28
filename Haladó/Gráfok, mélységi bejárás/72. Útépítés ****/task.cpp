/*
Megoldás lényege: minden kereszteződésbe legfeljebb egy új út futhat be, ezért a feladat maximális párosítás keresése a kereszteződések (rácspontok) és a cellákban lévő utak között.
Minden átlós út két szomszédos sorban lévő rácspontot köt össze, ezért a rácspontokat a sorszámuk paritása szerint két csoportba osztva minden út a két csoport között fut: a gráf páros.
Egy cellában legfeljebb egy út épülhet, így minden cella egy él, és a párosításba került él azt jelenti, hogy az adott cellába az út kerül.
A maximális párosítást Hopcroft-Karp algoritmussal keressük, majd a párosításhoz tartozó cellákat írjuk ki a megfelelő iránnyal, a többi cella maradjon pont.
Az időigény O(E * sqrt(V)), ahol E legfeljebb N * M, V pedig a rácspontok száma.
*/
/*
Hint 1: || Minden kereszteződéshez legfeljebb egy új út csatlakozhat, ezért a kereszteződések egymás közötti versenyét kell kezelni. Gondolj úgy a feladatra, hogy a kereszteződések és az utak között kapcsolat van. ||
Hint 2: || Egy átlós út két rácspontot köt össze, és a két pont sorindexe pontosan 1-gyel különbözik. Ha a rácspontokat a sorindex paritása szerint színezed, minden út két különböző színű pont között fut. ||
Hint 3: || A kétszínű gráfban a legtöbb út kiválasztása maximális párosítás keresése. Hopcroft-Karp algoritmussal gyorsan megkapod, és a párosított élek cellái adják a kiírandó mátrixot. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

int N, M;
vector<string> grid;
vector<vector<pair<int, int>>> adj;  // bal csúcs -> (jobb csúcs, cella azonosító)
vector<int> matchL, matchR, cellOf, distL, itp;
vector<int> lefts;

int pid(int r, int c) { return r * (M + 1) + c; }

bool bfs() {
    queue<int> q;
    bool found = false;
    for (int u : lefts) {
        if (matchL[u] == -1) {
            distL[u] = 0;
            q.push(u);
        } else {
            distL[u] = INF;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, c] : adj[u]) {
            int w = matchR[v];
            if (w == -1) {
                found = true;
            } else if (distL[w] == INF) {
                distL[w] = distL[u] + 1;
                q.push(w);
            }
        }
    }
    return found;
}

bool dfs(int u) {
    for (int &i = itp[u]; i < (int)adj[u].size(); ++i) {
        auto [v, c] = adj[u][i];
        int w = matchR[v];
        if (w == -1 || (distL[w] == distL[u] + 1 && dfs(w))) {
            matchL[u] = v;
            matchR[v] = u;
            cellOf[u] = c;
            return true;
        }
    }
    distL[u] = INF;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    grid.resize(N);
    for (int i = 0; i < N; ++i) cin >> grid[i];

    int P = (N + 1) * (M + 1);
    adj.assign(P, {});
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            char ch = grid[i][j];
            if (ch == '.') continue;
            int a, b;
            if (ch == '\\') {
                a = pid(i, j);
                b = pid(i + 1, j + 1);
            } else {
                a = pid(i, j + 1);
                b = pid(i + 1, j);
            }
            int left = a, right = b;
            if ((a / (M + 1)) % 2 == 1) {  // a páratlan sorban van, így a másik a bal oldali
                left = b;
                right = a;
            }
            adj[left].push_back({right, i * M + j});
        }
    }

    for (int r = 0; r <= N; r += 2)
        for (int c = 0; c <= M; ++c) lefts.push_back(pid(r, c));

    matchL.assign(P, -1);
    matchR.assign(P, -1);
    cellOf.assign(P, -1);
    distL.assign(P, INF);
    itp.assign(P, 0);

    int matched = 0;
    while (bfs()) {
        fill(itp.begin(), itp.end(), 0);
        for (int u : lefts)
            if (matchL[u] == -1 && dfs(u)) ++matched;
    }

    vector<string> out(N, string(M, '.'));
    for (int u : lefts) {
        if (matchL[u] != -1) {
            int cid = cellOf[u];
            out[cid / M][cid % M] = grid[cid / M][cid % M];
        }
    }

    cout << matched << "\n";
    for (int i = 0; i < N; ++i) cout << out[i] << "\n";
    return 0;
}
