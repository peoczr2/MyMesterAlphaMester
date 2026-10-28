/*
Megoldás lényege:
Első lépésben a legnagyobb elvihető tehersúly W, amelyet ugyanúgy kapunk meg, mint az egyszerű szállítási feladatnál: az utakat csökkenő teherbírás szerint unió-kereső struktúrával húzzuk be, és amikor A és B egy összefüggő részbe kerül, az utoljára behúzott út teherbírása a W. Második lépésben csak a legalább W teherbírású utakat tartjuk meg: ezeken A-ból B-be vezető minden út tehersúlya pontosan W lesz, és a feltétel szerint a legkevesebb városon áthaladó utat keressük, vagyis a legkevesebb élből álló utat. Ezt szélességi bejárással kapjuk meg; a belső városok száma az élek számánál eggyel kevesebb. Az N≤10000 és M≤200000 méret mellett az O(M log M) rendezés gyors.
*/
/*
Hint 1: || Először határozd meg, mekkora a legnagyobb tehersúly, amit A-ból B-be vihetsz: ehhez az utakat nagy teherbírástól kicsi felé dolgozd fel egy unió-kereső struktúrával. ||
Hint 2: || A második szempont miatt a maximális W-hez tartozó utakon kell a legkevesebb élből álló A-B utat keresni: tartsd meg csak a legalább W teherbírású utakat, és azokon végezz szélességi bejárást, minden városnak tárolva a szülőjét. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Egész szám olvasása: a számjegyeken kívüli bájtok (pl. CR, vagy az ISO-8859-1 mintafájlok 0xA0 elválasztója) elválasztónak számítanak.
int readInt() {
    int c = getchar();
    while (c != EOF && (c < '0' || c > '9')) c = getchar();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

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
    int n = readInt();
    int m = readInt();
    int a = readInt();
    int b = readInt();
    vector<Road> roads(m);
    for (auto& r : roads) {
        r.x = readInt();
        r.y = readInt();
        r.t = readInt();
    }

    // 1. lépés: a legnagyobb tehersúly (szűk keresztmetszet maximuma)
    sort(roads.begin(), roads.end(), [](const Road& l, const Road& r) { return l.t > r.t; });
    parentOf.resize(n + 1);
    iota(parentOf.begin(), parentOf.end(), 0);
    int W = 0;
    for (const Road& r : roads) {
        int rx = findRoot(r.x), ry = findRoot(r.y);
        if (rx == ry) continue;
        parentOf[rx] = ry;
        if (findRoot(a) == findRoot(b)) {
            W = r.t;
            break;
        }
    }

    if (W == 0) {
        cout << 0 << '\n' << 0 << '\n';
        return 0;
    }

    // 2. lépés: a legkevesebb élből álló A-B út a legalább W teherbírású utakon
    vector<vector<int>> adj(n + 1);
    for (const Road& r : roads) {
        if (r.t >= W) {
            adj[r.x].push_back(r.y);
            adj[r.y].push_back(r.x);
        }
    }
    vector<int> par(n + 1, 0);
    vector<char> seen(n + 1, 0);
    queue<int> que;
    que.push(a);
    seen[a] = 1;
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (int y : adj[x]) {
            if (!seen[y]) {
                seen[y] = 1;
                par[y] = x;
                que.push(y);
            }
        }
    }

    vector<int> path;  // a belső városok (A és B nélkül)
    for (int x = par[b]; x != a; x = par[x]) path.push_back(x);
    reverse(path.begin(), path.end());

    cout << W << '\n';
    cout << path.size();
    for (int x : path) cout << ' ' << x;
    cout << '\n';
    return 0;
}
