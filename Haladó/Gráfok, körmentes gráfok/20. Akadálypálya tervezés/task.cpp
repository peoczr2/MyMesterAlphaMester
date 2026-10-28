/*
Megoldás lényege:
A terv minden ellenőrző pontja rajta van a start-cél legrövidebb útján, és ennek hossza nem változhat,
ezért minden pont szintje a startól mért távolság, és csak olyan utak használhatók, amelyek minden
lépésben eggyel nagyobb szintre vezetnek. Minden pontnak (a célon kívül) kell egy kimenő, és (a start
kivételével) egy bejövő megvalósított út; egy él egyszerre mindkét igényt kielégítheti. Ezt párosítási
feladatként kezeljük: a kimenő igények és a bejövő igények külön oldalt alkotnak, a párosítható élek a
szomszédos szintek közti tervezett utak. Ha a maximális párosítás mérete ν, a minimális élszám 2(N-1)-ν,
a párosítatlan igényekhez pedig egy-egy tetszőleges megfelelő él kerül. A Hopcroft-Karp-algoritmus
O(E*sqrt(V)) időben kiszámolja a párosítást, ami N=10 000 és M=120 000 mellett bőven belefér.
*/
/*
Hint 1: || Minden pont rajta van a start-cél legrövidebb úton, és ennek hossza nem változhat. Számold ki a startból a távolságokat (BFS), és csak olyan terv-éleket használj, amelyek pontosan eggyel nagyobb távolságú pontba vezetnek. ||
Hint 2: || Minden pontnak a céltól eltérőnek kell kimenő éle, a startól eltérőnek bejövő éle, és egy él egyszerre mindkét igényt kielégítheti. Gondold végig, hogy ez párosítási feladat: a kimenő és a bejövő igények külön oldalt alkotnak. ||
Hint 3: || A keresett élszám 2(N-1) mínusz a maximális párosítás mérete. A párosítatlan igényekhez egy-egy tetszőleges, a szomszédos szintek közti él kell; a párosítást Hopcroft-Karp-algoritmussal számold ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

int n, m;
vector<vector<int>> adj;     // adj[u]: u -> v, szomszédos szintek közti élek (bal oldal: kimenet)
vector<vector<int>> inAdj;   // inAdj[v]: u -> v, szomszédos szintek közti élek (jobb oldal: bejövés)
vector<int> matchL, matchR, dist_, itp;

bool bfs() {
    queue<int> q;
    bool found = false;
    for (int u = 1; u <= n; u++) {
        if (matchL[u] == 0) {
            dist_[u] = 0;
            q.push(u);
        } else {
            dist_[u] = INF;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            int w = matchR[v];
            if (w == 0) {
                found = true;
            } else if (dist_[w] == INF) {
                dist_[w] = dist_[u] + 1;
                q.push(w);
            }
        }
    }
    return found;
}

bool dfs(int u) {
    for (int &i = itp[u]; i < (int)adj[u].size(); i++) {
        int v = adj[u][i];
        int w = matchR[v];
        if (w == 0 || (dist_[w] == dist_[u] + 1 && dfs(w))) {
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }
    }
    dist_[u] = INF;
    return false;
}

int main() {
    cin >> n >> m;
    vector<pair<int, int>> E(m);
    vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);
    for (auto &e : E) {
        cin >> e.first >> e.second;
        outdeg[e.first]++;
        indeg[e.second]++;
    }

    int s = 1, t = 1;
    for (int v = 1; v <= n; v++) {
        if (indeg[v] == 0) s = v;
        if (outdeg[v] == 0) t = v;
    }

    vector<vector<int>> g(n + 1);
    for (auto &e : E) g[e.first].push_back(e.second);
    vector<int> d(n + 1, -1);
    queue<int> q;
    d[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (d[v] < 0) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }

    adj.assign(n + 1, {});
    inAdj.assign(n + 1, {});
    for (auto &e : E) {
        int u = e.first, v = e.second;
        if (d[u] >= 0 && d[v] == d[u] + 1 && u != t && v != s) {
            adj[u].push_back(v);
            inAdj[v].push_back(u);
        }
    }

    matchL.assign(n + 1, 0);
    matchR.assign(n + 1, 0);
    dist_.assign(n + 1, 0);
    itp.assign(n + 1, 0);
    while (bfs()) {
        fill(itp.begin(), itp.end(), 0);
        for (int u = 1; u <= n; u++) {
            if (matchL[u] == 0) dfs(u);
        }
    }

    vector<pair<int, int>> res;
    for (int u = 1; u <= n; u++) {
        if (matchL[u] != 0) res.push_back({u, matchL[u]});
    }
    for (int u = 1; u <= n; u++) {
        if (u != t && matchL[u] == 0 && !adj[u].empty()) res.push_back({u, adj[u][0]});
    }
    for (int v = 1; v <= n; v++) {
        if (v != s && matchR[v] == 0 && !inAdj[v].empty()) res.push_back({inAdj[v][0], v});
    }

    cout << res.size() << "\n";
    for (auto &p : res) cout << p.first << " " << p.second << "\n";
    return 0;
}
