/*
Megoldás lényege:
A térképet gráfnak tekintjük: a 0-s mezőre nem lehet lépni, az 1-es és 2-es mezőkre négy irányba igen.
A három kérdés ugyanazon a gráfon fut, csak a lépés költsége más: (1) egy városba belépés 1, a városon belüli lépés 0;
(2) egy 1-es mezőre lépés 1, egy 2-es mezőre 0; (3) egy mező elhagyása 1 időegység 1-es, 2 időegység 2-es mezőről.
A költségek 0, 1 vagy 2 értékűek, ezért mindhárom esetben Dijkstra-algoritmussal (prioritási sorral) számolunk.
A városok területe egy BFS: a kiinduló mezőből csak 2-es mezőkön haladunk, a kiinduló mezőt mindig beszámítjuk.
Ha a megadott pont nem városmező, a szomszédos városok területe is hozzáadódik, ahogy azt a minta is mutatja.
Az időigény O(N*M*log(N*M)), ami 200x200-as térképen bőven belefér.
*/
/*
Hint 1: || A három kérdés ugyanazon a rácson fut, csak a lépés súlya más. Gondold végig, hogy egy lépés költsége a belépett vagy az elhagyott mező típusától függ-e. ||
Hint 2: || A súlyok 0, 1 vagy 2 lehetnek, ezért a legrövidebb utat prioritási sorral futtatott Dijkstra-algoritmussal kapod meg, mindhárom esetben más súlyfüggvénnyel. ||
Hint 3: || A terület egy egyszerű BFS: a kiinduló mezőt 1-nek veszed, majd csak a szomszédos 2-es mezőkön terjedsz tovább. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> g;
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

// A kiindulo mezotol 2-es mezokon at elerheto cellak szama (a kiindulo mezot mindig beszamitva)
long long area(int sx, int sy) {
    vector<vector<char>> seen(n, vector<char>(m, 0));
    queue<pair<int, int>> q;
    long long cnt = 1;
    seen[sx][sy] = 1;
    q.push({sx, sy});
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            if (seen[nx][ny] || g[nx][ny] != '2') continue;
            seen[nx][ny] = 1;
            cnt++;
            q.push({nx, ny});
        }
    }
    return cnt;
}

// kind 1: varosba lepes 1, egyebkent 0; kind 2: 1-es mezore lepes 1, egyebkent 0;
// kind 3: a kiindulo mezo elhagyasi ideje (1 vagy 2)
long long shortest(int sx, int sy, int tx, int ty, int kind) {
    const long long INF = LLONG_MAX / 4;
    vector<vector<long long>> dist(n, vector<long long>(m, INF));
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> pq;
    dist[sx][sy] = 0;
    pq.push({0, sx, sy});
    while (!pq.empty()) {
        auto [d, x, y] = pq.top();
        pq.pop();
        if (d != dist[x][y]) continue;
        if (x == tx && y == ty) return d;
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            if (g[nx][ny] == '0') continue;
            long long w;
            if (kind == 1) w = (g[x][y] == '1' && g[nx][ny] == '2') ? 1 : 0;
            else if (kind == 2) w = (g[nx][ny] == '1') ? 1 : 0;
            else w = (g[x][y] == '1') ? 1 : 2;
            if (d + w < dist[nx][ny]) {
                dist[nx][ny] = d + w;
                pq.push({dist[nx][ny], nx, ny});
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    g.resize(n);
    for (auto &row : g) cin >> row;
    int x, y, u, v;
    cin >> x >> y >> u >> v;
    x--; y--; u--; v--;
    cout << area(x, y) << ' ' << area(u, v) << '\n';
    for (int kind = 1; kind <= 3; kind++) cout << shortest(x, y, u, v, kind) << '\n';
    return 0;
}
