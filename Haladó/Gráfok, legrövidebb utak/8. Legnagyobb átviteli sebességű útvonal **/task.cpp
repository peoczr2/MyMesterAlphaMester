/*
Megoldás lényege:
Ez a legnagyobb szűk keresztmetszetű út (minimax út) feladat: az út átviteli sebessége az útba eső élek minimuma, és ezt
kell maximalizálni. Az éleket sebesség szerint csökkenő sorrendben dolgozzuk fel, és egy diszjunkt halmaz (DSU)
struktúrában összevonjuk a csomópontokat. Abban a pillanatban, amikor P és Q egy halmazba kerül, az aktuális él sebessége
a válasz: a nála gyorsabb élekkel P és Q még nem volt összekötve. A feldolgozott élek erdőt alkotnak, így a P és Q közötti
út ebben az erdőben egyértelmű, szélességi bejárással visszakereshető. A futás O(M·log M) időben lefut, a rendezés dominál.
*/
/*
Hint 1: || Dolgozd fel az éleket sebesség szerint csökkenő sorrendben, és közben figyeld, mikor lesz P és Q összekötve. ||
Hint 2: || Az első pillanat, amikor P és Q egy komponensbe kerül, az aktuális él sebessége lesz a válasz. Ehhez egy diszjunkt halmaz (DSU) struktúra elég. ||
Hint 3: || A feldolgozott élekből csak erdő épül, így P és Q között egy egyértelmű út van. Ezt tárold el a feldolgozás közben, és szélességi bejárással add vissza a P–Q utat. ||
*/

#include <bits/stdc++.h>

using namespace std;

vector<int> parentDsu;

int findRoot(int x) {
    while (parentDsu[x] != x) {
        parentDsu[x] = parentDsu[parentDsu[x]];
        x = parentDsu[x];
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int p, q;
    cin >> p >> q;

    struct Edge {
        int speed, u, v;
    };
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].speed;
    }
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) { return a.speed > b.speed; });

    parentDsu.resize(n + 1);
    for (int i = 0; i <= n; ++i) parentDsu[i] = i;

    vector<vector<int>> forest(n + 1);   // a már feldolgozott (erdő-)élek
    int answer = 0;
    bool connected = false;

    for (const Edge &e : edges) {
        int ru = findRoot(e.u), rv = findRoot(e.v);
        if (ru != rv) {
            parentDsu[ru] = rv;
            forest[e.u].push_back(e.v);
            forest[e.v].push_back(e.u);
        }
        if (findRoot(p) == findRoot(q)) {
            answer = e.speed;
            connected = true;
            break;
        }
    }

    if (!connected) {
        cout << 0 << '\n';
        return 0;
    }

    // Szélességi bejárás az erdőben P-től, a visszavezető úttal.
    vector<int> from(n + 1, 0);
    vector<char> seen(n + 1, 0);
    queue<int> qu;
    qu.push(p);
    seen[p] = 1;
    while (!qu.empty()) {
        int u = qu.front();
        qu.pop();
        for (int v : forest[u]) {
            if (!seen[v]) {
                seen[v] = 1;
                from[v] = u;
                qu.push(v);
            }
        }
    }

    vector<int> path;
    for (int v = q; v != p; v = from[v]) path.push_back(v);
    path.push_back(p);
    reverse(path.begin(), path.end());

    cout << answer << '\n';
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << (i + 1 < path.size() ? ' ' : '\n');
    }
    return 0;
}
