/*
Megoldás lényege:
Minden településre ugyanannyi (M) előrejelzés van, ezért az átlagok rangsora megegyezik az összegek rangsorával: nem kell osztani, elég az összegeket összehasonlítani. Soronként beolvassuk a település előrejelzéseit, összeadjuk őket, és közben nyilvántartjuk az eddigi legnagyobb összeget és annak sorszámát. Csak szigorúan nagyobb összegnél frissítünk, így azonos összeg esetén a kisebb sorszám marad meg, ahogy a feladat kéri. A futásidő O(N·M), ami legfeljebb 10^6 összeadás.
*/
/*
Hint 1: || Mivel minden településre ugyanannyi, M előrejelzés tartozik, az átlag akkor a legnagyobb, ha az összeg a legnagyobb; így nincs szükség osztásra. ||
Hint 2: || Soronként olvasd be a település előrejelzéseit és add össze őket, közben egy változóban tartsd az eddigi legnagyobb összeget és a hozzá tartozó sorszámot; csak szigorúan nagyobb összegnél írd felül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int k; // a hőmérséklet-korlát (K) a számoláshoz nem kell, csak be kell olvasni
    cin >> k;

    int legjobb_sorszam = 1;
    int legjobb_osszeg = -1;

    for (int i = 1; i <= n; ++i) {
        int osszeg = 0;
        for (int j = 0; j < m; ++j) {
            int h;
            cin >> h;
            osszeg += h;
        }
        if (osszeg > legjobb_osszeg) {
            legjobb_osszeg = osszeg;
            legjobb_sorszam = i;
        }
    }

    cout << legjobb_sorszam << '\n';
    return 0;
}
