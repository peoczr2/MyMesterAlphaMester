/*
Megoldás lényege:
A gyalog, a bástya és a királynő legfeljebb két lépésben célba ér, ezeket közvetlenül számoljuk (a királynőnél a
köztes mezőket O(C) jelöltön próbáljuk végig). A futó egy minimális úton mindig előre halad, és az irányát minden lépésben
váltja: falról falra cikázik. Ha minden fordulópont a falon van, az út a lehető leghosszabb; a legkisebb ilyen k
lépésszám, amelynél ez a hossz legalább R-1, a válasz. A felesleget (2s sort) úgy tüntetjük el, hogy a k-1
fordulópontot összesen s-sel beljebb húzzuk; ennek módszáma ismétléses kombináció, a legelső fordulópont korlátja
miatt egy tag levonásával (a többi korlát magától teljesül, mert s kisebb az utolsó lépésnél). Ezt mindkét
kezdőirányra kiszámoljuk, így egy kérdés O(C). A király mindig R-1 lépést tesz, az útvonalak száma az M^(R-1)
mátrix egy eleme, ahol M a C×C-s "oszlop ±1" mátrix. M hatványai felcserélhetők M-mel, ezért egy ilyen mátrixot
az első sora O(C²) időben meghatároz; így a gyorshatványozás egy szorzása O(C²), az egész O(C² log R), utána
minden király-kérdés O(1). Memória: egy C×C-s tömb.
*/
/*
Hint 1: || A király minden lépéssel pontosan egy sort halad, így a lépésszám R-1, a módszám pedig a C×C-s "szomszédos oszlop" mátrix (R-1)-edik hatványának eleme. A sima mátrixhatványozás O(C³ log R), ez túl lassú. ||
Hint 2: || Ha P = M^k, akkor P·M = M·P. Ebből P[i+1][j] = P[i][j-1] + P[i][j+1] - P[i-1][j], vagyis az első sorból az egész mátrix O(C²) alatt felépíthető, és a szorzat első sora is O(C²). ||
Hint 3: || A futó minimális úton nem lép vissza, és minden lépésben irányt vált. Ha minden fordulópont a falon van, megkapjuk a k lépésből elérhető leghosszabb utat; a legkisebb ilyen k, amivel legalább R-1 sort meg lehet tenni, a lépésszám. ||
Hint 4: || A túllógás 2s sor; ezt a k-1 fordulópont falról való beljebb húzásával kell eltüntetni, összesen s-sel. Ez C(s+k-2, k-2) módon lehetséges, levonva azokat, ahol az első fordulópont túl messzire kerülne. Mindkét kezdőirányt nézd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A modulo-műveleteket magunk végezzük, így az arithmetics.h könyvtárra nincs szükség.
const long long MOD = 1000000007;

long long R;
int C;
vector<long long> invFact;  // invFact[i] = 1 / i!

long long power(long long b, long long e) {
    long long r = 1;
    b %= MOD;
    while (e > 0) {
        if (e & 1) r = r * b % MOD;
        b = b * b % MOD;
        e >>= 1;
    }
    return r;
}

// C(n, r) mod p, ahol r kicsi (r <= C), n akár 10^9 körüli is lehet
long long binom(long long n, long long r) {
    if (r < 0 || n < r) return 0;
    long long num = 1;
    for (long long i = 0; i < r; i++) num = num * ((n - i) % MOD) % MOD;
    return num * invFact[r] % MOD;
}

// ---------- Király ----------
// Az M^k mátrix felépítése az első sorából: P·M = M·P miatt
// P[i+1][j] = P[i][j-1] + P[i][j+1] - P[i-1][j].
void expand(const vector<long long> &row, vector<vector<long long>> &F) {
    F[0] = row;
    for (int i = 0; i + 1 < C; i++)
        for (int j = 0; j < C; j++) {
            long long v = 0;
            if (j > 0) v += F[i][j - 1];
            if (j + 1 < C) v += F[i][j + 1];
            if (i > 0) v -= F[i - 1][j];
            v %= MOD;
            if (v < 0) v += MOD;
            F[i + 1][j] = v;
        }
}

// sorvektor szorozva a teljes F mátrixszal
vector<long long> rowTimes(const vector<long long> &v, const vector<vector<long long>> &F) {
    vector<long long> out(C, 0);
    for (int t = 0; t < C; t++) {
        if (v[t] == 0) continue;
        for (int j = 0; j < C; j++) out[j] = (out[j] + v[t] * F[t][j]) % MOD;
    }
    return out;
}

// a teljes M^e mátrix, gyorshatványozással, mindig csak az első sort tárolva
void kingMatrix(long long e, vector<vector<long long>> &F) {
    vector<long long> res(C, 0), base(C, 0);
    res[0] = 1;              // az egységmátrix első sora
    base[0] = 1, base[1] = 1;  // M első sora
    while (e > 0) {
        expand(base, F);
        if (e & 1) res = rowTimes(res, F);
        e >>= 1;
        if (e > 0) base = rowTimes(base, F);
    }
    expand(res, F);
}

// ---------- Futó ----------
// Az a oszlopból indul, első lépése jobbra megy, a b oszlopba kell érnie R-1 sor alatt.
// Visszaadja a minimális lépésszámot és a módszámot; lépésszám -1, ha így nem megy.
pair<long long, long long> bishopRightFirst(long long a, long long b) {
    long long L = R - 1;
    if (a == C) return {-1, 0};
    long long first = C - a;  // az első lépés leghosszabb változata (a jobb falig)
    long long w = C - 1;      // egy falról falra lépés hossza
    // k páros: az utolsó lépés balra megy, k páratlan: jobbra
    auto lastLen = [&](long long k) { return k % 2 == 0 ? C - b : b - 1; };
    auto maxLen = [&](long long k) { return first + (k - 2) * w + lastLen(k); };
    auto ceilDiv = [](long long x, long long y) { return x <= 0 ? 0 : (x + y - 1) / y; };
    long long kEven = 2 + 2 * ceilDiv(L - maxLen(2), 2 * w);
    long long kOdd = 3 + 2 * ceilDiv(L - maxLen(3), 2 * w);
    long long k = min(kEven, kOdd);
    long long s = (maxLen(k) - L) / 2;  // ennyivel kell összesen beljebb húzni a fordulópontokat
    long long m = k - 1;                // fordulópontok száma
    long long A = first - 1, B = lastLen(k) - 1;  // az első és az utolsó fordulópont korlátja
    if (m == 1) {
        if (s <= A && s <= B) return {k, 1};
        return {-1, 0};
    }
    // d_1 + ... + d_m = s, d_1 <= A (a többi korlát s kicsisége miatt automatikusan teljesül)
    long long cnt = binom(s + m - 1, s);
    if (s > A) cnt = (cnt - binom(s - A - 1 + m - 1, s - A - 1) + MOD) % MOD;
    return {k, cnt};
}

pair<long long, long long> bishop(int c1, int cR) {
    if ((1 + c1 + R + cR) % 2 != 0) return {0, 0};
    if (llabs((long long)c1 - cR) == R - 1) return {1, 1};
    pair<long long, long long> p = bishopRightFirst(c1, cR);
    pair<long long, long long> q = bishopRightFirst(C + 1 - c1, C + 1 - cR);  // tükrözve: balra indul
    if (p.first == -1) return q.first == -1 ? make_pair(0LL, 0LL) : q;
    if (q.first == -1 || p.first < q.first) return p;
    if (q.first < p.first) return q;
    return {p.first, (p.second + q.second) % MOD};
}

// ---------- Királynő ----------
pair<long long, long long> queen(int c1, int cR) {
    long long dc = llabs((long long)cR - c1);
    if (c1 == cR || R - 1 == dc) return {1, 1};
    auto inBoard = [&](long long x, long long y) { return x >= 1 && x <= R && y >= 1 && y <= C; };
    // az (x, y) mezőről egy lépéssel elérhető a cél (R, cR)
    auto reachesTarget = [&](long long x, long long y) {
        if (x == R && y == cR) return false;
        return x == R || y == cR || llabs(x - R) == llabs(y - cR);
    };
    long long cnt = 0;
    for (int y = 1; y <= C; y++)  // a kezdősorban
        if (y != c1 && reachesTarget(1, y)) cnt++;
    long long cand[3] = {R, R - dc, R + dc};  // a kezdőoszlopban
    for (long long x : cand)
        if (x != 1 && inBoard(x, c1) && reachesTarget(x, c1)) cnt++;
    for (int t = 1; t <= C - 1; t++)  // a kezdőmező átlóin
        for (int sg = -1; sg <= 1; sg += 2) {
            long long x = 1 + t, y = c1 + (long long)sg * t;
            if (inBoard(x, y) && reachesTarget(x, y)) cnt++;
        }
    return {2, cnt};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int qn;
    cin >> R >> C >> qn;
    vector<char> type(qn);
    vector<int> from(qn), to(qn);
    bool hasKing = false;
    for (int i = 0; i < qn; i++) {
        cin >> type[i] >> from[i] >> to[i];
        if (type[i] == 'K') hasKing = true;
    }
    invFact.assign(C + 1, 1);
    long long f = 1;
    for (int i = 1; i <= C; i++) f = f * i % MOD;
    invFact[C] = power(f, MOD - 2);
    for (int i = C; i > 0; i--) invFact[i - 1] = invFact[i] * i % MOD;

    vector<vector<long long>> K;
    if (hasKing) {
        K.assign(C, vector<long long>(C, 0));
        kingMatrix(R - 1, K);
    }
    string out;
    for (int i = 0; i < qn; i++) {
        int c1 = from[i], cR = to[i];
        pair<long long, long long> ans;
        if (type[i] == 'P')
            ans = (c1 == cR) ? make_pair(R - 1, 1LL) : make_pair(0LL, 0LL);
        else if (type[i] == 'R')
            ans = (c1 == cR) ? make_pair(1LL, 1LL) : make_pair(2LL, 2LL);
        else if (type[i] == 'B')
            ans = bishop(c1, cR);
        else if (type[i] == 'Q')
            ans = queen(c1, cR);
        else
            ans = {R - 1, K[c1 - 1][cR - 1]};
        out += to_string(ans.first) + " " + to_string(ans.second) + "\n";
    }
    cout << out;
    return 0;
}
