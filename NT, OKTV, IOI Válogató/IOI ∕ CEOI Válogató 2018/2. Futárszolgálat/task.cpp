/*
Megoldás lényege:
Fa esetén a kézbesítendő városokat tartalmazó minimális összekötő részfa (Steiner-féle
részfa) minden szükséges utat tartalmaz. Ennek az összes éle kétszer járva be az
összköltség 2*összeg lenne, de az optimális séta két végpontja a részfa átmérőjének
végpontjai, ezért az átmérő mentén nem kell visszafordulni.

Először gyökeres DFS-sel kiszámítjuk minden csúcsban a kézbesítendő városok számát
a részfában. Egy él pontosan akkor része a szükséges részfának, ha a gyereke oldalán
1 és K-1 közötti kézbesítendő város van. Ezután a kiválasztott részfán két DFS-sel
megtaláljuk az átmérőt, majd ezen az átmérőn vezetjük végig a sétát, a mellékágakat
pedig visszaforduló bejárással járjuk be.
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int w;
    int id;
};

struct State {
    int v, p, idx;
};

static void appendClosedWalk(const vector<vector<Edge>>& g, int start, int parentForbidden,
                             const vector<char>& onMain, vector<int>& out) {
    out.push_back(start);
    vector<State> st;
    st.push_back({start, parentForbidden, 0});

    while (!st.empty()) {
        State &cur = st.back();
        while (cur.idx < (int)g[cur.v].size()) {
            int to = g[cur.v][cur.idx++].to;
            if (to == cur.p || onMain[to]) continue;
            out.push_back(to);
            st.push_back({to, cur.v, 0});
            goto next_iteration;
        }

        {
            int parent = cur.p;
            st.pop_back();
            if (!st.empty()) out.push_back(st.back().v);
            else if (parent != -1) out.push_back(parent);
        }
        next_iteration: ;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<vector<Edge>> g(n + 1);
    struct RawEdge { int u, v, w; };
    vector<RawEdge> edges;
    edges.reserve(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        edges.push_back({a, b, w});
        g[a].push_back({b, w, i});
        g[b].push_back({a, w, i});
    }

    vector<int> terminals(k);
    for (int i = 0; i < k; ++i) cin >> terminals[i];

    if (k == 1) {
        cout << 0 << '\n' << terminals[0] << '\n';
        return 0;
    }

    vector<int> parent(n + 1, 0), parentEdge(n + 1, -1), order;
    order.reserve(n);
    vector<int> stack = {1};
    parent[1] = -1;
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        order.push_back(v);
        for (const auto& e : g[v]) {
            if (e.to == parent[v]) continue;
            parent[e.to] = v;
            parentEdge[e.to] = e.id;
            stack.push_back(e.to);
        }
    }

    vector<int> termCount(n + 1, 0);
    vector<char> isTerminal(n + 1, 0);
    for (int x : terminals) isTerminal[x] = 1;
    for (int x : terminals) termCount[x] = 1;
    long long totalWeight = 0;

    vector<char> takeEdge(n - 1, 0);
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int v = order[i];
        if (parent[v] != -1) termCount[parent[v]] += termCount[v];
        if (parent[v] != -1 && termCount[v] > 0 && termCount[v] < k) {
            takeEdge[parentEdge[v]] = 1;
            totalWeight += edges[parentEdge[v]].w;
        }
    }

    vector<vector<Edge>> sub(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        if (!takeEdge[i]) continue;
        auto e = edges[i];
        sub[e.u].push_back({e.v, e.w, i});
        sub[e.v].push_back({e.u, e.w, i});
    }

    auto farthest = [&](int s) {
        vector<long long> dist(n + 1, -1);
        vector<int> par(n + 1, -1);
        vector<int> st = {s};
        dist[s] = 0;
        for (size_t it = 0; it < st.size(); ++it) {
            int v = st[it];
            for (const auto& e : sub[v]) {
                if (e.to == par[v]) continue;
                if (dist[e.to] != -1) continue;
                dist[e.to] = dist[v] + e.w;
                par[e.to] = v;
                st.push_back(e.to);
            }
        }
        int best = s;
        for (int v = 1; v <= n; ++v) if (dist[v] > dist[best]) best = v;
        return tuple<int, vector<int>, vector<long long>>(best, par, dist);
    };

    int any = terminals[0];
    while (any <= n && sub[any].empty()) ++any;
    if (any > n) any = terminals[0];

    auto [u, par1, dist1] = farthest(any);
    auto [v, par2, dist2] = farthest(u);

    totalWeight = 0;
    for (int i = 0; i < n - 1; ++i) if (takeEdge[i]) totalWeight += edges[i].w;
    long long answerDist = 2 * totalWeight - dist2[v];

    vector<int> mainPath;
    for (int x = v; x != -1; x = par2[x]) mainPath.push_back(x);
    reverse(mainPath.begin(), mainPath.end());

    vector<char> onMain(n + 1, 0);
    for (int x : mainPath) onMain[x] = 1;

    vector<int> walk;
    walk.reserve(2 * n);
    walk.push_back(mainPath[0]);
    for (int i = 0; i < (int)mainPath.size(); ++i) {
        int cur = mainPath[i];
        for (const auto& e : sub[cur]) {
            int to = e.to;
            if (i + 1 < (int)mainPath.size() && to == mainPath[i + 1]) continue;
            if (i > 0 && to == mainPath[i - 1]) continue;
            if (onMain[to]) continue;
            appendClosedWalk(sub, to, cur, onMain, walk);
        }
        if (i + 1 < (int)mainPath.size()) walk.push_back(mainPath[i + 1]);
    }

    cout << answerDist << '\n';
    for (int i = 0; i < (int)walk.size(); ++i) {
        if (i) cout << ' ';
        cout << walk[i];
    }
    cout << '\n';
    return 0;
}