/*
Megoldás lényege:
Az i. középpontos N-szögszám zárt alakban adódik: 1 + N * i * (i - 1) / 2. Az
i legfeljebb 10^8, így az N * i * (i - 1) szorzat 64 bites egészben túlcsordulna.
Ezért előbb a háromszögszám-jellegű i * (i - 1) / 2 részt számoljuk ki és vesszük
modulo 10^6, utána szorzunk N-nel (N <= 1000). A művelet ideje O(1).
*/
/*
Hint 1: || Nem kell sorozatot építgetni, a keresett szám közvetlenül kiszámolható egy képlettel. ||
Hint 2: || Az első néhány értékből felismerhető, hogy az i-edik szám 1 + N * (i * (i - 1) / 2) alakú, a zárójeles részt viszont a szorzás előtt érdemes modulo 1 000 000 vennie. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long i, n;
    cin >> i >> n;
    const long long MOD = 1000000;
    long long tri = (i * (i - 1) / 2) % MOD;
    cout << (1 + n * tri) % MOD << '\n';
    return 0;
}
