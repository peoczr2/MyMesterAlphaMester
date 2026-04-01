/*
Ötlet:
Az AB egyenes két oldalán külön rendezzük a pontokat a dot/|cross| projektív
koordináta szerint. A két oldalon kapott két monoton lánc nem metszi egymást,
ezért az A -> felső lánc -> alsó lánc -> B sorrend egyszerű törtvonal.
*/

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    int id;
};

static long long sqDist(const Point& a, const Point& b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, aId, bId;
    if (!(cin >> n >> aId >> bId)) return 0;

    vector<Point> pts(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].id = i;
    }

    const Point a = pts[aId];
    const Point b = pts[bId];
    long long bx = b.x - a.x;
    long long by = b.y - a.y;

    struct Item {
        Point p;
        long long dot;
        long long cross;
    };

    vector<Item> upper, lower;
    upper.reserve(n);
    lower.reserve(n);

    for (int i = 1; i <= n; ++i) {
        if (i == aId || i == bId) continue;
        long long px = pts[i].x - a.x;
        long long py = pts[i].y - a.y;
        long long dot = px * bx + py * by;
        long long cross = bx * py - by * px;
        Item item{pts[i], dot, cross};
        if (cross > 0 || (cross == 0 && dot >= 0)) upper.push_back(item);
        else lower.push_back(item);
    }

    auto cmpUpper = [](const Item& lhs, const Item& rhs) {
        if (lhs.cross == 0 || rhs.cross == 0) {
            if (lhs.cross == 0 && rhs.cross == 0) {
                if (lhs.dot != rhs.dot) return lhs.dot < rhs.dot;
                return lhs.p.id < rhs.p.id;
            }
            return lhs.cross != 0;
        }
        __int128 left = (__int128)lhs.dot * rhs.cross;
        __int128 right = (__int128)rhs.dot * lhs.cross;
        if (left != right) return left < right;
        return lhs.p.id < rhs.p.id;
    };

    auto cmpLower = [](const Item& lhs, const Item& rhs) {
        if (lhs.cross == 0 || rhs.cross == 0) {
            if (lhs.cross == 0 && rhs.cross == 0) {
                if (lhs.dot != rhs.dot) return lhs.dot > rhs.dot;
                return lhs.p.id < rhs.p.id;
            }
            return lhs.cross == 0;
        }
        __int128 left = (__int128)lhs.dot * (-rhs.cross);
        __int128 right = (__int128)rhs.dot * (-lhs.cross);
        if (left != right) return left < right;
        return lhs.p.id < rhs.p.id;
    };

    sort(upper.begin(), upper.end(), cmpUpper);
    sort(lower.begin(), lower.end(), cmpLower);

    vector<int> ans;
    ans.reserve(n);
    ans.push_back(aId);
    for (const auto& item : upper) ans.push_back(item.p.id);
    for (const auto& item : lower) ans.push_back(item.p.id);
    ans.push_back(bId);

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}