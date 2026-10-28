/*
Megoldás lényege:
Egy négyzet területe az oldalhosszának négyzete, így a gazda összterülete a földek szélességeinek négyzeteinek összege. Az első sorban álló K után K számot olvasunk be, mindegyiket négyzetre emeljük, és egy összegző változóhoz adjuk. Minden földet pontosan egyszer dolgozunk fel, ezért az időigény O(K), ami K ≤ 100 esetén gyorsan lefut. A szélesség legfeljebb 1000, így az összeg legfeljebb 100 · 10^6 = 10^8, ez long long típusban biztosan elfér.
*/
/*
Hint 1: || Nincs szükség az összes szélesség eltárolására: egy négyzet területe az oldal hosszának négyzete, tehát elég egy összegző változó. ||
Hint 2: || Egy ciklusban K-szor olvass be egy egész számot, és minden körben add hozzá az értéke négyzetét az összeghez. Az összeg típusa long long legyen. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int k;
    cin >> k;

    long long osszeg = 0;
    for (int i = 0; i < k; i++) {
        long long szelesseg;
        cin >> szelesseg;
        osszeg += szelesseg * szelesseg;
    }

    cout << osszeg << "\n";
    return 0;
}
