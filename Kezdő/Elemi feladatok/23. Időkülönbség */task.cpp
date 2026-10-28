/*
Megoldás lényege:
Mindkét időpontot átalakítjuk a hónap elejétől eltelt másodpercek számává: nap*86400 + óra*3600 + perc*60 + másodperc.
Ezek különbsége adja a két kezdés között eltelt másodpercek számát, amelyet egész osztással és maradékképzéssel
visszabontunk nap, óra, perc és másodperc részekre (86400, 3600, 60 szerint). Mivel mindkét verseny ugyanabban
a hónapban van, nem kell a hónapok hosszával foglalkozni, és a művelet ideje konstans.
*/
/*
Hint 1: || Ne hasonlítsd össze külön a napokat, órákat, perceket és másodperceket: alakítsd át mindkét időpontot egyetlen egész számmá, például a másodpercek számává. Így a különbség egyetlen kivonás lesz. ||
Hint 2: || A különbségből a napok száma a másodpercek számának 86400-zal való egész osztása. A maradékot 3600-zal osztva kapod az órát, majd a maradékot 60-nal osztva a percet; a végső maradék a másodperc. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long nap1, ora1, perc1, mp1;
    long long nap2, ora2, perc2, mp2;
    cin >> nap1 >> ora1 >> perc1 >> mp1;
    cin >> nap2 >> ora2 >> perc2 >> mp2;

    // Az időpontok másodpercben kifejezve
    long long t1 = ((nap1 * 24 + ora1) * 60 + perc1) * 60 + mp1;
    long long t2 = ((nap2 * 24 + ora2) * 60 + perc2) * 60 + mp2;
    long long kulonbseg = t2 - t1;

    // Visszabontás nap, óra, perc, másodperc részekre
    long long nap = kulonbseg / 86400;
    kulonbseg %= 86400;
    long long ora = kulonbseg / 3600;
    kulonbseg %= 3600;
    long long perc = kulonbseg / 60;
    long long mp = kulonbseg % 60;

    cout << nap << " " << ora << " " << perc << " " << mp << "\n";
    return 0;
}
