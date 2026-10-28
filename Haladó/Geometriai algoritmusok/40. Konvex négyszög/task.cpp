/*
Megoldás lényege:
Egy ponthalmaz háromszögelésében (minden pont csúcs, a háromszögek üresek) két szomszédos háromszög uniója akkor adja
az üres konvex négyszöget, ha az egyik átló éle a közös él, és a négyszög szigorúan konvex. Az élcserék összefüggősége miatt
ha egy háromszögelésben nincs ilyen (cserélhető) él, akkor a halmaznak egyáltalán nincs üres konvex négyszöge.
A háromszögelést a pontok (x,y) szerinti rendezett sorrendjében építjük: két veremben (alsó és felső lánc) tartjuk az eddigi
pontok konvex burkát, minden burokélhez eltároljuk a mögötte lévő háromszög harmadik csúcsát. Az új pont a rajta látható
burokélekkel háromszögeket alkot; ekkor az élek belsővé válnak, és O(1) időben eldönthető, hogy az új pont és az
eltárolt harmadik csúcs szakasza az élt a belsejében metszi-e. A háromszögek üresek maradnak, mert minden későbbi pont
az (x,y) sorrendben hátrébb van, ezért nem eshet beléjük; így az első találatnál meg is állhatunk.
Elég a legkisebb pontokat venni (előbb 256 db, ha ez nem elég, akkor mindet). Idő: O(N log N), a söprés O(N).
*/
/*
Hint 1: || Négy pont akkor alkot üres konvex négyszöget, ha két üres háromszög közös él mentén szigorúan konvex négyszöget ad, vagyis a két átló belső pontban metszi egymást. ||
Hint 2: || Háromszögeld a ponthalmazt úgy, hogy (x,y) szerint rendezve veszed a pontokat, és az eddigi pontok konvex burkát két veremben (alsó és felső lánc) tartod; az új pont a rajta látható burokcsúcsokkal alkot háromszögeket. Minden burokélhez jegyezd meg a mögötte lévő háromszög harmadik csúcsát. ||
Hint 3: || Amikor egy burokél belsővé válik, a mögötte lévő harmadik csúcs és az új pont a négyszög két másik csúcsa; szigorúan konvex, ha az él két végpontja ennek a szakasznak az ellentétes oldalán van (két keresztszorzat ellentétes, nem nulla előjelű). A kollineáris pontokat a burkon meg kell tartani, de azokból nem lesz háromszög. Ha egyik él sem cserélhető, a válasz 0 0 0 0. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

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

static vector<ll> X, Y;   // a vizsgált pontok (x,y) szerint rendezve
static vector<int> ID;    // eredeti sorszámuk (1-től)
static int ans[4];

static inline ll orient(int a, int b, int c) {
    return (X[b] - X[a]) * (Y[c] - Y[a]) - (Y[b] - Y[a]) * (X[c] - X[a]);
}

// Az (a,b) él két oldalán a w és p pont van: szigorúan konvex-e az a,w,b,p négyszög?
// Ha igen, az óramutatóval ellentétes körüljárást a legkisebb (x,y) csúcsból kezdve az ans-ba írja.
static bool convexQuad(int a, int w, int b, int p) {
    ll o1 = orient(w, p, a), o2 = orient(w, p, b);
    if (!((o1 > 0 && o2 < 0) || (o1 < 0 && o2 > 0))) return false;
    int q[4] = {a, w, b, p};
    if (orient(a, w, b) < 0) swap(q[1], q[3]);
    int s = 0;
    for (int i = 1; i < 4; ++i)
        if (X[q[i]] < X[q[s]] || (X[q[i]] == X[q[s]] && Y[q[i]] < Y[q[s]])) s = i;
    for (int i = 0; i < 4; ++i) ans[i] = ID[q[(s + i) % 4]];
    return true;
}

// Van-e cserélhető él az n pont háromszögelésében? (a pontok már rendezettek)
static bool solveSet(int n) {
    if (n < 4) return false;
    int r = 2;
    while (r < n && orient(0, 1, r) == 0) ++r;
    if (r == n) return false;             // minden pont egy egyenesen van
    // U, L: felső és alsó lánc balról jobbra; aU[k], aL[k]: a (k-1,k) él mögötti háromszög harmadik csúcsa
    vector<int> U, L, aU, aL;
    if (orient(0, 1, r) > 0) {
        U = {0, r};
        aU = {-1, 1};
        for (int i = 0; i < r; ++i) { L.push_back(i); aL.push_back(i == 0 ? -1 : r); }
        L.push_back(r);
        aL.push_back(r - 2);
    } else {
        L = {0, r};
        aL = {-1, 1};
        for (int i = 0; i < r; ++i) { U.push_back(i); aU.push_back(i == 0 ? -1 : r); }
        U.push_back(r);
        aU.push_back(r - 2);
    }
    for (int p = r + 1; p < n; ++p) {
        bool popU = false, popL = false;
        int firstU = -1, lastU = -1, firstL = -1, lastL = -1;
        while (U.size() >= 2 && orient(U[U.size() - 2], U.back(), p) > 0) {   // p látja az élt
            int a = U[U.size() - 2], b = U.back(), w = aU.back();
            if (!popU) { popU = true; firstU = a; }
            if (w >= 0 && convexQuad(a, w, b, p)) return true;
            lastU = b;
            U.pop_back();
            aU.pop_back();
        }
        while (L.size() >= 2 && orient(L[L.size() - 2], L.back(), p) < 0) {
            int a = L[L.size() - 2], b = L.back(), w = aL.back();
            if (!popL) { popL = true; firstL = a; }
            if (w >= 0 && convexQuad(a, w, b, p)) return true;
            lastL = b;
            L.pop_back();
            aL.pop_back();
        }
        // az új burokélek mögötti háromszög harmadik csúcsa
        int nu = popU ? lastU : (popL ? firstL : -1);
        int nl = popL ? lastL : (popU ? firstU : -1);
        U.push_back(p);
        aU.push_back(nu);
        L.push_back(p);
        aL.push_back(nl);
    }
    return false;
}

int main() {
    const int FIRST = 256;     // először csak ennyi legkisebb pontot nézünk
    ll K;
    readInt(K);
    string out;
    vector<ll> ox, oy;
    vector<ull> key;
    while (K--) {
        ll nn;
        readInt(nn);
        int n = (int)nn;
        ox.resize(n);
        oy.resize(n);
        key.resize(n);
        for (int i = 0; i < n; ++i) {
            readInt(ox[i]);
            readInt(oy[i]);
            key[i] = ((ull)((ox[i] + 1000000) * 2000001 + (oy[i] + 1000000)) << 17) | (ull)i;
        }
        bool ok = false;
        int m = min(n, FIRST);
        while (true) {
            if (m < n) nth_element(key.begin(), key.begin() + m, key.end());
            sort(key.begin(), key.begin() + m);
            X.resize(m);
            Y.resize(m);
            ID.resize(m);
            for (int i = 0; i < m; ++i) {
                int id = (int)(key[i] & ((1u << 17) - 1));
                X[i] = ox[id];
                Y[i] = oy[id];
                ID[i] = id + 1;
            }
            ok = solveSet(m);
            if (ok || m == n) break;
            m = n;
        }
        if (ok)
            out += to_string(ans[0]) + " " + to_string(ans[1]) + " " + to_string(ans[2]) + " " + to_string(ans[3]) + "\n";
        else
            out += "0 0 0 0\n";
    }
    fputs(out.c_str(), stdout);
    return 0;
}
