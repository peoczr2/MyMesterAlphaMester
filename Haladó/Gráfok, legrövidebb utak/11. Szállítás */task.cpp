/*
Megoldás lényege:
Egy útvonal tehersúlya az útvonal leggyengébb útjának teherbírása, és ezt kell maximalizálni. Az utakat csökkenő teherbírás szerint rendezve, unió-kereső (DSU) segítségével húzzuk be őket egy erdőbe; abban a pillanatban, amikor A és B egy komponensbe kerül, az utolsó behúzott út teherbírása a keresett maximum. Az addig behúzott utak mind legalább ekkora teherbírásúak, így az erdőben A-ból B-be vezető egyetlen út optimális, és ennek a városait szélességi bejárással kapjuk meg. Az M≤1000000 él rendezése O(M log M) időben fut, ami a 0,7 mp-es időlimitbe belefér.
*/
/*
Hint 1: || Egy útvonal tehersúlya a rajta lévő legkisebb teherbírású út; a feladat ezt az értéket akarja a lehető legnagyobbra választani. ||
Hint 2: || Az utakat nagy teherbírástól kicsi felé dolgozd fel, és unió-kereső struktúrával figyeld, mikor lesz A és B egy összefüggő részben: az éppen akkor hozzávett út teherbírása a válasz. A kiválasztott utak erdejében szélességi bejárással keresd meg az A-ból B-be vezető utat. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Road {
    int x, y, t;
};

vector<int> parentOf;

int findRoot(int x) {
    while (parentOf[x] != x) {
        parentOf[x] = parentOf[parentOf[x]];
        x = parentOf[x];
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<Road> roads(m);
    for (auto& r : roads) cin >> r.x >> r.y >> r.t;
    sort(roads.begin(), roads.end(), [](const Road& l, const Road& r) { return l.t > r.t; });

    parentOf.resize(n + 1);
    iota(parentOf.begin(), parentOf.end(), 0);
    vector<vector<int>> forest(n + 1);
    int answer = 0;
    for (const Road& r : roads) {
        int rx = findRoot(r.x), ry = findRoot(r.y);
        if (rx == ry) continue;
        parentOf[rx] = ry;
        forest[r.x].push_back(r.y);
        forest[r.y].push_back(r.x);
        if (findRoot(a) == findRoot(b)) {
            answer = r.t;
            break;
        }
    }

    if (answer == 0) {
        cout << 0 << '\n';
        return 0;
    }

    // A-ból B-be vezető út a kiválasztott erdőben
    vector<int> par(n + 1, 0);
    vector<char> seen(n + 1, 0);
    queue<int> que;
    que.push(a);
    seen[a] = 1;
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (int y : forest[x]) {
            if (!seen[y]) {
                seen[y] = 1;
                par[y] = x;
                que.push(y);
            }
        }
    }

    vector<int> path;
    for (int x = b; x != a; x = par[x]) path.push_back(x);
    path.push_back(a);
    reverse(path.begin(), path.end());

    cout << answer << '\n';
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i] << (i + 1 < path.size() ? ' ' : '\n');
    }
    return 0;
}
