/*
Megoldás lényege:
Ha a játékfajták darabszáma c_1, ..., c_k, akkor a különböző napok száma Π (c_i + 1), vagyis n az f_i = c_i + 1 ≥ 2 tényezők szorzata, a játékok száma pedig Σ (f_i − 1). Így az n összes (rendezetlen) szorzattá bontásán kell végigmenni, és a különböző összegeket összegyűjtve, rendezve kiírni. A bontásokat nemcsökkenő tényezőkkel, visszalépéses kereséssel járjuk be az osztók előre kiszámított listáit használva, és csak azokat az ágakat vizsgáljuk, ahol a maradék nagyobb vagy egyenlő a következő tényező négyzetével. Az összegeket nyílt címzésű halmazban gyűjtjük, mert a bontások száma jóval nagyobb lehet, mint a különböző összegeké. Az n = 1 eset az üres szorzat: 0 játék.
*/
/*
Hint 1: || A feltétel szerint a különböző napok száma pontosan Π (c_i + 1), ahol c_i ≥ 1 a játékfajták darabszáma; így a napok száma egy szorzattá bontás tényezőiből (f_i = c_i + 1) adódik, a játékok száma pedig Σ (f_i − 1). ||
Hint 2: || Ezért minden szorzattá bontáshoz egy játékszám tartozik, és a feladat az n összes bontásából kapható különböző összegek felsorolása, növekvő sorrendben. ||
Hint 3: || A bontásokat n osztóira építve, nemcsökkenő tényezőkkel generáld; egy tényező után csak akkor folytasd a rekurziót, ha a maradék legalább a tényező négyzete, különben a maradék egyetlen tényezőként már lezárja a bontást. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int u32;

// D: all divisors of n in increasing order (D[0] = 1).
// A factor f of D[r] (f >= 2) is stored with the index of D[r]/f and the index of f.
struct Fac {
    u32 f;    // the factor value
    u32 q;    // index of D[r] / f in D
    u32 fi;   // index of f in D
};

static vector<ll> D;
static vector<vector<Fac>> fac;       // fac[r]: factors of D[r] in increasing order; the last one is D[r] itself
static vector<vector<u32>> startPos;  // startPos[r][j]: first position in fac[r] whose factor is >= D[j]

// Set of achieved toy totals (open addressing; the stored value is value + 1, 0 means empty).
static vector<u32> table;
static size_t tableCount = 0;
static bool hasZero = false;

static inline size_t slotOf(u32 x, size_t mask) {
    return ((size_t)(x * 2654435761u)) & mask;
}
static void growTable(size_t newSize) {
    vector<u32> old;
    old.swap(table);
    table.assign(newSize, 0u);
    size_t mask = newSize - 1;
    for (u32 v : old) {
        if (!v) continue;
        size_t h = slotOf(v - 1, mask);
        while (table[h]) h = (h + 1) & mask;
        table[h] = v;
    }
}
static void addTotal(u32 x) {
    if (x == 0) {
        hasZero = true;
        return;
    }
    if ((tableCount + 1) * 2 > table.size()) growTable(table.empty() ? (1u << 12) : table.size() * 2);
    size_t mask = table.size() - 1;
    size_t h = slotOf(x, mask);
    for (;;) {
        u32 v = table[h];
        if (v == 0) {
            table[h] = x + 1;
            tableCount++;
            return;
        }
        if (v == x + 1) return;
        h = (h + 1) & mask;
    }
}

// Enumerates the factorizations of D[r] whose factors are >= D[j] (non-decreasing order,
// so every factorization is visited once). acc = sum of (f - 1) over the factors already chosen.
// A factor f can only be followed by further factors if D[r]/f >= f, so the loop stops at f*f > D[r].
static void walk(int r, int j, u32 acc) {
    const vector<Fac>& L = fac[r];
    size_t last = L.size() - 1;
    size_t k = startPos[r][j];
    if (k > last) return;
    ll R = D[r];
    for (; k < last; k++) {
        ll f = L[k].f;
        if (f * f > R) break;
        walk((int)L[k].q, (int)L[k].fi, acc + (u32)(f - 1));
    }
    addTotal(acc + (u32)(R - 1));   // the single remaining factor D[r] itself
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;
    cin >> n;
    if (n == 1) {                    // the empty factorization: Johnny has no toys
        cout << "1\n0\n";
        return 0;
    }
    for (ll d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            D.push_back(d);
            if (d != n / d) D.push_back(n / d);
        }
    }
    sort(D.begin(), D.end());
    int m = (int)D.size();
    fac.assign(m, {});
    for (int r = 0; r < m; r++) {
        for (int k = 1; k < m && D[k] <= D[r]; k++) {
            if (D[r] % D[k] == 0) {
                ll q = D[r] / D[k];
                int qi = (int)(lower_bound(D.begin(), D.end(), q) - D.begin());
                fac[r].push_back({(u32)D[k], (u32)qi, (u32)k});
            }
        }
    }
    startPos.assign(m, vector<u32>(m, 0));
    for (int r = 0; r < m; r++) {
        size_t p = 0;
        for (int j = 0; j < m; j++) {
            while (p < fac[r].size() && (ll)fac[r][p].f < D[j]) p++;
            startPos[r][j] = (u32)p;
        }
    }
    walk(m - 1, 1, 0);

    vector<u32> res;
    if (hasZero) res.push_back(0);
    for (u32 v : table)
        if (v) res.push_back(v - 1);
    sort(res.begin(), res.end());
    string out = to_string(res.size()) + "\n";
    for (size_t i = 0; i < res.size(); i++) {
        if (i) out += ' ';
        out += to_string(res[i]);
    }
    out += "\n";
    cout << out;
    return 0;
}
