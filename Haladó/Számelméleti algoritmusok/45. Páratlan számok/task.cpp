/*
 * Az i. szám, amelynek kettes alakjában páratlan számú 1-bit van.
 
Hint 1: || A feladat csak a bitek darabszámának paritásáról szól, ezért a `popcount` a legfontosabb művelet. ||
Hint 2: || Növeld sorban a számokat, és csak azokat számold bele, amelyeknél a bináris 1-es bitek száma páratlan. ||
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
        if (__builtin_popcountll((unsigned long long)x) % 2 == 1) ++cnt;
    }
    cout << x << '\n';
    return 0;
}
