/*
Megoldás lényege:
Három szín áll rendelkezésre: F, P, Z. A megengedett átmenetek:
- F után bármi jöhet,
- P után csak F jöhet,
- Z után nem jöhet Z.

Ez egy 3 állapotú lineáris DP, amelyet modulo 20160109 számolunk.
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
        long long nf = (f + p + z) % MOD;
        long long np = (f + z) % MOD;
        long long nz = f % MOD;
        f = nf;
        p = np;
        z = nz;
    }

    cout << (f + p + z) % MOD << '\n';
    return 0;
}