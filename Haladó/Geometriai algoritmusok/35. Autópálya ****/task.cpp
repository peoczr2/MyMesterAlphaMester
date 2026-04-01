/*
Megoldás lényege:
A keresett autópálya olyan egyenes, amelyre a két hálózat minden csomópontja ugyanazon az oldalon van,
és az egyenes legalább egy piros és egy kék csomóponton átmegy. Ez pontosan egy tartóegyenes a két
ponthalmaz egyesítésének konvex burkán. Elég tehát az összes csomópont konvex burkának határát
végignézni: ha a határon egymás melletti két pont különböző színű, akkor az őket összekötő egyenes jó.
Ha ilyen pár nincs, akkor nincs megoldás.

Az Andrew-féle monotone chain algoritmust használjuk, és a határon fekvő kollineáris pontokat is megtartjuk,
így egy él mentén minden lehetséges színváltás megmarad.
*/

#include <bits/stdc++.h>
using namespace std;

struct FastInput {
    static constexpr size_t BUFSIZE = 1 << 20;
    char data[BUFSIZE];
    size_t idx = 0, size = 0;

    inline char read() {
        if (idx >= size) {
            size = fread(data, 1, BUFSIZE, stdin);
            idx = 0;
            if (size == 0) return 0;
        }
        return data[idx++];
    }

    template <class T>
    bool readInt(T& out) {
        char c;
        T sign = 1;
        T value = 0;
        c = read();
        if (!c) return false;
        while (c != '-' && (c < '0' || c > '9')) {
            c = read();
            if (!c) return false;
        }
        if (c == '-') {
            sign = -1;
            c = read();
        }
        while (c >= '0' && c <= '9') {
            value = value * 10 + (c - '0');
            c = read();
        }
        out = value * sign;
        return true;
    }
};

struct Point {
    long long x, y;
    int color;
    int idx;
};

static int cross(const Point& a, const Point& b, const Point& c) {
    __int128 x1 = b.x - a.x;
    __int128 y1 = b.y - a.y;
    __int128 x2 = c.x - a.x;
    __int128 y2 = c.y - a.y;
    __int128 value = x1 * y2 - y1 * x2;
    if (value < 0) return -1;
    if (value > 0) return 1;
    return 0;
}

int main() {
    FastInput in;

    int n;
    if (!in.readInt(n)) return 0;

    vector<Point> points;
    points.reserve(800000);

    for (int i = 1; i <= n; ++i) {
        long long x, y;
        in.readInt(x);
        in.readInt(y);
        points.push_back({x, y, 0, i});
    }

    int m;
    in.readInt(m);
    for (int i = 1; i <= m; ++i) {
        long long x, y;
        in.readInt(x);
        in.readInt(y);
        points.push_back({x, y, 1, i});
    }

    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        if (a.color != b.color) return a.color < b.color;
        return a.idx < b.idx;
    });

    vector<Point> lower, upper;
    lower.reserve(points.size());
    upper.reserve(points.size());

    for (const Point& p : points) {
        while (lower.size() >= 2 && cross(lower[lower.size() - 2], lower.back(), p) < 0) {
            lower.pop_back();
        }
        lower.push_back(p);
    }

    for (int i = (int)points.size() - 1; i >= 0; --i) {
        const Point& p = points[i];
        while (upper.size() >= 2 && cross(upper[upper.size() - 2], upper.back(), p) < 0) {
            upper.pop_back();
        }
        upper.push_back(p);
    }

    vector<Point> hull;
    hull.reserve(lower.size() + upper.size());
    for (const Point& p : lower) hull.push_back(p);
    for (int i = 1; i + 1 < (int)upper.size(); ++i) hull.push_back(upper[i]);

    vector<Point> boundary;
    boundary.reserve(hull.size());
    for (const Point& p : hull) {
        if (boundary.empty() || boundary.back().x != p.x || boundary.back().y != p.y || boundary.back().color != p.color || boundary.back().idx != p.idx) {
            boundary.push_back(p);
        }
    }
    if (boundary.size() >= 2) {
        const Point& a = boundary.front();
        const Point& b = boundary.back();
        if (a.x == b.x && a.y == b.y && a.color == b.color && a.idx == b.idx) {
            boundary.pop_back();
        }
    }

    for (int i = 0; i < (int)boundary.size(); ++i) {
        const Point& a = boundary[i];
        const Point& b = boundary[(i + 1) % boundary.size()];
        if (a.color != b.color) {
            int red = (a.color == 0 ? a.idx : b.idx);
            int blue = (a.color == 1 ? a.idx : b.idx);
            cout << red << ' ' << blue << '\n';
            return 0;
        }
    }

    cout << "0 0\n";
    return 0;
}