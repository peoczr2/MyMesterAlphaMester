/*
Megoldás lényege:
Egy d kavicsos kupacból az elvett kavicsok sorban d, d-1, …, 1 forintot érnek, így az összes kupac ezen értékei közül kell a legnagyobb K darab összegét venni.
Mivel egy kupac értékei csökkenő sorrendben következnek, a legnagyobb K érték kiválasztása mindig megvalósítható, ezért a mohó megoldás helyes.
Nem kell szimulálni: a v értékből annyi darab van, ahány kupac mérete legalább v.
A kupacméretek gyakoriságát tömbbe írjuk, majd a nagy értékektől lefelé haladva a darabszámból legfeljebb a még hiányzó K-t vesszük.
Az időigény O(N + max D + K), a válasz akár 2·10^10 is lehet, ezért 64 bites egész kell hozzá.
*/
/*
Hint 1: || Egy kupacból minden elvétel után eggyel kevesebb kavics marad, ezért egy d-elemű kupacból az elvételek d, d-1, …, 1 forintot érnek. Az a kérdés, hogy az összes ilyen érték közül melyik K darabot válasszuk. ||
Hint 2: || Ne szimuláld a kupacokat, hanem számold meg, hány kupac mérete legalább v: ennyi darab v értéket kapsz. A nagy értékektől lefelé haladva vedd a darabokat, amíg K darab nincs meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

static int freq[200002];

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

static inline long long readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9')) c = gc();
    long long x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

int main() {
    long long n = readInt();
    long long k = readInt();

    int maxd = 0;
    for (long long i = 0; i < n; ++i) {
        int d = (int)readInt();
        freq[d]++;
        if (d > maxd) maxd = d;
    }

    long long ans = 0, cum = 0, rem = k;
    for (int v = maxd; v >= 1 && rem > 0; --v) {
        cum += freq[v];
        long long t = min(cum, rem);
        ans += t * v;
        rem -= t;
    }

    printf("%lld\n", ans);
    return 0;
}
