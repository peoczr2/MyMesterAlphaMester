/*
Megoldás lényege:
A robot állapota a 2x2-es négyzet bal felső sarka, így legfeljebb N·M állapot van.
Egy lépés a négy irány valamelyike 1 időegységgel, és minden "+" cella, amelyet az új négyzet elfoglal, további 1 időegységbe kerül (elmozdítás).
A "*" cellába a robot nem léphet, ezért az ilyen lépés nem megengedett.
A lépésköltség így 1, 2 vagy 3, ezért a legrövidebb utat Dijkstra-algoritmussal keressük, de prioritási sor helyett 4 elemű, körkörös vödörtömbbel (Dial-algoritmus).
Az időigény O(N·M), ami a 0.2 mp-es korláton belül marad.
*/
/*
Hint 1: || Állapotnak a 2x2-es robot bal felső sarkát válaszd; egy lépés a négy irány valamelyike. ||
Hint 2: || Az új négyzet két újonnan elfoglalt cellájából számold a költséget: 1 + a "+" cellák száma. Ha ezek között "*" van, a lépés nem lehetséges. ||
Hint 3: || A költségek csak 1, 2 vagy 3 lehetnek, ezért a prioritási sor helyett tarts 4 listát a távolság modulo 4 szerint; így a távolságszintek egymás után feldolgozhatók. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (auto &row : g) cin >> row;

    int sr = -1, sc = -1, tr = -1, tc = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'K' && sr < 0) { sr = i; sc = j; }
            if (g[i][j] == 'C' && tr < 0) { tr = i; tc = j; }
        }
    }

    // Irányok: le, fel, jobbra, balra. Az er/ec tömbök az újonnan elfoglalt két cellát adják
    // a bal felső sarokhoz képest.
    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};
    const int er[4][2] = {{2, 2}, {-1, -1}, {0, 1}, {0, 1}};
    const int ec[4][2] = {{0, 1}, {0, 1}, {2, 2}, {-1, -1}};

    const int INF = INT_MAX;
    vector<int> dist(n * m, INF);
    vector<int> bucket[4];
    int start = sr * m + sc, goal = tr * m + tc;
    dist[start] = 0;
    bucket[0].push_back(start);
    long long pending = 1;

    for (int d = 0; pending > 0; d++) {
        vector<int> &cur = bucket[d % 4];
        while (!cur.empty()) {
            int u = cur.back();
            cur.pop_back();
            pending--;
            if (dist[u] != d) continue;
            int r = u / m, c = u % m;
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr < 0 || nr > n - 2 || nc < 0 || nc > m - 2) continue;
                int w = 1;
                bool ok = true;
                for (int q = 0; q < 2 && ok; q++) {
                    char ch = g[r + er[k][q]][c + ec[k][q]];
                    if (ch == '*') ok = false;
                    else if (ch == '+') w++;
                }
                if (!ok) continue;
                int v = nr * m + nc;
                if (d + w < dist[v]) {
                    dist[v] = d + w;
                    bucket[(d + w) % 4].push_back(v);
                    pending++;
                }
            }
        }
    }

    cout << (dist[goal] == INF ? 0 : dist[goal]) << "\n";
    return 0;
}
