/*
Megoldás lényege:
Először meg kell építeni a főváros (F) és a legnépesebb város (L) közötti
legolcsóbb vasútvonalat, vagyis a legrövidebb utat a gráfban. Ezután a már elért
városokból indulva mindig a legolcsóbb, új várost elérő szakaszt választjuk. Ez
pontosan egy Prim-szerű bővítés egy kezdeti fáról.

Ezért az algoritmus két részből áll:
1. Dijkstra F-ből L-ig, a szülőéllel visszaépítjük az induló utat.
2. Az így elért városokból prioritási sorral folytatjuk a legolcsóbb új él
   kiválasztását, amíg legalább K másik várost el nem érünk.

Az eredmény a kiválasztott élek listája és ezek összköltsége.
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int cost;
    int id;
};

struct Item {
    int cost;
    int from;
    int to;
    int id;
    bool operator>(const Item& other) const {
        if (cost != other.cost) return cost > other.cost;
        if (from != other.from) return from > other.from;
        if (to != other.to) return to > other.to;
        return id > other.id;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, f, l;
    if (!(cin >> n >> k >> f >> l)) return 0;

    int m;
    cin >> m;
    vector<vector<Edge>> g(n + 1);
    vector<int> ea(m + 1), eb(m + 1), ec(m + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> ea[i] >> eb[i] >> ec[i];
        g[ea[i]].push_back({eb[i], ec[i], i});
        g[eb[i]].push_back({ea[i], ec[i], i});
    }

    const long long INF = (1LL << 60);
    vector<long long> dist(n + 1, INF);
    vector<int> parentV(n + 1, -1), parentE(n + 1, -1);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dist[f] = 0;
    pq.push({0, f});
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d != dist[v]) continue;
        for (const auto& e : g[v]) {
            long long nd = d + e.cost;
            if (nd < dist[e.to]) {
                dist[e.to] = nd;
                parentV[e.to] = v;
                parentE[e.to] = e.id;
                pq.push({nd, e.to});
            }
        }
    }

    vector<int> chosenEdges;
    vector<char> reached(n + 1, 0);
    long long totalCost = 0;

    vector<int> pathNodes;
    for (int v = l; v != -1; v = parentV[v]) pathNodes.push_back(v);
    reverse(pathNodes.begin(), pathNodes.end());
    for (int i = 0; i + 1 < (int)pathNodes.size(); ++i) {
        int v = pathNodes[i + 1];
        reached[v] = 1;
        chosenEdges.push_back(parentE[v]);
        totalCost += ec[parentE[v]];
    }
    reached[f] = 1;

    int reachedCount = (int)pathNodes.size() - 1;

    priority_queue<Item, vector<Item>, greater<Item>> best;
    auto pushEdges = [&](int v) {
        for (const auto& e : g[v]) {
            if (!reached[e.to]) {
                best.push({e.cost, v, e.to, e.id});
            }
        }
    };

    for (int v : pathNodes) pushEdges(v);

    while (reachedCount < k && !best.empty()) {
        Item cur = best.top();
        best.pop();
        if (reached[cur.to]) continue;
        reached[cur.to] = 1;
        ++reachedCount;
        chosenEdges.push_back(cur.id);
        totalCost += cur.cost;
        pushEdges(cur.to);
    }

    cout << totalCost << '\n';
    cout << chosenEdges.size() << '\n';
    for (int id : chosenEdges) {
        cout << ea[id] << ' ' << eb[id] << '\n';
    }
    return 0;
}