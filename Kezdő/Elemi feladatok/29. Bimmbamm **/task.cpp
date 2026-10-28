/*
Megoldás lényege: a sorszám ismeretében mindig egyértelmű, mit kellene az adott játékosnak mondania: a 15-tel osztható sorszámnál BUMM, a 3-mal osztható sorszámnál BIMM, az 5-tel osztható sorszámnál BAMM, minden más esetben SZAM. A bemondásokat sorban beolvassuk, és az első olyan sorszámot írjuk ki, ahol a bemondás nem egyezik a helyessel; ha nincs eltérés, a válasz 0. Az időigény O(N), N ≤ 1000 miatt ez bőven elég.
*/
/*
Hint 1: || Nem kell tárolni a bemondásokat: a helyes szó az 1-től induló sorszámból közvetlenül kiszámolható, a 3-mal, 5-tel és 15-tel való oszthatóság maradékkal eldönthető. ||
Hint 2: || Olvasd be a bemondásokat sorban, és a sorszámot minden lépésben növeld. Az első olyan i-nél, ahol a beolvasott szó más, mint a helyes, írd ki az i-t és fejezd be; ha végig egyezik, írj 0-t. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int hiba = 0;
    for (int i = 1; i <= n; i++) {
        string bemondas;
        cin >> bemondas;

        string helyes;
        if (i % 15 == 0) helyes = "BUMM";
        else if (i % 3 == 0) helyes = "BIMM";
        else if (i % 5 == 0) helyes = "BAMM";
        else helyes = "SZAM";

        if (bemondas != helyes) {
            hiba = i;
            break;
        }
    }

    cout << hiba << "\n";
    return 0;
}
