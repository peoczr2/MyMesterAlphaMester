/*
Megoldás lényege:
A feladat a start (1) és a cél (N) közötti minimális csúcs-vágás: a legkevesebb olyan csúcs, amelynek elhagyásával nem marad 1-ből N-be vezető út. A start és a cél nem lehet kontrollpont, ezt a mintából is látjuk (a példában K = 3). A Menger-tétel szerint a minimális vágás mérete egyenlő a csúcsdiszjunkt utak maximális számával, ezért a feladat maximális folyam problémára vezethető vissza. Minden csúcsot két csúcsra bontunk (be és ki), a be-ki él kapacitása 1, a pályaszakaszoké végtelen. A forrás az 1 kimenő csúcsa, a nyelő az N bemenő csúcsa. A Dinic-algoritmus a maximális folyamot adja, a minimális vágást pedig a folyam utáni maradékhálón a forrásból elérhető csúcsok határa adja: az a csúcs kontrollpont, amelynek a bemenő csúcsa elérhető, de a kimenő csúcsa nem. Mivel a hálón minden út átmegy legalább egy egységkapacitású élen, a Dinic gyorsan fut: a gráf 2N csúcsú, N + M élű.
*/
/*
Hint 1: || Keress minimális számú csúcsot, amelyek mindegyik 1-ből N-be vezető útról legalább egyet lefognak. Ez egy minimális csúcs-vágás, és a Menger-tétel miatt ugyanannyi, mint a csúcsdiszjunkt utak maximális száma. ||
Hint 2: || A csúcsdiszjunktságot úgy kényszerítheted ki, hogy minden csúcsot két csúcsra bontasz (bemenő és kimenő), és köztük egységnyi kapacitású élt húzol; a pályaszakaszok nagy kapacitású élek legyenek. ||
Hint 3: || A folyam lefutása után járd be a maradékgráfban a forrásból elérhető csúcsokat: kontrollpont az a csúcs, amelynek bemenő csúcsa elérhető, de a kimenő csúcsa nem. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev, cap;
};

class Dinic {
public:
    explicit Dinic(int n) : g(n), level(n), it(n) {}

    void addEdge(int u, int v, int cap) {
        g[u].push_back({v, (int)g[v].size(), cap});
        g[v].push_back({u, (int)g[u].size() - 1, 0});
    }

    long long maxFlow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (true) {
                int f = augment(s, t);
                if (f == 0) break;
                flow += f;
            }
        }
        return flow;
    }

    // a maradékhálón a forrásból elérhető csúcsok
    vector<char> reachable(int s) {
        vector<char> vis(g.size(), 0);
        queue<int> q;
        q.push(s);
        vis[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const Edge &e : g[u]) {
                if (e.cap > 0 && !vis[e.to]) {
                    vis[e.to] = 1;
                    q.push(e.to);
                }
            }
        }
        return vis;
    }

private:
    vector<vector<Edge>> g;
    vector<int> level, it;

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const Edge &e : g[u]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    // egy kiegészítő út keresése a szintezett gráfban, iteratív DFS-sel; 1-et ad, ha talált
    int augment(int s, int t) {
        vector<pair<int, int>> path;  // (csúcs, a csúcs élének indexe)
        int u = s;
        while (true) {
            if (u == t) {
                for (auto [v, i] : path) {
                    Edge &e = g[v][i];
                    e.cap -= 1;
                    g[e.to][e.rev].cap += 1;
                }
                return 1;
            }
            bool moved = false;
            for (int &i = it[u]; i < (int)g[u].size(); i++) {
                const Edge &e = g[u][i];
                if (e.cap > 0 && level[e.to] == level[u] + 1) {
                    path.push_back({u, i});
                    u = e.to;
                    moved = true;
                    break;
                }
            }
            if (!moved) {
                if (u == s) return 0;
                level[u] = -1;  // ebből a csúcsból már nem érhető el t
                auto [pu, pi] = path.back();
                path.pop_back();
                u = pu;
                it[u] = pi + 1;
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    auto inNode = [](int v) { return 2 * (v - 1); };
    auto outNode = [](int v) { return 2 * (v - 1) + 1; };
    const int INF = 1000000000;

    Dinic din(2 * N);
    for (int v = 1; v <= N; v++) {
        din.addEdge(inNode(v), outNode(v), (v == 1 || v == N) ? INF : 1);
    }
    for (int i = 1; i <= N - 1; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int to;
            cin >> to;
            din.addEdge(outNode(i), inNode(to), INF);
        }
    }

    int s = outNode(1), t = inNode(N);
    din.maxFlow(s, t);
    vector<char> vis = din.reachable(s);

    vector<int> cut;
    for (int v = 2; v <= N - 1; v++) {
        if (vis[inNode(v)] && !vis[outNode(v)]) cut.push_back(v);
    }

    cout << cut.size() << '\n';
    for (size_t i = 0; i < cut.size(); i++) {
        cout << cut[i] << (i + 1 < cut.size() ? ' ' : '\n');
    }
    if (cut.empty()) cout << '\n';
    return 0;
}
