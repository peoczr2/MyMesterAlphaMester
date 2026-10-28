/*
Megoldás lényege:
A feladat két olyan P–Q útvonal, amelyek a végpontokon kívül nem érintkeznek, vagyis két csúcsdiszjunkt út. Ezt folyammal oldjuk meg: minden P-től és Q-tól különböző csúcsot egy be- és egy kimeneti csúcsra bontunk egy 1 kapacitású éllel, így rajta legfeljebb egy út haladhat át. Minden irányítatlan élt két irányított élként veszünk fel, szintén 1 kapacitással, de P bemenetébe és Q kimenetéből nem vezetünk élt. A feltétel miatt két ilyen út létezik (Menger-tétel), ezért két kapacitásnövelő BFS-út biztosan talál 2 egységnyi folyamot. A folyam éleit P-től Q-ig követve kapjuk a két útvonalat. Az időigény két BFS, azaz O(N + M).
*/
/*
Hint 1: || Két útvonal kell, amelyek a végpontokon kívül nem találkoznak. Ezt úgy keresd, mint egy folyamot P-től Q-ig, ahol a köztes csúcsokon legfeljebb egy egység mehet át. ||
Hint 2: || Bontsd minden köztes csúcsot egy be- és egy kimeneti csúcsra, köztük 1 kapacitású éllel. Minden irányítatlan élből két irányított élt vegyél fel, szintén 1 kapacitással. ||
Hint 3: || Két növelő úttal (BFS) kapsz 2 egységnyi folyamot. A folyam éleit P-től Q-ig követve kiolvashatod az útvonalakat; P bemenetébe és Q kimenetéből ne vezess élt. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev, cap;
    bool forward;
};

vector<vector<Edge>> g;

void addEdge(int u, int v, int cap) {
    g[u].push_back({v, (int)g[v].size(), cap, true});
    g[v].push_back({u, (int)g[u].size() - 1, 0, false});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, p, q;
    cin >> n >> m >> p >> q;

    // v bemeneti csúcsa 2v, kimeneti csúcsa 2v+1
    g.assign(2 * n + 2, vector<Edge>());
    for (int v = 1; v <= n; ++v)
        if (v != p && v != q)
            addEdge(2 * v, 2 * v + 1, 1);

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        // P bemenetébe és Q kimenetéből nem vezetünk élt
        if (x != q && y != p) addEdge(2 * x + 1, 2 * y, 1);
        if (y != q && x != p) addEdge(2 * y + 1, 2 * x, 1);
    }

    const int s = 2 * p + 1, t = 2 * q;
    int flow = 0;
    while (flow < 2) {
        vector<int> prevNode(g.size(), -1), prevEdge(g.size(), -1);
        vector<char> seen(g.size(), 0);
        queue<int> qu;
        qu.push(s);
        seen[s] = 1;
        while (!qu.empty() && !seen[t]) {
            int x = qu.front();
            qu.pop();
            for (int i = 0; i < (int)g[x].size(); ++i) {
                const Edge &e = g[x][i];
                if (e.cap > 0 && !seen[e.to]) {
                    seen[e.to] = 1;
                    prevNode[e.to] = x;
                    prevEdge[e.to] = i;
                    qu.push(e.to);
                }
            }
        }
        if (!seen[t]) break;
        for (int v = t; v != s; v = prevNode[v]) {
            Edge &e = g[prevNode[v]][prevEdge[v]];
            e.cap -= 1;
            g[v][e.rev].cap += 1;
        }
        ++flow;
    }

    // a folyam éleit P-től Q-ig követve kiolvassuk az utakat
    for (int k = 0; k < flow; ++k) {
        vector<int> path = {p};
        int cur = s;
        while (cur != t) {
            Edge *next = nullptr;
            for (Edge &e : g[cur])
                if (e.forward && e.cap == 0) {
                    next = &e;
                    break;
                }
            next->cap = 1;  // a felhasznált egységet elfogyasztjuk
            cur = next->to;
            if (cur % 2 == 0) path.push_back(cur / 2);
        }
        for (size_t i = 0; i < path.size(); ++i) {
            if (i) cout << ' ';
            cout << path[i];
        }
        cout << '\n';
    }
}
