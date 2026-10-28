/*
Megoldás lényege:
A megerősített utaknak az összes település összekötéséhez minimális költségű feszítőfát kell alkotniuk, így egy út akkor biztosan nem kerül megerősítésre, ha egyetlen minimális feszítőfában sincs benne. Egy (a, b, k) út pontosan akkor marad ki minden minimális feszítőfából, ha a és b már össze van kötve k-nál olcsóbb utakkal. Az utakat költség szerint növekvő sorrendben dolgozzuk fel, az azonos költségű utakat csoportonként kezeljük: először minden csoportbeli útra unió-find segítségével megnézzük, összekötöttek-e a végpontjai, és csak utána egyesítjük a csoport útjait. A kimenet a kizárt utak sorszáma növekvő sorrendben. Az időigény O(M log M), ami M = 500 000 mellett belefér.
*/
/*
Hint 1: || Nem az a kérdés, melyik utat építik meg, hanem az, hogy mely utak maradhatnak ki minden lehetséges olcsó összekötésből. ||
Hint 2: || Egy út akkor maradhat ki biztosan, ha végpontjait már összeköti olyan úthálózat, amelynek minden útja olcsóbb nála; ezt Kruskal-szerű bejárással, unió-find segítségével ellenőrizheted. ||
Hint 3: || Az azonos költségű utakat egyszerre kezeld: először minden csoportbeli útra vizsgáld az összefüggőséget a korábbi (olcsóbb) utak alapján, és csak utána egyesítsd őket. A végén a sorszámokat rendezd növekvő sorrendbe. ||
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
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) p[a] = b;
    }
};

struct Road {
    int a, b, k, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<Road> roads(M);
    for (int i = 0; i < M; i++) {
        cin >> roads[i].a >> roads[i].b >> roads[i].k;
        roads[i].id = i + 1;
    }

    sort(roads.begin(), roads.end(), [](const Road& x, const Road& y) {
        return x.k < y.k;
    });

    DSU dsu(N + 1);
    vector<int> safe;
    int i = 0;
    while (i < M) {
        int j = i;
        while (j < M && roads[j].k == roads[i].k) j++;

        // Az azonos költségű csoportot a korábbi, olcsóbb utak alapján vizsgáljuk.
        for (int t = i; t < j; t++) {
            if (dsu.find(roads[t].a) == dsu.find(roads[t].b)) {
                safe.push_back(roads[t].id);
            }
        }
        for (int t = i; t < j; t++) {
            dsu.unite(roads[t].a, roads[t].b);
        }
        i = j;
    }

    sort(safe.begin(), safe.end());
    cout << safe.size() << "\n";
    for (size_t t = 0; t < safe.size(); t++) {
        if (t) cout << ' ';
        cout << safe[t];
    }
    cout << "\n";
    return 0;
}
