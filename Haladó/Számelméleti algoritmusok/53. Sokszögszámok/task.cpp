/*
 * Az i. N-szögszám modulo 1 000 000.
 
Hint 1: || Az N-szögszámokra van zárt képlet, ezért nem kell sorban generálni az összes előző értéket. ||
Hint 2: || Írd fel az `i`-edik N-szögszám képletét, majd csak a végén vedd az eredményt `1 000 000` mod szerint. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long i, n;
    cin >> i >> n;
    const long long MOD = 1000000;
    long long ans = (i * i * (n - 2) - i * (n - 4)) / 2;
    cout << (ans % MOD + MOD) % MOD << '\n';
    return 0;
}
