/*
Megoldás lényege:
Az új csomópontból (A) körbejárjuk a csomópontok irányait. Egy csomópont akkor köthető A-hoz, ha
az A-ból hozzá húzott szakasz nem tartalmaz más csomópontot, és nem metsz útszakaszt. Irányonként
ezért csak a legközelebbi csomópont lehet jelölt, és azt kell ellenőrizni, hogy a sugár nála
közelebb nem metsz útszakaszt.
Az útszakaszok a sugárral való metszéspontjuk távolsága szerint rendezett halmazban vannak. Két
esemény között ez a sorrend nem változik, mert az útszakaszok nem keresztezik egymást; a közös
végpontból induló szakaszok sorrendjét a sugár kissé elforgatott helyzete dönti el. Az aktív
szakaszok közül a legkisebb távolságút hasonlítjuk össze a jelölt csomóponttal.
Idő: O(N log N).
*/
/*
Hint 1: || Az A-ból nézve minden csomópontnak van iránya. Ha egy irányban több csomópont is van,
csak a legközelebbi köthető hozzá, a többi takarásban van. Ezért elég irányonként egy jelöltet
vizsgálni. ||
Hint 2: || Egy útszakasz az A-ból nézve egy 180°-nál kisebb szögtartományt fed le, amelyet a
végpontjainak iránya határol. Ennek a két határirányát események jelölik: itt tesszük be a
szakaszt a rendezett halmazba, illetve vesszük ki belőle. A 0° körül átforduló íveket két részre
kell bontani. ||
Hint 3: || Egy irányban a sugár az aktív szakaszokat a távolságuk szerint rendezi. Ha a legközelebbi
aktív szakasz távolabb van, mint a jelölt csomópont, akkor az A és a csomópont közötti szakasz
szabad. A távolság összehasonlításához elég a metszéspont paramétere, törtként, egész számokkal. ||
Hint 4: || Két útszakasz csak közös csomópontban találkozhat, ezért a rendezés két esemény között
nem változik. Ha több szakasz indul ugyanabból a csomópontból, a sorrendjüket a sugár kicsit
elforgatott helyzetéből döntsd el. A törlésnél tárold el a beszúrás iterátorát, hogy ne kelljen
hasonlítani. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Vec {
    long long x, y;
};

static inline long long cross(const Vec& a, const Vec& b) { return a.x * b.y - a.y * b.x; }
static inline long long dot(const Vec& a, const Vec& b) { return a.x * b.x + a.y * b.y; }

static inline int halfPlane(const Vec& a) {
    return (a.y > 0 || (a.y == 0 && a.x > 0)) ? 0 : 1;
}

static inline bool angleLess(const Vec& a, const Vec& b) {
    int ha = halfPlane(a), hb = halfPlane(b);
    if (ha != hb) return ha < hb;
    return cross(a, b) > 0;
}

static inline bool sameAngle(const Vec& a, const Vec& b) {
    return cross(a, b) == 0 && halfPlane(a) == halfPlane(b);
}

static inline Vec normalizeDir(Vec v) {
    long long g = std::gcd(llabs(v.x), llabs(v.y));
    if (g == 0) return {0, 0};
    return {v.x / g, v.y / g};
}

struct Part {
    Vec p, e;
};

static Vec curDir;
static vector<Part> parts;

struct Key {
    __int128 num, den, dt;
};

static Key keyAt(const Part& s, const Vec& d) {
    Key k;
    k.num = cross(s.p, s.e);
    k.den = cross(d, s.e);
    k.dt = dot(d, s.e);
    if (k.den < 0) {
        k.num = -k.num;
        k.den = -k.den;
        k.dt = -k.dt;
    }
    return k;
}

struct PartCmp {
    bool operator()(int a, int b) const {
        if (a == b) return false;
        Key ka = keyAt(parts[a], curDir), kb = keyAt(parts[b], curDir);
        __int128 lhs = ka.num * kb.den, rhs = kb.num * ka.den;
        if (lhs != rhs) return lhs < rhs;
        lhs = ka.dt * kb.den;
        rhs = kb.dt * ka.den;
        if (lhs != rhs) return lhs < rhs;
        return a < b;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    Vec A;
    cin >> A.x >> A.y;

    vector<Vec> rel(N + 1), dirRaw(N + 1);
    for (int i = 1; i <= N; ++i) {
        Vec p;
        cin >> p.x >> p.y;
        rel[i] = {p.x - A.x, p.y - A.y};
        dirRaw[i] = normalizeDir(rel[i]);
    }

    vector<pair<int, int>> edges(N - 1);
    for (int j = 0; j < N - 1; ++j) cin >> edges[j].first >> edges[j].second;

    vector<Vec> dirs(dirRaw.begin() + 1, dirRaw.end());
    sort(dirs.begin(), dirs.end(), angleLess);
    dirs.erase(unique(dirs.begin(), dirs.end(), sameAngle), dirs.end());
    const int K = (int)dirs.size();

    auto dirIndex = [&](const Vec& d) {
        return (int)(lower_bound(dirs.begin(), dirs.end(), d, angleLess) - dirs.begin());
    };

    vector<int> gid(N + 1), nearest(K, 0);
    vector<long long> nearestDist(K, LLONG_MAX);
    for (int i = 1; i <= N; ++i) {
        gid[i] = dirIndex(dirRaw[i]);
        long long d2 = rel[i].x * rel[i].x + rel[i].y * rel[i].y;
        if (d2 < nearestDist[gid[i]]) {
            nearestDist[gid[i]] = d2;
            nearest[gid[i]] = i;
        }
    }

    vector<vector<int>> insAfter(K), remAt(K);
    vector<int> insBefore0;
    for (auto [u, v] : edges) {
        int ia = gid[u], ib = gid[v];
        if (ia == ib) continue;
        long long cr = cross(rel[u], rel[v]);
        if (cr == 0) continue;
        Vec s = cr > 0 ? rel[u] : rel[v];
        Vec t = cr > 0 ? rel[v] : rel[u];
        int l = cr > 0 ? ia : ib;
        int r = cr > 0 ? ib : ia;
        Vec e{t.x - s.x, t.y - s.y};
        if (l < r) {
            int id = (int)parts.size();
            parts.push_back({s, e});
            insAfter[l].push_back(id);
            remAt[r].push_back(id);
        } else {
            int idA = (int)parts.size();
            parts.push_back({s, e});
            insAfter[l].push_back(idA);
            if (r > 0) {
                int idB = (int)parts.size();
                parts.push_back({s, e});
                insBefore0.push_back(idB);
                remAt[r].push_back(idB);
            }
        }
    }

    using SetT = set<int, PartCmp>;
    SetT active;
    vector<SetT::iterator> its(parts.size());
    vector<char> visible(N + 1, 0);

    for (int g = 0; g < K; ++g) {
        curDir = dirs[g];
        if (g == 0) {
            for (int id : insBefore0) its[id] = active.insert(id).first;
        }
        for (int id : remAt[g]) active.erase(its[id]);

        int v = nearest[g];
        if (v != 0) {
            if (active.empty()) {
                visible[v] = 1;
            } else {
                Key ks = keyAt(parts[*active.begin()], curDir);
                __int128 nv = dot(rel[v], curDir), dv = dot(curDir, curDir);
                visible[v] = !(ks.num * dv < nv * ks.den);
            }
        }
        for (int id : insAfter[g]) its[id] = active.insert(id).first;
    }

    vector<int> ans;
    for (int i = 1; i <= N; ++i)
        if (visible[i]) ans.push_back(i);

    cout << ans.size() << '\n';
    for (size_t i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
