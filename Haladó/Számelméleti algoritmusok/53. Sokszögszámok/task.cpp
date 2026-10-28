/*
Megoldás lényege:
Az i-edik N-szögszám zárt képlettel számolható: P(N, i) = ((N - 2) * i^2 - (N - 4) * i) / 2. Nem kell sorban generálni az előző értékeket, elég egyetlen képletet kiértékelni. Mivel i legfeljebb 10^6 és N legfeljebb 1000, a számláló nagysága körülbelül 10^15, ami 64 bites egésszel még elfér. A számláló az osztás előtt mindig páros, így az eredmény egész; a végén 1 000 000 szerinti maradékot írunk ki. Az idő O(1).
*/
/*
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
