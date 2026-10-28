/*
Megoldás lényege:
Mohó stratégia: egy benzinkúton annyi benzint érdemes venni, amennyi a következő, nála olcsóbb benzinkútig elég, mert a közbeeső kutak nem lehetnek olcsóbbak. Ha az olcsóbb kút a tank méretén (K) belül nincs, akkor a tartályt tele töltjük, hiszen a későbbi kutak sem olcsóbbak elérhető távolságon belül. A célállomást 0 áron vesszük fel, így minden kútnak van olcsóbb „következője”. Ezt a jobbra eső első, nála olcsóbb kutat egy monoton veremmel számoljuk ki O(N) időben. Az út végigszimulálásakor nyilvántartjuk a tankban lévő benzint, a vásárlásokat kiírjuk, a pénzösszeg a vásárolt mennyiségek és az árak szorzatainak összege. Az összidő O(N).
*/
/*
Hint 1: || Egy benzinkúton érdemes annyit tankolni, amennyi a következő olcsóbb kútig elég, hiszen a közbeeső kutak nem lehetnek olcsóbbak. Mi határozza meg, meddig érdemes tankolni? ||
Hint 2: || Minden kútnál keresd meg az első, nála olcsóbb kutat jobbra, a célt pedig 0 árral vegyük fel. Ezt egy monoton veremmel lehet végigfutva megtalálni. ||
Hint 3: || Ha az olcsóbb kút a tank méretén belül van, elég annyit venni, hogy odaérj; különben tele tankolsz. Közben nyilvántartod, mennyi benzined van, és a vásárlásokat kiírod. ||
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

int main() {
    int n = (int)readLL();
    long long K = readLL();
    vector<long long> d(n), p(n + 1, 0);
    for (int i = 0; i < n; i++) {
        d[i] = readLL();
        p[i] = readLL();
    }
    p[n] = 0;  // a célállomás

    // pos[i]: az i-edik benzinkút helye; pos[n] a célé
    vector<long long> pos(n + 1, 0);
    for (int i = 0; i < n; i++) pos[i + 1] = pos[i] + d[i];

    // nxt[i]: az első jobbra lévő, szigorúan olcsóbb állomás (monoton verem, jobbról balra)
    vector<int> nxt(n + 1, -1), stk;
    stk.reserve(n + 1);
    for (int i = n; i >= 0; i--) {
        while (!stk.empty() && p[stk.back()] >= p[i]) stk.pop_back();
        nxt[i] = stk.empty() ? -1 : stk.back();
        stk.push_back(i);
    }

    long long fuel = 0, cost = 0;
    vector<pair<int, long long>> buys;
    for (int i = 0; i < n; i++) {
        int j = nxt[i];
        // ha az olcsóbb kút elérhető, annyi kell, hogy odaérjünk; különben tele tankolunk
        long long target = (pos[j] - pos[i] <= K) ? pos[j] - pos[i] : K;
        if (fuel < target) {
            long long buy = target - fuel;
            cost += buy * p[i];
            buys.push_back({i + 1, buy});
            fuel = target;
        }
        fuel -= d[i];  // átmenet a következő kútig (pos[i+1] - pos[i])
    }

    printf("%lld %d\n", cost, (int)buys.size());
    for (auto &b : buys) printf("%d %lld\n", b.first, b.second);
    return 0;
}
