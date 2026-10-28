/*
Megoldás lényege:
Legyen o a q-hoz legközelebbi pont. Az oq szakasz belsejében nincs P-pont, ezért a q-t tartalmazó üres háromszöget az oq szakasz mentén keressük. Az o-ból nézve az irányonként legközelebbi pontok szögrendezésével kapott szomszédos (a, b) pár (o, a, b) üres háromszöget ad; ha ez tartalmazza q-t, kész. Különben q-t a (a, b) él metszi az oq szakaszt, és az élen túli, q oldalán lévő pontok közül a (u, v) élt legkisebb beírt szögből látó z pontot választjuk: az (u, v, z) háromszög üres, mert benne lévő pont nagyobb szögből látná az élt. Ha q benne van, kész; különben az oq szakaszt metsző új élen folytatjuk. Ha nincs pont q oldalán, vagy q nincs a burkon, a válasz 0 0 0.
Idő: a rendezés O(N log N), minden séta-lépés O(N); a lépések száma a valós tesztekre kicsi.
*/
/*
Hint 1: || Válaszd o-nak a q-hoz legközelebbi pontot: így az oq szakasz belsejében nincs P-pont, és a q-t tartalmazó háromszöget az oq szakasz mentén kereshetjük. ||
Hint 2: || Az o-ból nézve az irányonként legközelebbi pontok szögrendben adnak üres (o, a, b) háromszögeket; ha q nincs bennük, az (a, b) él átmetszi az oq szakaszt. ||
Hint 3: || Az élen túli, q oldalán lévő pontok közül keresd azt a z pontot, amelyre az (u, v) él látószöge ∠uzv a legkisebb; az (u, v, z) háromszög üres, és az oq szakaszt metsző új élen folytasd. ||
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Pt {
    ll x, y;
};

struct Dir {
    ll x, y;  // vektor o-ból
    int id;   // a pont sorszáma (1-től)
    ll d2;    // négyzetes távolság o-tól
};

static ll cross(ll ax, ll ay, ll bx, ll by) {
    return ax * by - ay * bx;
}

static int sgn(ll v) {
    return (v > 0) - (v < 0);
}

static int halfOf(ll x, ll y) {
    return (y > 0 || (y == 0 && x > 0)) ? 0 : 1;
}

// Irányok szerinti rendezés (körüljárás szerint, az (1,0) iránytól).
static bool angLess(const Dir& a, const Dir& b) {
    int ha = halfOf(a.x, a.y), hb = halfOf(b.x, b.y);
    if (ha != hb) return ha < hb;
    ll c = cross(a.x, a.y, b.x, b.y);
    if (c != 0) return c > 0;
    return a.d2 < b.d2;
}

static ll dist2(ll ax, ll ay, ll bx, ll by) {
    return (ax - bx) * (ax - bx) + (ay - by) * (ay - by);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    ll qx, qy;
    cin >> qx >> qy;
    vector<Pt> p(n + 1);
    for (int i = 1; i <= n; ++i) cin >> p[i].x >> p[i].y;

    // o: a q-hoz legközelebbi pont. Az oq szakasz belsejében nincs P-pont, ezért
    // a bejárás sosem megy át csúcson.
    int o = 1;
    for (int i = 2; i <= n; ++i) {
        if (dist2(p[i].x, p[i].y, qx, qy) < dist2(p[o].x, p[o].y, qx, qy)) o = i;
    }
    const ll ox = p[o].x, oy = p[o].y;
    const ll Qx = qx - ox, Qy = qy - oy;  // q az o-ból nézve

    // Irányonként a legközelebbi pont, körüljárási sorrendben.
    vector<Dir> dirs;
    dirs.reserve(n);
    for (int i = 1; i <= n; ++i) {
        if (i == o) continue;
        ll dx = p[i].x - ox, dy = p[i].y - oy;
        dirs.push_back({dx, dy, i, dx * dx + dy * dy});
    }
    sort(dirs.begin(), dirs.end(), angLess);
    vector<Dir> C;
    C.reserve(dirs.size());
    for (const auto& d : dirs) {
        if (!C.empty()) {
            const Dir& t = C.back();
            if (halfOf(t.x, t.y) == halfOf(d.x, d.y) && cross(t.x, t.y, d.x, d.y) == 0) continue;
        }
        C.push_back(d);
    }
    const int m = (int)C.size();
    if (m < 2) {
        cout << "0 0 0\n";
        return 0;
    }

    // 1) Ha a q-n át húzott sugárban van pont c: q az (o, c) élen van, és a
    //    (o, c, szomszéd) háromszög üres (szomszédos irányok).
    for (int k = 0; k < m; ++k) {
        if (halfOf(C[k].x, C[k].y) == halfOf(Qx, Qy) && cross(C[k].x, C[k].y, Qx, Qy) == 0) {
            const Dir& c = C[k];
            const Dir& nx = C[(k + 1) % m];
            const Dir& pv = C[(k - 1 + m) % m];
            if (cross(c.x, c.y, nx.x, nx.y) > 0) {
                cout << o << ' ' << c.id << ' ' << nx.id << '\n';
            } else if (cross(pv.x, pv.y, c.x, c.y) > 0) {
                cout << o << ' ' << pv.id << ' ' << c.id << '\n';
            } else {
                cout << "0 0 0\n";
            }
            return 0;
        }
    }

    // 2) A q irányát közrefogó szomszédos (A, B) pár (körüljárási sorrendben).
    Dir qd{Qx, Qy, 0, Qx * Qx + Qy * Qy};
    int j = (int)(partition_point(C.begin(), C.end(), [&](const Dir& d) { return !angLess(qd, d); }) - C.begin());
    const Dir A = C[(j == 0) ? m - 1 : j - 1];
    const Dir B = C[j % m];
    // q az (A, B) irányok között, kisebb mint π szögben: különben q nincs a burkon.
    if (!(cross(A.x, A.y, B.x, B.y) > 0 && cross(A.x, A.y, Qx, Qy) > 0 && cross(Qx, Qy, B.x, B.y) > 0)) {
        cout << "0 0 0\n";
        return 0;
    }

    // (o, A, B) zárt háromszög (o-ból CCW, mert cross(A,B) > 0): tartalmazza-e q-t?
    // Feltétel: q a három él belső (vagy határ) oldalán van.
    {
        bool in1 = cross(A.x, A.y, Qx, Qy) >= 0;              // o–A él
        bool in2 = cross(Qx, Qy, B.x, B.y) >= 0;              // B–o él
        bool in3 = cross(B.x - A.x, B.y - A.y, Qx - A.x, Qy - A.y) >= 0;  // A–B él
        if (in1 && in2 && in3) {
            cout << o << ' ' << A.id << ' ' << B.id << '\n';
            return 0;
        }
    }

    // 3) Séta az oq szakasz mentén. Az aktuális (u, v) él q-t nem tartalmazó háromszög
    //    oldalán lévő, a (u,v) élt legkisebb beírt szögből látó z pontot vesszük: az
    //    (u, v, z) háromszög üres (körlapja is üres). Ha q benne van, kész; különben
    //    a háromszög azon oldalán lépünk tovább, amelyet az oq szakasz metsz.
    int u = A.id, v = B.id;
    while (true) {
        const ll ux = p[u].x, uy = p[u].y, vx = p[v].x, vy = p[v].y;
        const ll ex = vx - ux, ey = vy - uy;
        const int sq = sgn(cross(ex, ey, qx - ux, qy - uy));  // q oldala az (u,v) egyeneshez képest (≠ 0)
        int z = -1;
        ll bestDot = 0, bestCr = 1;  // a legjobb z: cot(∠uzv) = bestDot / bestCr maximális
        for (int i = 1; i <= n; ++i) {
            if (i == u || i == v) continue;
            if (sgn(cross(ex, ey, p[i].x - ux, p[i].y - uy)) != sq) continue;  // csak q oldalán lévő pontok
            // ∠uzv minimális <=> cot(∠uzv) maximális (ugyanazon a félsíkon)
            ll Ux = ux - p[i].x, Uy = uy - p[i].y;
            ll Vx = vx - p[i].x, Vy = vy - p[i].y;
            ll dot = Ux * Vx + Uy * Vy;
            ll cr = llabs(Ux * Vy - Uy * Vx);  // > 0, mert i nincs az uv egyenesen
            if (z == -1 || (__int128)dot * bestCr > (__int128)bestDot * cr) {
                z = i;
                bestDot = dot;
                bestCr = cr;
            }
        }
        if (z == -1) {
            // nincs pont q oldalán: q kívül esik a konvex burkon
            cout << "0 0 0\n";
            return 0;
        }

        // Tartalmazza-e a (u, v, z) zárt háromszög q-t?
        const int o1 = sq;
        const int o2 = sgn(cross(p[z].x - vx, p[z].y - vy, qx - vx, qy - vy));
        const int o3 = sgn(cross(ux - p[z].x, uy - p[z].y, qx - p[z].x, qy - p[z].y));
        const bool hasPos = (o1 > 0) || (o2 > 0) || (o3 > 0);
        const bool hasNeg = (o1 < 0) || (o2 < 0) || (o3 < 0);
        if (!(hasPos && hasNeg)) {
            if (sq > 0) cout << u << ' ' << v << ' ' << z << '\n';
            else cout << u << ' ' << z << ' ' << v << '\n';
            return 0;
        }

        // Az oq egyenes (L) két oldalán lévő csúcsok: az új belépő él a metsző él.
        const int sU = sgn(cross(Qx, Qy, p[u].x - ox, p[u].y - oy));
        const int sZ = sgn(cross(Qx, Qy, p[z].x - ox, p[z].y - oy));
        if (sZ == sU) {
            u = v;
            v = z;
        } else {
            v = z;
        }
    }
    return 0;
}
