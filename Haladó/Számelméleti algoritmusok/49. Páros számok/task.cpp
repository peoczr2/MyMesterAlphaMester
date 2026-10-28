/*
Megoldás lényege:
Az 1-től kezdve sorban végigmegyünk a számokon, és mindegyikben a __builtin_popcountll függvénnyel megszámoljuk a bináris alakjában lévő 1-eseket. Ha ez a szám páros, a számlálót eggyel növeljük; amint a számláló eléri i-t, az éppen vizsgált szám a keresett érték. A 0-t kihagyjuk, mert a feladatban a természetes számok 1-től indulnak. Az ilyen számok aránya kb. 1/2, így az i-edik szám közelítőleg 2i, és a futásidő O(i), ami i ≤ 1 000 000 esetén gyors.
*/
/*
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
