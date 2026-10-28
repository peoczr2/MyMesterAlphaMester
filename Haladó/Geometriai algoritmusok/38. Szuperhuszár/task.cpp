/*
Megoldás lényege:
A második játékos akkor és csak akkor nyerhet, ha bármely p pozícióhoz, ahová az első játékos eljuthat, a −p is elérhető.
Ez pontosan azt jelenti, hogy a lépésvektorok által kifeszített pozitív kúp egy altér. Két dimenzióban ez akkor teljesül,
ha a lépésvektorok irányai között nincs 180 foknál nagyobb (és pontosan 180 fokos) szögrés, vagyis az origó a lépések
konvex burkának belsejében van. Ha minden lépés egy egyenesre esik, akkor mindkét irányba kell legyen lépés.
A (0,0) lépés nem mozgatja a bábut, ezért figyelmen kívül hagyjuk.
Idő: O(L log L) játékonként.
*/
/*
Hint 1: || A második játékos akkor nyer, ha minden olyan p pozícióhoz, ahová az első játékos eljuthat, a −p is elérhető. Ez azt jelenti, hogy a lépésekből álló pozitív kúpnak szimmetrikusnak kell lennie. ||
Hint 2: || Két dimenzióban a kúp akkor a teljes sík, ha a lépésvektorok iránya nincs egy legalább 180 fokos szögtartományba zárva. Rendezd a vektorokat szög szerint, és nézd meg a szomszédos vektorok közötti szögeket. ||
Hint 3: || Ha minden lépés egy egyenesre esik, akkor kell lennie lépésnek mindkét irányba. Egyébként a szomszédos vektorpár keresztszorzatának előjeléből látszik, hogy a köztük lévő szög legalább 180 fok-e. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Vec {
    ll x, y;
};

static ll cross(const Vec& a, const Vec& b) { return a.x * b.y - a.y * b.x; }
static ll dot(const Vec& a, const Vec& b) { return a.x * b.x + a.y * b.y; }

// Igaz, ha a és b közötti, óramutató-ellenes irányú szög legalább 180 fok (egész számokkal).
static bool gapAtLeastPi(const Vec& a, const Vec& b) {
    ll c = cross(a, b);
    return c < 0 || (c == 0 && dot(a, b) < 0);
}

// Monoton szögkulcs [0,4) a (x,y) != (0,0) vektorokra: a szög növekedésével nő.
// Az ellentett vektor kulcsa mindig 2-vel nagyobb (vagy 2-vel kisebb, körbefordulva).
static double pseudoAngle(const Vec& a) {
    double x = (double)a.x, y = (double)a.y;
    if (y >= 0) {
        if (x >= 0) return y / (x + y);                 // [0,1)
        return 1.0 + (-x) / (-x + y);                    // [1,2)
    }
    if (x < 0) return 2.0 + (-y) / (-x - y);             // [2,3)
    return 3.0 + x / (x - y);                            // [3,4)
}

// Igaz, ha a lépések által kifeszített kúp a teljes sík (2D) vagy egy egyenes (1D).
static bool nyerő(vector<Vec> v) {
    // a nulla lépés nem változtatja a pozíciót
    v.erase(remove_if(v.begin(), v.end(), [](const Vec& a) { return a.x == 0 && a.y == 0; }), v.end());
    if (v.empty()) return true;  // a bábu mindig az origóban marad

    // 1. eset: minden lépés egy egyenesre esik
    bool egyenesen = true;
    for (const Vec& a : v)
        if (cross(v[0], a) != 0) { egyenesen = false; break; }
    if (egyenesen) {
        bool pozitív = false, negatív = false;
        for (const Vec& a : v) {
            ll d = dot(v[0], a);
            if (d > 0) pozitív = true;
            if (d < 0) negatív = true;
        }
        return pozitív && negatív;
    }

    // 2. eset: vödrös rendezés a monoton szögkulcs (pszeudoszög) szerint, O(L) időben.
    // Egy vödörben lévő lépések szöge kicsi (a vödör szélessége 4/L), ezért a 180 foknál nagyobb rés
    // mindig két különböző vödör között van. Az ilyen szomszédos párokat pontosan (egész számokkal) ellenőrizzük.
    size_t n = v.size();
    vector<double> key(n);
    for (size_t i = 0; i < n; i++) key[i] = pseudoAngle(v[i]);
    vector<int> minIdx(n, -1), maxIdx(n, -1);
    for (size_t i = 0; i < n; i++) {
        size_t b = (size_t)(key[i] * (double)n / 4.0);
        if (b >= n) b = n - 1;
        if (minIdx[b] < 0 || key[i] < key[minIdx[b]]) minIdx[b] = (int)i;
        if (maxIdx[b] < 0 || key[i] > key[maxIdx[b]]) maxIdx[b] = (int)i;
    }
    // a (körbe zárt) szomszédos vödrök közötti rés ellenőrzése
    int firstMin = -1, prevMax = -1;
    for (size_t b = 0; b < n; b++) {
        if (minIdx[b] < 0) continue;
        if (firstMin < 0) firstMin = minIdx[b];
        if (prevMax >= 0 && gapAtLeastPi(v[prevMax], v[minIdx[b]])) return false;
        prevMax = maxIdx[b];
    }
    if (prevMax >= 0 && gapAtLeastPi(v[prevMax], v[firstMin])) return false;
    return true;
}

// gyors beolvasás: a bemenet nagy lehet, ezért darabonként olvasunk (a memóriakorlát miatt)
static char ibuf[1 << 16];
static size_t ilen = 0, ipos = 0;
static int nextChar() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}
static ll readLL() {
    int c = nextChar();
    while (c != -1 && c != '-' && (c < '0' || c > '9')) c = nextChar();
    bool neg = false;
    if (c == '-') { neg = true; c = nextChar(); }
    ll v = 0;
    while (c >= '0' && c <= '9') { v = v * 10 + (c - '0'); c = nextChar(); }
    return neg ? -v : v;
}

int main() {
    int K = (int)readLL();
    string out;
    while (K--) {
        int L = (int)readLL();
        vector<Vec> v(L);
        for (int i = 0; i < L; ++i) {
            v[i].x = readLL();
            v[i].y = readLL();
        }
        out += nyerő(v) ? "IGEN\n" : "NEM\n";
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
