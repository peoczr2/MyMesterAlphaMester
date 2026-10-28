/*
Megoldás lényege:
Az épület bal alsó sarka (a, S-a) alakú, ezért elég az a = 0..S értékeket végigvenni. Egy (X, Y) szobor akkor takart, ha a bejárat felől a szobor irányába húzott félegyenes átmegy az épület négyzetén, és a szobor a négyzet mögött van; ez két lineáris egyenlőtlenség a-ra (a négyzet jobb alsó és bal felső sarkának szöge közé esés) és az X >= a, Y >= b feltétel együttese, így minden szoborhoz egy [l, r] intervallum tartozik azokra az a-kra, amelyekre takarja. Ezeket különbségtömbbel gyűjtjük, és prefix-összeggel kapjuk a-nként a takart szobrok számát. Külön különbségtömb adja azokat az a-kat, amelyeknél egy szobor az épület belsejében vagy falán van; ezeket kizárjuk. A maximális takarást adó érvényes a-t keressük, döntetlennél a nagyobb x-koordinátát választjuk. Idő: O(N + S).
*/
/*
Hint 1: || Az épület bal alsó sarka (a, S-a) alakú, ezért csak a = 0, 1, ..., S értékeket kell kipróbálni. Minden a-ra két kérdés van: van-e szobor az épület belsejében vagy falán, és hány szobrot takar. ||
Hint 2: || Egy (X, Y) szobrot akkor takar az épület, ha a bejárattól a szobor felé húzott félegyenes átmegy a négyzeten, és a szobor a négyzet mögött van. A félegyenes szögét a négyzet jobb alsó és bal felső sarka határolja, így ez két egyenlőtlenség a-ra; a törtet a nevezővel (X+Y) szorozva egész számokkal dolgozhatsz. ||
Hint 3: || A "mögötte van" feltétel a szobor koordinátáival egyszerű: X >= a és Y >= b. Így minden szoborhoz egy egész intervallum tartozik azokra az a-kra, amelyekre takarja. Ezeket az intervallumokat egy különbségtömbbe írva, prefix-összeggel lehet az összes a-ra egyszerre megkapni. ||
Hint 4: || Egy szobor pontosan akkor van az épület zárt négyzetén, ha a ∈ [X-H, X] és a ∈ [S-Y, S-Y+H]. Ezeket az a-kat egy második különbségtömbbel jelöld meg, és csak a többi a-ra keress maximumot. ||
*/
#include <bits/stdc++.h>
using namespace std;

static long long floor_div(long long a, long long b) {
    if (a >= 0) return a / b;
    return -(( -a + b - 1) / b);
}

static long long ceil_div(long long a, long long b) {
    if (a >= 0) return (a + b - 1) / b;
    return -((-a) / b);
}

// Gyors bemenetolvasás (1e6 sor esetén a cin lassú az 0.1 mp-es időlimithez).
static char ibuf[1 << 16];
static size_t ilen = 0, ipos = 0;

static int readChar() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}

static long long readInt() {
    int c = readChar();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == -1) return 0;
        c = readChar();
    }
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = readChar();
    }
    long long v = 0;
    while (c >= '0' && c <= '9') {
        v = v * 10 + (c - '0');
        c = readChar();
    }
    return neg ? -v : v;
}

int main() {
    int n = (int)readInt();
    long long h = readInt();
    long long s = readInt();

    vector<int> hiddenDiff(s + 3, 0);
    vector<int> badDiff(s + 3, 0);

    for (int i = 0; i < n; ++i) {
        long long x = readInt();
        long long y = readInt();

        if (x == 0 && y == 0) {
            continue;
        }

        long long denom = x + y;
        long long l = max<long long>({0, s - y, ceil_div(x * s - y * h, denom)});
        long long r = min<long long>({s, x, floor_div(x * (s + h), denom)});
        if (l <= r) {
            ++hiddenDiff[l];
            --hiddenDiff[r + 1];
        }

        long long badL = max<long long>({0, x - h, s - y});
        long long badR = min<long long>({s, x, s - y + h});
        if (badL <= badR) {
            ++badDiff[badL];
            --badDiff[badR + 1];
        }
    }

    int hidden = 0;
    int bad = 0;
    int bestCount = -1;
    long long bestX = -1;

    for (long long x = 0; x <= s; ++x) {
        hidden += hiddenDiff[x];
        bad += badDiff[x];
        if (bad == 0) {
            if (hidden > bestCount || (hidden == bestCount && x > bestX)) {
                bestCount = hidden;
                bestX = x;
            }
        }
    }

    if (bestCount < 0) {
        cout << -1 << '\n';
        return 0;
    }

    cout << bestCount << '\n' << bestX << ' ' << (s - bestX) << '\n';
    return 0;
}
