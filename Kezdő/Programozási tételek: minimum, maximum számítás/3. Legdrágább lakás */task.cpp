/*
Megoldás lényege:
A kérdés csak az árról szól, ezért az alapterületet beolvassuk, de a döntésben nem használjuk. Egy menetben végigolvassuk a lakásokat, és tároljuk az eddigi legdrágább ár értékét és annak sorszámát. A csere csak szigorúan nagyobb ár esetén történik, így egyenlő áraknál a kisebb sorszámú lakás marad, ahogy a feladat kéri. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || A döntéshez csak az ár kell: a lakás alapterületét be kell olvasni, de a legdrágább kiválasztásában nem szerepel. ||
Hint 2: || Egy menetes maximumkiválasztás: tárold az eddigi legnagyobb árat és a hozzá tartozó sorszámot, és csak szigorúan nagyobb ár esetén frissítsd őket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int bestPrice = -1;
    int bestIdx = 1;
    for (int i = 1; i <= n; i++) {
        int area, price;
        cin >> area >> price;
        if (price > bestPrice) {
            bestPrice = price;
            bestIdx = i;
        }
    }

    cout << bestIdx << "\n";
    return 0;
}
