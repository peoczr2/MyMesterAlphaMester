/*
Megoldás lényege:
Két csomópont közötti útvonal sávszélessége az útvonal legkeskenyebb vezetékének sávszélessége, ezért a legjobb útvonalat úgy kapjuk, hogy a vezetékeket csökkenő sávszélesség szerint egyesével hozzáadjuk egy diszjunkt halmaz (DSU) szerkezethez. Amint az A és B csomópont ugyanabba a halmazba kerül, az éppen hozzáadott vezeték sávszélessége a keresett érték, mert a nagyobb sávszélességű vezetékekből még nem tudtak összeköttetést kialakítani. Ha ez nem következik be, a válasz 0. Az időigény O(M log M) a rendezés miatt, ami az M <= 100 000 esetén a 0,1 mp-es időlimitbe belefér.
*/
/*
Hint 1: || Egy útvonal sávszélessége a legszűkebb vezetékétől függ, ezért érdemes a nagy sávszélességű vezetékeket előre venni. ||
Hint 2: || Rendezd a vezetékeket csökkenő sávszélesség szerint, és egyesével vedd hozzá őket egy diszjunkt halmaz (DSU) szerkezethez. ||
Hint 3: || Az a pillanat adja a választ, amikor A és B ugyanabba a halmazba kerül: az éppen hozzáadott vezeték sávszélessége lesz a keresett érték. Ha ez soha nem történik meg, a kiírandó szám 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Dsu {
    vector<int> parent;
    explicit Dsu(int n) : parent(n + 1) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void unite(int a, int b) { parent[find(a)] = find(b); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    cin >> n >> a >> b;
    int m;
    cin >> m;

    // (sávszélesség, csomópont, csomópont)
    vector<array<int, 3>> edges(m);
    for (auto &e : edges) {
        int u, v, s;
        cin >> u >> v >> s;
        e = {s, u, v};
    }
    sort(edges.rbegin(), edges.rend());

    Dsu dsu(n);
    int answer = 0;
    for (auto [s, u, v] : edges) {
        dsu.unite(u, v);
        if (dsu.find(a) == dsu.find(b)) {
            answer = s;
            break;
        }
    }
    cout << answer << '\n';
    return 0;
}
