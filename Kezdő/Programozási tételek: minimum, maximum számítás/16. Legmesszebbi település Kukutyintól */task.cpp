/*
Megoldás lényege:
Minden településhez két távolság tartozik, de a kérdés csak a Kukutyintól mért K távolságra vonatkozik, ezért a Piripócstól mért P értéket beolvassuk, de nem használjuk. Egy menetben haladunk végig, és az eddigi legnagyobb K-t és annak sorszámát tartjuk nyilván. Szigorú nagyobb-összehasonlítással egyenlő távolság esetén a kisebb sorszám marad, ahogy a feladat kéri. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || A feladat csak a Kukutyintól mért távolságot kérdezi, a Piripócstól mért adat a megoldást nem befolyásolja. ||
Hint 2: || Egyetlen menetes maximumkiválasztás: tartsd nyilván a legnagyobb K értéket és annak sorszámát, és csak szigorúan nagyobb értéknél írd felül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int bestIndex = 1;
    int bestDist = INT_MIN;
    for (int i = 1; i <= n; i++) {
        int k, p;
        cin >> k >> p;
        if (k > bestDist) {
            bestDist = k;
            bestIndex = i;
        }
    }

    cout << bestIndex << "\n";

    return 0;
}
