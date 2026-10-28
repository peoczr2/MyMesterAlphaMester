/*
Megoldás lényege:
Két olyan 1-ből induló utat keresünk, amelyek az 1. városon kívül nem érintenek közös várost, az egyik U-ba, a másik V-be ér. Ez csúcsdiszjunkt utak kérdése, amelyet folyammal oldunk meg: minden várost két csúcsra bontunk (be és ki), a befelé és a kifelé csúcsot 1-es kapacitású él köti össze, így minden várost legfeljebb egy út érinthet. A közlekedési utakat a kifelé csúcsoktól a befelé csúcsokig vezető, 1-es kapacitású élek jelentik. Az U és V kifelé csúcsából egy közös T nyelőbe vezet él, az 1. város kifelé csúcsa a forrás. Ha a maximális folyam értéke 2, akkor a két útvonal kiolvasható a folyamból: a folyam minden városon legfeljebb egy úton halad át, így a két út csak az 1. városban találkozik. Mivel minden él kisebb sorszámú városból a nagyobba mutat, a gráf körmentes, és a folyam nem tartalmaz kört. Legfeljebb két megnövelő utat keresünk BFS-sel, így az idő O(N + M).
*/
/*
Hint 1: || Két úton kell eljutni 1-ből U-ba és V-be úgy, hogy a két út csak 1-ben találkozzon. Ez csúcsdiszjunkt utak kérdése, amelyet folyammal lehet megoldani. ||
Hint 2: || Minden várost bontsd két csúcsra (befelé és kifelé), köztük 1-es kapacitású él legyen. Az U és a V kifelé csúcsából egy közös T nyelőbe menjen él. ||
Hint 3: || Ha a maximális folyam értéke 2, a két útvonal a folyam élein végigkövetve adódik. Ha kisebb, nincs megoldás, és 0 0 a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev, cap, orig;
    bool taken;
};

vector<vector<Edge>> g;

void addEdge(int a, int b, int c) {
    g[a].push_back({b, (int)g[b].size(), c, c, false});
    g[b].push_back({a, (int)g[a].size() - 1, 0, 0, false});
}

// Egy megnövelő út keresése BFS-sel; igaz, ha talált.
bool augment(int s, int t) {
    vector<int> prevNode(g.size(), -1), prevEdge(g.size(), -1);
    queue<int> q;
    prevNode[s] = s;
    q.push(s);
    while (!q.empty() && prevNode[t] == -1) {
        int x = q.front();
        q.pop();
        for (int e = 0; e < (int)g[x].size(); ++e) {
            const Edge &ed = g[x][e];
            if (ed.cap > 0 && prevNode[ed.to] == -1) {
                prevNode[ed.to] = x;
                prevEdge[ed.to] = e;
                q.push(ed.to);
            }
        }
    }
    if (prevNode[t] == -1) return false;
    for (int v = t; v != s; v = prevNode[v]) {
        Edge &ed = g[prevNode[v]][prevEdge[v]];
        ed.cap -= 1;
        g[v][ed.rev].cap += 1;
    }
    return true;
}

int main() {
    int n, u, v, m;
    cin >> n >> u >> v >> m;

    auto in = [](int x) { return 2 * x; };
    auto out = [](int x) { return 2 * x + 1; };
    int T = 2 * n + 2;
    g.assign(2 * n + 3, {});

    for (int x = 2; x <= n; ++x) addEdge(in(x), out(x), 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        addEdge(out(a), in(b), 1);
    }
    addEdge(out(u), T, 1);
    addEdge(out(v), T, 1);

    int flow = 0;
    while (flow < 2 && augment(out(1), T)) ++flow;

    if (flow < 2) {
        cout << "0 0\n";
        return 0;
    }

    // Egy út kiolvasása: a forrás kifelé éleiből indulunk, a foglalt éleket megjelöljük.
    auto extract = [&](int &endCity) {
        vector<int> path = {1};
        int cur = out(1);
        while (true) {
            int pick = -1;
            for (int e = 0; e < (int)g[cur].size(); ++e) {
                const Edge &ed = g[cur][e];
                if (ed.orig == 1 && ed.cap == 0 && !ed.taken) {
                    pick = e;
                    break;
                }
            }
            if (pick == -1) break;
            Edge &ed = g[cur][pick];
            ed.taken = true;
            if (ed.to == T) {
                endCity = path.back();
                break;
            }
            int city = ed.to / 2;
            path.push_back(city);
            cur = out(city);
        }
        return path;
    };

    int endA = -1, endB = -1;
    vector<int> p1 = extract(endA);
    vector<int> p2 = extract(endB);

    vector<int> toU, toV;
    if (endA == u) {
        toU = p1;
        toV = p2;
    } else {
        toU = p2;
        toV = p1;
    }

    cout << toU.size() << ' ' << toV.size() << "\n";
    for (size_t i = 0; i < toU.size(); ++i) cout << toU[i] << (i + 1 < toU.size() ? ' ' : '\n');
    for (size_t i = 0; i < toV.size(); ++i) cout << toV[i] << (i + 1 < toV.size() ? ' ' : '\n');
    return 0;
}
