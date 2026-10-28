/*
Megoldás lényege:
A bemenet számait egész számokként olvassuk be, amíg van adat, és közben összegezzük az összes számot, valamint külön a páratlanok összegét és darabszámát. Az átlag az összeg és az elemszám hányadosa, amelyet kilenc tizedesjegyre írunk ki, így a kimenet a mintával pontosan egyezik. A leghosszabb szigorúan növekvő összefüggő részsorozatot egy menetben keressük: az aktuális szakasz hosszát és kezdőindexét tartjuk nyilván, és a szakasz csak akkor kerül frissítésre, ha a hossza szigorúan nagyobb a korábbinál, így döntetlen esetén a legkorábbi kezdet marad meg. Az időigény O(N), a memóriaigény O(N), ahol N a számok száma.
*/
/*
Hint 1: || Egy szám akkor páratlan, ha kettővel osztva 1 maradékot ad. A számok darabszáma, a páratlanok összege és darabszáma, valamint az összes szám összege egyetlen bejárással kiszámolható. ||
Hint 2: || Az átlagnál az összeget kell elosztani az elemszámmal, de ügyelj rá, hogy az osztás valós számokkal történjen, különben egész osztást kapsz. A tizedesjegyek számát a kiírás előtt állítsd be, például a fixed és a setprecision függvényekkel. ||
Hint 3: || A leghosszabb részsorozatnál tartsd nyilván az aktuális növekvő szakasz hosszát és kezdőindexét: ha az aktuális szám nagyobb az előzőnél, a szakasz nő, különben új szakasz kezdődik az aktuális indexnél. A legjobb értéket csak szigorúan nagyobb hossznál írd felül, így a legkorábbi kezdőindex marad meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<long long> szamok;
    long long x;
    while (cin >> x) {
        szamok.push_back(x);
    }
    long long n = szamok.size();

    // 1. részfeladat: a sorozat elemszáma
    cout << "#\n";
    cout << n << "\n";

    // 2. részfeladat: a páratlan számok összege és darabszáma, valamint az összes szám összege
    long long osszeg = 0, paratlanOsszeg = 0, paratlanDb = 0;
    for (long long a : szamok) {
        osszeg += a;
        if (a % 2 != 0) {
            paratlanOsszeg += a;
            paratlanDb++;
        }
    }
    cout << "#\n";
    cout << paratlanOsszeg << " " << paratlanDb << "\n";

    // 3. részfeladat: az átlag legalább 10^-5 pontossággal
    double atlag = (n > 0) ? (double)osszeg / n : 0.0;
    cout << "#\n";
    cout << fixed << setprecision(9) << atlag << "\n";

    // 4. részfeladat: a leghosszabb szigorúan növekvő összefüggő részsorozat hossza és kezdőindexe
    long long legHossz = 0, legKezd = 0;
    long long hossz = 0, kezd = 0;
    for (long long i = 0; i < n; i++) {
        if (i > 0 && szamok[i] > szamok[i - 1]) {
            hossz++;
        } else {
            hossz = 1;
            kezd = i;
        }
        if (hossz > legHossz) {
            legHossz = hossz;
            legKezd = kezd;
        }
    }
    cout << "#\n";
    cout << legHossz << "\n";
    cout << legKezd + 1 << "\n";

    return 0;
}
