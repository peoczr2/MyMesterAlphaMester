/*
Megoldás vázlat:
Az épület a téglalapok uniója. A belső udvarok az unió komplementerének
korlátos összefüggő komponensei.

1) Koordináta-kompresszió (x/y töréspontok a téglalapélekből).
2) Y-szinteken végigsöprés:
   - eseményekkel (téglalap kezdete/vége) fenntartjuk az aktív x-fedést,
   - egy sorban előállítjuk az üres x-intervallumokat (run-ok).
3) A run-okból DSU-val komponenseket építünk (szomszédos sorok átfedő run-jai
   összekapcsolódnak).
   Komponens-aggregátumok:
   - terület,
   - kerület,
   - érinti-e a külső keretet (akkor nem udvar),
   - rendezési kulcs: legkisebb y, azon belül legkisebb x ("bal alsó sarok").
4) Az üres térrész kerületét run-rectangulumok unió-kerületként számoljuk:
   új run: +2*(szélesség+magasság),
   függőleges szomszédsági átfedés: -2*átfedés-szélesség.

A végén a nem-keretérintő komponensek a belső udvarok.
*/

#include <bits/stdc++.h>
using namespace std;

struct Rect {
    int x1, y1, x2, y2;
};

struct Event {
    int l, r, delta; // cella-index intervallum: [l, r]
};

struct Run {
    int l, r; // cella-index intervallum: [l, r]
    int node; // DSU csúcs id
};

struct DSU {
    vector<int> p, r;
    vector<long long> area, perim;
    vector<char> exterior;
    vector<int> minY;
    vector<long long> minX;

    int addNode(long long a, long long pe, bool ex, int my, long long mx) {
        int id = (int)p.size();
        p.push_back(id);
        r.push_back(0);
        area.push_back(a);
        perim.push_back(pe);
        exterior.push_back(ex ? 1 : 0);
        minY.push_back(my);
        minX.push_back(mx);
        return id;
    }

    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }

    int unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return a;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) ++r[a];

        area[a] += area[b];
        perim[a] += perim[b];
        exterior[a] = (exterior[a] || exterior[b]);
        if (minY[b] < minY[a] || (minY[b] == minY[a] && minX[b] < minX[a])) {
            minY[a] = minY[b];
            minX[a] = minX[b];
        }
        return a;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<Rect> rects(N);
    vector<int> xs, ys;
    xs.reserve(2 * N);
    ys.reserve(2 * N);

    for (int i = 0; i < N; ++i) {
        cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
        if (rects[i].x1 > rects[i].x2) swap(rects[i].x1, rects[i].x2);
        if (rects[i].y1 > rects[i].y2) swap(rects[i].y1, rects[i].y2);
        xs.push_back(rects[i].x1);
        xs.push_back(rects[i].x2);
        ys.push_back(rects[i].y1);
        ys.push_back(rects[i].y2);
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    int W = (int)xs.size() - 1; // cellák száma x irányban
    int H = (int)ys.size() - 1; // cellák száma y irányban

    if (W <= 0 || H <= 0) {
        cout << 0 << "\n\n\n";
        return 0;
    }

    vector<vector<Event>> events(H + 1);
    events.reserve(H + 1);

    auto xIdx = [&](int x) {
        return (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin());
    };
    auto yIdx = [&](int y) {
        return (int)(lower_bound(ys.begin(), ys.end(), y) - ys.begin());
    };

    for (const auto& rc : rects) {
        int lx = xIdx(rc.x1), rx = xIdx(rc.x2);
        int ly = yIdx(rc.y1), ry = yIdx(rc.y2);
        if (lx >= rx || ly >= ry) continue;
        events[ly].push_back({lx, rx - 1, +1});
        events[ry].push_back({lx, rx - 1, -1});
    }

    vector<int> diff(W + 1, 0);
    vector<long long> xw(W), prefW(W + 1, 0);
    for (int i = 0; i < W; ++i) {
        xw[i] = (long long)xs[i + 1] - xs[i];
        prefW[i + 1] = prefW[i] + xw[i];
    }

    DSU dsu;
    vector<Run> prevRuns, curRuns;

    for (int j = 0; j < H; ++j) {
        for (const auto& ev : events[j]) {
            diff[ev.l] += ev.delta;
            diff[ev.r + 1] -= ev.delta;
        }

        curRuns.clear();
        long long yh = (long long)ys[j + 1] - ys[j];

        int cover = 0;
        int runL = -1;
        for (int i = 0; i < W; ++i) {
            cover += diff[i];
            bool emptyCell = (cover == 0);
            if (emptyCell) {
                if (runL == -1) runL = i;
            } else {
                if (runL != -1) {
                    int l = runL, r = i - 1;
                    long long width = prefW[r + 1] - prefW[l];
                    bool ex = (j == 0 || j == H - 1 || l == 0 || r == W - 1);
                    int node = dsu.addNode(
                        width * yh,
                        2LL * (width + yh),
                        ex,
                        ys[j],
                        (long long)xs[l]
                    );
                    curRuns.push_back({l, r, node});
                    runL = -1;
                }
            }
        }
        if (runL != -1) {
            int l = runL, r = W - 1;
            long long width = prefW[r + 1] - prefW[l];
            bool ex = (j == 0 || j == H - 1 || l == 0 || r == W - 1);
            int node = dsu.addNode(
                width * yh,
                2LL * (width + yh),
                ex,
                ys[j],
                (long long)xs[l]
            );
            curRuns.push_back({l, r, node});
        }

        // Kapcsolatok az előző sor run-jaival (függőleges szomszédság).
        int p = 0, c = 0;
        while (p < (int)prevRuns.size() && c < (int)curRuns.size()) {
            int L = max(prevRuns[p].l, curRuns[c].l);
            int R = min(prevRuns[p].r, curRuns[c].r);
            if (L <= R) {
                int ra = dsu.find(prevRuns[p].node);
                int rb = dsu.find(curRuns[c].node);
                int rr = dsu.unite(ra, rb);
                long long overlapW = prefW[R + 1] - prefW[L];
                dsu.perim[rr] -= 2LL * overlapW;
            }
            if (prevRuns[p].r < curRuns[c].r) ++p;
            else ++c;
        }

        prevRuns = curRuns;
    }

    struct Courtyard {
        int minY;
        long long minX;
        long long perim;
        long long area;
    };

    vector<char> seen(dsu.p.size(), 0);
    vector<Courtyard> ans;

    for (int i = 0; i < (int)dsu.p.size(); ++i) {
        int r = dsu.find(i);
        if (seen[r]) continue;
        seen[r] = 1;
        if (!dsu.exterior[r]) {
            ans.push_back({dsu.minY[r], dsu.minX[r], dsu.perim[r], dsu.area[r]});
        }
    }

    sort(ans.begin(), ans.end(), [](const Courtyard& a, const Courtyard& b) {
        if (a.minY != b.minY) return a.minY < b.minY;
        return a.minX < b.minX;
    });

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i].perim;
    }
    cout << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i].area;
    }
    cout << '\n';

    return 0;
}
