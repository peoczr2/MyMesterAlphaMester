/*
 * Az i. olyan szám, amelynek bináris alakjában páros számú 1-bit van.
 
Hint 1: || Itt is a `popcount` a lényeg, csak most a páros darabszámú 1-biteket kell keresni. ||
Hint 2: || Növeld sorban a természetes számokat, és akkor növeld a számlálót, ha a bináris alak 1-eseinek száma páros. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 i;
    cin >> i;
    int64 x = 0, cnt = 0;
    while (cnt < i) {
        ++x;
        if (__builtin_popcountll((unsigned long long)x) % 2 == 0) ++cnt;
    }
    cout << x << '\n';
    return 0;
}
