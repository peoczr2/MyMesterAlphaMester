/*
Megoldás lényege:
A feladat nem adja meg a pontos diplomázási napot, csak a végzés évét, ezért a diplomázáskori életkort a végzés éve és a születési év különbségeként számoljuk. Egyetlen bejárással minden végzetthez kiszámítjuk ezt a különbséget, és megtartjuk a legkisebbet a hozzá tartozó születési dátummal. Egyenlőség esetén a szigorú összehasonlítás miatt a bemenetben korábban szereplő végzett marad. Az időigény O(N), a tárigény O(1).
*/
/*
Hint 1: || A diplomázás pontos napját nem ismerjük, csak az évét. Gondold végig, melyik két megadott évszám különbsége adja az életkort a diplomázáskor, és hogyan lehet ebből a legkisebb értéket kiválasztani. ||
Hint 2: || Végigmenve a végzetteken minden sorra számold ki a végzés éve és a születési év különbségét, és tartsd nyilván a legkisebb különbséget a hozzá tartozó születési dátummal. Csak szigorú kisebb értéknél frissíts, így a bemenetben elsőként szereplő legfiatalabb marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int bestAge = INT_MAX;
    int by = 0, bm = 0, bd = 0;
    for (int i = 0; i < n; i++) {
        int y, m, d, k, v;
        cin >> y >> m >> d >> k >> v;
        int age = v - y;
        if (age < bestAge) {
            bestAge = age;
            by = y;
            bm = m;
            bd = d;
        }
    }
    cout << by << " " << bm << " " << bd << "\n";
    return 0;
}
