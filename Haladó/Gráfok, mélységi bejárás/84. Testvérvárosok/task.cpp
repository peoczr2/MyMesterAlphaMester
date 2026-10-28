/*
Megoldás lényege:
A városok fája egy fa, a párok száma N^2/2 nagyságrendű, ezért nem nézhetjük végig az összes párt. Centroid-felbontást használunk: kiválasztunk egy súlypontot, és minden olyan párt, amelynek útja átmegy rajta, egyszerre számolunk. Ha u és v távolsága a súlypontig d(u) és d(v), akkor dist(u,v) = d(u) + d(v), így a pár akkor testvérváros, ha (d(u) + d(v)) mod K = 0. A maradékok számlálásával egy végigmenéssel megkapjuk az ilyen párok számát: egy új x maradékú csúcs annyi párt alkot, ahány korábbi csúcs maradéka (K - x) mod K. A súlypont ugyanazon részfájába eső párokat kivonjuk, mert azokat nem ezen a súlyponton keresztül kell számolni. A rekurzió mélysége O(log N), így az összes munka O(N log N).
*/
/*
Hint 1: || Ne a párokat nézd, hanem a fa egy "középső" csúcsából mért távolságokat: két csúcs távolsága ilyenkor csak két távolság összege. ||
Hint 2: || A súlypont kiválasztása után a maradékokat K-val osztva számold össze a párokat, majd vond ki azokat, amelyek ugyanabba a részfába esnek. Ezután a súlypontot töröld, és a maradék részfákra ismételd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, K;
vector<vector<pair<int, int>>> g;
vector<char> removed;
vector<int> par, sz, dres, cnt;
long long answer = 0;

// BFS a root csúcsból a még nem törölt csúcsokon; a szülőket a par tömbbe írja
vector<int> bfsOrder(int root) {
    vector<int> order = {root};
    par[root] = 0;
    for (size_t i = 0; i < order.size(); ++i) {
        int x = order[i];
        for (auto [y, w] : g[x])
            if (!removed[y] && y != par[x]) {
                par[y] = x;
                order.push_back(y);
            }
    }
    return order;
}

// A részfa súlypontját keresi: olyan csúcsot, amelynek minden komponense legfeljebb a fele
int findCentroid(int root) {
    vector<int> order = bfsOrder(root);
    int total = order.size();
    for (int i = total - 1; i >= 0; --i) {
        int x = order[i];
        sz[x] = 1;
        for (auto [y, w] : g[x])
            if (!removed[y] && y != par[x]) sz[x] += sz[y];
    }
    for (int x : order) {
        int big = total - sz[x];
        for (auto [y, w] : g[x])
            if (!removed[y] && y != par[x]) big = max(big, sz[y]);
        if (2 * big <= total) return x;
    }
    return root;
}

// Megszámolja az (i < j) párokat, amelyekre (v_i + v_j) mod K = 0
long long countPairs(const vector<int>& v) {
    long long res = 0;
    for (int x : v) {
        res += cnt[(K - x) % K];
        ++cnt[x];
    }
    for (int x : v) cnt[x] = 0;
    return res;
}

void decompose(int start) {
    int c = findCentroid(start);

    // A súlyponttól mért távolságok maradékai: az összes csúcs, és részfánként
    vector<int> all = {0};
    vector<vector<int>> parts;
    for (auto [y, w] : g[c]) {
        if (removed[y]) continue;
        vector<int> part;
        par[y] = c;
        dres[y] = w % K;
        vector<int> q = {y};
        for (size_t i = 0; i < q.size(); ++i) {
            int x = q[i];
            part.push_back(dres[x]);
            for (auto [z, wz] : g[x])
                if (!removed[z] && z != par[x]) {
                    par[z] = x;
                    dres[z] = (dres[x] + wz) % K;
                    q.push_back(z);
                }
        }
        all.insert(all.end(), part.begin(), part.end());
        parts.push_back(move(part));
    }

    answer += countPairs(all);
    for (auto& part : parts) answer -= countPairs(part);

    removed[c] = 1;
    for (auto [y, w] : g[c])
        if (!removed[y]) decompose(y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> K;
    g.assign(n + 1, {});
    removed.assign(n + 1, 0);
    par.assign(n + 1, 0);
    sz.assign(n + 1, 0);
    dres.assign(n + 1, 0);
    cnt.assign(K, 0);

    for (int i = 0; i < n - 1; ++i) {
        int a, b, t;
        cin >> a >> b >> t;
        g[a].push_back({b, t});
        g[b].push_back({a, t});
    }

    decompose(1);
    cout << answer << '\n';
    return 0;
}
