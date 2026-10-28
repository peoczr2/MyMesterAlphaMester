/*
Megoldás lényege:
Egy d kavicsos kupacból az elvett kavicsok sorban d, d-1, …, 1 forintot érnek, így az összes kupac ezen értékei közül kell a legnagyobb K darab összegét venni.
Mivel egy kupac értékei csökkenő sorrendben következnek, a legnagyobb K érték kiválasztása mindig megvalósítható, ezért a mohó megoldás helyes.
A memória korlátja 1 MB, ezért a kupacokat nem tároljuk, hanem a méretek gyakoriságát egy tömbbe olvassuk be (a méretek legfeljebb 200 000-esek lehetnek, így a tömb kb. 800 KB).
Ezután a nagy értékektől lefelé haladva minden v értékből annyit veszünk, ahány kupac mérete legalább v, amíg K darab nincs meg.
Az időigény O(N + max D + K), a válasz akár 10^11 körüli is lehet, ezért 64 bites egész kell hozzá.
*/
/*
Hint 1: || Egy kupacból minden elvétel után eggyel kevesebb kavics marad, ezért egy d-elemű kupacból az elvételek d, d-1, …, 1 forintot érnek. Az a kérdés, hogy az összes ilyen érték közül melyik K darabot válasszuk. ||
Hint 2: || Ne tárold el az összes kupacot, csak a méretek előfordulását számold egy tömbben. A nagy értékektől lefelé haladva minden v értékből annyit vegyél, ahány kupac mérete legalább v, amíg K darab nincs meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

static int freq[200002];

static char ibuf[1 << 14];
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
