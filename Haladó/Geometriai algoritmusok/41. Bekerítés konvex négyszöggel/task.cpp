/*
Megoldás lényege:
Először egy olyan üres háromszöget keresünk, amelynek szigorúan a belsejében van a T célpont: a pontokat háromszögeljük
(x,y) szerinti söpréssel, és megkeressük a T-t tartalmazó háromszöget. Elég a T-hez legközelebbi 256 pontot venni: ezek
háromszögei a körlapjukon belül maradnak, ezért az összes pontra nézve is üresek; ha ebből nem dönthető el, az összeset használjuk.
Ha T szigorúan a Δ=(a,b,c) háromszög belsejében van, akkor akkor és csak akkor van megoldás, ha valamelyik oldal túloldalán,
a másik két oldal egyenesei között (az „éltartományban”) van pont: ilyenből az oldalhoz legközelebbi x pont az (a,x,b,c)
négyszöget adja, amely szigorúan konvex és üres. Ha egyik tartományban sincs pont, akkor a három csúcs minden jó
négyszögbe belekerülne, ezért nincs megoldás. Ha T egy háromszögelési él (a,c) belső pontja, akkor olyan bal és jobb oldali
pontpár kell, amelynek összekötő szakasza átmetszi az (a,c) élt; ezt rendezéssel és előtag-minimummal döntjük el, majd
mindkét oldalon a legközelebbi megfelelő pontot választjuk. Ha T egybeesik egy ponttal, vagy kívül van a burkon vagy
annak élén, a válasz 0 0 0 0. Idő: O(N log N), több megoldás is lehet.
*/
/*
Hint 1: || Keress a pontokból egy üres háromszöget, amelynek szigorúan a belsejében van a bekerítendő pont: háromszögeld a pontokat, és keresd meg a célpontot tartalmazó háromszöget. ||
Hint 2: || A háromszög három oldalegyenese hét részre osztja a síkot. Egy x pont akkor ad (a,x,b,c) szigorúan konvex négyszöget, ha az (a,b) oldal túloldalán van, a másik két oldal egyenesei között. Ha van ilyen pont, az (a,b)-hez legközelebbi jó, mert a keletkező négyszög üres marad; ha egyik oldalnál sincs ilyen pont, akkor nincs megoldás. ||
Hint 3: || Ha a célpont a háromszögelés egy élének belső pontja, akkor az él két végpontja a négyszög egyik átlója: keress bal és jobb oldali pontot, amelyek összekötő szakasza az élt a belsejében metszi (a feltétel törtekkel írható fel, a törteket rendezd és használj előtag-minimumot), majd mindkét oldalon válaszd a legközelebbi megfelelő pontot. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;

static char buf[1 << 16];
static int bufLen = 0, bufPos = 0;

static inline int readChar() {
    if (bufPos == bufLen) {
        bufLen = (int)fread(buf, 1, sizeof(buf), stdin);
        bufPos = 0;
        if (bufLen <= 0) return -1;
    }
    return buf[bufPos++];
}

static bool readInt(ll& v) {
    int c = readChar();
    while (c != -1 && c != '-' && (c < '0' || c > '9')) c = readChar();
    if (c == -1) return false;
    int sign = 1;
    if (c == '-') { sign = -1; c = readChar(); }
    ll r = 0;
    while (c >= '0' && c <= '9') { r = r * 10 + (c - '0'); c = readChar(); }
    v = r * sign;
    return true;
}

static vector<ll> X, Y;   // az összes pont (eredeti sorrendben)
static ll TX, TY;         // a bekerítendő pont
static int n;
static vector<int> ord;   // a vizsgált pontok (eredeti indexek), (x,y) szerint rendezve
static int ans[4];

static inline ll orient(int a, int b, int c) {
    return (X[b] - X[a]) * (Y[c] - Y[a]) - (Y[b] - Y[a]) * (X[c] - X[a]);
}
static inline ll orientT(int a, int b) {
    return (X[b] - X[a]) * (TY - Y[a]) - (Y[b] - Y[a]) * (TX - X[a]);
}
static inline int sgn(ll v) { return (v > 0) - (v < 0); }

// A négy pont óramutatóval ellentétes körüljárását a legkisebb (x,y) csúcsból kezdve az ans-ba írja.
static void setAnswer(int q0, int q1, int q2, int q3) {
    int q[4] = {q0, q1, q2, q3};
    if (orient(q[0], q[1], q[2]) < 0) swap(q[1], q[3]);
    int s = 0;
    for (int i = 1; i < 4; ++i)
        if (X[q[i]] < X[q[s]] || (X[q[i]] == X[q[s]] && Y[q[i]] < Y[q[s]])) s = i;
    for (int i = 0; i < 4; ++i) ans[i] = q[(s + i) % 4] + 1;
}

// Az (a,b,c) háromszögben van-e T? 2: szigorúan belül; 1: az (e1,e2) élén; 0: nincs benne.
static int locate(int a, int b, int c, int& e1, int& e2) {
    int s = sgn(orient(a, b, c));
    int o1 = s * sgn(orientT(a, b)), o2 = s * sgn(orientT(b, c)), o3 = s * sgn(orientT(c, a));
    if (o1 < 0 || o2 < 0 || o3 < 0) return 0;
    if (o1 > 0 && o2 > 0 && o3 > 0) return 2;
    if (o1 == 0) { e1 = a; e2 = b; }
    else if (o2 == 0) { e1 = b; e2 = c; }
    else { e1 = c; e2 = a; }
    return 1;
}

// (a,b,c) pozitív körüljárású üres háromszög, T szigorúan belül van.
static bool enclosedByTriangle(int a, int b, int c) {
    int v[3] = {a, b, c};
    int best[3] = {-1, -1, -1};
    ll bestD[3] = {0, 0, 0};
    for (int z = 0; z < n; ++z) {
        if (z == a || z == b || z == c) continue;
        ll o[3] = {orient(a, b, z), orient(b, c, z), orient(c, a, z)};
        for (int e = 0; e < 3; ++e) {
            // az e. oldal éltartománya: az oldal túloldalán, a másik két oldal belső oldalán
            if (o[e] < 0 && o[(e + 1) % 3] > 0 && o[(e + 2) % 3] > 0)
                if (best[e] < 0 || -o[e] < bestD[e]) { best[e] = z; bestD[e] = -o[e]; }
        }
    }
    for (int e = 0; e < 3; ++e) {
        if (best[e] >= 0) {
            setAnswer(v[e], best[e], v[(e + 1) % 3], v[(e + 2) % 3]);
            return true;
        }
    }
    return false;
}

// Az (p,q) szakasz átmetszi-e az (a,c) szakasz belsejét? (p és q az egyenes két oldalán van)
static bool crossing(int p, int q, int a, int c) {
    ll o1 = orient(p, q, a), o2 = orient(p, q, c);
    return (o1 > 0 && o2 < 0) || (o1 < 0 && o2 > 0);
}

// T az (a,c) üres szakasz belső pontja, mindkét oldalán van háromszög.
static bool enclosedByEdge(int a, int c) {
    ll ex = X[c] - X[a], ey = Y[c] - Y[a];
    ll E = ex * ex + ey * ey;
    // koordináták: x = az (a,c) irányú vetület (a-nál 0, c-nél E), h = a egyenestől mért (előjeles) távolság
    struct P { ll x, h; int id; };
    vector<P> left, right;
    for (int z = 0; z < n; ++z) {
        if (z == a || z == c) continue;
        ll h = ex * (Y[z] - Y[a]) - ey * (X[z] - X[a]);
        ll x = ex * (X[z] - X[a]) + ey * (Y[z] - Y[a]);
        if (h > 0) left.push_back({x, h, z});
        else if (h < 0) right.push_back({x, -h, z});
    }
    if (left.empty() || right.empty()) return false;
    // Az (p,q) szakasz metszéspontja 0 és E között van <=> x_p/h_p + x_q/d_q > 0 és (x_p-E)/h_p + (x_q-E)/d_q < 0.
    // A bal pontokat x/h szerint csökkenőbe rendezzük, és előtag-minimumot veszünk (x-E)/h-ból.
    sort(left.begin(), left.end(), [](const P& p, const P& q) { return (lll)p.x * q.h > (lll)q.x * p.h; });
    int m = (int)left.size();
    vector<int> pm(m);
    for (int i = 0; i < m; ++i) {
        pm[i] = i;
        if (i > 0) {
            int j = pm[i - 1];
            if ((lll)(left[i].x - E) * left[j].h >= (lll)(left[j].x - E) * left[i].h) pm[i] = j;
        }
    }
    int q0 = -1;
    for (const P& q : right) {
        int lo = 0, hi = m;   // hány bal pontra teljesül az első feltétel
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if ((lll)left[mid].x * q.h + (lll)q.x * left[mid].h > 0) lo = mid + 1; else hi = mid;
        }
        if (lo == 0) continue;
        const P& p = left[pm[lo - 1]];
        if ((lll)(p.x - E) * q.h + (lll)(q.x - E) * p.h < 0) { q0 = q.id; break; }
    }
    if (q0 < 0) return false;
    // legközelebbi megfelelő pontok: üres háromszögeket adnak az (a,c) két oldalán
    int b = -1, d = -1;
    ll bh = 0, dh = 0;
    for (const P& p : left)
        if (crossing(p.id, q0, a, c) && (b < 0 || p.h < bh)) { b = p.id; bh = p.h; }
    for (const P& q : right)
        if (crossing(b, q.id, a, c) && (d < 0 || q.h < dh)) { d = q.id; dh = q.h; }
    setAnswer(a, d, c, b);
    return true;
}

// Háromszögelés (x,y) szerinti söpréssel a kiválasztott pontokra, amíg meg nem találjuk a T-t tartalmazó háromszöget.
// Visszatérés: 0: a kiválasztott pontokból nem dönthető el, 1: nincs megoldás, 2: megoldás az ans-ban.
static int sweep() {
    int m = (int)ord.size();
    if (m < 3) return 0;
    int r = 2;
    while (r < m && orient(ord[0], ord[1], ord[r]) == 0) ++r;
    if (r == m) return 0;     // minden pont egy egyenesen van
    int edgeCount = 0, status = -1;
    auto triangle = [&](int a, int b, int c) {
        if (status >= 0) return;
        int e1 = -1, e2 = -1;
        int t = locate(a, b, c, e1, e2);
        if (t == 2) {
            if (orient(a, b, c) < 0) swap(b, c);
            status = enclosedByTriangle(a, b, c) ? 2 : 1;
        } else if (t == 1) {
            if (++edgeCount == 2) status = enclosedByEdge(e1, e2) ? 2 : 1;   // az él mindkét oldalán van háromszög
        }
    };
    vector<int> U, L;   // felső és alsó burokláncok
    for (int i = 0; i + 1 < r && status < 0; ++i) triangle(ord[i], ord[i + 1], ord[r]);
    if (status >= 0) return status;
    if (orient(ord[0], ord[1], ord[r]) > 0) {
        U = {ord[0], ord[r]};
        for (int i = 0; i <= r; ++i) L.push_back(ord[i]);
    } else {
        L = {ord[0], ord[r]};
        for (int i = 0; i <= r; ++i) U.push_back(ord[i]);
    }
    for (int k = r + 1; k < m && status < 0; ++k) {
        int p = ord[k];
        while (U.size() >= 2 && orient(U[U.size() - 2], U.back(), p) > 0) {
            triangle(U[U.size() - 2], U.back(), p);
            U.pop_back();
        }
        while (L.size() >= 2 && orient(L[L.size() - 2], L.back(), p) < 0) {
            triangle(L[L.size() - 2], L.back(), p);
            L.pop_back();
        }
        U.push_back(p);
        L.push_back(p);
    }
    return status >= 0 ? status : 0;
}

static bool solveSet() {
    if (n < 4) return false;
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    vector<ll> dist(n);
    for (int i = 0; i < n; ++i) dist[i] = (X[i] - TX) * (X[i] - TX) + (Y[i] - TY) * (Y[i] - TY);
    int m = min(n, 256);       // először csak a T-hez legközelebbi pontokkal próbálkozunk
    while (true) {
        if (m < n)
            nth_element(idx.begin(), idx.begin() + m, idx.end(), [&](int a, int b) { return dist[a] < dist[b]; });
        ord.assign(idx.begin(), idx.begin() + m);
        sort(ord.begin(), ord.end(), [&](int a, int b) { return X[a] != X[b] ? X[a] < X[b] : Y[a] < Y[b]; });
        int st = sweep();
        if (st == 2) return true;
        if (st == 1 || m == n) return false;
        m = n;
    }
}

int main() {
    ll K;
    readInt(K);
    string out;
    while (K--) {
        ll nn;
        readInt(nn);
        readInt(TX);
        readInt(TY);
        n = (int)nn;
        X.resize(n);
        Y.resize(n);
        bool onPoint = false;
        for (int i = 0; i < n; ++i) {
            readInt(X[i]);
            readInt(Y[i]);
            if (X[i] == TX && Y[i] == TY) onPoint = true;
        }
        bool ok = !onPoint && solveSet();
        if (ok)
            out += to_string(ans[0]) + " " + to_string(ans[1]) + " " + to_string(ans[2]) + " " + to_string(ans[3]) + "\n";
        else
            out += "0 0 0 0\n";
    }
    fputs(out.c_str(), stdout);
    return 0;
}
