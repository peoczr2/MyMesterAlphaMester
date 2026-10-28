/*
Megoldás lényege:
A gyártók neveit sorszámuk szerint tároljuk. Minden feljegyzésnél a gyártó sorszámát (az első számot) használjuk, és a harmadik szám, a kiadott konzolok száma, a gyártó összegéhez adódik. A generáció (a középső szám) a számláláshoz nem kell, mert egy gyártóhoz és generációhoz csak egy feljegyzés tartozik.
A végén a két megadott gyártó összegét hasonlítjuk össze: egyenlőség esetén „EGYEZIK”, különben a nagyobb összegű gyártó neve kerül a kimenetre. Az időigény O(N + M).
*/
/*
Hint 1: || A kérdés a gyártó összes konzolszámára vonatkozik, a generációtól függetlenül. Melyik mező adja a gyártó sorszámát és melyik a konzolok számát a feljegyzésben? ||
Hint 2: || Egy feljegyzés beolvasása után az első számmal azonosítsd a gyártót, és a harmadik számot add hozzá az összegéhez. A két megadott gyártó összegét a végén hasonlítsd össze, egyenlőség esetén EGYEZIK a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> nev(n + 1);
    for (int i = 1; i <= n; i++) {
        getline(cin, nev[i]);
        while (!nev[i].empty() && isspace((unsigned char)nev[i].back())) {
            nev[i].pop_back();
        }
    }

    int m;
    cin >> m;
    vector<long long> osszeg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int sorszam, generacio;
        long long darab;
        cin >> sorszam >> generacio >> darab;
        osszeg[sorszam] += darab;
    }

    int gy1, gy2;
    cin >> gy1 >> gy2;

    if (osszeg[gy1] == osszeg[gy2]) {
        cout << "EGYEZIK\n";
    } else if (osszeg[gy1] > osszeg[gy2]) {
        cout << nev[gy1] << "\n";
    } else {
        cout << nev[gy2] << "\n";
    }
    return 0;
}
