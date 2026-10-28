/*
Megoldás lényege:
Követjük, hány utas van a vonaton az adott állomás előtt: ez kezdetben 0, és minden állomás után változik a felszállók és leszállók különbségével.
Egy állomáson akkor szálltak volna le többen, mint ahányan a vonaton voltak, ha a leszállók száma nagyobb, mint az állomás előtti utaslétszám. Ezt egy bejárásban minden állomásra ellenőrizzük.
Ha van ilyen állomás, a válasz 1, különben 0. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Az állomás előtt a vonaton lévő utasok számát kell tudni az adott állomáson, a leszállás előtt. Ezt az előző állomások felszállóiból és leszállóiból lehet kiszámolni. ||
Hint 2: || Tartsd nyilván a vonaton lévő utasok számát: minden állomás után add hozzá a felszállókat, és vond ki a leszállókat. Közben minden állomásnál hasonlítsd össze a leszállók számát az akkori utaslétszámmal. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long onTrain = 0;
    bool found = false;
    for (int i = 0; i < n; i++) {
        long long le, fel;
        cin >> le >> fel;
        if (le > onTrain) found = true;
        onTrain += fel - le;
    }

    cout << (found ? 1 : 0) << "\n";
    return 0;
}
