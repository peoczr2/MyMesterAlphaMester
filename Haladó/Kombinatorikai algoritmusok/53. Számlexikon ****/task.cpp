/*
Megoldás lényege: a K szám pozíciója (Q_{N,K}) az 1..N számok lexikografikus
sorrendjében nem csökken, ha N nő, ezért a legkisebb N-et bináris kereséssel
keressük. Q_{N,K} megszámolása: azon x <= N számok száma, amelyekre str(x) <= str(K).
Ezek a K prefixei, plusz azok a számok, amelyek a K-val közös prefix után kisebb
számjegynél térnek el; egy p prefixszel kezdődő, L hosszú számok egy
[p*10^(L-|p|), (p+1)*10^(L-|p|)-1] intervallumot alkotnak, így az N-nél nem nagyobb
darabszám egyszerűen összeadható. Egy lekérdezés O(log N * jegyek^2 * 10) műveletet
igényel, így T <= 10 000 mellett bőven belefér a 0,2 másodpercbe.
*/
/*
Hint 1: || Q_{N,K} növekvő N-ben, ezért a „legalább P” feltétel bináris kereséssel kezelhető. A felső korlátot duplázással találhatod meg. ||
Hint 2: || Q_{N,K} = #{x <= N : str(x) <= str(K)}. Ide tartoznak K prefixei, és azok a számok, amelyek a K-val közös prefix után egy kisebb számjegynél térnek el. ||
Hint 3: || Egy adott p prefixszel kezdődő, L hosszú számok a [p*10^(L-|p|), (p+1)*10^(L-|p|)-1] intervallumban vannak, így az N-nél nem nagyobbak számát min-műveletekkel kapod meg, minden L-re. ||
*/
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using i128 = __int128_t;

static ull prefixCount(ull pref, ull N) {
    ull next = pref + 1;
    ull cnt = 0;
    while (pref <= N) {
        cnt += (ull)(min<i128>((i128)N + 1, (i128)next) - pref);
        pref *= 10;
        next *= 10;
    }
    return cnt;
}

static ull rankOf(ull N, ull K) {
    string s = to_string(K);
    ull rank = 0;
    ull pref = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (i > 0) ++rank;
        int cur = s[i] - '0';
        int start = (i == 0 ? 1 : 0);
        for (int d = start; d < cur; ++d) {
            ull p = pref * 10 + d;
            if (p <= N) rank += prefixCount(p, N);
        }
        pref = pref * 10 + cur;
    }
    ++rank;
    return rank;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        ull K, P;
        cin >> K >> P;

        ull lo = K, hi = K;
        if (rankOf(hi, K) < P) {
            while (hi < (ull)4e18 && rankOf(hi, K) < P) {
                hi = hi * 2 + 1;
            }
        }
        if (rankOf(hi, K) < P) {
            cout << 0 << '\n';
            continue;
        }
        while (lo < hi) {
            ull mid = lo + (hi - lo) / 2;
            if (rankOf(mid, K) >= P) hi = mid;
            else lo = mid + 1;
        }
        if (rankOf(lo, K) == P) cout << lo << '\n';
        else cout << 0 << '\n';
    }
    return 0;
}