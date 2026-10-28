/*
Megoldás lényege:
Egy menetben végigmegyünk a napi hőmérsékleteken, és tároljuk az eddigi legmagasabb értéket és annak sorszámát. Csak akkor cseréljük a tárolt eredményt, ha az aktuális érték szigorúan nagyobb, így egyenlő hőmérsékletnél az első előfordulás marad, ahogy a feladat kéri. Nem kell a teljes sorozatot eltárolni. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egyetlen maximumkiválasztás kell: elég az eddigi legjobb értéket és a hozzá tartozó sorszámot megtartani. ||
Hint 2: || A sorszámot 1-től számold, a csere feltétele pedig legyen szigorú (>), így egyenlő hőmérsékletnél az első nap marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int bestIndex = 1;
    int bestTemp = INT_MIN;
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        if (t > bestTemp) {
            bestTemp = t;
            bestIndex = i;
        }
    }

    cout << bestIndex << "\n";

    return 0;
}
