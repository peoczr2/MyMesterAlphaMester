/*
Megoldás lényege:
Nincs szükség a teljes N×M-es táblázat tárolására: a bemenetet soronként olvassuk, és minden település sorából kiszámoljuk a napi hőmérsékletek maximumát. Ezt hasonlítjuk az eddigi legnagyobb maximumhoz, és ha szigorúan nagyobb, megjegyezzük az aktuális település sorszámát. A szigorú összehasonlítás miatt holtverseny esetén a legkisebb sorszámú település marad. A K korlátot a számítás nem használja. Az időigény O(N·M), a memóriaigény O(1).
*/
/*
Hint 1: || Egy település eredménye csak a saját sorának maximumától függ, így a sorokat nem kell egyszerre tárolni. ||
Hint 2: || Soronként olvass be, és tartsd nyilván az eddigi legnagyobb maximumot és a hozzá tartozó település sorszámát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    int bestCity = 0;
    int bestMax = -1;
    for (int i = 1; i <= n; i++) {
        int rowMax = -1;
        for (int j = 0; j < m; j++) {
            int h;
            cin >> h;
            rowMax = max(rowMax, h);
        }
        if (rowMax > bestMax) {
            bestMax = rowMax;
            bestCity = i;
        }
    }

    cout << bestCity << "\n";
    return 0;
}
