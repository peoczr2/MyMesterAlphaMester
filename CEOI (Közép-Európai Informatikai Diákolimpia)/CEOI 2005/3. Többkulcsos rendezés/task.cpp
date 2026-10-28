/*
Megoldás lényege:
A Sort(k) művelet stabil rendezés, ezért a végső sorrendet a sorozat végéről visszafelé az oszlopok első előfordulásai adják: az utoljára rendezett oszlop a legfontosabb kulcs, mögötte a korábban utoljára rendezett oszlopok állnak. Két sorozat pontosan akkor ekvivalens, ha ugyanezt a kulcslistát adják, így a legrövidebb ekvivalens sorozat az összes előforduló oszlop, mindegyik egyszer, az utolsó előfordulásuk szerinti növekvő sorrendben. A bemenetet egyszer olvassuk végig, és egy kétirányú láncolt listában tartjuk az oszlopokat: minden előfordulásnál az oszlop (ha már benne volt, előbb kivesszük) a lista végére kerül. Az idő O(C + K), a memória két egész tömb C+1 elemmel.
*/
/*
Hint 1: || Csak az oszlop utolsó előfordulása számít, mert a későbbi rendezés felülírja a korábbi sorrendet. Gondold végig, melyik oszlop legyen a legfontosabb rendezési kulcs. ||
Hint 2: || Tartsd nyilván az oszlopok utolsó előfordulásának sorrendjét, és a sorozat végén add ki az oszlopokat ebben a sorrendben. Az egész sorozatot nem kell tárolni: egy kétirányú láncolt lista elég, amelybe az oszlopot előforduláskor a végére tesszük. ||
*/
#include <bits/stdc++.h>
using namespace std;

static char ibuf[1 << 16];
static size_t ipos = 0, ilen = 0;

inline int gc() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}

inline long long readInt() {
    int c = gc();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == -1) return 0;
        c = gc();
    }
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = gc();
    }
    long long x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return neg ? -x : x;
}

static char obuf[1 << 16];
static size_t opos = 0;

inline void flushOut() {
    fwrite(obuf, 1, opos, stdout);
    opos = 0;
}

inline void putChar(char c) {
    if (opos == sizeof(obuf)) flushOut();
    obuf[opos++] = c;
}

inline void putInt(int x) {
    char tmp[12];
    int n = 0;
    if (x == 0) tmp[n++] = '0';
    while (x > 0) {
        tmp[n++] = char('0' + x % 10);
        x /= 10;
    }
    while (n > 0) putChar(tmp[--n]);
}

int main() {
    int C = (int)readInt();
    long long K = readInt();

    // Kétirányú körkörös lista az 1..C oszlopokon, az őrszem a 0-s csomópont.
    // nxt[k] == -1: az oszlop még nincs a listában.
    vector<int> nxt(C + 1, -1), prv(C + 1, 0);
    nxt[0] = 0;
    prv[0] = 0;

    for (long long i = 0; i < K; i++) {
        int k = (int)readInt();
        if (nxt[k] != -1) {
            int p = prv[k], q = nxt[k];
            nxt[p] = q;
            prv[q] = p;
        }
        int tail = prv[0];
        nxt[tail] = k;
        prv[k] = tail;
        nxt[k] = 0;
        prv[0] = k;
    }

    int D = 0;
    for (int v = nxt[0]; v != 0; v = nxt[v]) D++;

    putInt(D);
    putChar('\n');
    bool first = true;
    for (int v = nxt[0]; v != 0; v = nxt[v]) {
        if (!first) putChar(' ');
        putInt(v);
        first = false;
    }
    putChar('\n');
    flushOut();
    return 0;
}
