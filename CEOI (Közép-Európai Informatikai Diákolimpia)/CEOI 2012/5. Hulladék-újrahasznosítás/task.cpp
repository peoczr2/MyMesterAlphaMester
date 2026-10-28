/*
Megoldás lényege:
A kisegítő vágány verem, és a feldolgozott vagonok mindig egy prefixumot (1..L) alkotnak. Ha a három nap beállítása a, b, c, akkor az 1..L vagonok pontosan akkor dolgozhatók fel, ha három egymás utáni (akár üres) szakaszra bonthatók: az első szakasz típusai a∪c-ben, a másodiké a∪b-ben, a harmadiké b∪c-ben vannak. Ugyanis az 1. nap az első két szakaszt olvassa: az a-típusúakat azonnal feldolgozza, a többit a verembe tolja, így alul az első szakasz c-típusú vagonjai várnak a 3. napra, felül a második szakasz b-típusúi, ezeket a 2. nap leveszi; a 2. nap a harmadik szakaszt olvassa, a b-ket feldolgozza, a c-ket a verembe teszi, és a 3. nap mindent levesz. Rögzített hármasnál a szakaszokat mohón, a lehető leghosszabbra érdemes nyújtani.
A hármast keresőfával építjük: haladunk a mohó szakaszokon, és ha egy vagont az aktuális szakasz eddig rögzített beállításai nem fedik, akkor vagy a szakasz egy még szabad napjához rendelünk egy, a vagon típusát tartalmazó beállítást (legfeljebb 10 lehetőség), vagy lezárjuk a szakaszt. Legfeljebb 3 hozzárendelés és 2 lezárás történik, ezért a fának legfeljebb néhány tízezer levele van. A következő nem fedett vagont beállításonkénti bitsetekkel keressük (két bitset VAGY-a, első 0 bit), ez N/64 szónyi munka; az időigény így kb. 15000·N/64 egyszerű lépés, a memória S·N bit.
Ha L = N, külön megnézzük, elég-e 1 nap (egy beállítás minden típust tartalmaz) vagy 2 nap (két beállítás uniója).
*/
/*
Hint 1: || Írd le naponként, mi kerül a verembe és mi jön le onnan. Mutasd meg, hogy az 1..L prefixum pontosan akkor jó, ha három egymás utáni szakaszra bomlik: a típusok rendre a∪c-ben, a∪b-ben és b∪c-ben vannak. ||
Hint 2: || Rögzített a, b, c mellett a szakaszokat mohón nyújtsd. Az első vagon, amelyet az aktuális szakasz eddig választott beállításai nem fednek, vagy kijelöli a szakasz egy szabad napjának beállítását (legfeljebb 10 jelölt), vagy lezárja a szakaszt: ebből egy kicsi keresőfa lesz. ||
Hint 3: || A következő nem fedett vagonhoz minden beállításnak legyen egy N bites bitsete; két beállítás uniójában a (bx|by) szavakban az első 0 bitet keresd. Ha L = N, nézd meg külön, elég-e 1 vagy 2 nap. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

int N, K, S, W;
vector<int> V;                  // V[0..N-1]: a vagonok hulladéktípusa
vector<vector<int>> setsOf;     // setsOf[t]: a t típust tartalmazó beállítások
vector<ull> bits;               // bits[s*W + w]: az s beállítás által fedett vagonok (s = 0: üres)

// Az i-től kezdve az első vagon, amelyet sem x, sem y nem fed (N, ha nincs ilyen).
int nextFree(int i, int x, int y) {
    if (i >= N) return N;
    const ull *bx = &bits[(size_t)x * W], *by = &bits[(size_t)y * W];
    int w = i >> 6;
    ull cur = ~(bx[w] | by[w]) & (~0ULL << (i & 63));
    while (cur == 0) {
        w++;
        if (w >= W) return N;
        cur = ~(bx[w] | by[w]);
    }
    return min(N, w * 64 + __builtin_ctzll(cur));
}

// napok: 0 = a (1. nap), 1 = b (2. nap), 2 = c (3. nap)
const int segRole[3][2] = {{0, 2}, {0, 1}, {1, 2}};
int bestL = -1;
array<int, 3> bestA = {0, 0, 0};

// k: az aktuális szakasz, i: az első még nem vizsgált vagon, A: a rögzített beállítások (0: szabad)
void dfs(int k, int i, array<int, 3> A) {
    if (bestL == N) return;
    int j = nextFree(i, A[segRole[k][0]], A[segRole[k][1]]);
    if (j > bestL) { bestL = j; bestA = A; }
    if (j >= N) return;
    for (int r : segRole[k])
        if (A[r] == 0)
            for (int s : setsOf[V[j]]) {
                array<int, 3> B = A;
                B[r] = s;
                dfs(k, j, B);
            }
    if (k < 2) dfs(k + 1, j, A);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K >> S;
    setsOf.assign(K + 1, {});
    for (int s = 1; s <= S; s++) {
        int t;
        while (cin >> t && t != 0)
            if (t >= 1 && t <= K) setsOf[t].push_back(s);
    }
    for (auto &v : setsOf) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }
    V.assign(N, 0);
    for (int i = 0; i < N; i++) cin >> V[i];

    W = (N + 63) / 64;
    bits.assign((size_t)(S + 1) * W, 0);
    for (int i = 0; i < N; i++)
        for (int s : setsOf[V[i]]) bits[(size_t)s * W + (i >> 6)] |= 1ULL << (i & 63);

    dfs(0, 0, {0, 0, 0});

    array<int, 3> ans = bestA;
    for (int &x : ans)
        if (x == 0) x = 1;          // a szabad napra bármelyik beállítás jó
    if (bestL == N) {
        bool found = false;
        // elég-e egy nap?
        for (int x : setsOf[V[0]])
            if (!found && nextFree(0, x, 0) == N) { ans = {x, 0, 0}; found = true; }
        // elég-e két nap? (az első vagont fedő x, és az x által nem fedett első vagont fedő y)
        for (int x : setsOf[V[0]]) {
            if (found) break;
            int j = nextFree(0, x, 0);
            for (int y : setsOf[V[j]])
                if (!found && nextFree(0, x, y) == N) { ans = {x, y, 0}; found = true; }
        }
    }

    cout << bestL << '\n';
    cout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << '\n';
    return 0;
}
