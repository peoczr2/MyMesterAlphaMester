/*
Megoldás lényege:
Bitonikus (x-monoton) egyszerű poligont építünk:
1) pontokat rendezzük (x,y) szerint,
2) a bal szélső L és jobb szélső R pont meghatározza az LR egyenest,
3) az LR feletti pontok mennek az "felső" láncba növekvő sorrendben,
4) az LR alatti pontok mennek az "alsó" láncba, de visszafelé járjuk be őket.
Az így kapott L -> felső -> R -> alsó(vissza) sorrend nem tartalmaz metsző éleket.

Idő: O(N log N)
*/

#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
    int id;
};

static long long cross(const Pt& a, const Pt& b, const Pt& c) {
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

    vector<Pt> pts(N);
    for (int i = 0; i < N; ++i) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].id = i + 1;
    }

    sort(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.id < b.id;
    });

    Pt L = pts.front(), R = pts.back();
    vector<Pt> upper, lower;

    for (int i = 1; i + 1 < N; ++i) {
        long long c = cross(L, R, pts[i]);
        if (c >= 0) upper.push_back(pts[i]);
        else lower.push_back(pts[i]);
    }

    vector<int> order;
    order.reserve(N);

    order.push_back(L.id);
    for (auto& p : upper) order.push_back(p.id);
    order.push_back(R.id);
    for (int i = (int)lower.size() - 1; i >= 0; --i) order.push_back(lower[i].id);

    for (int i = 0; i < N; ++i) {
        if (i) cout << ' ';
        cout << order[i];
    }
    cout << '\n';

    return 0;
}
