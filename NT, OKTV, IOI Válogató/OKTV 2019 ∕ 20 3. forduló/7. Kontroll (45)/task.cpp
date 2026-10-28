/*
Megoldás lényege:
A kérdés egy minimális csúcshalmaz (vágás), amely elvágja a start pontot a céltól, ahol sem a start, sem a cél nem választható. Menger tétele szerint ez megegyezik a start és a cél közötti csúcsdiszjunkt utak maximális számával. Minden elágazási pontot egy bemeneti és egy kimeneti csúcsra bontunk egységnyi kapacitású éllel, a pályaszakaszokat pedig nagy kapacitású élekkel kötjük össze, így a maximális folyam megadja a kontroll pontok minimális K számát. A folyamot Dinic-algoritmussal számoljuk, az utolsó sikertelen keresés után a start pontból elérhető csúcsok határán lévő egységélek adják a kontroll pontokat. Az időigény egységkapacitású hálózatokon O(E·√V) jellegű, a memóriaigény O(N + M).
*/
/*
Hint 1: || Gondold végig: a kontroll pontok száma legalább annyi, ahány csúcsdiszjunkt start–cél út van, mert egy kontroll pont legfeljebb egy ilyen utat tud blokkolni. Ezért a diszjunkt utak maximális száma adja a választ (Menger-tétel). ||
Hint 2: || Bontsd szét minden csúcsot egy bemeneti és egy kimeneti csúcsra egységnyi kapacitású éllel, az eredeti pályaszakaszokat pedig nagy kapacitású élekként vedd fel a kimenetektől a bemenetek felé. Így a maximális folyam közvetlenül a csúcsdiszjunkt utak számát adja. ||
Hint 3: || A maximális folyam után keresd meg, mely csúcsok érhetők el a start csúcs kimenetéből a maradék hálózatban. Az a kontroll pont kell a vágáshoz, amelynek bemenete elérhető, kimenete viszont nem. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev, cap;
};

vector<vector<Edge>> g;
vector<int> level, itp;

void addEdge(int u, int v, int c) {
    g[u].push_back({v, (int)g[v].size(), c});
    g[v].push_back({u, (int)g[u].size() - 1, 0});
}

bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1);
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const Edge &e : g[u])
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[u] + 1;
                q.push(e.to);
            }
    }
    return level[t] >= 0;
}

// Blokkoló folyam a szintgráfban; iteratív DFS, hogy hosszú utaknál se legyen mélységi rekurzió.
int blockingFlow(int s, int t) {
    int total = 0;
    vector<pair<int, int>> path;  // (csúcs, az élének indexe a csúcs listájában)
    int v = s;
    while (true) {
        if (v == t) {
            int f = INT_MAX;
            for (auto [u, idx] : path) f = min(f, g[u][idx].cap);
            for (auto [u, idx] : path) {
                Edge &e = g[u][idx];
                e.cap -= f;
                g[e.to][e.rev].cap += f;
            }
            total += f;
            path.clear();
            v = s;
            continue;
        }
        bool moved = false;
        while (itp[v] < (int)g[v].size()) {
            const Edge &e = g[v][itp[v]];
            if (e.cap > 0 && level[e.to] == level[v] + 1) {
                path.push_back({v, itp[v]});
                v = e.to;
                moved = true;
                break;
            }
            itp[v]++;
        }
        if (!moved) {
            if (v == s) break;
            // zsákutca: visszalépünk az előző csúcsba, és annak a következő élét nézzük
            int pu = path.back().first;
            path.pop_back();
            v = pu;
            itp[v]++;
        }
    }
    return total;
}

int main() {
    int n;
    cin >> n;
    // a v csúcs bemeneti csúcsa 2(v-1), kimeneti csúcsa 2(v-1)+1
    auto inNode = [](int v) { return 2 * (v - 1); };
    auto outNode = [](int v) { return 2 * (v - 1) + 1; };
    int V = 2 * n;
    g.assign(V, {});
    level.assign(V, -1);
    itp.assign(V, 0);

    const int BIG = 1000000;
    // a start (1) és a cél (N) nem lehet kontroll pont: csak a többi csúcsnak van egységnyi éle
    for (int v = 2; v <= n - 1; v++) addEdge(inNode(v), outNode(v), 1);
    for (int u = 1; u <= n - 1; u++) {
        int cnt;
        cin >> cnt;
        for (int i = 0; i < cnt; i++) {
            int w;
            cin >> w;
            addEdge(outNode(u), inNode(w), BIG);
        }
    }

    int s = outNode(1), t = inNode(n);
    int flow = 0;
    while (bfs(s, t)) {
        fill(itp.begin(), itp.end(), 0);
        flow += blockingFlow(s, t);
    }

    // az utolsó (sikertelen) bfs után a level >= 0 csúcsok az s-ből elérhetők a maradék hálózatban
    vector<int> cut;
    for (int v = 2; v <= n - 1; v++)
        if (level[inNode(v)] >= 0 && level[outNode(v)] < 0)
            cut.push_back(v);

    cout << flow << "\n";
    for (size_t i = 0; i < cut.size(); i++) {
        if (i) cout << ' ';
        cout << cut[i];
    }
    cout << "\n";
    return 0;
}
