/*
Megoldás lényege:
Minden verseny időeredményét egyetlen számmá alakítjuk másodpercekre: perc·60 + másodperc. A versenyeken egy menetben haladunk, és az eddigi legjobb időt, valamint a hozzá tartozó legjobb helyezést tartjuk nyilván. Ha az aktuális idő kisebb, mindkettőt frissítjük; ha egyenlő, a kisebb helyezést tartjuk meg, mert a feladat a legjobb időhöz tartozó legjobb helyezést kéri. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || A versenyek összehasonlításához elég egyetlen szám: az időeredmény másodpercben kifejezve. ||
Hint 2: || Egy menetben haladj végig a versenyeken, és tartsd nyilván az eddigi legjobb időt és a hozzá tartozó helyezést; egyenlő időnél a kisebb helyezés legyen az érvényes. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int bestTime = INT_MAX;
    int bestPlace = INT_MAX;
    for (int i = 0; i < n; i++) {
        int h, p, mp;
        cin >> h >> p >> mp;
        int t = p * 60 + mp;
        if (t < bestTime || (t == bestTime && h < bestPlace)) {
            bestTime = t;
            bestPlace = h;
        }
    }

    cout << bestPlace << "\n";
    return 0;
}
