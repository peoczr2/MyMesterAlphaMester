/*
Megoldás lényege:
A malmokat egyetlen közös kiindulópontnak tekintjük: a DSU-ban előre egy halmazba vonjuk őket, így a feladat a malmokat gyökérnek tekintő minimális összhosszú feszítőerdő keresésére vezet. Kruskal-algoritmussal az utakat hossz szerint növekvő sorrendben dolgozzuk fel, és csak azt az utat vesszük be, amely két még különálló városcsoportot köt össze. Minden nem malom városba pontosan egy út vezet, így a kiválasztott N-M út összhossza adja a minimális költséget. A kamionok szülőit a kiválasztott utakon a malmoktól indított szélességi bejárással határozzuk meg: minden városhoz azt a várost írjuk, ahonnan először elértük. Az időigény a rendezés miatt O(U log U), a DSU-műveletek gyakorlatilag állandó idejűek.
*/
/*
Hint 1: || Ha az összes malmot egyetlen közös csomópontnak tekinted, a feladat egy minimális összsúlyú feszítőfa keresésére vezet. ||
Hint 2: || Használj Kruskal-algoritmust: az utakat hossz szerint rendezd, és csak azt vedd be, amely két különböző városcsoportot köt össze; a csoportokat uniós-megtalálós (DSU) struktúrával kezeld, a malmokat kezdetben egy csoportba tedd. Az eredményül kapott utakból szélességi bejárással, a malmoktól indulva kapod meg minden városhoz a szülőt. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int a, b, w;
};

vector<int> dsu;

int findSet(int x) {
    while (dsu[x] != x) {
        dsu[x] = dsu[dsu[x]];
        x = dsu[x];
    }
    return x;
}

bool unite(int x, int y) {
    x = findSet(x);
    y = findSet(y);
    if (x == y) return false;
    dsu[x] = y;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, u;
    cin >> n >> m >> u;

    vector<int> mills(m);
    for (int& x : mills) cin >> x;

    vector<Edge> edges(u);
    for (Edge& e : edges) cin >> e.a >> e.b >> e.w;

    dsu.resize(n + 1);
    iota(dsu.begin(), dsu.end(), 0);
    for (int i = 1; i < m; i++) unite(mills[0], mills[i]);

    sort(edges.begin(), edges.end(), [](const Edge& x, const Edge& y) { return x.w < y.w; });

    long long total = 0;
    vector<vector<int>> g(n + 1);
    for (const Edge& e : edges) {
        if (unite(e.a, e.b)) {
            total += e.w;
            g[e.a].push_back(e.b);
            g[e.b].push_back(e.a);
        }
    }

    // Szélességi bejárás a malmoktól: from[v] a v-be közvetlenül szállító város (malom: 0).
    vector<int> from(n + 1, 0);
    vector<char> seen(n + 1, 0);
    queue<int> q;
    for (int x : mills) {
        if (!seen[x]) {
            seen[x] = 1;
            q.push(x);
        }
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (!seen[to]) {
                seen[to] = 1;
                from[to] = v;
                q.push(to);
            }
        }
    }

    cout << total << '\n';
    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << ' ';
        cout << from[i];
    }
    cout << '\n';
    return 0;
}
