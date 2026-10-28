/*
Megoldás lényege:
A feladat azoknak a hallgatóknak a számát kérdezi, akiknek a röpzárthelyi pontszáma 10-nél kisebb. Elég egyetlen menetben beolvasni a pontszámokat, és minden olyan esetben növelni egy számlálót, amikor a pontszám kisebb 10-nél. Tömbben nincs szükség a pontok tárolására, mert a döntés minden pontszámnál azonnal meghozható. Az időigény O(N), ami az N ≤ 99 korlát mellett bőven elég. Az N = 0 esetben a ciklus nem fut le, és a kimenet 0 lesz.
*/
/*
Hint 1: || Egyetlen ciklus elég: a pontszámokat egyesével olvasd be, és minden pontszámnál döntsd el, hogy teljesíti-e a feltételt. ||
Hint 2: || A feltétel: a pontszám kisebb 10-nél, azaz r < 10. Egy számlálóban összegezd a feltételnek megfelelő hallgatókat, és a végén ezt írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int db = 0;
    for (int i = 0; i < n; i++) {
        int r;
        cin >> r;
        if (r < 10) db++;
    }

    cout << db << '\n';

    return 0;
}
