/*
Megoldás lényege:
Három város összekötéséhez a minimális költségű részgráf egy U csomópontban ágazik el: innen indul három út A-ba, B-be és C-be, és ezek költsége adja az építési költséget. Ezért minden N csomópontból Dijkstra-algoritmussal kiszámoljuk a legolcsóbb távolságot A-ba, B-be és C-be, majd minden v csomópontra vesszük a három távolság összegét; a minimum adja a minimális költséget. Ha ez nem véges, a három város nem köthető össze, és a kimenet -1. Különben a kiépítendő szakaszok a minimumot adó v csomópontból az A, B, C felé vezető legolcsóbb utak éleinek egyesítése; minden élt egyszer írunk ki. Az időigény három Dijkstra-futás, N <= 100 és M <= 1000 mellett elhanyagolható.
*/
/*
Hint 1: || A három város összekötésénél az optimális hálózat elágazási pontot tartalmaz; ezt a pontot nem kell előre ismerned, elég minden csomópontra megvizsgálni. ||
Hint 2: || Futtass Dijkstra-algoritmust külön-külön az A, a B és a C városból, és tárold el minden csomópontra a távolságot és az utolsó élt, amelyen oda értünk; így egy csomópontból visszafelé végig tudod követni az utat. ||
Hint 3: || Válaszd azt a v csomópontot, amelyre a három távolság összege minimális, majd v-ből mindhárom forrásig visszakövetve jelöld meg az utak éleit; az egyforma élt csak egyszer számold és írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    int A, B, C;
    cin >> A >> B >> C;

    vector<Edge> E(M);
    vector<vector<pair<int, int>>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        cin >> E[i].u >> E[i].v >> E[i].w;
        adj[E[i].u].push_back({E[i].v, i});
        adj[E[i].v].push_back({E[i].u, i});
    }

    const long long INF = LLONG_MAX / 4;

    // Dijkstra egy forrásból: távolság, előző csomópont és az ott használt él.
    auto dijkstra = [&](int src, vector<long long>& dist, vector<int>& pnode, vector<int>& pedge) {
        dist.assign(N + 1, INF);
        pnode.assign(N + 1, -1);
        pedge.assign(N + 1, -1);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        dist[src] = 0;
        pq.push({0, src});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;
            for (auto [to, ei] : adj[u]) {
                long long nd = d + E[ei].w;
                if (nd < dist[to]) {
                    dist[to] = nd;
                    pnode[to] = u;
                    pedge[to] = ei;
                    pq.push({nd, to});
                }
            }
        }
    };

    vector<long long> dA, dB, dC;
    vector<int> pnA, peA, pnB, peB, pnC, peC;
    dijkstra(A, dA, pnA, peA);
    dijkstra(B, dB, pnB, peB);
    dijkstra(C, dC, pnC, peC);

    long long best = INF;
    int bv = -1;
    for (int v = 1; v <= N; v++) {
        if (dA[v] >= INF || dB[v] >= INF || dC[v] >= INF) continue;
        long long s = dA[v] + dB[v] + dC[v];
        if (s < best) {
            best = s;
            bv = v;
        }
    }

    if (bv == -1) {
        cout << -1 << "\n";
        return 0;
    }

    // Az A, B, C városokból a bv csomópontig vezető utak éleit írjuk ki, a forrástól indulva.
    vector<bool> printed(M, false);
    vector<pair<int, int>> lines;
    long long cost = 0;
    auto collect = [&](int src, const vector<int>& pnode, const vector<int>& pedge) {
        vector<int> path;
        int cur = bv;
        while (cur != src) {
            path.push_back(cur);
            cur = pnode[cur];
        }
        path.push_back(src);
        reverse(path.begin(), path.end());
        for (size_t i = 0; i + 1 < path.size(); i++) {
            int ei = pedge[path[i + 1]];
            if (!printed[ei]) {
                printed[ei] = true;
                cost += E[ei].w;
                lines.push_back({path[i], path[i + 1]});
            }
        }
    };
    collect(A, pnA, peA);
    collect(B, pnB, peB);
    collect(C, pnC, peC);

    cout << cost << "\n";
    cout << lines.size() << "\n";
    for (auto [a, b] : lines) {
        cout << a << " " << b << "\n";
    }
    return 0;
}
