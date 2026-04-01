/*
 * A középpontos N-szögszám képlete modulo 1 000 000.
 
Hint 1: || A középpontos sokszögszámokra is van közvetlen képlet, itt sem érdemes iteratívan építkezni. ||
Hint 2: || Ha leírod az első néhány értéket, felismerhető, hogy az `1 + N*i*(i-1)/2` alakú formula adja a keresett számot. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long i, n;
    cin >> i >> n;
    const long long MOD = 1000000;
    long long ans = 1 + n * i * (i - 1) / 2;
    cout << (ans % MOD + MOD) % MOD << '\n';
    return 0;
}
