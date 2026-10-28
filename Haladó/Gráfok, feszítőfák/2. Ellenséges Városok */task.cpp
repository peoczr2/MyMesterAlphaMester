/*
Megoldás lényege:
A kiválasztott utak egy feszítőfát alkotnak, és azt keressük, amelyiknek a legrövidebb éle a lehető leghosszabb. Ez a maximális feszítőfa: az utakat hosszuk szerint csökkenő sorrendben dolgozzuk fel, és egy unió-find struktúrával csak azokat vesszük fel, amelyek két még különálló városcsoportot kötnek össze. Ez a Kruskal-algoritmus csökkenő változata, amely bizonyíthatóan maximalizálja a fa legrövidebb élét. A kiírt érték a felvett utak közül a legrövidebb hossza, a második sorban pedig a felvett utak sorszámai szerepelnek a felvétel sorrendjében. Az időigény O(M log M), ami M = 500 000 éllel is elfogadható.
*/
/*
Hint 1: || Nem a legrövidebb, hanem a leghosszabb utakat érdemes előnyben részesíteni, mert a cél, hogy a kiválasztott úthálózat legrövidebb útja minél hosszabb legyen. ||
Hint 2: || Dolgozd fel az utakat hosszuk szerint csökkenő sorrendben, és egy unió-find (DSU) struktúrával vedd fel azt az utat, amely két még nem összekötött városcsoportot köt össze. ||
Hint 3: || Az egyforma hosszú utaknál tartsd meg a bemeneti sorrendet (stabil rendezés), így a felvételi sorrend megegyezik az elvárt kimenettel; a felvett utak közül a legrövidebb hosszát írd az első sorba. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n) : p(n) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        while (p[x] != x) {
            p[x] = p[p[x]];
            x = p[x];
        }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        p[a] = b;
        return true;
    }
};

struct Road {
    int u, v, w, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<Road> roads(M);
    for (int i = 0; i < M; i++) {
        cin >> roads[i].u >> roads[i].v >> roads[i].w;
        roads[i].id = i + 1;
    }

    stable_sort(roads.begin(), roads.end(), [](const Road& a, const Road& b) {
        return a.w > b.w;
    });

    DSU dsu(N + 1);
    vector<int> chosen;
    int minLen = INT_MAX;
    for (const Road& r : roads) {
        if (dsu.unite(r.u, r.v)) {
            chosen.push_back(r.id);
            minLen = min(minLen, r.w);
            if ((int)chosen.size() == N - 1) break;
        }
    }

    cout << minLen << "\n";
    for (size_t i = 0; i < chosen.size(); i++) {
        if (i) cout << ' ';
        cout << chosen[i];
    }
    cout << "\n";
    return 0;
}
