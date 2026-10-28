/*
Megoldás lényege:
A legidősebb ember az, aki legkorábban született, ezért ez egy maximumkiválasztás az életkor szerint, ami a születési dátum szerinti minimumkiválasztással egyenértékű. A dátumot egyetlen számmá alakítjuk: év·10000 + hónap·100 + nap, így két dátum időrendje egyszerű számösszehasonlítással eldönthető. Egy menetben végigmegyünk az embereken, és tároljuk az eddigi legkorábbi dátumot és annak sorszámát. Csak szigorúan korábbi dátumnál cserélünk, így egyenlő dátumnál a kisebb sorszám marad. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Az idősebb az, aki korábban született: két dátumnál előbb az évet, majd a hónapot, végül a napot kell összevetni. ||
Hint 2: || Egy menetben haladj végig az embereken, és tartsd nyilván az eddigi legkorábbi dátumot és a hozzá tartozó sorszámot; csak szigorúan korábbi dátumnál frissíts. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int legkorabbi = INT_MAX;
    int legidosebb = 1;
    for (int i = 1; i <= n; i++) {
        int ev, honap, nap;
        cin >> ev >> honap >> nap;
        int datum = ev * 10000 + honap * 100 + nap;
        if (datum < legkorabbi) {
            legkorabbi = datum;
            legidosebb = i;
        }
    }

    cout << legidosebb << "\n";
    return 0;
}
