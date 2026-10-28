/*
Megoldás lényege:
A játék állapota: a két játékos még meglévő dominói (bitmaszk), a sor bal oldalán lévő szabad vég értéke
és az, hogy ki következik. Az első lépés kötelező: a legnagyobb dupla kezdi és rakja le, így a kezdő állapot
egyértelmű. Az állapotokból memoizált DFS-sel bejárjuk az összes szabályos lépést (ahol pass csak akkor van,
ha az aktuális játékos nem tud lépni), és az eredményt bitmaszkban gyűjtjük: bit0 = A nyerhet, bit1 = B nyerhet.
Egyik ág eredményét a másikéval VAGY-oljuk, így a végeredmény az összes lehetséges kimenetel uniója.
Az állapotok száma legfeljebb 2^(2N) * 14, ezt 4 bites tömbben tároljuk (N <= 11 esetén kb. 29 MB).
*/
/*
Hint 1: || Az állapothoz elég tudni, melyik dominók maradtak meg mindkét játékosnál, mi a bal oldali szabad vég értéke és ki lép következőnek. Ugyanaz az állapot többféle úton is elérhető, ezért érdemes megjegyezni az eredményét. ||
Hint 2: || A kérdés nem az, hogy van-e nyerő stratégia, hanem az, hogy melyik játékos nyerhet valamelyik játékmenetben. Ezért minden lépés után a részeredményeket VAGY-old össze bitmaszkban, például A = 1, B = 2 jelöléssel. ||
Hint 3: || Ha valaki nem tud lépni, az ellenfél lép (ha tud), különben a játék döntetlen. Az első lépést nem kell választani: a legnagyobb dupla kezdi és rakja le. Akinek elfogy a dominója, az lépése után azonnal nyer. ||
*/
#include <bits/stdc++.h>
using namespace std;

static int N;
static int LO[2][12], HI[2][12];      // a két játékos dominói (kisebb, nagyobb pötty)
static vector<unsigned char> memo;    // 4 bites tároló: 0 = még nincs kiszámolva, különben eredmény + 1

static inline size_t keyIdx(const unsigned mk[2], int e, int turn) {
    return ((((size_t)mk[0] << N) | mk[1]) * 7 + e) * 2 + turn;
}
static inline int getMemo(size_t k) {
    unsigned char v = memo[k >> 1];
    return (k & 1) ? (v >> 4) : (v & 15);
}
static inline void setMemo(size_t k, int r) {
    unsigned char &v = memo[k >> 1];
    if (k & 1) v = (unsigned char)((v & 15) | (r << 4));
    else       v = (unsigned char)((v & 240) | r);
}

// Visszaadja, hogy melyik játékos nyerhet (bit0: A, bit1: B) ebből az állapotból.
static int solve(unsigned mk[2], int e, int turn) {
    size_t k = keyIdx(mk, e, turn);
    int g = getMemo(k);
    if (g) return g - 1;
    int res = 0;
    unsigned M = mk[turn];
    bool anyMove = false;
    for (int i = 0; i < N && res != 3; i++) {
        if (!(M >> i & 1)) continue;
        int other;                        // a lerakott dominó másik fele lesz az új szabad vég
        if (LO[turn][i] == e) other = HI[turn][i];
        else if (HI[turn][i] == e) other = LO[turn][i];
        else continue;
        anyMove = true;
        unsigned nk[2] = {mk[0], mk[1]};
        nk[turn] &= ~(1u << i);
        int sub;
        if (nk[turn] == 0) sub = 1 << turn;          // az utolsó dominót rakta le: nyert
        else sub = solve(nk, other, 1 - turn);
        res |= sub;
    }
    if (!anyMove) {
        // nem tud lépni: átadja a lépés jogát, de csak ha az ellenfél tud lépni; különben döntetlen
        unsigned O = mk[1 - turn];
        bool oppMove = false;
        for (int i = 0; i < N && !oppMove; i++) {
            if (!(O >> i & 1)) continue;
            if (LO[1 - turn][i] == e || HI[1 - turn][i] == e) oppMove = true;
        }
        if (oppMove) res = solve(mk, e, 1 - turn);
    }
    setMemo(k, res + 1);
    return res;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        if (scanf("%d", &N) != 1) return 0;
        for (int p = 0; p < 2; p++)
            for (int i = 0; i < N; i++) {
                int a, b;
                if (scanf("%d %d", &a, &b) != 2) return 0;
                LO[p][i] = min(a, b); HI[p][i] = max(a, b);
            }
        // a legnagyobb dupla kezdi, és az első lépésként le is rakja
        int sp = -1, si = -1, sv = -1;
        for (int p = 0; p < 2; p++)
            for (int i = 0; i < N; i++)
                if (LO[p][i] == HI[p][i] && LO[p][i] > sv) { sv = LO[p][i]; sp = p; si = i; }
        unsigned mk[2] = {(1u << N) - 1, (1u << N) - 1};
        mk[sp] &= ~(1u << si);
        int res;
        if (mk[sp] == 0) res = 1 << sp;               // csak egy dominója volt: azonnal nyert
        else {
            memo.assign(((size_t)1 << (2 * N)) * 14 / 2 + 1, 0);
            res = solve(mk, sv, 1 - sp);
        }
        string out;
        if (res & 1) out += 'A';
        if (res & 2) out += 'B';
        if (out.empty()) out = "D";
        printf("%s\n", out.c_str());
    }
    return 0;
}
