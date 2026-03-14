/*
Megoldás lényege:
A keresett autópálya olyan egyenes, amelyre minden csomópont ugyanazon az oldalon (vagy az
egyenesen) van, és az egyenes átmegy legalább egy piros és egy kék csomóponton.
Ez pontosan azt jelenti, hogy az egyenes a teljes pontunió egy tartóegyenese, ezért a közös
konvex burok valamelyik határszakaszán kell feküdnie. Emiatt elég a két hálózat pontjainak
konvex burkát (a teljes ponthalmazét) vizsgálni, és a burok határán egymás melletti pontok
közül keresni különböző színű párt. Ha találunk ilyet, az egyenes megfelelő; ha nem, nincs
megoldás.

Idő: O((N+M) log(N+M))
*/

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    int color; // 0: red, 1: blue
    int idx;   // 1-based index in own color list
};

static long long cross(const Point& a, const Point& b, const Point& c) {
    __int128 x1 = b.x - a.x;
    __int128 y1 = b.y - a.y;
    __int128 x2 = c.x - a.x;
    __int128 y2 = c.y - a.y;
    __int128 v = x1 * y2 - y1 * x2;
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<Point> pts;
    pts.reserve(200000);

    for (int i = 1; i <= N; ++i) {
        long long x, y;
        cin >> x >> y;
        pts.push_back({x, y, 0, i});
    }

    int M;
    cin >> M;
    for (int i = 1; i <= M; ++i) {
        long long x, y;
        cin >> x >> y;
        pts.push_back({x, y, 1, i});
    }

    sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.color < b.color;
    });

    // Monotone chain, strict right-turn removal (<0), thus boundary collinear points are kept.
    vector<Point> lower, upper;
    lower.reserve(pts.size());
    upper.reserve(pts.size());

    for (const auto& p : pts) {
        while (lower.size() >= 2 && cross(lower[lower.size() - 2], lower.back(), p) < 0) {
            lower.pop_back();
        }
        lower.push_back(p);
    }

    for (int i = (int)pts.size() - 1; i >= 0; --i) {
        const auto& p = pts[i];
        while (upper.size() >= 2 && cross(upper[upper.size() - 2], upper.back(), p) < 0) {
            upper.pop_back();
        }
        upper.push_back(p);
    }

    vector<Point> hull;
    hull.reserve(lower.size() + upper.size());
    for (const auto& p : lower) hull.push_back(p);
    for (int i = 1; i + 1 < (int)upper.size(); ++i) hull.push_back(upper[i]);

    if (hull.size() < 2) {
        cout << "0 0\n";
        return 0;
    }

    // Remove immediate duplicates if any.
    vector<Point> boundary;
    boundary.reserve(hull.size());
    for (const auto& p : hull) {
        if (boundary.empty() || boundary.back().x != p.x || boundary.back().y != p.y || boundary.back().color != p.color || boundary.back().idx != p.idx) {
            boundary.push_back(p);
        }
    }
    if (boundary.size() >= 2) {
        const auto& a = boundary.front();
        const auto& b = boundary.back();
        if (a.x == b.x && a.y == b.y && a.color == b.color && a.idx == b.idx) {
            boundary.pop_back();
        }
    }

    int H = (int)boundary.size();
    for (int i = 0; i < H; ++i) {
        const auto& a = boundary[i];
        const auto& b = boundary[(i + 1) % H];
        if (a.color != b.color) {
            int red = (a.color == 0 ? a.idx : b.idx);
            int blue = (a.color == 1 ? a.idx : b.idx);
            cout << red << ' ' << blue << "\n";
            return 0;
        }
    }

    cout << "0 0\n";
    return 0;
}
