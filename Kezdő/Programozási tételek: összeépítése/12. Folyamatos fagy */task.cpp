/*
Megoldás lényege:
Egy nap akkor fagyos, ha a napi maximum hőmérséklete negatív, mert így egész nap fagypont alatt van. Balról
jobbra haladva számoljuk az egymás utáni fagyos napokat. Ha a számláló eléri K-t, az aktuális nap a keresett
K napos szakasz utolsó napja, az első nap pedig K-1 nappal korábbi. Az első ilyen találatnál megállunk, így
ez a legkorábbi szakasz. Az időigény O(N).
*/
/*
Hint 1: || Egy nap fagyos, ha a napi maximum hőmérséklete negatív. A napi minimum most nem számít. ||
Hint 2: || Haladj a napokon balról jobbra, és számold az egymás utáni fagyos napok hosszát. Ha a hossz eléri K-t, ott van a keresett szakasz, és az első ilyen találat adja a választ. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    int run = 0; // az aktuális nap végéig tartó egymás utáni fagyos napok száma
    for (int i = 0; i < n; i++) {
        int lo, hi;
        cin >> lo >> hi;
        run = (hi < 0) ? run + 1 : 0;
        if (run == k) {
            // a szakasz a (i - k + 1). naptól az (i + 1). napig tart (1-tól számozva)
            cout << i - k + 2 << ' ' << i + 1 << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
    return 0;
}
