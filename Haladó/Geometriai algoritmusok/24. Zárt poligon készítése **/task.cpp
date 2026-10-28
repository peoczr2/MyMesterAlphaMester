/*
Megoldás lényege:
Rendezzük a pontokat (x, y) szerint. A legbaloldalibb L és a legjobboldalibb R pont közötti LR egyenes két oldalán lévő pontokból két láncot építünk: a felső láncot x szerint növekvő, az alsót csökkenő sorrendben bejárva az L -> felső -> R -> alsó (visszafelé) -> L sorrend x-monoton zárt poligont ad. A két lánc csak L-ben és R-ben érintkezik, így nincs metsző élpár. Az LR egyenesen fekvő pontokat úgy kell besorolni, hogy ne fusson rajtuk közvetlenül L és R között él: ha van LR alatti pont, a felső láncba kerülnek, különben az alsóba. Idő: O(N log N)
*/
/*
Hint 1: || Keress olyan bejárást, ahol a poligon két x-monoton láncból áll: a bal szélső pont (L) és a jobb szélső pont (R) közötti egyenes két oldalán lévő pontok alkotják a láncokat. ||
Hint 2: || Rendezd a pontokat (x, y) szerint. A felső láncot balról jobbra, az alsót jobbról balra járd be; így a két lánc csak L-ben és R-ben érintkezhet, tehát nincs metsző él. ||
Hint 3: || Az LR egyenesen fekvő pontokat úgy kell besorolni, hogy ne fussanak rajtuk a poligon olyan élei, amelyek L és R között közvetlenül haladnak. Ha van az egyenes alatt pont, ezek a felső láncba kerüljenek; ha nincs, az alsóba. ||
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

    // Az LR egyenesen fekvő pontok (c == 0) a felső láncba kerülnek, ha van LR alatti pont,
    // különben az alsó láncba: így az L és R közötti közvetlen él nem fut át köztes csúcson.
    bool anyBelow = false;
    for (int i = 1; i + 1 < N; ++i) {
        if (cross(L, R, pts[i]) < 0) {
            anyBelow = true;
            break;
        }
    }
    for (int i = 1; i + 1 < N; ++i) {
        long long c = cross(L, R, pts[i]);
        if (c > 0 || (c == 0 && anyBelow)) upper.push_back(pts[i]);
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
