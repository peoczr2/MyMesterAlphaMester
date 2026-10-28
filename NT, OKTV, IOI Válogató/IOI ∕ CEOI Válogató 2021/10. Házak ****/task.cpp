/*
Megoldás lényege:
A origóból nézve egy ház csak a két "elülső" oldalán lehet látható: a bal oldali élén (x = x1)
és az alsó élén (y = y1), hiszen a többi oldal mögött van. Így a feladat 2N, egymást nem metsző
szakasz láthatóságáról szól. Szögszerint (a nézőpontból húzott félegyenesek szerint) sweepelünk:
a szakaszok kezdő- és végpontjainál eseményeket generálunk, és egy rendezett halmazban
tartjuk az aktuális félegyenest metsző szakaszokat a távolságuk szerint (a szakaszok nem
metszik egymást, így a sorrend a szögtartomány alatt nem változik). Minden szögnél a halmaz
első eleme az adott félegyenes legközelebbi ütköző pontjához tartozó szakasz, így a ház
látszik. A szögek pontos kezeléséhez egész számokat használunk (a távolság-összehasonlítás
törtjeit 128 bites szorzással hasonlítjuk össze), a pontos szögegyezéseket külön kezeljük.
Időigény O(N log N).
*/
/*
Hint 1: || A origóból nézve egy téglalap csak a bal oldali élén és az alsó élén keresztül lehet elöl: a másik két oldal mindig a belső pont után van. Így minden házból két szakasz marad. ||
Hint 2: || Szögszerint haladj végig az eseményeken (a szakaszok kezdő- és végpontjainak irányai), és tarts nyilván egy rendezett halmazt az éppen metszett szakaszokról, a origótól mért távolságuk szerint. ||
Hint 3: || A halmaz összehasonlításához nem kell lebegőpontos szög: egy adott irányvektor D és egy szakasz esetén a metszéspont paramétere cross(A, E) / cross(D, E), ahol A a szakasz kezdőpontja, E az iránya; a törteket szorzással hasonlítsd össze. A minden szögnél a halmaz első eleme a legközelebbi ház. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 lll;

struct Pt {
    ll x, y;
};

static ll crossp(const Pt &a, const Pt &b) { return a.x * b.y - a.y * b.x; }

static vector<Pt> LO, HI;  // a szakasz szögben kisebb, illetve nagyobb végpontja
static vector<int> HOUSE;  // szakasz -> ház sorszáma (0-tól)
static Pt curD;            // az éppen feldolgozott irány

// lambda(s) = cross(LO, E) / cross(D, E), E = HI - LO: a metszéspont a D-irányú félegyenesen
static void lambdaOf(int s, ll &num, ll &den) {
    Pt E{HI[s].x - LO[s].x, HI[s].y - LO[s].y};
    num = crossp(LO[s], E);
    den = crossp(curD, E);
    if (den < 0) {
        num = -num;
        den = -den;
    }
}

struct Cmp {
    bool operator()(int a, int b) const {
        ll na, da, nb, db;
        lambdaOf(a, na, da);
        lambdaOf(b, nb, db);
        lll L = (lll)na * db;
        lll R = (lll)nb * da;
        if (L != R) return L < R;  // kisebb lambda = közelebbi pont
        return a < b;              // ugyanabban a sarokpontban találkozó két szakasz (ugyanaz a ház)
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    LO.resize(2 * N);
    HI.resize(2 * N);
    HOUSE.resize(2 * N);
    for (int h = 0; h < N; h++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        // alsó él: (x1,y1)-(x2,y1); a (x2,y1) pont szögben kisebb
        LO[2 * h] = {x2, y1};
        HI[2 * h] = {x1, y1};
        HOUSE[2 * h] = h;
        // bal él: (x1,y1)-(x1,y2); a (x1,y1) pont szögben kisebb
        LO[2 * h + 1] = {x1, y1};
        HI[2 * h + 1] = {x1, y2};
        HOUSE[2 * h + 1] = h;
    }

    struct Ev {
        Pt dir;
        int type;  // 0: kezdés, 1: vég
        int seg;
    };
    vector<Ev> ev;
    ev.reserve(4 * N);
    for (int s = 0; s < 2 * N; s++) {
        ev.push_back({LO[s], 0, s});
        ev.push_back({HI[s], 1, s});
    }
    // szög szerinti rendezés: a és b előtt van, ha cross(a,b) > 0 (mindkettő az első síknegyedben van)
    sort(ev.begin(), ev.end(), [](const Ev &a, const Ev &b) { return crossp(a.dir, b.dir) > 0; });

    set<int, Cmp> active;
    vector<set<int, Cmp>::iterator> itOf(2 * N);
    vector<char> visible(N, 0);

    size_t i = 0;
    while (i < ev.size()) {
        size_t j = i;
        while (j < ev.size() && crossp(ev[i].dir, ev[j].dir) == 0) j++;
        curD = ev[i].dir;
        for (size_t k = i; k < j; k++) {
            if (ev[k].type == 0) itOf[ev[k].seg] = active.insert(ev[k].seg).first;
        }
        if (!active.empty()) visible[HOUSE[*active.begin()]] = 1;
        for (size_t k = i; k < j; k++) {
            if (ev[k].type == 1) active.erase(itOf[ev[k].seg]);
        }
        if (!active.empty()) visible[HOUSE[*active.begin()]] = 1;
        i = j;
    }

    vector<int> res;
    for (int h = 0; h < N; h++)
        if (visible[h]) res.push_back(h + 1);
    cout << res.size() << '\n';
    for (size_t k = 0; k < res.size(); k++) {
        if (k) cout << ' ';
        cout << res[k];
    }
    cout << '\n';
    return 0;
}
