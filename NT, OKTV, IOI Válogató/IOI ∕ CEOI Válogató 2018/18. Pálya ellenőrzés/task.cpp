/*
Megoldás lényege:
Minden ellenőr a startól a célig megy, így egy ellenőr egy folyamegységnek felel meg. Az a követelmény,
hogy minden elágazási ponton haladjon át ellenőr, azt jelenti, hogy a csúcsokon átmenő folyamnak legalább
1 egységnek kell lennie: ez a feladat alsó korlátos minimális folyam. Minden csúcsot be- és kicsúcsra
bontunk, a be-ki élre alsó korlát 1 kerül, a pályaszakaszok irányított élek végtelen kapacitással.
Először egy megengedett folyamot keresünk szuperforrással és szuperszumnyelővel (Dinic), majd a cél
kicsúcsából a start becsúcsa felé húzott végtelen élen a folyamot a lehető legnagyobb mértékben
visszatoljuk. A minimális folyam értéke a két lépés különbsége.
Idő: Dinic-algoritmus a csúcsok és élek számában; a térkép planáris, így az élek száma O(N).
*/
/*
Hint 1: || Minden ellenőr start-ból célba megy, így egy ellenőr egy folyamegységnek felel meg. Gondold át, hogy a minden elágazási ponton áthalad legalább egy ellenőr feltétel milyen alsó korlátot jelent a csúcsokon átmenő folyamra, és ekkor mit kell minimalizálni. ||
Hint 2: || Bontsd minden csúcsot egy be- és egy kimeneti csúcsra, és a kettő közötti élre alsó korlát 1 kerüljön. A pályaszakaszok irányított élek, kapacitásuk végtelen. ||
Hint 3: || Alsó korlátos folyamnál először szuperforrással és szuperszumnyelővel keress megengedett folyamot, és vedd fel a cél kicsúcsából a start becsúcsa felé mutató végtelen élt. Ezután ennek az élnek a folyamát csökkentsd a célból a startba visszatolható maximális mennyiséggel. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Dinic-algoritmus: maximális folyam
struct Dinic {
    struct Edge {
        int to, rev, cap;
    };
    vector<vector<Edge>> g;
    vector<int> level, it;

    explicit Dinic(int n) : g(n), level(n), it(n) {}

    // Él hozzáadása; visszaadja az él indexét a from csúcs listájában
    int addEdge(int from, int to, int cap) {
        g[from].push_back({to, (int)g[to].size(), cap});
        g[to].push_back({from, (int)g[from].size() - 1, 0});
        return (int)g[from].size() - 1;
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (const Edge &e : g[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    int dfs(int v, int t, int f) {
        if (v == t) return f;
        int pushed = 0;
        for (int &i = it[v]; i < (int)g[v].size(); i++) {
            Edge &e = g[v][i];
            if (e.cap > 0 && level[e.to] == level[v] + 1) {
                int d = dfs(e.to, t, min(f - pushed, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    pushed += d;
                    if (pushed == f) return pushed;
                }
            }
        }
        return pushed;
    }

    long long maxflow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (int f = dfs(s, t, INT_MAX)) flow += f;
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    const int INF = 1000000000;

    // v. elágazási pont: be = 2(v-1), ki = 2(v-1)+1
    auto in = [](int v) { return 2 * (v - 1); };
    auto out = [](int v) { return 2 * (v - 1) + 1; };
    const int SS = 2 * n, TT = 2 * n + 1;
    Dinic din(2 * n + 2);

    for (int v = 1; v <= n; v++) {
        din.addEdge(in(v), out(v), INF);  // csúcs-él; az alsó korlát 1 a kapacitásból levonva, így INF marad
        din.addEdge(SS, out(v), 1);       // a ki-csúcsra 1 egység többlet érkezik az alsó korlátból
        din.addEdge(in(v), TT, 1);        // a be-csúcsból 1 egység hiányzik
    }
    // Pályaszakaszok: az i. sor az i. pontból induló szakaszokat adja meg
    for (int u = 1; u < n; u++) {
        int cnt;
        cin >> cnt;
        for (int j = 0; j < cnt; j++) {
            int v;
            cin >> v;
            din.addEdge(out(u), in(v), INF);
        }
    }

    // A folyam a start be-csúcsából indul, a cél ki-csúcsába érkezik; ezt a végtelen éllel zárjuk körré
    const int S = in(1), T = out(n);
    const int back = din.addEdge(T, S, INF);

    // 1. lépés: megengedett folyam
    din.maxflow(SS, TT);
    const int revIdx = din.g[T][back].rev;
    const long long f0 = din.g[S][revIdx].cap;  // a körélen átmenő folyam

    // 2. lépés: a körélt eltávolítjuk, és a folyamot T-ből S-be visszatoljuk
    din.g[T][back].cap = 0;
    din.g[S][revIdx].cap = 0;
    const long long r = din.maxflow(T, S);

    cout << f0 - r << '\n';
    return 0;
}
