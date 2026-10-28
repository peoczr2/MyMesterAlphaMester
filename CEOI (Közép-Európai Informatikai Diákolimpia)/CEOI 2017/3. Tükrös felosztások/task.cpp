/*
Megoldás lényege:
A tükrös felosztás elemei szélről befelé párosával egyeznek meg, ezért a felosztást a szó két
végéről befelé építjük. Mindig a legrövidebb olyan k hosszú kezdőszeletet vesszük, amely
megegyezik a maradék szó k hosszú végszeletével: így két elemet kapunk, és a középső szóra
ugyanezt a feladatot oldjuk meg. Ha nincs ilyen egyező szeletpár, a maradék egyetlen középső
elem, ami +1. A szeletek egyenlőségét polinomiális hash-sel (2^61-1 modulus) konstans időben
ellenőrizzük. Mivel a keresés hossza az elvett szeletek összhosszával arányos, egy szó
feldolgozása O(N) időt igényel.
*/
/*
Hint 1: || A tükrös felosztás első és utolsó eleme egyezik, ezért a felosztást a szó két végéről befelé haladva építheted. ||
Hint 2: || Ha a maradék szó elején és végén áll egy k hosszú egyező szelet, ezek két elemet adnak, és a közé eső részre ugyanazt a feladatot kell megoldanod. Mindig a legkisebb ilyen k-t válaszd. ||
Hint 3: || Az egyező szeletek gyors összehasonlításához használj prefixum-hasht: egy véletlen alappal számolt hash megmutatja, hogy két részszó egyenlő-e konstans időben. Ha nincs egyező szeletpár, a maradék egy középső elem. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

const ull MOD = (1ULL << 61) - 1;

ull mulmod(ull a, ull b) {
    __uint128_t c = (__uint128_t)a * b;
    ull r = (ull)(c >> 61) + (ull)(c & MOD);
    if (r >= MOD) r -= MOD;
    if (r >= MOD) r -= MOD;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    mt19937_64 rng((ull)chrono::steady_clock::now().time_since_epoch().count());
    const ull B = rng() % (MOD - 1000) + 500;

    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        int n = (int)s.size();

        vector<ull> H(n + 1, 0), P(n + 1, 1);
        for (int i = 0; i < n; i++) {
            P[i + 1] = mulmod(P[i], B);
            H[i + 1] = (mulmod(H[i], B) + (ull)(unsigned char)s[i]) % MOD;
        }
        // hash of s[l, r)
        auto get = [&](int l, int r) -> ull {
            ull x = mulmod(H[l], P[r - l]);
            return (H[r] + MOD - x) % MOD;
        };

        long long ans = 0;
        int l = 0, r = n;
        while (l < r) {
            int len = r - l;
            int found = -1;
            for (int k = 1; 2 * k <= len; k++) {
                if (get(l, l + k) == get(r - k, r)) {
                    found = k;
                    break;
                }
            }
            if (found == -1) {
                ans += 1;
                break;
            }
            ans += 2;
            l += found;
            r -= found;
        }
        cout << ans << "\n";
    }
    return 0;
}
