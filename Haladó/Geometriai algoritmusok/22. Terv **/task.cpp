/*
Megoldás lényege:
A megadott feltételeknek megfelelő síkbeli konstrukciót kell előállítani. A megoldás a geometriai összefüggésekből visszafejtett szerkesztésre épül.
*/
#include <bits/stdc++.h>
using namespace std;

struct Rect {
    long long x, y, dx, dy;
    int id;
};

static bool rightLess(const Rect& a, const Rect& b) {
    __int128 lhs = (__int128)(a.y + a.dy) * b.x;
    __int128 rhs = (__int128)(b.y + b.dy) * a.x;
    if (lhs != rhs) return lhs < rhs;

    __int128 la = (__int128)a.y * (b.x + b.dx);
    __int128 lb = (__int128)b.y * (a.x + a.dx);
    if (la != lb) return la > lb;

    return a.id < b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<Rect> rects(n);
    for (int i = 0; i < n; ++i) {
        cin >> rects[i].x >> rects[i].y >> rects[i].dx >> rects[i].dy;
        rects[i].id = i + 1;
    }

    sort(rects.begin(), rects.end(), rightLess);

    vector<int> chosen;
    chosen.reserve(n);

    bool hasEnd = false;
    long long endNum = 0, endDen = 1;

    for (const auto& r : rects) {
        __int128 leftLhs = (__int128)r.y * endDen;
        __int128 leftRhs = (__int128)endNum * (r.x + r.dx);
        if (!hasEnd || leftLhs > leftRhs) {
            chosen.push_back(r.id);
            hasEnd = true;
            endNum = r.y + r.dy;
            endDen = r.x;
        }
    }

    cout << chosen.size() << '\n';
    for (int i = 0; i < (int)chosen.size(); ++i) {
        if (i) cout << ' ';
        cout << chosen[i];
    }
    cout << '\n';

    return 0;
}