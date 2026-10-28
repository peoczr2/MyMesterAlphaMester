/*
Megoldás lényege:
Egy állomáson az utasok száma pontosan akkor nő, ha a felszállók száma nagyobb a leszállókénál.
A feladat azt kérdezi, meddig tart ez a növekedés Budapesttől kezdve, ezért elölről haladunk, és az első olyan állomásnál megállunk, ahol a felszállók száma már nem nagyobb a leszállókénál.
Az utolsó még növekvő állomás sorszámát írjuk ki; ha már Budapesten sem nő az utasok száma, a kiírt érték 0.
Az adatokat egyszer olvassuk be, így az időigény O(N).
*/
/*
Hint 1: || Egy állomáson az utasok száma pontosan akkor nő, ha a felszállók száma nagyobb a leszállókénál. ||
Hint 2: || Budapesttől kezdve haladj előre, és tartsd meg az utolsó olyan sorszámot, ahol még teljesül a feltétel. A ciklust szakítsd meg az első állomásnál, ahol már nem teljesül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int eredmeny = 0;
    for (int i = 1; i <= n; i++) {
        int leszallo, felszallo;
        cin >> leszallo >> felszallo;
        if (felszallo > leszallo) {
            eredmeny = i;
        } else {
            break;
        }
    }
    cout << eredmeny << endl;
    return 0;
}
