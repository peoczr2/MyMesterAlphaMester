/*
A természetes számokat növekvő sorrendben végignézzük, és minden számnál megvizsgáljuk a kettes alakjában lévő 1-es bitek számának paritását.
Ha az 1-es bitek száma páratlan, a számlálót eggyel növeljük; amikor a számláló eléri i-t, az aktuális szám a keresett válasz.
Az 1-es bitek számát a beépített popcount adja meg, így egy szám ellenőrzése konstans időt vesz igénybe.
A páratlan popcountú számok sűrűsége 1/2, ezért az i-edik ilyen szám nagyjából 2i, a keresés i ≤ 10^6 esetén kb. 2·10^6 lépés.
*/
/*
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
