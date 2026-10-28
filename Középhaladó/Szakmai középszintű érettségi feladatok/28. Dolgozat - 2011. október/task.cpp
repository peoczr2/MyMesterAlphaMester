/*
Megoldás lényege:
A maximális pontszám 50, ezért a százalékos eredmény egyszerűen a pontszám * 100 / 50 egész szám. Az érdemjegyet a küszöbök alapján döntjük el: 85% felett 5-ös, 70%-tól 4-es, 55%-tól 3-as, 40%-tól 2-es, különben 1-es. Minden tanulónál ezt azonnal kiírjuk, a pontszámokat nem kell eltárolni. Az átlaghoz a pontok összegét 64 bites egészben gyűjtjük, majd az átlagot félértéknél felfelé kerekítve írjuk ki: (2 * összeg + N) / (2 * N) egész osztással. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || A maximum 50 pont 100 százaléknak felel meg, így a százalék a pontszámból arányosan számolható. Az érdemjegyhez a küszöböket a legmagasabbtól lefelé ellenőrizd, így az első teljesülő feltétel dönt. ||
Hint 2: || Az átlaghoz nem kell a pontokat tárolni, elég az összegüket nyilvántartani. Az egészre kerekítést egész számokkal oldd meg: a (2 * összeg + N) / (2 * N) kifejezés adja a félértéknél felfelé kerekített átlagot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    long long osszeg = 0;
    cout << "#\n";
    for (int i = 0; i < n; i++) {
        int pont;
        cin >> pont;
        osszeg += pont;

        int szazalek = pont * 100 / 50;
        int jegy;
        if (szazalek >= 85) jegy = 5;
        else if (szazalek >= 70) jegy = 4;
        else if (szazalek >= 55) jegy = 3;
        else if (szazalek >= 40) jegy = 2;
        else jegy = 1;

        cout << szazalek << " " << jegy << "\n";
    }

    long long atlag = (2 * osszeg + n) / (2 * n);
    cout << "#\n";
    cout << atlag << "\n";

    return 0;
}
