/*
Megoldás lényege:
Q-t origónak véve a téglalap [L,R] x [B,T] alakú (L<0<R, B<0<T), és mind a négy oldalán pontosan egy pont van (a sarokpont két oldalhoz számít). A felső oldalpont vagy az L vagy R oszlopában van (sarok), vagy belül: ekkor T az L és R közötti oszlopok legkisebb pozitív y-ja, és ez a belső pont csak egyszer fordulhat elő; az alsó oldalnál ugyanígy. Attól függően, hogy a felső és az alsó oldalpont a bal (x<=0) vagy a jobb (x>0) félsíkon van, négy eset marad, amelyek közül kettő a másik kettő tükörképe; az esetek együtt minden lehetséges téglalapot lefednek, ezért ha van megoldás, valamelyik jelöltként előkerül. Ha mindkettő a bal oldalon van, T és B a bal oldali pontból legfeljebb 2-2 lehetőség, R pedig a (B,T) sáv első jobb oldali találata (y szerint rendezett pontokon prefix-minimum). Ha a felső a bal, az alsó a jobb oldali, akkor T a bal pontból adódik, B pedig a jobb oldali oszlopok monoton növekvő "alsó rekord" opcióiból bináris kereséssel választható, plusz az a jelölt, amikor R maga a sáv első találata. Az egyenlőségeket előszámolt számlálók szűrik, és minden jelöltet rendezett oszlop-/sorlistákon, bináris kereséssel ellenőrzünk. Az idő O(N log N): három irányításban O(N) jelölt, egyenként O(log N); N=10^5 mellett kb. 20 ms.
*/
/*
Hint 1: || Tolj el úgy, hogy Q legyen az origó. A felső oldal egyetlen pontja vagy a sarokban van, vagy az oldal belsejében; belső esetben T az L és R közötti oszlopok legkisebb pozitív y-ja, ezért a bal oldali pont csak olyan lehet, amelyet Q felé nézve nem takar alacsonyabb pont (rekord). Gondold végig, hogy a felső és az alsó oldalpont a bal (x <= 0) vagy a jobb (x > 0) oldalon van: négy eset adódik, és kettő közülük tükrözéssel visszavezethető a másikra. ||
Hint 2: || Ha a felső és az alsó oldalpont is a bal oldalon van, akkor minden bal oldali pontból T és B legfeljebb 2-2 féleképpen jöhet ki (a pont maga, ha sarok, vagy a belső rekord), R pedig csak a (B,T) vízszintes sáv első jobb oldali találata lehet. Ezt a jobb oldali pontok y szerint rendezett listájából prefix-minimummal és bináris kereséssel kapod meg. ||
Hint 3: || Ha a felső oldalpont a bal, az alsó a jobb oldalon van, akkor T a bal pontból adott, B viszont a jobb oszlopoktól függ: jobbra haladva a B nem csökken (az eddigi legnagyobb negatív y, vagy az oszlop legfelső negatív pontja). A megfelelő (x, B) opciókat tárold egy listában, és bináris kereséssel válaszd ki azt, amelyre B a bal oldali oszlop és a bal belső rekord által megengedett határok között van, az x pedig még a sáv első jobb oldali találata előtt van; külön jelölt, amikor R pontosan ez az első találat. ||
Hint 4: || A "pontosan egy pont" feltételt számlálókkal szűrd: az oszlopban a szomszédos pontok y-ja, a belső rekord előfordulásának száma, és a sarokpont két oldalhoz számít. Minden jelöltet végül rendezett (x,y) és (y,x) listákon ellenőrizz: a bal és jobb oszlopban, a felső és alsó sorban is pontosan egy pont legyen a zárt szakaszon, és belül nem lehet pont. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int INF = 1000000000;

struct Rect { int L, R, B, T; };   // a téglalap oldalai, Q-t origónak véve

// (első, második) szerinti rendezés számjegyes módszerrel; az értékek abszolút értéke legfeljebb 10^6
static void radixSort(vector<pii>& v) {
    const int OFF = 1 << 20;
    vector<pii> tmp(v.size());
    for (int pass = 0; pass < 4; ++pass) {
        int shift = (pass & 1) ? 11 : 0;
        bool onFirst = pass >= 2;
        static int cnt[2049];
        fill(cnt, cnt + 2049, 0);
        for (auto& p : v) cnt[((((onFirst ? p.first : p.second) + OFF) >> shift) & 2047) + 1]++;
        for (int i = 0; i < 2048; ++i) cnt[i + 1] += cnt[i];
        for (auto& p : v) tmp[cnt[(((onFirst ? p.first : p.second) + OFF) >> shift) & 2047]++] = p;
        v.swap(tmp);
    }
}

// x tükrözése: a rendezett (x,y) és (y,x) listák O(n) idő alatt átalakíthatók
static void flipX(const vector<pii>& cv, const vector<pii>& rv, vector<pii>& c2, vector<pii>& r2) {
    int n = cv.size();
    c2.clear(); r2.clear();
    for (int j = n; j > 0;) {                      // oszlopcsoportok hátulról, csoporton belül y szerint
        int k = j;
        while (k > 0 && cv[k - 1].first == cv[j - 1].first) --k;
        for (int t = k; t < j; ++t) c2.push_back(pii(-cv[t].first, cv[t].second));
        j = k;
    }
    for (int i = 0; i < n;) {                      // soronként a csoport megfordítva
        int k = i;
        while (k < n && rv[k].first == rv[i].first) ++k;
        for (int t = k - 1; t >= i; --t) r2.push_back(pii(rv[t].first, -rv[t].second));
        i = k;
    }
}
// y tükrözése
static void flipY(const vector<pii>& cv, const vector<pii>& rv, vector<pii>& c2, vector<pii>& r2) {
    int n = cv.size();
    c2.clear(); r2.clear();
    for (int i = 0; i < n;) {
        int k = i;
        while (k < n && cv[k].first == cv[i].first) ++k;
        for (int t = k - 1; t >= i; --t) c2.push_back(pii(cv[t].first, -cv[t].second));
        i = k;
    }
    for (int j = n; j > 0;) {
        int k = j;
        while (k > 0 && rv[k - 1].first == rv[j - 1].first) --k;
        for (int t = k; t < j; ++t) r2.push_back(pii(-rv[t].first, rv[t].second));
        j = k;
    }
}

// Esetszétválasztás. A felső oldal egyetlen pontja vagy a bal félsíkon (x <= 0), vagy a jobbon (x > 0),
// az alsóé szintén. Négy eset van:
//   LL: felső is, alsó is bal oldali     -> solveLL
//   LR: felső bal oldali, alsó jobb oldali -> solveLR
//   RR: x tükrözésével LL-lé alakul, RL: y tükrözésével LR-rel egyenértékű.
// Egy Frame egy rögzített irányítású pontlistán dolgozik (Q az origó); a main három irányítást próbál végig.
struct Frame {
    vector<pii> cv, rv;   // (x,y) szerint és (y,x) szerint rendezve
    int wMax = -INF, eMin = INF;   // az y = 0 egyenesen a legközelebbi pont balra / jobbra
    // bal oldali jelöltek (x < 0), minden pontra:
    //   lG/lH: a legkisebb pozitív / legnagyobb negatív y az (x, 0] oszlopokban, lcG/lcH: ezek előfordulása
    //   lylow/lyhigh: az oszlopban az alatta / fölötte levő legközelebbi pont y-ja
    vector<int> lx, ly, lG, lcG, lH, lcH, lylow, lyhigh;
    // jobb oldali oszlopok (x > 0): a (0, x) oszlopokban a legkisebb pozitív y (rcG) és a legnagyobb negatív y (rcM)
    vector<int> rcx, rcG, rcM;
    // (x, B) opciók: az x oszlop lehet a jobb oldal, és az alsó határ B (a jobb félsíkban dől el)
    vector<int> optX, optB;
    // jobb oldali pontok: y >= 0 szerint növekvő y, és prefix-minimum x; y < 0 pontok -y szerint
    vector<int> upY, upMin, dnK, dnMin;

    Frame(const vector<pii>& c, const vector<pii>& r) : cv(c), rv(r) { build(); }

    int cntCol(int x, int lo, int hi) const {
        return (int)(upper_bound(cv.begin(), cv.end(), pii(x, hi)) - lower_bound(cv.begin(), cv.end(), pii(x, lo)));
    }
    int cntRow(int y, int lo, int hi) const {
        return (int)(upper_bound(rv.begin(), rv.end(), pii(y, hi)) - lower_bound(rv.begin(), rv.end(), pii(y, lo)));
    }

    void build() {
        int n = cv.size();
        for (int i = 0; i < n; ++i) if (cv[i].second == 0) {
            if (cv[i].first < 0) wMax = max(wMax, cv[i].first);
            else if (cv[i].first > 0) eMin = min(eMin, cv[i].first);
        }
        int e = lower_bound(cv.begin(), cv.end(), pii(1, -INF)) - cv.begin();   // az első x > 0 pont
        // bal oldal: kintről befelé haladva (Q-tól távolodva) a belső oszlopok rekordjai
        {
            int curG = INF, cntG = 0, curH = -INF, cntH = 0;
            auto add = [&](int y) {
                if (y > 0) { if (y < curG) { curG = y; cntG = 1; } else if (y == curG) cntG++; }
                else if (y < 0) { if (y > curH) { curH = y; cntH = 1; } else if (y == curH) cntH++; }
            };
            int j = e;
            while (j > 0 && cv[j - 1].first == 0) { add(cv[j - 1].second); --j; }
            while (j > 0) {
                int x = cv[j - 1].first, k = j;
                while (k > 0 && cv[k - 1].first == x) --k;
                for (int t = k; t < j; ++t) {
                    lx.push_back(x); ly.push_back(cv[t].second);
                    lG.push_back(curG); lcG.push_back(cntG); lH.push_back(curH); lcH.push_back(cntH);
                    lylow.push_back(t > k ? cv[t - 1].second : -INF);
                    lyhigh.push_back(t + 1 < j ? cv[t + 1].second : INF);
                }
                for (int t = k; t < j; ++t) add(cv[t].second);
                j = k;
            }
        }
        // jobb oldal: oszlopról oszlopra haladva
        {
            int M = -INF, cntM = 0, Gm = INF;   // M: eddigi legnagyobb negatív y (cntM db), Gm: legkisebb pozitív y
            int j = e;
            while (j < n) {
                int x = cv[j].first, k = j;
                while (k < n && cv[k].first == x) ++k;
                rcx.push_back(x); rcG.push_back(Gm); rcM.push_back(M);
                int maxLow = -INF, cLow = 0, sizeS = 0, atM = 0;
                for (int t = j; t < k; ++t) {
                    int y = cv[t].second;
                    if (y < 0) {
                        if (y > maxLow) { maxLow = y; cLow = 1; } else if (y == maxLow) cLow++;
                        if (y > M) sizeS++; else if (y == M) atM++;
                    } else if (y > 0) Gm = min(Gm, y);
                }
                // az alsó pont belül van (B = M, egyetlen ilyen pont), és az oszlop egyetlen pontja M fölött
                if (M > -INF && cntM == 1 && sizeS == 1 && atM == 0) { optX.push_back(x); optB.push_back(M); }
                // az alsó pont maga az oszlop legfelső negatív pontja (sarok)
                if (sizeS >= 1 && cLow == 1) { optX.push_back(x); optB.push_back(maxLow); }
                if (maxLow > M) { M = maxLow; cntM = cLow; }
                else if (maxLow == M && maxLow > -INF) cntM += cLow;
                j = k;
            }
        }
        // a jobb oldali pontok y szerinti prefix-minimumai (x-ek)
        {
            int cur = INF;
            for (int i = 0; i < n; ++i) if (rv[i].second > 0 && rv[i].first >= 0) {
                cur = min(cur, rv[i].second);
                upY.push_back(rv[i].first); upMin.push_back(cur);
            }
            cur = INF;
            for (int i = n - 1; i >= 0; --i) if (rv[i].second > 0 && rv[i].first < 0) {
                cur = min(cur, rv[i].second);
                dnK.push_back(-rv[i].first); dnMin.push_back(cur);
            }
        }
    }

    // a legkisebb x > 0, amelynek van pontja a 0 <= y <= T sávban
    int rupOf(int T) const {
        int idx = upper_bound(upY.begin(), upY.end(), T) - upY.begin();
        return idx ? upMin[idx - 1] : INF;
    }
    // a legkisebb x > 0, amelynek van pontja a B < y < T sávban
    int rstar(int B, int T) const {
        int idx = lower_bound(upY.begin(), upY.end(), T) - upY.begin();
        int m1 = idx ? upMin[idx - 1] : INF;
        int idx2 = lower_bound(dnK.begin(), dnK.end(), -B) - dnK.begin();
        int m2 = idx2 ? dnMin[idx2 - 1] : INF;
        return min(m1, m2);
    }

    // a bal jelölt (i. pont) x-e, valamint R, B, T téglalap teljes ellenőrzése
    bool fullCheck(int i, int R, int B, int T) const {
        int L = lx[i];
        if (L < wMax || R > eMin) return false;
        if (T > lG[i] || B < lH[i]) return false;
        int c = lower_bound(rcx.begin(), rcx.end(), R) - rcx.begin();
        if (c >= (int)rcx.size() || rcx[c] != R) return false;
        if (T > rcG[c] || B < rcM[c]) return false;
        return cntCol(L, B, T) == 1 && cntCol(R, B, T) == 1 && cntRow(T, L, R) == 1 && cntRow(B, L, R) == 1;
    }

    // a felső és az alsó oldalpont is a bal oldalon (x <= 0) van: R a sáv első jobb oldali találata
    bool solveLL(Rect& out) const {
        int nl = lx.size();
        for (int i = 0; i < nl; ++i) {
            int y = ly[i], G = lG[i], H = lH[i];
            if (lx[i] < wMax) continue;
            if (y > 0 && y >= G) continue;
            if (y < 0 && y <= H) continue;
            int Ts[2], Bs[2], nt = 0, nb = 0;
            if (y > 0 && lyhigh[i] > y) Ts[nt++] = y;                          // sarok: a bal pont a felső pont
            if (G < INF && lcG[i] == 1 && lyhigh[i] > G) Ts[nt++] = G;         // a felső pont belül van
            if (y < 0 && lylow[i] < y) Bs[nb++] = y;
            if (H > -INF && lcH[i] == 1 && lylow[i] < H) Bs[nb++] = H;
            for (int a = 0; a < nt; ++a) for (int b = 0; b < nb; ++b) {
                int T = Ts[a], B = Bs[b];
                int R = rstar(B, T);
                if (R >= INF || R > eMin) continue;
                if (fullCheck(i, R, B, T)) { out = {lx[i], R, B, T}; return true; }
            }
        }
        return false;
    }

    // a felső oldalpont a bal oldalon (x <= 0), az alsó a jobb oldalon (x > 0) van
    bool solveLR(Rect& out) const {
        int nl = lx.size();
        for (int i = 0; i < nl; ++i) {
            int y = ly[i], G = lG[i], H = lH[i];
            if (lx[i] < wMax) continue;
            if (y > 0 && y >= G) continue;
            if (y < 0 && y <= H) continue;
            int Ts[2], nt = 0;
            if (y > 0 && lyhigh[i] > y) Ts[nt++] = y;
            if (G < INF && lcG[i] == 1 && lyhigh[i] > G) Ts[nt++] = G;
            int lowB = max(lylow[i], H);        // B > lowB
            int highB = y < 0 ? y : 0;          // B < highB
            int i1 = upper_bound(optB.begin(), optB.end(), lowB) - optB.begin();
            int i2 = lower_bound(optB.begin(), optB.end(), highB) - optB.begin();
            for (int a = 0; a < nt; ++a) {
                int T = Ts[a];
                int Rup = rupOf(T);
                // (b) a jobb oszlop a sáv első találata előtt van: bármelyik jó opció megfelel
                int hi = min(i2, (int)(lower_bound(optX.begin(), optX.end(), Rup) - optX.begin()));
                if (i1 < hi && fullCheck(i, optX[i1], optB[i1], T)) { out = {lx[i], optX[i1], optB[i1], T}; return true; }
                // (a) a jobb oszlop épp a sáv első találata
                if (Rup < INF) {
                    int c = lower_bound(rcx.begin(), rcx.end(), Rup) - rcx.begin();
                    int B = rcM[c];
                    if (B > -INF && fullCheck(i, Rup, B, T)) { out = {lx[i], Rup, B, T}; return true; }
                }
            }
        }
        return false;
    }
};

// A bemenet gyors beolvasása (a limit 0.1 mp, N akár 10^5).
int main() {
    size_t cap = 1 << 16, len = 0;
    char* buf = (char*)malloc(cap);
    for (;;) {
        if (len == cap) { cap *= 2; buf = (char*)realloc(buf, cap); }
        size_t r = fread(buf + len, 1, cap - len, stdin);
        if (r == 0) break;
        len += r;
    }
    size_t pos = 0;
    auto readInt = [&]() -> int {
        while (pos < len && (buf[pos] < '0' || buf[pos] > '9') && buf[pos] != '-') ++pos;
        bool neg = false;
        if (pos < len && buf[pos] == '-') { neg = true; ++pos; }
        int v = 0;
        while (pos < len && buf[pos] >= '0' && buf[pos] <= '9') v = v * 10 + (buf[pos++] - '0');
        return neg ? -v : v;
    };
    int qx = readInt(), qy = readInt(), n = readInt();
    vector<pii> cv(n), rv(n);
    bool up = false, dn = false, lf = false, rt = false;
    for (int i = 0; i < n; ++i) {
        int x = readInt() - qx, y = readInt() - qy;
        cv[i] = pii(x, y); rv[i] = pii(y, x);
        if (y > 0) up = true;
        if (y < 0) dn = true;
        if (x < 0) lf = true;
        if (x > 0) rt = true;
    }
    free(buf);
    if (up && dn && lf && rt) {
        radixSort(cv);
        radixSort(rv);
        Rect r;
        {
            Frame f(cv, rv);
            if (f.solveLL(r) || f.solveLR(r)) {
                printf("%d %d %d %d\n", r.L + qx, r.B + qy, r.R + qx, r.T + qy);
                return 0;
            }
        }
        vector<pii> c2, r2;
        flipX(cv, rv, c2, r2);
        {
            Frame f(c2, r2);
            if (f.solveLL(r)) {
                printf("%d %d %d %d\n", -r.R + qx, r.B + qy, -r.L + qx, r.T + qy);
                return 0;
            }
        }
        flipY(cv, rv, c2, r2);
        {
            Frame f(c2, r2);
            if (f.solveLR(r)) {
                printf("%d %d %d %d\n", r.L + qx, -r.T + qy, r.R + qx, -r.B + qy);
                return 0;
            }
        }
    }
    printf("0 0 0 0\n");
    return 0;
}
