/*
Megoldás lényege:
Az oszlopok sorrendje a sorban sosem változik, két oszlop csak szomszédosan olvadhat össze, és az összeolvasztás akkor megengedett, ha az egyik oszlop minden eleme kisebb a másikénál.
Így a sorozatot úgy kell rekurzívan kettévágni, hogy a két rész értékei elkülönüljenek; ez pontosan akkor lehetséges, ha a bemenet megoldható.
A legnagyobb konténer oszlopa helyben marad, ezért a rekurzió mindig ezt a részt gyűjtőhelynek tekinti, és a másik részt annak irányába olvasztja be.
Az olvasztandó oszlopot az üres helyeken át a célhoz visszük, majd rátoljuk; minden mozgás egy kimeneti sor.
A keresés és a rekurzió összesen O(N²) lépésben fut, N ≤ 1000 mellett ez bőven belefér az időkorlátba.
*/
/*
Hint 1: || A lépések nem változtatják meg a konténer-oszlopok egymáshoz viszonyított sorrendjét: két oszlop csak akkor olvadhat össze, ha szomszédos helyen állnak. Gondold végig, mikor lehet két szomszédos oszlopot összeolvasztani. ||
Hint 2: || Keress olyan vágást a sorban, ahol a bal és a jobb rész értékei elkülönülnek: az egyik rész minden eleme kisebb a másik rész összes eleménél. Ilyen vágás mentén a részek külön-külön összegyűjthetők. ||
Hint 3: || A legnagyobb konténer oszlopa nem mozdul, ezért a rekurzióban a pozícióját mindig tartsd szem előtt: a többi oszlopot a neki megfelelő oldalról kell odahúzni és ráolvasztani. Az üres helyeken történő mozgatás egyetlen lépés. ||
*/
#include <bits/stdc++.h>
using namespace std;

static int n;
static int pN;                    // a legnagyobb konténer helye (0-tól indexelve)
static vector<int> a;             // a[h]: a h-adik helyen lévő konténer mérete
static vector<vector<int>> stk;   // stk[id]: az oszlop elemei alulról felfelé (csökkenő)
static vector<int> posOf;         // posOf[id]: az oszlop helye
static vector<int> at;            // at[h]: a h-n lévő oszlop azonosítója, vagy -1
static string out;

// Egy lépés: a 'id' oszlopot dir irányba (-1: balra, +1: jobbra) átrakja.
static void step(int id, int dir) {
    int from = posOf[id];
    int to = from + dir;
    out += to_string(from + 1);
    out += (dir > 0) ? " J\n" : " B\n";
    if (at[to] == -1) {
        at[to] = id;
        at[from] = -1;
        posOf[id] = to;
    } else {
        int t = at[to];
        stk[t].insert(stk[t].end(), stk[id].begin(), stk[id].end());
        stk[id].clear();
        at[from] = -1;
        posOf[id] = -1;
    }
}

// Az mv oszlopot a tg oszlop mellé viszi az üres helyeken át, majd ráolvasztja.
static void merge_into(int mv, int tg) {
    while (posOf[mv] < posOf[tg] - 1) step(mv, +1);
    while (posOf[mv] > posOf[tg] + 1) step(mv, -1);
    step(mv, posOf[tg] > posOf[mv] ? +1 : -1);
}

// Az [l..r] szakasz oszlopait egy oszlopba gyűjti; visszaadja a kapott oszlop azonosítóját.
static int solve_all(int l, int r) {
    if (l == r) return l;
    int len = r - l + 1;
    vector<int> smax(len + 1), smin(len + 1);
    smax[len] = INT_MIN;
    smin[len] = INT_MAX;
    for (int i = len - 1; i >= 0; --i) {
        smax[i] = max(a[l + i], smax[i + 1]);
        smin[i] = min(a[l + i], smin[i + 1]);
    }
    int pmax = INT_MIN, pmin = INT_MAX, cut = -1;
    for (int k = 0; k + 1 < len && cut < 0; ++k) {
        pmax = max(pmax, a[l + k]);
        pmin = min(pmin, a[l + k]);
        if (pmax < smin[k + 1] || smax[k + 1] < pmin) cut = l + k;
    }
    int x = solve_all(l, cut);
    int y = solve_all(cut + 1, r);
    if (stk[x].front() < stk[y].back()) {  // a bal rész kisebb: x jobbra, y-ra
        merge_into(x, y);
        return y;
    }
    merge_into(y, x);                      // a jobb rész kisebb: y balra, x-re
    return x;
}

// Az [l..r] szakasz (benne a legnagyobb konténerrel) oszlopait a pN-es helyen gyűjti.
static void solve_n(int l, int r) {
    if (l == r) return;
    int len = r - l + 1;
    vector<int> smax(len + 1), smin(len + 1);
    smax[len] = INT_MIN;
    smin[len] = INT_MAX;
    for (int i = len - 1; i >= 0; --i) {
        smax[i] = max(a[l + i], smax[i + 1]);
        smin[i] = min(a[l + i], smin[i + 1]);
    }
    int pmax = INT_MIN, pmin = INT_MAX;
    for (int k = 0; k + 1 < len; ++k) {
        int m = l + k;
        pmax = max(pmax, a[m]);
        pmin = min(pmin, a[m]);
        bool rightSmaller = smax[k + 1] < pmin;
        bool leftSmaller = pmax < smin[k + 1];
        if (pN <= m && rightSmaller) {
            solve_n(l, m);
            int x = solve_all(m + 1, r);
            merge_into(x, pN);
            return;
        }
        if (pN > m && leftSmaller) {
            solve_n(m + 1, r);
            int x = solve_all(l, m);
            merge_into(x, pN);
            return;
        }
    }
}

int main() {
    if (scanf("%d", &n) != 1) return 0;
    a.assign(n, 0);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

    pN = (int)(find(a.begin(), a.end(), n) - a.begin());
    stk.assign(n, vector<int>());
    posOf.assign(n, 0);
    at.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        stk[i] = {a[i]};
        posOf[i] = i;
        at[i] = i;
    }

    solve_n(0, n - 1);
    fputs(out.c_str(), stdout);
    return 0;
}
