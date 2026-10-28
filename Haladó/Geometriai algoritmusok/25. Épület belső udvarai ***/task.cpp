/*
Megoldás lényege:
A koordináták tömörítése után az üres cellák (amelyeket egyetlen téglalap sem fed) összefüggő komponensei a belső udvarok; a cellák csak oldalukkal kapcsolódnak, sarkukkal nem. Sávonként (y szerint alulról felfelé) az üres cellák vízszintes futásokat alkotnak. Egy futás addig nem változik, amíg az eseményei nem érintik, ezért a több egymás fölötti sávon át azonos futásokból csempéket képezünk. Minden eseménynél csak az esemény x-tartományát és a szomszédos futásokat számoljuk újra, a lefedettségi számlálókat szakasz-fa tartja. Két egymás fölötti csempe, ha x-irányban átfedi egymást, unió-keresési (DSU) halmazba kerül, a kerületből pedig a közös vízszintes élek hosszának kétszeresét levonjuk. Egy komponens területe a csempeterületek összege; ha valamelyik csempe a rács szélét éri, a komponens a külső térhez tartozik, nem udvar. Az udvarokat a bal alsó sarkuk (y, majd x) szerint rendezzük. Idő: a csempék száma az események számával arányos, szakasz-fával.
*/
/*
Hint 1: || Koordináta-tömörítés után minden téglalap cellák halmaza. Az udvar olyan üres cellák összefüggő halmaza, amely nem éri el a rács szélét; a cellák csak oldalukkal kapcsolódnak, sarkukkal nem. ||
Hint 2: || Sávonként (y szerint) haladva az üres cellák vízszintes futásokat alkotnak. Két egymás fölötti futás akkor van összeköttetésben, ha x-irányban legalább egy cellán átfedik egymást. ||
Hint 3: || Ha minden sávban újra felsorolod az összes futást, az O(W*H) túl lassú. Egy esemény csak az x-tartományát érinti: a többi futás változatlan, ezért annak nem kell új csomópontot létrehozni. Egy lefedettségi számláló szakasz-fával gyorsan megtalálható az első üres és az első lefedett cella. ||
Hint 4: || Egy udvar kerülete a csempék kerületeinek összege, mínusz a közös élek hosszának kétszerese. A területe a csempeterületek összege, a bal alsó sarka pedig a legkisebb (y, x) párú csúcs. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Rect {
    int x1, y1, x2, y2;
};

// Lefedettségi számlálók a cellákon: tartományra összeadás, és az első nem üres / üres cella keresése.
// Az index 0 és az utolsó (n-1) őrszem, mindig lefedett.
struct Cover {
    int n;
    vector<int> add, mn, mx;
    explicit Cover(int size) : n(size), add(4 * size, 0), mn(4 * size, 0), mx(4 * size, 0) {}

    void update(int node, int nl, int nr, int l, int r, int v) {
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            add[node] += v;
            mn[node] += v;
            mx[node] += v;
            return;
        }
        int mid = (nl + nr) / 2;
        update(2 * node, nl, mid, l, r, v);
        update(2 * node + 1, mid + 1, nr, l, r, v);
        mn[node] = add[node] + min(mn[2 * node], mn[2 * node + 1]);
        mx[node] = add[node] + max(mx[2 * node], mx[2 * node + 1]);
    }

    int value(int p) const {
        int node = 1, nl = 0, nr = n - 1, s = 0;
        while (true) {
            s += add[node];
            if (nl == nr) return s;
            int mid = (nl + nr) / 2;
            if (p <= mid) { node = 2 * node; nr = mid; }
            else { node = 2 * node + 1; nl = mid + 1; }
        }
    }

    // Első p-nél nem kisebb index, ahol az érték > 0 (pos), illetve == 0 (!pos); ha nincs, n.
    int find(int node, int nl, int nr, int p, int acc, bool pos) const {
        if (nr < p) return -1;
        int best = acc + (pos ? mx[node] : mn[node]);
        if (pos ? best <= 0 : best != 0) return -1;
        if (nl == nr) return nl;
        int mid = (nl + nr) / 2;
        int acc2 = acc + add[node];
        int res = find(2 * node, nl, mid, p, acc2, pos);
        if (res != -1) return res;
        return find(2 * node + 1, mid + 1, nr, p, acc2, pos);
    }
    int firstFrom(int p, bool pos) const {
        int r = find(1, 0, n - 1, p, 0, pos);
        return r == -1 ? n : r;
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

    int W = (int)xs.size() - 1;
    int H = (int)ys.size() - 1;
    if (W <= 0 || H <= 0) {
        cout << 0 << "\n\n\n";
        return 0;
    }

    auto xIdx = [&](int x) { return (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin()); };
    auto yIdx = [&](int y) { return (int)(lower_bound(ys.begin(), ys.end(), y) - ys.begin()); };

    // Sávonként a változások: {l, r, delta}, ahol l..r a cellaindexek (a cella i indexe i+1).
    vector<vector<array<int, 3>>> events(H + 1);
    for (const auto& rc : rects) {
        int lx = xIdx(rc.x1), rx = xIdx(rc.x2);
        int ly = yIdx(rc.y1), ry = yIdx(rc.y2);
        if (lx >= rx || ly >= ry) continue;
        events[ly].push_back({lx + 1, rx, +1});
        events[ry].push_back({lx + 1, rx, -1});
    }

    // Csempék: a szabad tér olyan téglalapjai, amelyek több sávon át változatlanok.
    vector<int> tKl, tKr, tStart, par, siz;
    vector<char> tExt;
    vector<long long> tArea, tPer, tAdj;
    auto newTile = [&](int kl, int kr, int st) -> int {
        int id = (int)tKl.size();
        tKl.push_back(kl);
        tKr.push_back(kr);
        tStart.push_back(st);
        par.push_back(id);
        siz.push_back(1);
        tExt.push_back((kl == 1 || kr == W || st == 0) ? 1 : 0);
        tArea.push_back(0);
        tPer.push_back(0);
        tAdj.push_back(0);
        return id;
    };
    // A csempe a j. sáv alsó éléig tart (felső határa ys[j]).
    auto closeTile = [&](int t, int j) {
        long long w = xs[tKr[t]] - xs[tKl[t] - 1];
        long long h = ys[j] - ys[tStart[t]];
        tArea[t] = w * h;
        tPer[t] = 2 * (w + h);
    };
    auto findp = [&](int x) {
        while (par[x] != x) {
            par[x] = par[par[x]];
            x = par[x];
        }
        return x;
    };
    auto unite = [&](int a, int b) {
        a = findp(a);
        b = findp(b);
        if (a == b) return;
        if (siz[a] < siz[b]) swap(a, b);
        par[b] = a;
        siz[a] += siz[b];
    };
    auto mergeRegs = [](vector<pair<int, int>>& v) {
        sort(v.begin(), v.end());
        vector<pair<int, int>> out;
        for (auto [a, b] : v) {
            if (!out.empty() && a <= out.back().second + 1) out.back().second = max(out.back().second, b);
            else out.push_back({a, b});
        }
        v.swap(out);
    };

    int n = W + 2;
    Cover cov(n);
    cov.update(1, 0, n - 1, 0, 0, 1);
    cov.update(1, 0, n - 1, n - 1, n - 1, 1);

    // Az aktuális maximális üres futások: kl -> (kr, csempe)
    map<int, pair<int, int>> runs;
    runs[1] = {W, newTile(1, W, 0)};

    for (int j = 0; j < H; ++j) {
        if (events[j].empty()) continue;
        for (const auto& e : events[j]) cov.update(1, 0, n - 1, e[0], e[1], e[2]);

        // Az érintett tartományok: minden esemény cellái és a szomszédos cella; kiterjesztve az érintett futásokkal.
        vector<pair<int, int>> reg;
        for (const auto& e : events[j]) reg.push_back({e[0] - 1, e[1] + 1});
        mergeRegs(reg);
        bool changed = true;
        while (changed) {
            changed = false;
            for (auto& rg : reg) {
                int P = rg.first, Q = rg.second;
                int nP = P, nQ = Q;
                auto it = runs.upper_bound(P);
                if (it != runs.begin()) {
                    auto pv = prev(it);
                    if (pv->second.first >= P) it = pv;
                }
                for (; it != runs.end() && it->first <= Q; ++it) {
                    nP = min(nP, it->first);
                    nQ = max(nQ, it->second.first);
                }
                if (nP != P || nQ != Q) {
                    rg = {nP, nQ};
                    changed = true;
                }
            }
            if (changed) mergeRegs(reg);
        }

        for (const auto& rg : reg) {
            int P = rg.first, Q = rg.second;
            vector<int> oKl, oKr, oT;
            for (auto it = runs.lower_bound(P); it != runs.end() && it->first <= Q; ++it) {
                oKl.push_back(it->first);
                oKr.push_back(it->second.first);
                oT.push_back(it->second.second);
            }
            // Új futások a tartományban
            vector<pair<int, int>> nR;
            int p = P;
            while (p <= Q) {
                if (cov.value(p) > 0) {
                    p = cov.firstFrom(p, false);
                    continue;
                }
                int e = min(cov.firstFrom(p, true) - 1, Q);
                nR.push_back({p, e});
                p = e + 1;
            }

            map<pair<int, int>, int> oldTile;
            for (size_t i = 0; i < oKl.size(); ++i) oldTile[{oKl[i], oKr[i]}] = oT[i];
            set<pair<int, int>> newSet(nR.begin(), nR.end());

            // A megszűnt régi futások csempéi a j. sávnál zárulnak
            vector<int> uo;
            for (size_t i = 0; i < oKl.size(); ++i) {
                if (!newSet.count({oKl[i], oKr[i]})) {
                    uo.push_back((int)i);
                    closeTile(oT[i], j);
                }
            }
            // Az új futások: az azonosak megtartják a csempéjüket, a többi új csempe a j. sávtól indul
            vector<int> nT(nR.size());
            vector<int> un;
            for (size_t k = 0; k < nR.size(); ++k) {
                auto f = oldTile.find(nR[k]);
                if (f != oldTile.end()) {
                    nT[k] = f->second;
                } else {
                    nT[k] = newTile(nR[k].first, nR[k].second, j);
                    un.push_back((int)k);
                }
            }
            // Közös vízszintes él: a régi (lezáruló) és az új csempék között
            size_t a = 0, b = 0;
            while (a < uo.size() && b < un.size()) {
                int oi = uo[a], ni = un[b];
                int L = max(oKl[oi], nR[ni].first);
                int R = min(oKr[oi], nR[ni].second);
                if (L <= R) {
                    long long ov = xs[R] - xs[L - 1];
                    int ta = oT[oi], tb = nT[ni];
                    unite(ta, tb);
                    tAdj[ta] -= ov;
                    tAdj[tb] -= ov;
                }
                if (oKr[oi] < nR[ni].second) ++a;
                else ++b;
            }

            for (int kl : oKl) runs.erase(kl);
            for (size_t k = 0; k < nR.size(); ++k) runs[nR[k].first] = {nR[k].second, nT[k]};
        }
    }

    // A még nyitott csempék a felső határig (ys[H]) tartanak; ezek a külső térhez érnek.
    for (auto& kv : runs) {
        closeTile(kv.second.second, H);
        tExt[kv.second.second] = 1;
    }

    int T = (int)tKl.size();
    vector<long long> cArea(T, 0), cPer(T, 0);
    vector<char> cExt(T, 0);
    vector<pair<int, int>> cMin(T, {INT_MAX, INT_MAX});
    for (int t = 0; t < T; ++t) {
        int r = findp(t);
        cArea[r] += tArea[t];
        cPer[r] += tPer[t] + tAdj[t];
        cExt[r] |= tExt[t];
        pair<int, int> cand = {ys[tStart[t]], xs[tKl[t] - 1]};
        cMin[r] = min(cMin[r], cand);
    }

    struct Courtyard {
        int minY, minX;
        long long perim, area;
    };
    vector<Courtyard> ans;
    for (int t = 0; t < T; ++t) {
        if (findp(t) != t || cExt[t]) continue;
        ans.push_back({cMin[t].first, cMin[t].second, cPer[t], cArea[t]});
    }
    sort(ans.begin(), ans.end(), [](const Courtyard& a, const Courtyard& b) {
        if (a.minY != b.minY) return a.minY < b.minY;
        return a.minX < b.minX;
    });

    cout << ans.size() << '\n';
    for (size_t i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i].perim;
    }
    cout << '\n';
    for (size_t i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i].area;
    }
    cout << '\n';
    return 0;
}
