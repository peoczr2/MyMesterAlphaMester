/*
Megoldás lényege:
Söprővonal módszer az x-tengely mentén. Egy vízszintes szakasz (x1, x2, y) az x1 koordinátánál aktívvá válik, az x2 koordinátánál pedig megszűnik, a zárt szakaszok miatt a függőleges szakaszok kiértékelése után. Egy függőleges szakasz (x, y1, y2) az x koordinátájánál azt kérdezi meg, hány aktív vízszintes szakasz y-koordinátája esik a [y1, y2] zárt intervallumba. Az y-koordinátákat tömörítjük, és az aktív szakaszokat egy Fenwick-fában számoljuk. Mivel a vízszintes szakaszok nincsenek egymással közös pontban, egy y-érték egyszerre legfeljebb egy aktív szakaszt jelöl. A legtöbb metszést adó függőleges szakasz legkisebb sorszámát választjuk, ha nincs metszés, 0-t írunk. Az események rendezése O((M + N) log(M + N)), a lekérdezések Fenwick-fával logaritmikusak.
*/
/*
Hint 1: || Egy függőleges szakasz akkor metsz egy vízszintes szakaszt, ha az x-e a vízszintes szakasz x-tartományába esik, és a vízszintes szakasz y-ja a függőleges szakasz intervallumába. ||
Hint 2: || Söpört végig az x-tengelyt: a vízszintes szakasz x1-nél kerül egy halmazba, x2-nél kikerül. Egy függőleges szakasz x-nél megkérdezi, hány aktív y-érték esik az [y1, y2] intervallumba. ||
Hint 3: || Az aktív y-értékeket Fenwick-fában tárold, az y-koordinátákat tömörítsd, és az eseményeket úgy rendezd, hogy a bekerülés a lekérdezés előtt, a kivétel pedig utána történjen. ||
*/
#include <bits/stdc++.h>
using namespace std;

static char ibuf[1 << 16];
static size_t ipos = 0, ilen = 0;

static inline int gc() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}

static inline long long readLL() {
    int c = gc();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == -1) return 0;
        c = gc();
    }
    bool neg = false;
    if (c == '-') { neg = true; c = gc(); }
    long long x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return neg ? -x : x;
}

struct Event {
    long long x;
    int type;  // 0: vízszintes bekerül, 1: függőleges lekérdezés, 2: vízszintes kikerül
    int id;
};

int main() {
    int M = (int)readLL();
    int N = (int)readLL();
    vector<long long> hx1(M), hx2(M), hy(M);
    for (int i = 0; i < M; i++) {
        hx1[i] = readLL();
        hx2[i] = readLL();
        hy[i] = readLL();
        if (hx1[i] > hx2[i]) swap(hx1[i], hx2[i]);
    }
    vector<long long> vx(N), vy1(N), vy2(N);
    for (int j = 0; j < N; j++) {
        vx[j] = readLL();
        vy1[j] = readLL();
        vy2[j] = readLL();
        if (vy1[j] > vy2[j]) swap(vy1[j], vy2[j]);
    }

    // a vízszintes szakaszok y-koordinátáinak tömörítése
    vector<long long> ys(hy);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int Y = (int)ys.size();
    vector<int> hyi(M);
    for (int i = 0; i < M; i++) hyi[i] = (int)(lower_bound(ys.begin(), ys.end(), hy[i]) - ys.begin());

    vector<Event> ev;
    ev.reserve(2 * M + N);
    for (int i = 0; i < M; i++) {
        ev.push_back({hx1[i], 0, i});
        ev.push_back({hx2[i], 2, i});
    }
    for (int j = 0; j < N; j++) ev.push_back({vx[j], 1, j});
    sort(ev.begin(), ev.end(), [](const Event &a, const Event &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.type < b.type;
    });

    // Fenwick-fa az aktív vízszintes szakaszokra az y-tömörített indexek szerint
    vector<int> bit(Y + 1, 0);
    auto add = [&](int pos, int d) {
        for (int i = pos + 1; i <= Y; i += i & -i) bit[i] += d;
    };
    auto prefix = [&](int cnt) {  // az első cnt pozíció összege
        int s = 0;
        for (int i = cnt; i > 0; i -= i & -i) s += bit[i];
        return s;
    };

    vector<int> cnt(N, 0);
    for (const Event &e : ev) {
        if (e.type == 0) {
            add(hyi[e.id], 1);
        } else if (e.type == 2) {
            add(hyi[e.id], -1);
        } else {
            int lo = (int)(lower_bound(ys.begin(), ys.end(), vy1[e.id]) - ys.begin());
            int hi = (int)(upper_bound(ys.begin(), ys.end(), vy2[e.id]) - ys.begin());
            cnt[e.id] = prefix(hi) - prefix(lo);
        }
    }

    int best = 0, ans = 0;
    for (int j = 0; j < N; j++) {
        if (cnt[j] > best) {
            best = cnt[j];
            ans = j + 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}
