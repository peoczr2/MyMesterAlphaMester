/*
Megoldás lényege:
A különböző építési fázisok falai nem érintkeznek egymással, tehát az egy fázishoz tartozó falak
pontosan egy összefüggő komponensbe esnek. Ezért a válasz a fal-szakaszok komponenseinek
száma, ahol két szakasz szomszédos, ha közös végpontjuk van.

Lépések:
1) minden végpont koordinátáját azonosítóvá képezzük,
2) végpont -> szakaszlista indexelés,
3) DSU-val egyesítjük azokat a szakaszokat, amelyek ugyanahhoz a végponthoz tartoznak.
A komponensek száma lesz a keresett építésszám.

Idő: O(N α(N))
*/

#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n) : p(n), r(n, 0) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) ++r[a];
    }
};

struct Point {
    int x, y;
    bool operator<(const Point& o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<pair<Point, Point>> segs(N);
    map<Point, vector<int>> atPoint;

    for (int i = 0; i < N; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        Point a{x1, y1}, b{x2, y2};
        segs[i] = {a, b};
        atPoint[a].push_back(i);
        atPoint[b].push_back(i);
    }

    DSU dsu(N);
    for (auto& kv : atPoint) {
        auto& v = kv.second;
        for (int i = 1; i < (int)v.size(); ++i) {
            dsu.unite(v[0], v[i]);
        }
    }

    int comps = 0;
    for (int i = 0; i < N; ++i) {
        if (dsu.find(i) == i) ++comps;
    }

    cout << comps << '\n';
    return 0;
}
