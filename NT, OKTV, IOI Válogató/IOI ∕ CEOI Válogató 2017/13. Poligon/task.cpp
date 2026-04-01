/*
Megoldás lényege:
Az A és B pontot összekötő egyenes két oldalára bontjuk a többi pontot.
A felső oldal pontjait (pozitív orientáció) x, majd y szerint növekvően rendezzük,
ezután jönnek az egyenesre eső pontok, végül az alsó oldali pontok ugyanígy rendezve.

Így az A -> felső lánc -> egyenes pontjai -> alsó lánc -> B sorrendben kapott
törtvonal x-monoton az A-B tengelyhez képest, ezért nem metsző. A feladat
garantálja, hogy ilyen sorrend mindig létezik.
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

    int N, A, B;
    if (!(cin >> N >> A >> B)) return 0;

    vector<Pt> pts(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].id = i;
    }

    vector<Pt> upper, middle, lower;
    for (int i = 1; i <= N; ++i) {
        if (i == A || i == B) continue;
        long long s = cross(pts[A], pts[B], pts[i]);
        if (s > 0) upper.push_back(pts[i]);
        else if (s < 0) lower.push_back(pts[i]);
        else middle.push_back(pts[i]);
    }

    auto cmp = [](const Pt& p, const Pt& q) {
        if (p.x != q.x) return p.x < q.x;
        if (p.y != q.y) return p.y < q.y;
        return p.id < q.id;
    };

    sort(upper.begin(), upper.end(), cmp);
    sort(middle.begin(), middle.end(), cmp);
    sort(lower.begin(), lower.end(), cmp);

    vector<int> order;
    order.reserve(N);
    order.push_back(A);
    for (auto& p : upper) order.push_back(p.id);
    for (auto& p : middle) order.push_back(p.id);
    for (auto& p : lower) order.push_back(p.id);
    order.push_back(B);

    for (int i = 0; i < N; ++i) {
        if (i) cout << ' ';
        cout << order[i];
    }
    cout << '\n';
    return 0;
}