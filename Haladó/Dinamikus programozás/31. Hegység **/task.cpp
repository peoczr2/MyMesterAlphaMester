/*
Megoldás lényege:
Minden lépés szigorúan magasabb mezőre visz, ezért a mezők között az "innen léphetsz oda" kapcsolat körmentes: ha a mezőket
magasság szerint csökkenő sorrendben dolgozzuk fel, egy mező feldolgozásakor az összes nála magasabb szomszédja már kész.
Legyen dp[mező] a belőle induló leghosszabb emelkedő út lépésszáma: dp = 0, ha nincs magasabb szomszéd, különben
1 + a magasabb szomszédok dp-jének maximuma. A válasz a legnagyobb dp, és az a mező, ahol ezt az értéket először elértük.
Ha sehonnan sem lehet lépni, a válasz 0 és tetszőleges pozíció (itt: 1 1). A magasság legfeljebb 10000, ezért a rendezést
számlálva (counting sort) végezzük, így az egész O(N*M + magasságok száma) idejű. Az időlimit nagyon szigorú (0.1 mp), ezért
a bemenetet saját gyors beolvasóval olvassuk, a táblát pedig 0 magasságú szegéllyel vesszük körül, hogy ne kelljen határellenőrzés.
*/
/*
Hint 1: || Egy emelkedő úton a magasság szigorúan nő, ezért sosem érsz vissza ugyanarra a mezőre: nincs kör, így dinamikus programozással lehet számolni. ||
Hint 2: || Legyen dp[mező] az innen indulható leghosszabb emelkedő út lépésszáma. Ez 1 + max(dp[szomszéd]) a nála szigorúan magasabb szomszédokra, vagy 0, ha nincs ilyen. ||
Hint 3: || A dp értékeket a magasabb mezőktől az alacsonyabbak felé számold: rendezd a mezőket magasság szerint csökkenően (a magasság legfeljebb 10000, ezért számláló rendezés elég), és a rendezett sorrendben dolgozz. ||
*/

#include <bits/stdc++.h>

using namespace std;

static char buf[1 << 16];
static size_t buf_len = 0, buf_pos = 0;

// a következő karakter anélkül, hogy továbblépne; -1, ha a bemenet véget ért
static int peek_char() {
    if (buf_pos == buf_len) {
        buf_len = fread(buf, 1, sizeof(buf), stdin);
        buf_pos = 0;
        if (buf_len == 0) return -1;
    }
    return (unsigned char)buf[buf_pos];
}

// nemnegatív egész beolvasása (a számjegyeken kívüli karaktereket átugorja)
static int read_int() {
    int c = peek_char();
    while (c != -1 && (c < '0' || c > '9')) {
        ++buf_pos;
        c = peek_char();
    }
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        ++buf_pos;
        c = peek_char();
    }
    return x;
}

// van-e még szám az aktuális sor hátralévő részében?
static bool more_on_line() {
    int c = peek_char();
    while (c == ' ' || c == '\t' || c == '\r') {
        ++buf_pos;
        c = peek_char();
    }
    return c != '\n' && c != -1;
}

int main() {
    const int MAX_H = 65535;

    int n = read_int();
    // a feladat "N M" alakú első sort ír; ha csak egy szám áll a sorban, a tábla négyzetes
    int m = more_on_line() ? read_int() : n;
    const int w = m + 2;

    vector<uint16_t> h((size_t)(n + 2) * w, 0);  // 0 magasságú szegély: oda sosem lépünk fel
    vector<int> cnt(MAX_H + 2, 0);
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= m; ++c) {
            int v = read_int();
            h[(size_t)r * w + c] = (uint16_t)v;
            ++cnt[v];
        }
    }

    // számláló rendezés csökkenő magasság szerint: a v magasságú mezők a start[v]-től kezdődnek
    vector<int> start(MAX_H + 2, 0);
    int acc = 0;
    for (int v = MAX_H; v >= 0; --v) {
        start[v] = acc;
        acc += cnt[v];
    }
    vector<int> order(acc);
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= m; ++c) {
            int idx = r * w + c;
            order[start[h[idx]]++] = idx;
        }
    }

    vector<uint16_t> dp(h.size(), 0);
    int best_len = 0;
    int best_idx = w + 1;  // ha nincs lépés, tetszőleges pozíció: 1 1
    for (int k = 0; k < acc; ++k) {
        int idx = order[k];
        int hv = h[idx];
        int best_here = 0;
        if (h[idx - 1] > hv) best_here = max(best_here, dp[idx - 1] + 1);
        if (h[idx + 1] > hv) best_here = max(best_here, dp[idx + 1] + 1);
        if (h[idx - w] > hv) best_here = max(best_here, dp[idx - w] + 1);
        if (h[idx + w] > hv) best_here = max(best_here, dp[idx + w] + 1);
        dp[idx] = (uint16_t)best_here;
        if (best_here > best_len) {
            best_len = best_here;
            best_idx = idx;
        }
    }

    printf("%d\n%d %d\n", best_len, best_idx / w, best_idx % w);
    return 0;
}
