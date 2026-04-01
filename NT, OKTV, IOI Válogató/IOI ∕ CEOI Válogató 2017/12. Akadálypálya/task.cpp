/*
Megoldás lényege:
Legyen a start az egyetlen olyan csúcs, amelybe nem vezet él, a cél pedig az,
amelyből nem vezet él. Egy start-tól célig vezető útvonalakra keresett két pont
pontosan egy 2 elemű csúcsvágás.

A gráfot csúcsszétválasztással alakítjuk át: minden belső csúcsból in->out él lesz
1 kapacitással, a startból és a célból pedig INF kapacitású él. Az eredeti élek
out->in irányban mennek INF kapacitással. Ezután legfeljebb 3 egységnyi max-flowt
számolunk (Edmonds-Karp BFS-sel). Ha legalább 3 egység flow van, akkor nincs két
pont, különben a maradék gráfban a source-ból elérhető in/out határán lévő csúcsok
adják a minimális vágást. Egyetlen ilyen csúcs esetén ugyanazt kétszer írjuk ki.
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev, cap;
};

static const int INF = 3;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<pair<int, int>> edges;
    edges.reserve(m);
    vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
        ++indeg[v];
        ++outdeg[u];
    }

    int s = 1, t = 1;
    for (int i = 1; i <= n; ++i) {
        if (indeg[i] == 0) s = i;
        if (outdeg[i] == 0) t = i;
    }

    auto inNode = [&](int v) { return 2 * (v - 1); };
    auto outNode = [&](int v) { return 2 * (v - 1) + 1; };

    int V = 2 * n;
    vector<vector<Edge>> g(V);
    auto addEdge = [&](int a, int b, int cap) {
        Edge f{b, (int)g[b].size(), cap};
        Edge r{a, (int)g[a].size(), 0};
        g[a].push_back(f);
        g[b].push_back(r);
    };

    for (int v = 1; v <= n; ++v) {
        int cap = (v == s || v == t) ? INF : 1;
        addEdge(inNode(v), outNode(v), cap);
    }
    for (auto [u, v] : edges) {
        addEdge(outNode(u), inNode(v), INF);
    }

    int source = outNode(s);
    int sink = inNode(t);

    long long flow = 0;
    while (flow < 3) {
        vector<int> parentV(V, -1), parentE(V, -1);
        queue<int> q;
        q.push(source);
        parentV[source] = source;
        while (!q.empty() && parentV[sink] == -1) {
            int v = q.front();
            q.pop();
            for (int i = 0; i < (int)g[v].size(); ++i) {
                if (g[v][i].cap <= 0) continue;
                int to = g[v][i].to;
                if (parentV[to] != -1) continue;
                parentV[to] = v;
                parentE[to] = i;
                q.push(to);
                if (to == sink) break;
            }
        }
        if (parentV[sink] == -1) break;

        int aug = INF;
        for (int v = sink; v != source; v = parentV[v]) {
            aug = min(aug, g[parentV[v]][parentE[v]].cap);
        }
        for (int v = sink; v != source; v = parentV[v]) {
            Edge &e = g[parentV[v]][parentE[v]];
            e.cap -= aug;
            g[v][e.rev].cap += aug;
        }
        flow += aug;
    }

    if (flow >= 3) {
        cout << "0 0\n";
        return 0;
    }

    vector<char> vis(V, 0);
    queue<int> q;
    q.push(source);
    vis[source] = 1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (const auto& e : g[v]) {
            if (e.cap > 0 && !vis[e.to]) {
                vis[e.to] = 1;
                q.push(e.to);
            }
        }
    }

    vector<int> cut;
    for (int v = 1; v <= n; ++v) {
        if (v == s || v == t) continue;
        if (vis[inNode(v)] && !vis[outNode(v)]) cut.push_back(v);
    }

    if (cut.empty()) {
        cout << "0 0\n";
    } else if (cut.size() == 1) {
        cout << cut[0] << ' ' << cut[0] << '\n';
    } else {
        cout << cut[0] << ' ' << cut[1] << '\n';
    }

    return 0;
}