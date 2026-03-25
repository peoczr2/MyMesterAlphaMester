/*
Megoldás lényege:
A különböző időkben épített várfalak nem érintkeznek, így minden bekerítés külön
összefüggő komponens a szakaszok gráfjában (kapcsolat: közös végpont).

1) DSU-val komponensekre bontjuk a szakaszokat.
2) Komponensenként:
   - hossz = szakaszhosszak összege,
   - terület = a komponens zárt vonalának előjeles területe (shoelace),
     csúcspont-sorrendet a fokszám-2 gráf bejárásával kapjuk.
3) A kimenet kívülről befelé kell, ezért abszolút terület szerint csökkenően rendezünk.

Idő: O(N α(N)) + rendezés.
*/

#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n) : p(n), r(n, 0) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) ++r[a];
    }
};

struct Point {
    int x, y;
};

struct Segment {
    int u, v;
    long long len;
};

static long long pointKey(int x, int y) {
    // Biztonságos egyedi kulcs az adott koordináta-tartományban.
    return (static_cast<long long>(x) << 32) ^ (static_cast<unsigned int>(y));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    unordered_map<long long, int> pid;
    pid.reserve(2 * N + 16);

    vector<Point> points;
    points.reserve(2 * N + 16);

    auto getPointId = [&](int x, int y) {
        long long k = pointKey(x, y);
        auto it = pid.find(k);
        if (it != pid.end()) return it->second;
        int id = (int)points.size();
        pid.emplace(k, id);
        points.push_back({x, y});
        return id;
    };

    vector<Segment> segs(N);
    vector<vector<int>> atPoint;
    atPoint.reserve(2 * N + 16);

    for (int i = 0; i < N; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int u = getPointId(x1, y1);
        int v = getPointId(x2, y2);
        if ((int)atPoint.size() < (int)points.size()) atPoint.resize(points.size());
        long long len = llabs((long long)x1 - x2) + llabs((long long)y1 - y2);
        segs[i] = {u, v, len};
        atPoint[u].push_back(i);
        atPoint[v].push_back(i);
    }

    DSU dsu(N);
    for (const auto& lst : atPoint) {
        for (int i = 1; i < (int)lst.size(); ++i) dsu.unite(lst[0], lst[i]);
    }

    unordered_map<int, vector<int>> compSegs;
    compSegs.reserve(N);
    for (int i = 0; i < N; ++i) compSegs[dsu.find(i)].push_back(i);

    struct Ans {
        long long area2abs;
        long long perim;
    };
    vector<Ans> all;
    all.reserve(compSegs.size());

    for (auto& kv : compSegs) {
        const vector<int>& ids = kv.second;

        long long perim = 0;
        unordered_map<int, vector<int>> adj;
        adj.reserve(ids.size() * 2 + 8);

        for (int sid : ids) {
            const auto& s = segs[sid];
            perim += s.len;
            adj[s.u].push_back(s.v);
            adj[s.v].push_back(s.u);
        }

        int start = adj.begin()->first;
        int prev = -1;
        int cur = start;

        vector<int> cyc;
        cyc.reserve(adj.size() + 1);

        do {
            cyc.push_back(cur);
            const auto& nb = adj[cur];
            int nxt;
            if (nb.size() == 1) nxt = nb[0];
            else nxt = (nb[0] == prev ? nb[1] : nb[0]);
            prev = cur;
            cur = nxt;
        } while (cur != start && (int)cyc.size() <= (int)adj.size() + 5);

        long long area2 = 0;
        int m = (int)cyc.size();
        for (int i = 0; i < m; ++i) {
            const Point& a = points[cyc[i]];
            const Point& b = points[cyc[(i + 1) % m]];
            area2 += 1LL * a.x * b.y - 1LL * a.y * b.x;
        }

        all.push_back({llabs(area2), perim});
    }

    sort(all.begin(), all.end(), [](const Ans& A, const Ans& B) {
        if (A.area2abs != B.area2abs) return A.area2abs > B.area2abs;
        return A.perim > B.perim;
    });

    cout << all.size() << '\n';
    for (int i = 0; i < (int)all.size(); ++i) {
        if (i) cout << ' ';
        cout << all[i].perim;
    }
    cout << '\n';

    return 0;
}
