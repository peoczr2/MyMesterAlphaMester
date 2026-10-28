/*
Megoldás lényege:
Az udvarok azok az üres cellák véges, oldalukon keresztül összefüggő komponensei, amelyek nincsenek a külső térrel kapcsolatban. A koordinátákat tömörítjük, és y szerint sávonként haladunk: egy sávban az üres x-cellák maximális futamait kapjuk. Egy futam addig marad érvényes, amíg az őt határoló téglalapok nem változnak, ezért futamokat darabokként kezelünk, és csak a lefedettség változásakor hozunk létre újat. Egy darab területét és kerületét a lezárásakor téglalapként adjuk hozzá, a két egymás fölötti, átfedő darab közös szakaszát pedig kétszer levonjuk a kerületből. A darabokat DSU-val kötjük össze; a külső keretet érintő komponensek nem udvarok. Az udvar bal alsó sarka a komponens legkisebb (y, x) pontja.
Idő: a sávonkénti munka a téglalapok határaira korlátozódik, a valós tesztekre gyors.
*/
/*
Hint 1: || Ne a teljes rácsot járd be: egy sávban elég a téglalapok kezdő- és végcelláit figyelembe venni, mert a lefedettség csak ott változik. ||
Hint 2: || Két egymás feletti sáv között egy üres futam változatlan maradhat, ezért csak a megváltozó futamokat hozd létre újra, és az átfedő darabokat DSU-val kösd össze. ||
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Run {
    int l, r;   // cella-index intervallum: [l, r] (inkluzív)
    int node;   // DSU csúcs (darab), amelyhez a futam tartozik
};

static vector<int> par, rnk_, startIdx;
static vector<ll> area_, perim_, minY_, minX_;
static vector<char> ex_;

static int findp(int x) {
    while (par[x] != x) {
        par[x] = par[par[x]];
        x = par[x];
    }
    return x;
}

static int unite(int a, int b) {
    a = findp(a);
    b = findp(b);
    if (a == b) return a;
    if (rnk_[a] < rnk_[b]) swap(a, b);
    par[b] = a;
    if (rnk_[a] == rnk_[b]) ++rnk_[a];
    area_[a] += area_[b];
    perim_[a] += perim_[b];
    ex_[a] = ex_[a] || ex_[b];
    if (minY_[b] < minY_[a] || (minY_[b] == minY_[a] && minX_[b] < minX_[a])) {
        minY_[a] = minY_[b];
        minX_[a] = minX_[b];
    }
    return a;
}

static int newNode(int startRow, ll y, ll x, bool exterior) {
    int id = (int)par.size();
    par.push_back(id);
    rnk_.push_back(0);
    startIdx.push_back(startRow);
    area_.push_back(0);
    perim_.push_back(0);
    minY_.push_back(y);
    minX_.push_back(x);
    ex_.push_back(exterior ? 1 : 0);
    return id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<array<int, 4>> rc(N);
    vector<int> xs, ys;
    xs.reserve(2 * N);
    ys.reserve(2 * N);
    for (auto& r : rc) {
        cin >> r[0] >> r[1] >> r[2] >> r[3];
        if (r[0] > r[2]) swap(r[0], r[2]);
        if (r[1] > r[3]) swap(r[1], r[3]);
        xs.push_back(r[0]);
        xs.push_back(r[2]);
        ys.push_back(r[1]);
        ys.push_back(r[3]);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    int W = (int)xs.size() - 1;  // cellák száma x irányban
    int H = (int)ys.size() - 1;  // sorok (sávok) száma y irányban
    if (W <= 0 || H <= 0) {
        cout << 0 << "\n\n\n";
        return 0;
    }

    vector<ll> prefW(W + 1, 0);
    for (int i = 0; i < W; ++i) prefW[i + 1] = prefW[i] + ((ll)xs[i + 1] - xs[i]);

    auto xIdx = [&](int x) { return (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin()); };
    auto yIdx = [&](int y) { return (int)(lower_bound(ys.begin(), ys.end(), y) - ys.begin()); };

    // A téglalap a sávok [ly, ry) tartományában aktív; cellák [lx, rx).
    vector<vector<pair<int, int>>> startAt(H), endAt(H + 1);
    for (const auto& r : rc) {
        int lx = xIdx(r[0]), rx = xIdx(r[2]);
        int ly = yIdx(r[1]), ry = yIdx(r[3]);
        if (lx >= rx || ly >= ry) continue;
        startAt[ly].push_back({lx, rx});
        endAt[ry].push_back({lx, rx});
    }

    // dm: kulcs = cellaindex, érték = a lefedettség változása ott.
    map<int, int> dm;
    vector<Run> prev, cur;

    for (int j = 0; j < H; ++j) {
        for (auto [lx, rx] : endAt[j]) {
            dm[lx] -= 1;
            dm[rx] += 1;
        }
        for (auto [lx, rx] : startAt[j]) {
            dm[lx] += 1;
            dm[rx] -= 1;
        }

        // Az üres (lefedetlen) cellák maximális futamai ebben a sávban.
        cur.clear();
        int prevPos = 0, cover = 0;
        for (auto it = dm.begin(); it != dm.end();) {
            int k = it->first, d = it->second;
            if (d == 0) {
                it = dm.erase(it);
                continue;
            }
            if (k > prevPos && cover == 0) cur.push_back({prevPos, k - 1, -1});
            cover += d;
            prevPos = k;
            ++it;
        }
        if (prevPos < W && cover == 0) cur.push_back({prevPos, W - 1, -1});

        const size_t P = prev.size(), C = cur.size();
        vector<char> pcont(P, 0);

        // A) Azonos (l,r) futamok folytatódnak: ugyanaz a darab, nincs új határ.
        {
            size_t p = 0, c = 0;
            while (p < P && c < C) {
                if (max(prev[p].l, cur[c].l) <= min(prev[p].r, cur[c].r)) {
                    if (prev[p].l == cur[c].l && prev[p].r == cur[c].r) {
                        cur[c].node = prev[p].node;
                        pcont[p] = 1;
                    }
                }
                if (prev[p].r < cur[c].r) ++p;
                else ++c;
            }
        }

        // B) Új futamok: új darab, a sáv alja adja a kezdő y-t.
        for (auto& cr : cur) {
            if (cr.node == -1) {
                bool exterior = (j == 0 || j == H - 1 || cr.l == 0 || cr.r == W - 1);
                cr.node = newNode(j, ys[j], xs[cr.l], exterior);
            } else if (j == 0 || j == H - 1) {
                ex_[findp(cr.node)] = 1;
            }
        }

        // C) Megszűnt darabok: téglalapként lezárjuk (terület, kerület).
        for (size_t p = 0; p < P; ++p) {
            if (pcont[p]) continue;
            int root = findp(prev[p].node);
            ll h = (ll)ys[j] - ys[startIdx[prev[p].node]];
            ll w = prefW[prev[p].r + 1] - prefW[prev[p].l];
            area_[root] += w * h;
            perim_[root] += 2LL * (w + h);
        }

        // D) Függőleges szomszédság: átfedő, de nem azonos futamok összekötése.
        {
            size_t p = 0, c = 0;
            while (p < P && c < C) {
                int L = max(prev[p].l, cur[c].l);
                int R = min(prev[p].r, cur[c].r);
                if (L <= R && !(prev[p].l == cur[c].l && prev[p].r == cur[c].r)) {
                    int rr = unite(prev[p].node, cur[c].node);
                    perim_[rr] -= 2LL * (prefW[R + 1] - prefW[L]);
                }
                if (prev[p].r < cur[c].r) ++p;
                else ++c;
            }
        }

        prev.swap(cur);
    }

    // A legfelső sáv futamai (és az alsó sáv) a külső térhez tartoznak; az
    // üreg-komponensek a nem külső gyökerek.
    struct Courtyard {
        ll minY, minX, perim, area;
    };
    vector<Courtyard> ans;
    for (int i = 0; i < (int)par.size(); ++i) {
        if (findp(i) != i || ex_[i]) continue;
        ans.push_back({minY_[i], minX_[i], perim_[i], area_[i]});
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
