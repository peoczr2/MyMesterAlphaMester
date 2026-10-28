/*
Megoldás lényege:
A 2N város közül minden útszakasz két végpontot ad, és a meglévő utak egymást nem metszik. Először a koordinátákat
ferdítjük: x' = K·x + y (K = 2·10^7 + 1), így minden városnak különböző x' koordinátája lesz, és nincs függőleges szakasz.
Ez affin transzformáció, ezért a metszési viszonyok megmaradnak. Balról jobbra, x' szerint söpörünk egy függőleges
egyenessel. Az egyenes által metszett szakaszokat y szerint rendezett halmazban tartjuk, így két szomszédos szakasz
között egy cella van. Amikor egy város a cellát lezárja (bal oldali határa az a város, amely a cellát nyitotta),
az összekötő szakasz a cellán belül fut, ezért nem metsz semmit. Minden cella legfeljebb egy ilyen élt ad.
Végül a kapott éleken DSU-val (Kruskal-szerűen) kiválasztunk N−1 élt, amely összeköti az összes utat.
Az időigény O(N log N).
*/
/*
Hint 1: || Ferdítsd a koordinátákat: x' = K·x + y, ahol K nagyobb, mint a y-különbségek maximuma (2·10^7). Így minden város x' szerint egyedi, és balról jobbra haladva egyszerűen tudsz söpörni. ||
Hint 2: || Söprés közben tartsd az éppen metszett szakaszokat y szerinti rendezett halmazban (set, egyedi összehasonlító függvénnyel). Két szomszédos szakasz között egy cella van: jegyezd meg minden cellához az utolsó olyan várost, amely a bal határát adja. ||
Hint 3: || Amikor egy város új szakaszt nyit, vagy egy szakasz végpontja zárja a cellákat, a cella bal határának városa és az aktuális város új útszakaszt adhat. Ezeket az éleket gyűjtsd össze, majd DSU-val válassz N−1 olyan élt, amely már különböző komponenseket köt össze. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 i128;

struct Pt {
    ll x, y;   // x: ferdített koordináta (x' = K·x + y), y: eredeti y
};

static vector<Pt> Lp, Rp;     // szakasz bal és jobb végpontja (x' szerint)
static Pt curP;               // a söprő aktuális eseményének pontja
static int npt;               // a "pont" kulcs azonosítója (= N)

static i128 orient(const Pt &a, const Pt &b, const Pt &c) {
    return (i128)(b.x - a.x) * (c.y - a.y) - (i128)(b.y - a.y) * (c.x - a.x);
}

// s "alatta" van t-nek a söprő pillanatában?
struct Cmp {
    bool operator()(int s, int t) const {
        if (s == t) return false;
        Pt sl = (s == npt) ? curP : Lp[s];
        Pt tl = (t == npt) ? curP : Lp[t];
        if (sl.x > tl.x) return orient(Lp[t], Rp[t], sl) < 0;
        return orient(Lp[s], Rp[s], tl) > 0;
    }
};

static vector<int> par;
static int findp(int a) {
    while (par[a] != a) {
        par[a] = par[par[a]];
        a = par[a];
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const ll K = 20000001LL;

    int n;
    cin >> n;
    npt = n;
    int m = 2 * n;                 // városok száma; a c. város a c/2. szakasz végpontja
    vector<ll> CX(m), CY(m), SX(m);
    for (int i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        CX[2 * i] = x1; CY[2 * i] = y1;
        CX[2 * i + 1] = x2; CY[2 * i + 1] = y2;
    }
    for (int c = 0; c < m; c++) SX[c] = K * CX[c] + CY[c];

    vector<int> Lc(n), Rc(n);
    Lp.resize(n); Rp.resize(n);
    for (int i = 0; i < n; i++) {
        int a = 2 * i, b = 2 * i + 1;
        if (SX[a] > SX[b]) swap(a, b);
        Lc[i] = a; Rc[i] = b;
        Lp[i] = Pt{SX[a], CY[a]};
        Rp[i] = Pt{SX[b], CY[b]};
    }

    vector<int> ev(m);
    iota(ev.begin(), ev.end(), 0);
    sort(ev.begin(), ev.end(), [&](int a, int b) { return SX[a] < SX[b]; });

    set<int, Cmp> act;
    vector<set<int, Cmp>::iterator> itOf(n);
    // gapOrig[0]: az legalsó cella; gapOrig[s+1]: az s szakasz feletti cella.
    // Az érték az a város, amely a cella bal határát adja (-1: nincs, keret).
    vector<int> gapOrig(n + 1, -1);
    vector<pair<int, int>> cand;

    for (int c : ev) {
        int s = c / 2;
        curP = Pt{SX[c], CY[c]};
        if (c == Lc[s]) {
            // bal végpont: új szakasz nyílik, a c-t tartalmazó cella két részre esik
            auto it = act.lower_bound(npt);
            int gidB = (it == act.begin()) ? 0 : (*prev(it) + 1);
            int o = gapOrig[gidB];
            if (o >= 0) cand.push_back({o, c});
            auto ins = act.insert(s).first;
            itOf[s] = ins;
            gapOrig[gidB] = c;
            gapOrig[s + 1] = c;
        } else {
            // jobb végpont: a szakasz két szomszédos cellája lezárul, és egy új cella nyílik
            auto it = itOf[s];
            int gidB = (it == act.begin()) ? 0 : (*prev(it) + 1);
            int o1 = gapOrig[gidB];
            int o2 = gapOrig[s + 1];
            if (o1 >= 0) cand.push_back({o1, c});
            if (o2 >= 0) cand.push_back({o2, c});
            act.erase(it);
            gapOrig[gidB] = c;
        }
    }

    par.resize(n);
    iota(par.begin(), par.end(), 0);
    string out;
    for (auto &pr : cand) {
        int a = pr.first / 2, b = pr.second / 2;
        int ra = findp(a), rb = findp(b);
        if (ra == rb) continue;
        par[ra] = rb;
        out += to_string(CX[pr.first]) + " " + to_string(CY[pr.first]) + " " +
               to_string(CX[pr.second]) + " " + to_string(CY[pr.second]) + "\n";
    }
    cout << out;
    return 0;
}
