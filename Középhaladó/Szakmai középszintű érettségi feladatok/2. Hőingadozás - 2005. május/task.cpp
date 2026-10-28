/*
Megoldás lényege:
A hőingadozás a legnagyobb és a legkisebb mért érték különbsége, ezért nem kell az összes mérést eltárolni. A beolvasás közben két változóban nyilvántartjuk az eddig látott legnagyobb és legkisebb értéket, és minden új mérésnél frissítjük őket. A két változót az első mérés értékével indítjuk, mert a hőmérséklet lehet negatív, így a nulla nem lenne biztonságos kezdőérték. A végén a legnagyobb és a legkisebb érték különbsége a válasz. Az időigény O(N), a memóriaigény O(1), ahol N legfeljebb 10^6.
*/
/*
Hint 1: || Nem kell az összes értéket eltárolni: elég két változó, amelyben az eddig látott legnagyobb, illetve legkisebb értéket tartod nyilván. ||
Hint 2: || A két változót az első beolvasott értékkel indítsd, majd a további N-1 értéknél egyszerre frissítsd őket. A végén a különbségük a keresett szám. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int legnagyobb, legkisebb;
    cin >> legnagyobb;
    legkisebb = legnagyobb;

    for (int i = 1; i < n; i++) {
        int h;
        cin >> h;
        legnagyobb = max(legnagyobb, h);
        legkisebb = min(legkisebb, h);
    }

    cout << legnagyobb - legkisebb << "\n";
    return 0;
}
