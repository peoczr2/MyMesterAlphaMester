/*
 * A duplakeverés a permutáció négyzetre emelése. Mivel N páratlan, a megfelelő
 * kitevő inverze létezik modulo N, így visszaemeljük az eredeti permutációt.
 
Hint 1: || A duplakeverés valójában a permutáció önmagával vett kompozíciója, vagyis négyzetre emelése. ||
Hint 2: || Ha S-szer négyzetre emelt permutációt kaptál, akkor modulo a ciklushosszak szerint vissza kell emelned az eredeti permutációt. ||
Hint 3: || A ciklusokban minden elem külön-külön mozog, ezért elég minden ciklusra kiszámolni, hány lépéssel kell visszaforgatni a keverést. ||
*/

#include "../common.hpp"

static vector<int> compose(const vector<int>& a, const vector<int>& b) {
    int n = (int)a.size() - 1;
    vector<int> c(n + 1);
    for (int i = 1; i <= n; ++i) c[i] = a[b[i]];
    return c;
}

static vector<int> power_perm(vector<int> a, long long e) {
    int n = (int)a.size() - 1;
    vector<int> r(n + 1);
    iota(r.begin(), r.end(), 0);
    while (e > 0) {
        if (e & 1) r = compose(a, r);
        a = compose(a, a);
        e >>= 1;
    }
    return r;
}

static long long mod_pow(long long a, long long e, long long mod) {
    long long r = 1 % mod;
    while (e > 0) {
        if (e & 1) r = (__int128)r * a % mod;
        a = (__int128)a * a % mod;
        e >>= 1;
    }
    return r;
}

static long long mod_inv(long long a, long long mod) {
    long long b = mod, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= mod;
    if (u < 0) u += mod;
    return u;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s;
    cin >> n >> s;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) cin >> p[i];
    long long e = mod_pow(2, s, n);
    long long inv = mod_inv(e, n);
    auto x = power_perm(p, inv);
    for (int i = 1; i <= n; ++i) cout << x[i] << '\n';
    return 0;
}
