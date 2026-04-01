/*
Megoldás lényege:
Három szín áll rendelkezésre: F, P, Z. A megengedett átmenetek:
- F után csak P jöhet,
- Z után nem jöhet P,
- P után bármi jöhet.

Ez ismét egy 3 állapotú DP, modulo 20160109.
*/

#include <bits/stdc++.h>
using namespace std;

static const int MOD = 20160109;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    long long f = 1, p = 1, z = 1;
    for (int i = 2; i <= n; ++i) {
        long long nf = (p + z) % MOD;
        long long np = (f + p) % MOD;
        long long nz = (f + z) % MOD;
        f = nf;
        p = np;
        z = nz;
    }

    cout << (f + p + z) % MOD << '\n';
    return 0;
}