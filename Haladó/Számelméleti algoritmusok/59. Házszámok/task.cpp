/*
 * Bináris keresés a legnagyobb házszámra, amelyhez az 1..x számok számjegy-
 * szükséglete belefér a megadott készletbe.
 
Hint 1: || A válasz monotonnak tekinthető: ha 1..X még kirakható, akkor minden kisebb határ is kirakható. ||
Hint 2: || Emiatt bináris keresést lehet használni X-re, és egy ellenőrzésnél helyiértékenként kell megszámolni, hogy 1..X-ig hány darab kell az egyes számjegyekből. ||
Hint 3: || Az ellenőrző függvény legfontosabb része az, hogy a számjegyek darabszámát ne egyenként, hanem blokkosítva, a helyiértékek szerint számold. ||
*/

#include "../common.hpp"

static vector<__int128> need(long long x, int k) {
    vector<__int128> cnt(k, 0);
    for (long long p = 1; p <= x; p *= k) {
        long long cycle = p * k;
        long long high = x / cycle;
        long long cur = (x / p) % k;
        long long low = x % p;
        for (int d = 1; d < k; ++d) {
            cnt[d] += (__int128)high * p;
            if (cur > d) cnt[d] += p;
            else if (cur == d) cnt[d] += low + 1;
        }
        if (high > 0) {
            cnt[0] += (__int128)(high - 1) * p;
            if (cur > 0) cnt[0] += p;
            else cnt[0] += low + 1;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    vector<long long> supply(k);
    for (int i = 0; i < k; ++i) cin >> supply[i];
    auto ok = [&](long long x) {
        auto cnt = need(x, k);
        for (int i = 0; i < k; ++i) if (cnt[i] > supply[i]) return false;
        return true;
    };
    long long lo = 0, hi = 1;
    while (ok(hi)) {
        if (hi > (long long)4e18 / 2) break;
        hi *= 2;
    }
    while (lo < hi) {
        long long mid = lo + (hi - lo + 1) / 2;
        if (ok(mid)) lo = mid; else hi = mid - 1;
    }
    cout << lo << '\n';
    return 0;
}
