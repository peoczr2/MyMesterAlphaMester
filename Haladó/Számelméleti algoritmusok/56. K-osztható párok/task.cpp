/*
 * Párok száma, melyek összege osztható K-val.
 
Hint 1: || Egy pár összege akkor osztható K-val, ha a két szám maradéka `r` és `K-r`. ||
Hint 2: || Előbb számold meg, hány elem esik az egyes maradékosztályokba, aztán ezekből kombinatorikusan add össze a jó párok számát. ||
Hint 3: || A `0` és `K/2` osztályok külön esetek, mert ott ugyanaz a maradék párosítható önmagával is. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> cnt(k);
    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        ++cnt[x % k];
    }
    long long ans = cnt[0] * (cnt[0] - 1) / 2;
    for (int r = 1; r * 2 < k; ++r) ans += cnt[r] * cnt[k - r];
    if (k % 2 == 0) ans += cnt[k / 2] * (cnt[k / 2] - 1) / 2;
    cout << ans << '\n';
    return 0;
}
