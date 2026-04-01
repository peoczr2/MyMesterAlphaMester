/*
   Számlexikon: megkeressük azt a legkisebb N-et, amelyre a K szám a P-edik
   helyen áll az 1..N számok lexikografikus sorrendjében.
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