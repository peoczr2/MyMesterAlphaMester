/*
Megoldás lényege:
A robot következő döntése attól függ, melyik úton érkezett a kereszteződésbe, ezért az állapot a
(előző kereszteződés, aktuális kereszteződés) pár. Egy kereszteződésben a visszaúthoz képest a két továbbvezető
út közül azt nevezzük jobbra esőnek (J), amelyet a BA félegyenestől az óramutató járásával ellentétesen haladva
előbb érünk el, a másik a balra eső (B). A szögeket egész koordinátákkal, keresztszorzattal hasonlítjuk össze.
Először szélességi bejárást végzünk az állapotgráfban (J ágat előre véve). Ha az így kapott út nem érint kétszer
kereszteződést, az a lehető legrövidebb megoldás. Ellenkező esetben egyszerű utakat keresünk iteratív mélyítéses
mélységi bejárással, ahol alsó korlátnak az állapotgráf visszafelé számolt távolságát használjuk.
*/
/*
Hint 1: || A robot következő döntése csak attól függ, melyik úton érkezett, ezért az állapot legyen az „előző és aktuális kereszteződés” pár. ||
Hint 2: || Egy kereszteződésben a két továbbvezető út sorrendjét szögekkel döntsd el: a visszaút irányától az óramutató járásával ellentétesen előbb elérhető út a jobbra eső. ||
Hint 3: || Ha a szélességi bejárás útja kétszer érintene egy kereszteződést, az állapotgráfban visszafelé számolt fordulásszámok alsó korlátként segítenek a rövid egyszerű út megtalálásában. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n, a, b, v;
vector<long long> X, Y;
vector<vector<int>> nb;
vector<vector<int>> distTo;  // distTo[p][c]: hány fordulás kell V-ig az (p -> c) állapotból
vector<char> vis;
string path;
const int INF = 1000000000;

// Igaz, ha n1 a (pr -> cu) úton érkezve jobbra esik n2-höz képest.
// A cu->pr félegyenestől az óramutató járásával ellentétesen haladva n1 előbb található.
bool rightOf(int pr, int cu, int n1, int n2) {
    long long ux = X[pr] - X[cu], uy = Y[pr] - Y[cu];
    long long ax = X[n1] - X[cu], ay = Y[n1] - Y[cu];
    long long bx = X[n2] - X[cu], by = Y[n2] - Y[cu];
    auto half = [&](long long wx, long long wy) {
        long long cr = ux * wy - uy * wx;
        long long dt = ux * wx + uy * wy;
        return (cr > 0 || (cr == 0 && dt > 0)) ? 0 : 1;
    };
    int h1 = half(ax, ay), h2 = half(bx, by);
    if (h1 != h2) return h1 < h2;
    return ax * by - ay * bx > 0;
}

// Az (p -> c) állapotból továbbvezető utak: a jobbra esőt (J) hagyjuk elöl
vector<int> nextCands(int p, int c) {
    vector<int> cand;
    for (int j : nb[c]) {
        if (j != p) cand.push_back(j);
    }
    sort(cand.begin(), cand.end(), [&](int p1, int p2) { return rightOf(p, c, p1, p2); });
    return cand;
}

// Szélességi bejárás az állapotgráfban; igaz, ha van út V-be
bool bfsWalk(string &res) {
    vector<vector<char>> seen(n + 1, vector<char>(n + 1, 0));
    vector<vector<pair<int, int>>> par(n + 1, vector<pair<int, int>>(n + 1, {0, 0}));
    vector<vector<char>> cmd(n + 1, vector<char>(n + 1, 0));
    queue<pair<int, int>> qu;
    seen[a][b] = 1;
    qu.push({a, b});
    while (!qu.empty()) {
        auto [pr, cu] = qu.front();
        qu.pop();
        vector<int> cand = nextCands(pr, cu);
        for (size_t k = 0; k < cand.size(); ++k) {
            int nx = cand[k];
            if (seen[cu][nx]) continue;
            seen[cu][nx] = 1;
            par[cu][nx] = {pr, cu};
            cmd[cu][nx] = (k == 0) ? 'J' : 'B';
            if (nx == v) {
                res.clear();
                pair<int, int> st{cu, nx};
                while (!(st.first == a && st.second == b)) {
                    res += cmd[st.first][st.second];
                    st = par[st.first][st.second];
                }
                reverse(res.begin(), res.end());
                return true;
            }
            qu.push({cu, nx});
        }
    }
    return false;
}

// Igaz, ha a parancssorozat útja nem érint kétszer kereszteződést
bool isSimple(const string &cmds) {
    vector<char> used(n + 1, 0);
    used[a] = 1;
    used[b] = 1;
    int pr = a, cu = b;
    for (char ch : cmds) {
        vector<int> cand = nextCands(pr, cu);
        int nx = (ch == 'J') ? cand[0] : cand[1];
        if (used[nx]) return false;
        used[nx] = 1;
        pr = cu;
        cu = nx;
    }
    return true;
}

// Élek száma s-ből V-be a még nem látogatott kereszteződéseken át (INF, ha nincs ilyen)
int unvisitedDist(int s) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (x == v) return dist[x];
        for (int u : nb[x]) {
            if (vis[u] || dist[u] != -1) continue;
            dist[u] = dist[x] + 1;
            q.push(u);
        }
    }
    return INF;
}

// Mélységi keresés egyszerű utakon, legfeljebb L fordulással
bool dfs(int p, int c, int d, int L) {
    if (c == v) return true;
    vector<int> cand = nextCands(p, c);
    for (size_t k = 0; k < cand.size(); ++k) {
        int nx = cand[k];
        if (vis[nx]) continue;
        if (d + 1 + distTo[c][nx] > L) continue;
        vis[nx] = 1;
        int rest = unvisitedDist(nx);
        if (rest < INF && d + 1 + rest <= L) {
            path.push_back(k == 0 ? 'J' : 'B');
            if (dfs(c, nx, d + 1, L)) return true;
            path.pop_back();
        }
        vis[nx] = 0;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> a >> b >> v;

    X.assign(n + 1, 0);
    Y.assign(n + 1, 0);
    nb.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        cin >> X[i] >> Y[i];
        for (int k = 0; k < 3; ++k) {
            int j;
            cin >> j;
            nb[i].push_back(j);
        }
    }

    if (b == v) {
        cout << '\n';
        return 0;
    }

    string walk;
    if (bfsWalk(walk) && isSimple(walk)) {
        cout << walk << '\n';
        return 0;
    }

    // Állapotgráf visszafelé: distTo[p][c] az (p -> c) állapotból a V-ig szükséges fordulások alsó korlátja
    distTo.assign(n + 1, vector<int>(n + 1, INF));
    deque<pair<int, int>> qu;
    for (int p = 1; p <= n; ++p) {
        for (int c : nb[p]) {
            if (c == v) {
                distTo[p][c] = 0;
                qu.push_back({p, c});
            }
        }
    }
    while (!qu.empty()) {
        auto [c, nx] = qu.front();
        qu.pop_front();
        // (c -> nx) elé: (p -> c) állapotok, ahol p a c szomszédja és p != nx
        for (int p : nb[c]) {
            if (p == nx) continue;
            if (distTo[p][c] != INF) continue;
            distTo[p][c] = distTo[c][nx] + 1;
            qu.push_back({p, c});
        }
    }

    if (distTo[a][b] >= INF) {
        cout << '\n';
        return 0;
    }

    vis.assign(n + 1, 0);
    vis[a] = 1;
    vis[b] = 1;
    for (int L = distTo[a][b]; L <= 4 * n + 10; ++L) {
        path.clear();
        if (dfs(a, b, 0, L)) {
            cout << path << '\n';
            return 0;
        }
    }
    cout << '\n';
    return 0;
}
