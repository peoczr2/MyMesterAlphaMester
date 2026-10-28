/*
Megoldás lényege:
Ha a ponthalmaz egy háromszögelésében (minden pont csúcs) két szomszédos háromszög szigorúan konvex négyszöget alkot, akkor ez a négyszög üres, mert a háromszögek üresek. Fordítva is igaz: ha egy háromszögelésben egyetlen él sem cserélhető (nincs két háromszög, amely konvex négyszöget ad), akkor a halmaznak más háromszögelése sincs, mert a háromszögelések élcserékkel összefüggő gráfot alkotnak; így üres konvex négyszög sincs, és a válasz 0 0 0 0. A háromszögelést a pontok (x,y) szerinti rendezett sorrendjében építjük: az eddigi pontok burkát két láncban (felső és alsó) tartjuk, minden burokélhez eltároljuk a mögötte lévő háromszög harmadik csúcsát. Az új pont a rajta szigorúan látható élekkel alkot háromszögeket; az él, amely belsővé válik, azonnal vizsgálható: a mögötte lévő harmadik csúcs w és az új pont p mellett a négyszög akkor szigorúan konvex, ha az él két végpontja a wp egyenes két ellentétes oldalán van. A sorrendben később érkező pontok nem eshetnek az eddigi pontokból álló négyszögbe, ezért az első találat jó válasz. A kollineáris pontok a láncokon maradnak, de nem adnak háromszöget. Időigény: O(N log N) a rendezés miatt, a söprés O(N).
*/
/*
Hint 1: || Négy pont akkor alkot üres konvex négyszöget, ha a ponthalmaz egy háromszögelésében van két szomszédos háromszög, amelyek közös élét kicserélve szigorúan konvex négyszöget kapunk (a háromszögek üresek, tehát a négyszög is). Ha egy háromszögelésben nincs ilyen cserélhető él, akkor nincs megoldás. ||
Hint 2: || Háromszögeld a halmazt úgy, hogy a pontokat (x,y) szerint rendezve egyenként veszed hozzá; az eddigi pontok burkát két láncban (felső és alsó) tartod, és minden burokélhez megjegyzed a mögötte lévő háromszög harmadik csúcsát. Az új pont a rajta szigorúan látható burokélekkel alkot háromszögeket. ||
Hint 3: || Amikor egy burokél belsővé válik, legyen w a mögötte lévő harmadik csúcs, p az új pont: a négyszög pontosan akkor szigorúan konvex, ha az él két végpontján a (w,p) egyenesre számolt két keresztszorzat ellentétes előjelű és nem nulla. Az első ilyen élnél készen vagy; ha a végéig nincs, a válasz 0 0 0 0. A kollineáris pontokat a burkon tartsd meg, de ne képezz belőlük háromszöget. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Pt { ll x, y; int id; };
static vector<Pt> S;        // (x,y) szerint rendezett, ismétlődés nélküli pontok
static vector<char> forb;   // az a hely, ahol több pont is van: nem lehet csúcs (a többi pont a csúcson lenne)
static int ans[4];

static inline ll cross(int a, int b, int c) {
    return (S[b].x - S[a].x) * (S[c].y - S[a].y) - (S[b].y - S[a].y) * (S[c].x - S[a].x);
}

// Az (a,b) él két oldalán van w (az él mögött) és p (az új pont). Az a-w-b-p négyszög szigorúan konvex,
// ha a és b a wp egyenes ellentétes oldalán van. Ekkor óramutatóval ellentétesen, a legkisebb csúcsból indulva eltároljuk.
static bool tryQuad(int a, int w, int b, int p) {
    ll o1 = cross(w, p, a), o2 = cross(w, p, b);
    if (!((o1 > 0 && o2 < 0) || (o1 < 0 && o2 > 0))) return false;
    if (forb[a] || forb[w] || forb[b] || forb[p]) return false;
    int q[4] = {a, w, b, p};
    if (cross(a, w, b) < 0) swap(q[1], q[3]);
    int st = min_element(q, q + 4) - q;       // a rendezett sorrendben a legkisebb indexű a legkisebb (x,y)
    for (int i = 0; i < 4; i++) ans[i] = S[q[(st + i) % 4]].id;
    return true;
}

struct Chain {
    vector<int> v, w;   // v: a lánc csúcsai balról jobbra; w[k]: a (v[k-1], v[k]) él mögötti háromszög harmadik csúcsa (-1: nincs)
    int sgn;            // +1: felső lánc (p akkor látja az élt, ha balra van tőle), -1: alsó lánc
    // Lebontja az új p pont által látott éleket; közben minden élre megvizsgálja a cserélhetőséget.
    bool eat(int p, bool &popped, int &firstA, int &lastB) {
        popped = false; firstA = lastB = -1;
        while (v.size() >= 2 && sgn * cross(v[v.size() - 2], v.back(), p) > 0) {
            int a = v[v.size() - 2], b = v.back(), x = w.back();
            if (!popped) { popped = true; firstA = a; }
            if (x >= 0 && tryQuad(a, x, b, p)) return true;
            lastB = b;
            v.pop_back(); w.pop_back();
        }
        return false;
    }
};

static bool sweep() {
    int n = S.size();
    if (n < 4) return false;
    int r = 2;
    while (r < n && cross(0, 1, r) == 0) r++;
    if (r == n) return false;                         // minden pont egy egyenesen van
    // Az első r pont egy egyenesen van, az r. pont ettől balra (felső lánc) vagy jobbra (alsó lánc) van: legyező.
    Chain up, lo;
    up.sgn = 1; lo.sgn = -1;
    bool above = cross(0, 1, r) > 0;
    Chain &direct = above ? up : lo;                  // r oldalán a burokél a (0,r)
    Chain &longer = above ? lo : up;                  // a másik oldalon a kollineáris pontok láncolata
    direct.v = {0, r}; direct.w = {-1, 1};
    for (int i = 0; i < r; i++) { longer.v.push_back(i); longer.w.push_back(i == 0 ? -1 : r); }
    longer.v.push_back(r); longer.w.push_back(r - 2);
    for (int p = r + 1; p < n; p++) {
        bool pu, pl;
        int fu, lu, fl, ls;
        if (up.eat(p, pu, fu, lu)) return true;
        if (lo.eat(p, pl, fl, ls)) return true;
        // az új burokélek mögötti háromszög harmadik csúcsa
        int nu = pu ? lu : (pl ? fl : -1);
        int nl = pl ? ls : (pu ? fu : -1);
        up.v.push_back(p); up.w.push_back(nu);
        lo.v.push_back(p); lo.w.push_back(nl);
    }
    return false;
}

static char buf[1 << 16];
static size_t bl = 0, bp = 0;
static int readChar() {
    if (bp == bl) { bl = fread(buf, 1, sizeof(buf), stdin); bp = 0; if (bl == 0) return -1; }
    return buf[bp++];
}
static bool readInt(ll &v) {
    int c = readChar();
    while (c != -1 && c != '-' && (c < '0' || c > '9')) c = readChar();
    if (c == -1) return false;
    bool neg = c == '-';
    if (neg) c = readChar();
    v = 0;
    for (; c >= '0' && c <= '9'; c = readChar()) v = v * 10 + (c - '0');
    if (neg) v = -v;
    return true;
}

int main() {
    ll n;
    if (!readInt(n)) return 0;
    vector<Pt> a(n);
    for (int i = 0; i < n; i++) { readInt(a[i].x); readInt(a[i].y); a[i].id = i + 1; }
    sort(a.begin(), a.end(), [](const Pt &p, const Pt &q) { return p.x != q.x ? p.x < q.x : p.y < q.y; });
    for (int i = 0; i < n;) {
        int j = i;
        while (j < n && a[j].x == a[i].x && a[j].y == a[i].y) j++;
        S.push_back(a[i]); forb.push_back(j - i > 1);
        i = j;
    }
    if (sweep()) printf("%d %d %d %d\n", ans[0], ans[1], ans[2], ans[3]);
    else printf("0 0 0 0\n");
    return 0;
}
