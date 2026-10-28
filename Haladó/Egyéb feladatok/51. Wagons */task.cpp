/*
Megoldás lényege:
Egy napon belül a segédvágány verem: a nap elején a verem tetejéről kivehető, amit a beállítás elfogad; közben az elfogadhatatlan vagonok a verem tetejére kerülnek, és a napon belül már nem vehetők ki. Ebből a három napra (A1, A2, A3 beállítás) az következik, hogy a feldolgozott vagonok egy 1..P prefixet adnak: j1 az első vagon, amelyet sem A1, sem A3 nem fogad el; j2 a j1-től számított első, amelyet sem A1, sem A2; j3 a j2-től számított első, amelyet sem A2, sem A3; és P = j3 (vagy N, ha nincs ilyen). Az 1 és 2 napos esetet külön ellenőrizzük (egy beállítás elfogad mindent, illetve két beállítás együtt lefed minden vagont). A hármas kereséséhez nem próbáljuk végig az S^3 hármast: részleges kiosztással indulunk (a még nem választott napokon semmi sem fogadható el), kiszámoljuk az első elakadó vagonokat j1, j2, j3-nál, és valamelyik elakadó vagon típusát egy még üres nap beállításának el kell fogadnia. Minden típust legfeljebb 10 beállítás fogad el, így legfeljebb 3 szinten, szintenként legfeljebb 60 ágon kell továbbmenni. Az „első elfogadhatatlan vagon” keresését bitkészletekkel (minden beállításhoz egy N bites vektor) gyorsítjuk, így egy kiértékelés kb. N/64 lépés. A fennmaradó nem kiosztott napokat optimista (mindent elfogadó) korláttal is metsszük.
*/
/*
Hint 1: || Egy napon belül a verem tetejéről csak a nap elején lehet kivenni, és ami nem fogadható el, az a nap végéig a verem tetején marad. Ebből az következik, hogy a három beállításhoz tartozó eredmény egy lánc: j1 = az első vagon, amit sem A1, sem A3 nem fogad el; j2 = a j1-től az első, amit sem A1, sem A2; j3 = a j2-től az első, amit sem A2, sem A3. A feldolgozott vagonok száma j3. ||
Hint 2: || Az S^3 darab hármast nem érdemes mind kipróbálni. Ha egy hármasból már kiválasztottál néhány beállítást, a lánc a hiányzó napoknál „semmit sem fogad el” feltevéssel kiszámolható, és megmondja, melyik vagonnál akad el. Ennek a vagonnak a típusát egy üres nap beállításának el kell fogadnia, és egy típust legfeljebb 10 beállítás fogad el. ||
Hint 3: || Így a keresési fa mélysége legfeljebb 3, az elágazások száma kicsi. A lánc kiértékelését gyorsíthatod: minden beállításhoz tárold bitkészletben, hogy mely vagonokat fogadja el, így két beállítás uniójában az első nulla bit gyorsan megtalálható. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long u64;

int n, K, S, W;
vector<int> a;                 // a vagonok típusa
vector<vector<int>> setsOf;    // típus -> beállítások
vector<u64> bits;              // beállítás -> elfogadott vagonok bitkészlete
// speciális sorok: S = üres (semmit sem fogad el), S+1 = minden vagon
int ZERO_ROW, ONE_ROW;

int bestP = -1;
int bestTriple[3] = {0, 0, 0};
bool done = false;
unordered_set<unsigned long long> seen;

// az első index >= from, ahol sem az x, sem az y sor nem fogad el vagont; n, ha nincs ilyen
static int firstMiss(int x, int y, int from) {
    if (from >= n) return n;
    const u64 *X = &bits[(size_t)x * W];
    const u64 *Y = &bits[(size_t)y * W];
    int wi = from >> 6;
    u64 w = ~(X[wi] | Y[wi]) & (~0ULL << (from & 63));
    while (true) {
        if (w) {
            int pos = wi * 64 + __builtin_ctzll(w);
            return pos < n ? pos : n;
        }
        if (++wi >= W) return n;
        w = ~(X[wi] | Y[wi]);
    }
}

// a lánc: j1, j2, j3; visszaadja P-t (feldolgozott vagonok száma)
static int chain(int r1, int r2, int r3, int j[3]) {
    j[0] = firstMiss(r1, r3, 0);
    if (j[0] >= n) { j[1] = j[2] = n; return n; }
    j[1] = firstMiss(r1, r2, j[0]);
    if (j[1] >= n) { j[2] = n; return n; }
    j[2] = firstMiss(r2, r3, j[1]);
    return j[2];
}

static void rec(int A[3]) {
    if (done) return;
    unsigned long long key = ((unsigned long long)(A[0] + 1) * 1002ULL + (A[1] + 1)) * 1002ULL + (A[2] + 1);
    if (!seen.insert(key).second) return;

    int rows[3], opt[3], j[3];
    for (int r = 0; r < 3; r++) {
        rows[r] = A[r] < 0 ? ZERO_ROW : A[r];
        opt[r] = A[r] < 0 ? ONE_ROW : A[r];
    }
    int P = chain(rows[0], rows[1], rows[2], j);
    if (P > bestP) {
        bestP = P;
        for (int r = 0; r < 3; r++) bestTriple[r] = A[r] < 0 ? 0 : A[r];
        if (P >= n) { done = true; return; }
    }
    int jo[3];
    if (chain(opt[0], opt[1], opt[2], jo) <= bestP) return;

    // elakadó vagonok: (j1: A1,A3), (j2: A1,A2), (j3: A2,A3)
    static const int pr[3][2] = {{0, 2}, {0, 1}, {1, 2}};
    for (int f = 0; f < 3; f++) {
        int type = a[j[f]];
        for (int q = 0; q < 2; q++) {
            int r = pr[f][q];
            if (A[r] >= 0) continue;
            for (int s : setsOf[type]) {
                A[r] = s;
                rec(A);
                A[r] = -1;
                if (done) return;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> K >> S;
    vector<vector<int>> setTypes(S);
    setsOf.assign(K + 1, {});
    for (int i = 0; i < S; i++) {
        int t;
        while (cin >> t && t != 0) {
            setTypes[i].push_back(t);
            setsOf[t].push_back(i);
        }
    }
    a.resize(n);
    for (auto &x : a) cin >> x;

    vector<char> present(K + 1, 0);
    for (int x : a) present[x] = 1;

    // 1 nap
    for (int i = 0; i < S; i++) {
        vector<char> ok(K + 1, 0);
        for (int t : setTypes[i]) ok[t] = 1;
        bool all = true;
        for (int t = 1; t <= K && all; t++)
            if (present[t] && !ok[t]) all = false;
        if (all) {
            cout << n << "\n" << i + 1 << " 0 0\n";
            return 0;
        }
    }
    // 2 nap: az első nem fedett típust a második beállításnak el kell fogadnia
    {
        vector<vector<char>> okRow(S, vector<char>(K + 1, 0));
        for (int i = 0; i < S; i++)
            for (int t : setTypes[i]) okRow[i][t] = 1;
        for (int i = 0; i < S; i++) {
            int first = -1;
            for (int t = 1; t <= K; t++)
                if (present[t] && !okRow[i][t]) { first = t; break; }
            for (int c : setsOf[first]) {
                bool all = true;
                for (int t = 1; t <= K && all; t++)
                    if (present[t] && !okRow[i][t] && !okRow[c][t]) all = false;
                if (all) {
                    cout << n << "\n" << i + 1 << " " << c + 1 << " 0\n";
                    return 0;
                }
            }
        }
    }

    // bitkészletek: beállítás -> elfogadott vagonok
    W = (n + 63) / 64;
    ZERO_ROW = S;
    ONE_ROW = S + 1;
    bits.assign((size_t)(S + 2) * W, 0ULL);
    {
        vector<vector<int>> pos(K + 1);
        for (int j = 0; j < n; j++) pos[a[j]].push_back(j);
        for (int i = 0; i < S; i++)
            for (int t : setTypes[i])
                for (int j : pos[t]) bits[(size_t)i * W + (j >> 6)] |= 1ULL << (j & 63);
        for (int w = 0; w < W; w++) bits[(size_t)ONE_ROW * W + w] = ~0ULL;
    }

    int A[3] = {-1, -1, -1};
    rec(A);

    // az eredmény pontos ellenőrzése a végleges hármasra
    int j[3];
    int P = chain(bestTriple[0], bestTriple[1], bestTriple[2], j);
    cout << P << "\n" << bestTriple[0] + 1 << " " << bestTriple[1] + 1 << " " << bestTriple[2] + 1 << "\n";
    return 0;
}
