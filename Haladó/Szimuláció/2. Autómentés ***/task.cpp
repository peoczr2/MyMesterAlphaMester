/*
Megoldás lényege:
Három részben dolgozunk. Először a forgalmat lépésenként (t -> t+1) szimuláljuk a baleset időpontjáig: egy autó új helye min(x+v, u-1), ahol u az előtte lévő autó új helye, az előzés pedig csak akkor történik meg, ha a célsávban nem halad át autó az átlépési pozíción; ebből adódik az A rész. A mentő útját időben haladó keresés (BFS) adja: egy állapot a (idő, pozíció, sáv) hármas, a legkisebb idő a célállapot első elérési ideje, az útvonalat a célból visszafelé építjük, mindig a legkisebb x-szel rendelkező megelőző állapotot választva. A B és C részben az autók pozíciója lineáris (állnak, vagy állandó sebességgel mennek, sávot nem váltanak), ezért az ütközés-ellenőrzés a legközelebbi autók keresésével gyorsan megoldható. A D részben a forgalom tovább halad, és a mentő csak olyan lépést tehet, amely egyetlen autó mozgását sem változtatja meg; ezt az érintett autók új helyének összevetésével ellenőrizzük. Az időigény a forgalomszimuláció (T lépés, n autó) és a BFS (időlépések x sávok x pozíciók), a memória a rétegenkénti bitmintákkal kevés.
*/
/*
Hint 1: || Egy autó új helyét egy lépésben az előtte lévő autó új helyéből kapod: ha az előtte lévő autó új helye u, akkor az új hely min(x+v, u-1). Az autókat sávonként, elölről hátrafelé dolgozd fel, és az előzést (balra előny) csak akkor engedd meg, ha az átlépési pozíción nem halad át autó. ||
Hint 2: || A mentő állapota (idő, x, sáv): rétegenként haladj előre az időben, és a következő réteg állapotai legyenek: előre legfeljebb a sebességéig, vagy egy lépéssel oldalra (x+1, sáv+-1). A B és C esetben az autók helye p0 + s*t alakú, így a szomszédos autó ellenőrzéséhez elég egy bináris keresés. ||
Hint 3: || A B rész útját a célból, (Bx, 0)-ból visszafelé rekonstruáld: minden lépésnél a megelőző rétegben azt az állapotot válaszd, amelyből a lépés lehetséges, és a legkisebb (x, sáv) párt. Így a feladat mintájával egyező útvonalat kapsz. ||
Hint 4: || A D részben nem kell minden időpontot eltárolni: elég két egymást követő forgalmi pillanatot megtartani. A mentő minden lépését úgy ellenőrizd, hogy az érintett autók ugyanúgy mozognak-e, mint mentő nélkül: az előzési kísérleteket, a mögötte haladó autó új helyét és a sávváltás keresztezését nézd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const int XMAX = 4000;  // a pálya hossza
static const int VMAX = 99;    // legnagyobb sebesség: S < 100
static const int KMAX = 20000; // védőkorlát az időlépésekre

int K, M, T, Bx, n;
vector<int> Tin, Yin, Vc;

struct Snap {
    vector<int> X, Y;
    vector<char> alive;
};

// Egy időlépés: a t időpontbeli állapotból a t+1-belit (új belépés nincs).
Snap step(const Snap& s) {
    vector<int> ids;
    for (int i = 0; i < n; ++i)
        if (s.alive[i]) ids.push_back(i);
    Snap out = s;
    if (ids.empty()) return out;

    vector<vector<pair<int, int>>> lanes(K + 2);  // (x, id), x szerint rendezve
    for (int i : ids) lanes[s.Y[i]].push_back({s.X[i], i});
    for (auto& L : lanes) sort(L.begin(), L.end());

    // az előzni próbáló autók: közvetlenül mögötte van, és gyorsabb
    vector<int> elig;
    for (int y = 1; y <= K; ++y) {
        const auto& L = lanes[y];
        for (size_t j = 0; j + 1 < L.size(); ++j)
            if (L[j + 1].first == L[j].first + 1 && Vc[L[j].second] > Vc[L[j + 1].second])
                elig.push_back(L[j].second);
    }

    vector<int> np(n, 0);
    // acc[i] = 0: marad a sávjában; különben az átvétel célsávja
    auto build = [&](const vector<int>& acc) {
        vector<vector<pair<int, int>>> E(K + 2);  // (kulcs, id): maradó 2x, sávot váltó 2x+1
        for (int i : ids) {
            if (acc[i] == 0) E[s.Y[i]].push_back({2 * s.X[i], i});
            else E[acc[i]].push_back({2 * s.X[i] + 1, i});
        }
        for (int y = 1; y <= K; ++y) {
            auto& e = E[y];
            sort(e.begin(), e.end(), greater<pair<int, int>>());
            set<int> ahead;  // már feldolgozott autók új helyei
            for (auto [key, i] : e) {
                int xt = s.X[i];
                if (key & 1) {
                    np[i] = xt + 1;
                    ahead.insert(xt + 1);
                } else {
                    int p = xt + Vc[i];
                    auto it = ahead.upper_bound(xt);
                    if (it != ahead.end() && *it - 1 < p) p = *it - 1;
                    np[i] = p;
                    ahead.insert(p);
                }
            }
        }
    };

    vector<int> acc(n, 0);
    for (int it = 0; it < 30; ++it) {
        build(acc);
        vector<pair<int, int>> nacc;  // (id, célsáv)
        for (int i : elig) {
            int x = s.X[i], y = s.Y[i], p = x + 1;
            auto ok = [&](int ty) {
                if (ty < 1 || ty > K) return false;
                const auto& L = lanes[ty];
                auto lo = lower_bound(L.begin(), L.end(), make_pair(p - VMAX - 1, INT_MIN));
                for (auto q = lo; q != L.end() && q->first < p; ++q) {
                    int d = q->second;
                    if (acc[d] != 0) continue;
                    if (p <= np[d]) return false;  // átmegy a p pozíción
                }
                return true;
            };
            if (ok(y + 1)) nacc.push_back({i, y + 1});
            else if (ok(y - 1)) nacc.push_back({i, y - 1});
        }
        // ütközés: a balra előzőnek van elsőbbsége
        stable_sort(nacc.begin(), nacc.end(), [&](const pair<int, int>& a, const pair<int, int>& b) {
            int ka = a.second > s.Y[a.first] ? 0 : 1;
            int kb = b.second > s.Y[b.first] ? 0 : 1;
            return ka < kb;
        });
        set<pair<int, int>> spots;
        vector<int> fin(n, 0);
        for (auto [i, ty] : nacc) {
            pair<int, int> key = {ty, s.X[i] + 1};
            if (spots.count(key)) continue;
            spots.insert(key);
            fin[i] = ty;
        }
        if (fin == acc) break;
        acc = fin;
    }
    build(acc);
    for (int i : ids) {
        if (acc[i]) {
            out.X[i] = s.X[i] + 1;
            out.Y[i] = acc[i];
        } else {
            out.X[i] = np[i];
            out.Y[i] = s.Y[i];
        }
    }
    for (int i : ids)
        if (out.X[i] > XMAX) out.alive[i] = 0;
    return out;
}

// A mentő útja a baleset után, ha az autók állandó s sebességgel mennek (s = 0: állnak).
// Az autók sávot nem váltanak. Visszaadja az időt (vagy -1), és ha want, az útvonalat.
int rescue_linear(const vector<pair<int, int>>& atT, int s, bool want, vector<pair<int, int>>& path) {
    vector<vector<int>> L(K + 2);
    for (auto [x, y] : atT) L[y].push_back(x);
    for (auto& v : L) sort(v.begin(), v.end());

    auto fwd_ok = [&](int y, int x, int xn, int k) {
        const auto& Lv = L[y];
        int a = int(upper_bound(Lv.begin(), Lv.end(), x - s * k) - Lv.begin());
        if (a < (int)Lv.size() && Lv[a] + s * (k + 1) <= xn) return false;
        int b = a - 1;
        if (b >= 0 && Lv[b] + s * (k + 1) >= xn) return false;
        return true;
    };
    auto lane_ok = [&](int yn, int xn, int k) {
        const auto& Lv = L[yn];
        int target = xn - s * (k + 1);
        int j = int(lower_bound(Lv.begin(), Lv.end(), target) - Lv.begin());
        if (j < (int)Lv.size() && Lv[j] == target) return false;
        int b = int(lower_bound(Lv.begin(), Lv.end(), xn - s * k) - Lv.begin()) - 1;
        if (b >= 0 && Lv[b] + s * (k + 1) >= xn) return false;
        return true;
    };
    auto lane0_ok = [&](int x, int k) {
        if (!(x < Bx && Bx <= x + M)) return false;
        for (int p0 : L[1]) {
            int p = p0 + s * k;
            if (x < p && p <= Bx) return false;
        }
        return true;
    };
    auto can_move = [&](int x, int y, int xn, int yn, int k) {
        if (yn == y) {
            if (xn < x || xn > min(x + M, Bx)) return false;
            return fwd_ok(y, x, xn, k);
        }
        if (y == 1 && yn == 0) return xn == Bx && x < Bx && Bx <= x + M && lane0_ok(x, k);
        if (abs(yn - y) == 1 && yn >= 1 && yn <= K) return xn == x + 1 && lane_ok(yn, xn, k);
        return false;
    };

    int W = (K + 1) * (Bx + 1);
    int WORDS = (W + 63) / 64;
    auto id = [&](int x, int y) { return y * (Bx + 1) + x; };
    auto getb = [&](const vector<uint64_t>& b, int i) { return (b[i >> 6] >> (i & 63)) & 1ULL; };
    auto setb = [&](vector<uint64_t>& b, int i) { b[i >> 6] |= 1ULL << (i & 63); };

    vector<vector<uint64_t>> layers;
    vector<pair<int, int>> curList;
    vector<uint64_t> first(WORDS, 0);
    for (int y0 = 1; y0 <= K; ++y0) {
        bool good = true;
        for (int p0 : L[y0])
            if (p0 + s == 1) good = false;
        if (good) {
            setb(first, id(1, y0));
            curList.push_back({1, y0});
        }
    }
    layers.push_back(first);
    int k = 1;
    int target = id(Bx, 0);
    while (!getb(layers.back(), target)) {
        if (curList.empty() || k >= KMAX) return -1;
        vector<uint64_t> nb(WORDS, 0);
        vector<pair<int, int>> nl;
        auto add = [&](int x, int y) {
            int i = id(x, y);
            if (!getb(nb, i)) {
                setb(nb, i);
                nl.push_back({x, y});
            }
        };
        for (auto [x, y] : curList) {
            if (y == 1 && lane0_ok(x, k)) add(Bx, 0);
            int top = min(x + M, Bx);
            for (int xn = x; xn <= top; ++xn)
                if (!getb(nb, id(xn, y)) && fwd_ok(y, x, xn, k)) add(xn, y);
            if (x + 1 <= Bx)
                for (int yn : {y - 1, y + 1})
                    if (yn >= 1 && yn <= K && !getb(nb, id(x + 1, yn)) && lane_ok(yn, x + 1, k))
                        add(x + 1, yn);
        }
        layers.push_back(nb);
        curList.swap(nl);
        ++k;
    }
    int Kend = k;
    if (want) {
        path.clear();
        pair<int, int> cur = {Bx, 0};
        path.push_back(cur);
        for (int kk = Kend - 1; kk >= 1; --kk) {
            const auto& lay = layers[kk - 1];
            pair<int, int> best = {-1, -1};
            for (int x = 1; x <= Bx && best.first < 0; ++x)
                for (int y = 1; y <= K; ++y) {
                    if (!getb(lay, id(x, y))) continue;
                    if (can_move(x, y, cur.first, cur.second, kk)) {
                        best = {x, y};
                        break;
                    }
                }
            if (best.first < 0) return -1;
            path.push_back(best);
            cur = best;
        }
        reverse(path.begin(), path.end());
    }
    return Kend;
}

// A mentő útja, ha az autók a baleset után tovább közlekednek a szokásos szabályok szerint.
// A mentő csak olyan lépést tehet, amely egyetlen autó mozgását sem változtatja meg.
int dsolve(const Snap& start) {
    Snap cur = step(start);  // a t = T+k időpontbeli forgalom (k = 1 -> T+1)
    Snap nxt = step(cur);    // a t = T+k+1 időpontbeli forgalom

    struct View {
        vector<vector<int>> xs, ids;  // sávonként x szerint rendezve
        vector<vector<int>> occ;      // occ[y][p] = autó a (p,y) cellában, vagy -1
    };
    int GX = max(XMAX, Bx) + 2;
    auto build_view = [&](const Snap& s) {
        View v;
        v.xs.assign(K + 2, {});
        v.ids.assign(K + 2, {});
        v.occ.assign(K + 2, vector<int>(GX, -1));
        vector<vector<pair<int, int>>> tmp(K + 2);
        for (int i = 0; i < n; ++i)
            if (s.alive[i]) tmp[s.Y[i]].push_back({s.X[i], i});
        for (int y = 1; y <= K; ++y) {
            sort(tmp[y].begin(), tmp[y].end());
            for (auto [x, i] : tmp[y]) {
                v.xs[y].push_back(x);
                v.ids[y].push_back(i);
                if (x < GX) v.occ[y][x] = i;
            }
        }
        return v;
    };

    vector<pair<int, int>> lay;
    {
        View v1 = build_view(cur);
        for (int y0 = 1; y0 <= K; ++y0)
            if (v1.occ[y0][1] < 0) lay.push_back({1, y0});
    }
    int k = 1;
    while (true) {
        if (lay.empty() || k >= KMAX) return -1;
        View V0 = build_view(cur), V1 = build_view(nxt);

        auto stay = [&](int c, int ly) { return nxt.alive[c] && nxt.Y[c] == ly; };
        // maradó autók: ugyanabban a sávban marad a következő lépésben
        vector<vector<int>> nxtStay(K + 2), prvStay(K + 2);
        for (int ly = 1; ly <= K; ++ly) {
            const auto& ids = V0.ids[ly];
            int m = (int)ids.size();
            nxtStay[ly].assign(m + 1, m);
            for (int j = m - 1; j >= 0; --j)
                nxtStay[ly][j] = stay(ids[j], ly) ? j : nxtStay[ly][j + 1];
            prvStay[ly].assign(m, -1);
            for (int j = 0; j < m; ++j)
                prvStay[ly][j] = stay(ids[j], ly) ? j : (j ? prvStay[ly][j - 1] : -1);
        }
        // előzési kísérletek, amelyek sávba érkeznek: (y, p) -> darab
        vector<vector<int>> pre(K + 2, vector<int>(GX, 0));
        for (int ly = 1; ly <= K; ++ly) {
            const auto& xs = V0.xs[ly];
            const auto& ids = V0.ids[ly];
            for (size_t j = 0; j < xs.size(); ++j) {
                int a = ids[j], p = xs[j] + 1;
                if (p >= GX) continue;
                int f = V0.occ[ly][p];
                if (f < 0) continue;
                if (Vc[a] > Vc[f]) {
                    if (ly - 1 >= 1) pre[ly - 1][p]++;
                    if (ly + 1 <= K) pre[ly + 1][p]++;
                }
            }
        }
        for (int y = 1; y <= K; ++y)
            for (int p = 1; p < GX; ++p) pre[y][p] += pre[y][p - 1];

        auto fwd_ok = [&](int x, int y, int xn) {
            if (V1.occ[y][xn] >= 0) return false;
            const auto& xs = V0.xs[y];
            const auto& ids = V0.ids[y];
            int a = int(upper_bound(xs.begin(), xs.end(), x) - xs.begin());
            int j = nxtStay[y][a];
            if (j < (int)xs.size() && nxt.X[ids[j]] <= xn) return false;
            int b = a - 1;
            if (b >= 0) {
                int jj = prvStay[y][b];
                if (jj >= 0 && nxt.X[ids[jj]] >= xn) return false;
            }
            const auto& xs1 = V1.xs[y];
            const auto& ids1 = V1.ids[y];
            int a1 = int(lower_bound(xs1.begin(), xs1.end(), xn) - xs1.begin()) - 1;
            if (a1 >= 0) {
                int c1 = ids1[a1];
                if (cur.Y[c1] == y && cur.alive[c1])
                    if (min(cur.X[c1] + Vc[c1], xn - 1) != nxt.X[c1]) return false;
            }
            int vm = xn - x;
            if (x - 1 >= 1 && V0.occ[y][x - 1] >= 0 && Vc[V0.occ[y][x - 1]] > vm) return false;
            if (pre[y][xn] - pre[y][x] > 0) return false;
            return true;
        };
        auto lane_ok = [&](int x, int y, int yn) {
            int xn = x + 1;
            if (V1.occ[yn][xn] >= 0) return false;
            const auto& xs = V0.xs[yn];
            const auto& ids = V0.ids[yn];
            int a = int(lower_bound(xs.begin(), xs.end(), xn) - xs.begin());
            int b = a - 1;
            if (b >= 0) {
                int jj = prvStay[yn][b];
                if (jj >= 0 && nxt.X[ids[jj]] >= xn) return false;
            }
            const auto& xs1 = V1.xs[yn];
            const auto& ids1 = V1.ids[yn];
            int a1 = int(lower_bound(xs1.begin(), xs1.end(), xn) - xs1.begin()) - 1;
            if (a1 >= 0) {
                int c1 = ids1[a1];
                if (cur.Y[c1] == yn && cur.alive[c1])
                    if (min(cur.X[c1] + Vc[c1], xn - 1) != nxt.X[c1]) return false;
            }
            if (x - 1 >= 1 && V0.occ[y][x - 1] >= 0 && Vc[V0.occ[y][x - 1]] > 1) return false;
            if (pre[yn][xn] - pre[yn][xn - 1] > 0) return false;
            return true;
        };
        auto lane0_ok = [&](int x) {
            if (!(x < Bx && Bx <= x + M)) return false;
            if (x - 1 >= 1 && V0.occ[1][x - 1] >= 0 && Vc[V0.occ[1][x - 1]] > Bx - x) return false;
            const auto& xs1 = V0.xs[1];
            auto it = upper_bound(xs1.begin(), xs1.end(), x);
            if (it != xs1.end() && *it <= Bx) return false;
            return true;
        };

        vector<char> nb((size_t)(K + 1) * (Bx + 1), 0);
        vector<pair<int, int>> nl;
        auto add = [&](int x, int y) {
            size_t i = (size_t)y * (Bx + 1) + x;
            if (!nb[i]) {
                nb[i] = 1;
                nl.push_back({x, y});
            }
        };
        for (auto [x, y] : lay) {
            if (y == 1 && lane0_ok(x)) add(Bx, 0);
            int top = min(x + M, Bx);
            for (int xn = x; xn <= top; ++xn)
                if (!nb[(size_t)y * (Bx + 1) + xn] && fwd_ok(x, y, xn)) add(xn, y);
            if (x + 1 <= Bx)
                for (int yn : {y - 1, y + 1})
                    if (yn >= 1 && yn <= K && !nb[(size_t)yn * (Bx + 1) + x + 1] && lane_ok(x, y, yn))
                        add(x + 1, yn);
        }
        ++k;
        if (nb[(size_t)0 * (Bx + 1) + Bx]) return k;
        if (nl.empty()) return -1;
        lay.swap(nl);
        cur = nxt;
        nxt = step(nxt);
    }
}

int main() {
    cin >> K >> M >> T >> Bx;
    vector<int> ty, yy, vv;
    while (true) {
        int t, y, v;
        if (!(cin >> t >> y >> v)) break;
        if (t == 0 && y == 0 && v == 0) break;
        ty.push_back(t);
        yy.push_back(y);
        vv.push_back(v);
    }
    n = (int)ty.size();
    Tin = ty;
    Yin = yy;
    Vc = vv;

    // A: az autók állapota a baleset T időpontjában
    Snap st;
    st.X.assign(n, 0);
    st.Y.assign(n, 0);
    st.alive.assign(n, 0);
    int ptr = 0;
    for (int t = 1; t <= T; ++t) {
        while (ptr < n && Tin[ptr] <= t) {
            st.alive[ptr] = 1;
            st.X[ptr] = 1;
            st.Y[ptr] = Yin[ptr];
            ++ptr;
        }
        if (t == T) break;
        st = step(st);
    }
    vector<pair<int, int>> sec;  // (sáv, x)
    for (int i = 0; i < n; ++i)
        if (st.alive[i] && st.X[i] >= 1 && st.X[i] <= Bx) sec.push_back({st.Y[i], st.X[i]});
    sort(sec.begin(), sec.end());

    vector<pair<int, int>> atT;  // (x, y)
    for (auto [y, x] : sec) atT.push_back({x, y});

    // B: az autók a baleset után megállnak
    vector<pair<int, int>> pathB;
    int tB = rescue_linear(atT, 0, true, pathB);
    // C: az autók állandó, (M-1) sebességgel haladnak, sávot nem váltanak
    vector<pair<int, int>> dummy;
    int tC = rescue_linear(atT, M - 1, false, dummy);
    // D: a forgalom tovább halad a szokásos szabályok szerint
    int tD = dsolve(st);

    string out;
    out += to_string(sec.size()) + "\n";
    for (size_t i = 0; i < sec.size(); ++i) {
        if (i) out += ' ';
        out += to_string(sec[i].second) + " " + to_string(sec[i].first);
    }
    out += "\n";
    out += to_string(tB < 0 ? -1 : tB) + "\n";
    if (tB >= 0) {
        for (size_t i = 0; i < pathB.size(); ++i) {
            if (i) out += ' ';
            out += to_string(pathB[i].first) + " " + to_string(pathB[i].second);
        }
    }
    out += "\n";
    out += to_string(tC) + "\n";
    out += to_string(tD) + "\n";
    cout << out;
    return 0;
}
