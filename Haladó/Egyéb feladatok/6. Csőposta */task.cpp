/*
Megoldás lényege:
Eseményvezérelt szimuláció. Minden csomag útja egyenes (állandó sebesség), ezért az ütközések
pontos ideje törtként kiszámítható (számláló és nevező, __int128-cal hasonlítva). Ütközés mindig
két szomszédos csomag között történik, a pályán lévő csomagok sorrendje nem változik, ezért a
csomagokat láncolt listában tartjuk (az A-ból induló csomagok a lista elején, a B-ből induló
csomagok a végén vannak). Ütközéskor kiesik a vesztes: szemből jövő esetén a lassabb (egyforma
sebességnél a korábban induló), azonos irányban az utolérő, gyorsabb csomag; a győztes útja nem
változik. Az ütközésben a sorszámában későbbi csomag számít ütköző csomagnak. Az események
időrendben jönnek: a szomszédos párok ütközési idejét egy indexelt min-kupac tartja nyilván.
A bemeneti időértékeket 32 bites egészként tároljuk (feltételezve, hogy 10^9 alatt vannak).
Idő: O(N log N), memória: csomagonként 24 bájt.
*/
/*
Hint 1: || Minden csomag útja a (idő, hely) síkon egy egyenes szakasz: az A-ból indulóé x = (t - s) / d, a B-ből indulóé x = 1 - (t - s) / d. Ütközés után a vesztes csomag nem vesz többé részt eseményekben, a győztes útja változatlan. ||
Hint 2: || A csomagok sorrendje a pályán nem változik, mert előzni csak ütközéssel lehet. Ezért tarthatod a pályát láncolt listában: az A-ból indulót a lista elejére, a B-ből indulót a végére teszed, és csak szomszédos párokat vizsgálsz. ||
Hint 3: || Az érkezéseket, indulásokat és ütközéseket időrendben dolgozd fel, és az ütközés idejét törtként számold (számláló / nevező), hogy az egyenlőségek pontosak maradjanak. Két ütközési idő összehasonlítása szorzással, __int128 típussal történjen. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 i128;

struct E {            // egy csomag adatai
    int s, d;         // indulási idő, út megtételéhez szükséges idő
    int nx, pv;       // szomszédok a pályán (A felől B felé), -1: nincs
    int pos;          // helye a kupacban, -1: nincs a kupacban
    unsigned char f;  // bit0: A-ból indul, bit1: ütköző csomag (kiírandó)
};
static int N;
static E *P;          // csomagok
static int *H;        // kupac: a bal oldali csomag indexe az ütközési esemény szerint
static int hn = 0;
static int HEAD = -1, TAIL = -1, RB = -1, LF = -1;   // lista eleje/vége, jobbszélső A-ból induló, bal szélső B-ből induló

static inline bool isA(int X) { return P[X].f & 1; }

// Az X és a jobb oldali szomszédja közötti ütközés ideje p/q, ha lesz ilyen.
static inline bool keyOf(int X, ll &p, ll &q) {
    int Y = P[X].nx;
    if (Y < 0) return false;
    const E &x = P[X], &y = P[Y];
    bool ax = x.f & 1, ay = y.f & 1;
    if (ax && ay) {                       // azonos irány (A -> B): X a hátsó, csak ha gyorsabb
        if (!(x.d < y.d)) return false;
        p = (ll)y.d * x.s - (ll)x.d * y.s; q = (ll)y.d - x.d;
    } else if (!ax && !ay) {              // azonos irány (B -> A): Y a hátsó, csak ha gyorsabb
        if (!(y.d < x.d)) return false;
        p = (ll)x.d * y.s - (ll)y.d * x.s; q = (ll)x.d - y.d;
    } else if (ax && !ay) {               // szemből közelednek
        p = (ll)x.d * y.d + (ll)x.s * y.d + (ll)y.s * x.d; q = (ll)x.d + y.d;
    } else return false;                  // távolodnak egymástól
    // csak akkor ütköznek, ha egyikük sem ért még a pálya végére
    if ((i128)p >= (i128)((ll)x.s + x.d) * q || (i128)p >= (i128)((ll)y.s + y.d) * q) return false;
    return true;
}

static inline bool lessAt(int a, int b) {
    ll pa, qa, pb, qb;
    keyOf(a, pa, qa); keyOf(b, pb, qb);
    return (i128)pa * qb < (i128)pb * qa;
}
static void siftUp(int i) {
    int x = H[i];
    while (i > 0) {
        int par = (i - 1) >> 1;
        if (!lessAt(x, H[par])) break;
        H[i] = H[par]; P[H[i]].pos = i; i = par;
    }
    H[i] = x; P[x].pos = i;
}
static void siftDown(int i) {
    int x = H[i];
    while (true) {
        int c = 2 * i + 1;
        if (c >= hn) break;
        if (c + 1 < hn && lessAt(H[c + 1], H[c])) c++;
        if (!lessAt(H[c], x)) break;
        H[i] = H[c]; P[H[i]].pos = i; i = c;
    }
    H[i] = x; P[x].pos = i;
}
static void heapRemove(int X) {
    int i = P[X].pos;
    if (i < 0) return;
    int last = H[--hn]; P[X].pos = -1;
    if (last != X) {
        H[i] = last; P[last].pos = i;
        siftUp(P[last].pos); siftDown(P[last].pos);
    }
}
// X szomszédja megváltozott: az ütközési idejét frissítjük a kupacban
static void refresh(int X) {
    ll p, q;
    if (!keyOf(X, p, q)) { heapRemove(X); return; }
    if (P[X].pos < 0) { H[hn] = X; P[X].pos = hn; hn++; siftUp(P[X].pos); }
    else { siftUp(P[X].pos); siftDown(P[X].pos); }
}
// X kiesik a pályáról (megérkezett, vagy legyőzte az ellenfele)
static void removeEl(int X) {
    int Pv = P[X].pv, Q = P[X].nx;
    heapRemove(X);
    if (Pv >= 0) P[Pv].nx = Q; else HEAD = Q;
    if (Q >= 0) P[Q].pv = Pv; else TAIL = Pv;
    if (RB == X) RB = (Pv >= 0 && isA(Pv)) ? Pv : -1;
    if (LF == X) LF = (Q >= 0 && !isA(Q)) ? Q : -1;
    if (Pv >= 0) refresh(Pv);
}

// gyors beolvasás
static char ibuf[1 << 16];
static size_t ipos = 0, ilen = 0;
static inline int gc() {
    if (ipos == ilen) { ilen = fread(ibuf, 1, sizeof(ibuf), stdin); ipos = 0; if (ilen == 0) return -1; }
    return ibuf[ipos++];
}
static inline ll readNum() {
    int c = gc();
    while (c != -1 && !(c >= '0' && c <= '9')) c = gc();
    ll v = 0;
    while (c >= '0' && c <= '9') { v = v * 10 + (c - '0'); c = gc(); }
    return v;
}
static inline int readLetter() {
    int c = gc();
    while (c != -1 && c != 'A' && c != 'B') c = gc();
    return c;
}

int main() {
    N = (int)readNum();
    P = (E *)malloc(sizeof(E) * (size_t)max(N, 1));
    H = (int *)malloc(sizeof(int) * (size_t)max(N, 1));
    for (int i = 0; i < N; i++) {
        int c = readLetter();
        P[i].f = (c == 'A') ? 1 : 0;
        P[i].s = (int)readNum(); P[i].d = (int)readNum();
        P[i].nx = P[i].pv = P[i].pos = -1;
    }
    const int T_ARR = 0, T_START = 1, T_COL = 2;   // egyenlő időnél: érkezés, indulás, ütközés
    int ps = 0;
    while (true) {
        int bestType = -1, bestEl = -1; ll bp = 0, bq = 1;
        auto consider = [&](ll p, ll q, int type, int el) {
            if (bestType < 0) { bestType = type; bestEl = el; bp = p; bq = q; return; }
            i128 l = (i128)p * bq, r = (i128)bp * q;
            if (l < r || (l == r && type < bestType)) { bestType = type; bestEl = el; bp = p; bq = q; }
        };
        if (RB >= 0) consider((ll)P[RB].s + P[RB].d, 1, T_ARR, RB);
        if (LF >= 0) consider((ll)P[LF].s + P[LF].d, 1, T_ARR, LF);
        if (ps < N) consider(P[ps].s, 1, T_START, ps);
        if (hn > 0) { ll p, q; keyOf(H[0], p, q); consider(p, q, T_COL, H[0]); }
        if (bestType < 0) break;
        if (bestType == T_ARR) {
            removeEl(bestEl);
        } else if (bestType == T_START) {
            int i = bestEl; ps++;
            if (isA(i)) {                     // A-ból indul: a lista elejére kerül
                P[i].pv = -1; P[i].nx = HEAD;
                if (HEAD >= 0) P[HEAD].pv = i;
                HEAD = i; if (TAIL < 0) TAIL = i;
                if (RB < 0) RB = i;
                refresh(i);
            } else {                          // B-ből indul: a lista végére kerül
                P[i].nx = -1; P[i].pv = TAIL;
                if (TAIL >= 0) { P[TAIL].nx = i; refresh(TAIL); }
                TAIL = i; if (HEAD < 0) HEAD = i;
                if (LF < 0) LF = i;
                refresh(i);
            }
        } else {                              // ütközés a bestEl és a jobb szomszédja között
            int X = bestEl, Y = P[X].nx;
            P[max(X, Y)].f |= 2;              // a később (sorszám szerint) induló csomag ütköző
            int loser;
            if (isA(X) && isA(Y)) loser = X;              // azonos irány: az utolérő gyorsabb
            else if (!isA(X) && !isA(Y)) loser = Y;
            else if (P[X].d < P[Y].d) loser = Y;          // szemből: a lassabb esik ki
            else if (P[Y].d < P[X].d) loser = X;
            else loser = min(X, Y);                       // egyforma sebesség: a később induló győz
            removeEl(loser);
        }
    }
    // kimenet: az ütközők száma, majd a sorszámuk növekvő sorrendben
    int cnt = 0;
    for (int i = 0; i < N; i++) if (P[i].f & 2) cnt++;
    printf("%d\n", cnt);
    static char obuf[1 << 16];
    size_t on = 0;
    for (int i = 0; i < N; i++) if (P[i].f & 2) {
        if (on > sizeof(obuf) - 16) { fwrite(obuf, 1, on, stdout); on = 0; }
        on += sprintf(obuf + on, "%d\n", i + 1);
    }
    fwrite(obuf, 1, on, stdout);
    return 0;
}
