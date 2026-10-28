/*
Megoldás lényege:
Az A pontból legyezőt (szög szerint rendezett bejárást) építünk. Ha egy pontból indulva a többit az irányuk szerint rendezve járjuk végig, akkor az egymás utáni pontokat összekötő szakaszok külön szögszeletekbe esnek, ezért nem metszhetik egymást (feltéve, hogy két szomszédos pont iránya között 180 foknál kisebb a szög). Az A-n és egy másik E ponton átmenő egyenest úgy választjuk, hogy a B pont az egyik oldalára essen. Az egyenes másik oldalán levő összes pontot egyetlen A körüli legyezővel bejárjuk E-ig, majd E-ből ugyanezt folytatjuk a megmaradt, egy félsíkba eső pontokkal. Mivel a már bejárt és a hátralévő pontokat egyenes választja el, az útvonal nem metszi önmagát. Minden körben a nagyobb oldalt fogyasztjuk el, ezért O(log N) kör és összesen O(N log N) idő kell. Az azonos irányban álló pontokat távolság szerint járjuk be, a B irányában állók közül B kerül utoljára. Ha az AB egyenesen is sok pont van (A előtt, A és B között, B után), az első jelölt zsákutcába vezethet, ezért kevesebb pontot fogyasztó jelölteket is kipróbálunk visszalépéssel, szükség esetén a keresést B-ből A felé is megismételjük. A feladat bármely helyes kimenetet elfogad, a program egyet ad.
*/
/*
Hint 1: || Ha egy pontból indulva a többit az irányuk szerint rendezve látogatod, a szakaszok külön szögszeletekbe esnek, és nem metszik egymást, amíg a bejárt irányok 180 foknál kisebb tartományt fognak át. Az azonos irányban levő pontokat távolság szerint kell sorra venni. ||
Hint 2: || Válassz egy E pontot: az A-n és E-n átmenő egyenes két oldalra osztja a többi pontot úgy, hogy B az egyik oldalon van. A másik oldal pontjait járd be egy A körüli legyezővel E-ben végződve, majd E-ből oldd meg ugyanezt a megmaradt pontokkal. A két rész között az egyenes miatt nincs metszés. ||
Hint 3: || E legyen valamelyik oldal B irányához szögben legközelebbi csoportjának legtávolabbi pontja, és mindig a nagyobb oldalt fogyaszd el, így O(log N) kör lesz. Ha az AB egyenesen sok pont van, ne fogyaszd el az összes egyenesen kívüli pontot: legalább egy ilyen pontnak maradnia kell, különben a B két oldalán álló egyenesbeli pontok már nem járhatók be. Ilyenkor próbálj kisebb szeletet leválasztani. ||
Hint 4: || Ha a megmaradt pontokat az A körüli teljes körüljárás úgy járja be, hogy B kerül utoljára, akkor ezzel fejezd be az útvonalat: a B irányában álló közelebbi pontok az elejére, a távolabbiak a végére (visszafelé) kerülnek, a többi csoport szög szerint a kettő közé. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
vector<ll> X, Y;
int T;                    // az útvonal célpontja (a keresés iránya szerint A vagy B)
vector<int> path;         // eddig bejárt pontok
ll work, workLimit;       // munkakorlát (mély visszalépés esetén)
int level;                // 0: kevés jelölt, 1: minden irány, 2: minden pont

static ll cr(ll ax, ll ay, ll bx, ll by) { return ax * by - ay * bx; }
static ll dt(ll ax, ll ay, ll bx, ll by) { return ax * bx + ay * by; }

// Az s pontból látott maradék pontok, szög szerint rendezve.
// A 0. csoport a T cél irányában levő (kollineáris) pontok, a többi csoport
// a T irányától az óramutató járásával ellentétesen növekvő szög szerint követi.
struct State {
    int s, k, posT;       // k: a 0. csoporton kívüli csoportok száma
    ll tx, ty;            // s -> T vektor
    vector<int> ord, gs;  // rendezett pontok, csoportkezdetek (gs.size() = k + 2)
    ll vx(int i) const { return X[ord[i]] - X[s]; }
    ll vy(int i) const { return Y[ord[i]] - Y[s]; }
};

// sg = +1: az óramutatóval ellentétes, sg = -1: az óramutatóval megegyező nézet.
static int vg(const State& st, int sg, int i) { return i == 0 ? 0 : (sg > 0 ? i : st.k + 1 - i); }
static ll turn(int sg, ll ax, ll ay, ll bx, ll by) { return sg * cr(ax, ay, bx, by); }

static void build(State& st, int s, const vector<int>& R) {
    st.s = s;
    st.tx = X[T] - X[s];
    st.ty = Y[T] - Y[s];
    struct E { ll x, y; int id, half; };
    vector<E> e(R.size());
    for (size_t i = 0; i < R.size(); i++) {
        e[i].id = R[i];
        e[i].x = X[R[i]] - X[s];
        e[i].y = Y[R[i]] - Y[s];
        ll c = cr(st.tx, st.ty, e[i].x, e[i].y);
        e[i].half = (c > 0 || (c == 0 && dt(st.tx, st.ty, e[i].x, e[i].y) > 0)) ? 0 : 1;
    }
    sort(e.begin(), e.end(), [](const E& a, const E& b) {
        if (a.half != b.half) return a.half < b.half;
        ll c = cr(a.x, a.y, b.x, b.y);
        if (c != 0) return c > 0;
        return a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y;
    });
    st.ord.resize(e.size());
    st.gs.assign(1, 0);
    for (size_t i = 0; i < e.size(); i++) {
        st.ord[i] = e[i].id;
        if (i > 0 && !(e[i - 1].half == e[i].half && cr(e[i - 1].x, e[i - 1].y, e[i].x, e[i].y) == 0))
            st.gs.push_back((int)i);
    }
    st.gs.push_back((int)e.size());
    st.k = (int)st.gs.size() - 2;
    st.posT = 0;
    for (int i = st.gs[0]; i < st.gs[1]; i++) if (st.ord[i] == T) st.posT = i - st.gs[0];
}

// A maradék pontok egyetlen szög szerinti körüljárása s körül: a T körüli
// csoport közeli pontjai az elején, a távoliak a végén (visszafelé) kerülnek sorra,
// így az útvonal T-ben ér véget.
static bool terminal(const State& st) {
    int k = st.k, g0 = st.gs[0], g1 = st.gs[1];
    bool near = st.posT > 0, far = g0 + st.posT + 1 < g1;
    if (k == 0) {
        if (far) return false;
        for (int i = 0; i < st.posT; i++) path.push_back(st.ord[g0 + i]);
        path.push_back(T);
        return true;
    }
    for (int sg = 1; sg >= -1; sg -= 2) {
        bool ok = true;
        for (int i = 1; i < k && ok; i++) {
            int a = st.gs[vg(st, sg, i)], b = st.gs[vg(st, sg, i + 1)];
            ok = turn(sg, st.vx(a), st.vy(a), st.vx(b), st.vy(b)) > 0;
        }
        if (!ok) continue;
        int f = st.gs[vg(st, sg, 1)], l = st.gs[vg(st, sg, k)];
        bool gapStart = turn(sg, st.tx, st.ty, st.vx(f), st.vy(f)) > 0;
        bool gapEnd = turn(sg, st.vx(l), st.vy(l), st.tx, st.ty) > 0;
        auto body = [&]() {
            for (int i = 1; i <= k; i++) {
                int g = vg(st, sg, i);
                for (int j = st.gs[g]; j < st.gs[g + 1]; j++) path.push_back(st.ord[j]);
            }
        };
        auto nearPart = [&]() { for (int i = 0; i < st.posT; i++) path.push_back(st.ord[g0 + i]); };
        auto farPart = [&]() { for (int i = g1 - 1; i > g0 + st.posT; i--) path.push_back(st.ord[i]); };
        if (near && gapStart && gapEnd) { nearPart(); body(); farPart(); path.push_back(T); return true; }
        if (near && !far && gapEnd) { body(); nearPart(); path.push_back(T); return true; }
        if (!near && gapEnd) { body(); farPart(); path.push_back(T); return true; }
    }
    return false;
}

struct Move { int sg, gi, idx, j, cnt; };

// Ellenőrzi a lépést: s-ből egy legyező (fan), amely a gi csoport idx-edik pontjában, E-ben ér véget,
// és az E-n átmenő egyenes egyik oldalán levő pontokat (a nézet szerinti gi+1..j csoportokat) mind bejárja.
static bool evalMove(const State& st, Move& m) {
    int g = vg(st, m.sg, m.gi);
    int e = st.gs[g] + m.idx;
    ll ex = st.vx(e), ey = st.vy(e);
    int j = m.gi;
    while (j + 1 <= st.k) {
        int f = st.gs[vg(st, m.sg, j + 1)];
        ll c = turn(m.sg, ex, ey, st.vx(f), st.vy(f));
        if (c > 0 || (c == 0 && dt(ex, ey, st.vx(f), st.vy(f)) < 0)) j++;
        else break;
    }
    for (int h = j; h > m.gi; h--) {  // két szomszédos csoport szöge kisebb legyen 180 foknál
        int a = st.gs[vg(st, m.sg, h)];
        int b = (h - 1 == m.gi) ? e : st.gs[vg(st, m.sg, h - 1)];
        if (!(turn(m.sg, st.vx(a), st.vy(a), st.vx(b), st.vy(b)) < 0)) return false;
    }
    m.j = j;
    m.cnt = m.idx + 1;
    for (int h = m.gi + 1; h <= j; h++) { int gg = vg(st, m.sg, h); m.cnt += st.gs[gg + 1] - st.gs[gg]; }
    return true;
}

static bool dfs(int s, vector<int>& R);

static bool tryMove(const State& st, const Move& m) {
    int g = vg(st, m.sg, m.gi);
    size_t save = path.size();
    vector<int> rest;
    auto addGroup = [&](vector<int>& to, int gg, int from, int upto) {
        for (int i = st.gs[gg] + from; i < st.gs[gg] + upto; i++) to.push_back(st.ord[i]);
    };
    for (int h = m.j; h > m.gi; h--) { int gg = vg(st, m.sg, h); addGroup(path, gg, 0, st.gs[gg + 1] - st.gs[gg]); }
    addGroup(path, g, 0, m.idx + 1);
    int E = st.ord[st.gs[g] + m.idx];
    if (m.gi != 0) {
        addGroup(rest, 0, 0, st.gs[1] - st.gs[0]);
        for (int h = 1; h < m.gi; h++) { int gg = vg(st, m.sg, h); addGroup(rest, gg, 0, st.gs[gg + 1] - st.gs[gg]); }
    }
    addGroup(rest, g, m.idx + 1, st.gs[g + 1] - st.gs[g]);
    for (int h = m.j + 1; h <= st.k; h++) { int gg = vg(st, m.sg, h); addGroup(rest, gg, 0, st.gs[gg + 1] - st.gs[gg]); }
    if (dfs(E, rest)) return true;
    path.resize(save);
    return false;
}

static bool dfs(int s, vector<int>& R) {
    if (R.size() == 1) { path.push_back(T); return true; }
    work += (ll)R.size();
    if (work > workLimit) return false;
    // ha a maradék pontok egy egyenesen vannak, a megoldhatóság azonnal eldönthető
    {
        ll ux = X[R[1]] - X[R[0]], uy = Y[R[1]] - Y[R[0]];
        bool col = true;
        for (size_t i = 2; i < R.size() && col; i++)
            col = cr(ux, uy, X[R[i]] - X[R[0]], Y[R[i]] - Y[R[0]]) == 0;
        if (col) {
            bool sOn = cr(ux, uy, X[s] - X[R[0]], Y[s] - Y[R[0]]) == 0;
            bool before = false, after = false;  // van-e T előtt / után pont az egyenesen
            for (int r : R) {
                if (r == T) continue;
                ll d = dt(ux, uy, X[r] - X[T], Y[r] - Y[T]);
                if (d < 0) before = true;
                if (d > 0) after = true;
            }
            if (before && after) return false;  // T nem szélső
            if (sOn) {
                ll tx = X[T] - X[s], ty = Y[T] - Y[s];
                for (int r : R)
                    if (dt(tx, ty, X[r] - X[s], Y[r] - Y[s]) < 0) return false;  // s két oldalán is van pont
            }
        }
    }
    State st;
    build(st, s, R);
    size_t save = path.size();
    if (terminal(st)) return true;
    path.resize(save);
    if (st.k == 0) return false;

    // jelöltek: mindkét nézetben a T-hez közeli, szélső és közbülső csoportok, valamint T közeli pontjai
    vector<Move> cands;
    for (int sg = 1; sg >= -1; sg -= 2) {
        int kc = 0;  // az 1..kc nézeti csoportok T-től 180 foknál kisebb szögre vannak
        while (kc + 1 <= st.k) {
            int f = st.gs[vg(st, sg, kc + 1)];
            if (turn(sg, st.tx, st.ty, st.vx(f), st.vy(f)) > 0) kc++; else break;
        }
        vector<int> picks;
        if (level >= 1 || kc <= 6) { for (int g = 1; g <= kc; g++) picks.push_back(g); }
        else for (int q = 0; q <= 4; q++) picks.push_back(1 + (kc - 1) * q / 4);
        picks.erase(unique(picks.begin(), picks.end()), picks.end());
        for (int g : picks) {
            int sz = st.gs[vg(st, sg, g) + 1] - st.gs[vg(st, sg, g)];
            if (level >= 2) { for (int i = 0; i < sz; i++) cands.push_back({sg, g, i, 0, 0}); }
            else cands.push_back({sg, g, sz - 1, 0, 0});
        }
        if (st.posT > 0) {
            if (level >= 2) { for (int i = 0; i < st.posT; i++) cands.push_back({sg, 0, i, 0, 0}); }
            else cands.push_back({sg, 0, st.posT - 1, 0, 0});
        }
    }
    vector<Move> good;
    for (Move& m : cands) if (evalMove(st, m)) good.push_back(m);
    stable_sort(good.begin(), good.end(), [](const Move& a, const Move& b) { return a.cnt > b.cnt; });
    for (const Move& m : good) {
        if (tryMove(st, m)) return true;
        if (work > workLimit) return false;
    }
    return false;
}

// Útvonalat keres a-ból b-be (a visszafelé keresés a b-ből a-ba megy).
static bool findPath(int a, int b, vector<int>& out) {
    for (level = 0; level <= 2; level++) {
        for (int dir = 0; dir < 2; dir++) {
            int s = dir == 0 ? a : b;
            T = dir == 0 ? b : a;
            work = 0;
            workLimit = level == 0 ? 2500000 : 1000000;
            path.assign(1, s);
            vector<int> R;
            for (int i = 0; i < N; i++) if (i != s) R.push_back(i);
            if (dfs(s, R)) {
                out = path;
                if (dir == 1) reverse(out.begin(), out.end());
                return true;
            }
        }
    }
    return false;
}

int main() {
    int a, b;
    if (scanf("%d %d %d", &N, &a, &b) != 3) return 0;
    a--; b--;
    X.resize(N); Y.resize(N);
    for (int i = 0; i < N; i++) if (scanf("%lld %lld", &X[i], &Y[i]) != 2) return 0;
    vector<int> out;
    if (!findPath(a, b, out)) {
        out.assign(1, a);
        for (int i = 0; i < N; i++) if (i != a && i != b) out.push_back(i);
        out.push_back(b);
    }
    for (size_t i = 0; i < out.size(); i++) printf("%d%c", out[i] + 1, i + 1 == out.size() ? '\n' : ' ');
    return 0;
}
