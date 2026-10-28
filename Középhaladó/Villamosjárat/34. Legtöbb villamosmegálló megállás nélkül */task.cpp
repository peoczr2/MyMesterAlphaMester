/*
Megoldás lényege:
Egy állomáson a villamos nem áll meg, ha az érkezési és az indulási idő megegyezik. Egy bejárásban követjük az aktuális, egymást követő nem megálló állomásokból álló szakasz kezdő sorszámát és hosszát: nem megálló állomásnál a hossz nő, megálló állomásnál a hossz nullázódik. Minden növelés után összevetjük az eddigi legjobb szakasszal, és csak szigorúan hosszabb szakasz írja felül, így az első ilyen szakasz marad meg. Ha minden állomáson megállt a villamos, nincs ilyen szakasz, ekkor a feladat szerint három 0 a kimenet. Az időigény O(N).
*/
/*
Hint 1: || Most a nem megálló állomások (érkezési idő = indulási idő) alkotnak egymást követő sorozatot; egy valódi megálló állomás megszakítja a sorozatot. ||
Hint 2: || Az előző feladathoz hasonlóan tartsd nyilván az aktuális sorozat kezdetét és hosszát, valamint a legjobb sorozat kezdetét, végét és hosszát; csak szigorúan hosszabb sorozat írja felül a legjobbat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int curStart = 0, curLen = 0;          // az aktuális nem megálló állomásokból álló sorozat
    int bestS = 0, bestE = 0, bestLen = 0; // a legjobb sorozat kezdete, vége, hossza

    for (int i = 1; i <= n; i++) {
        long long t, arr, dep;
        cin >> t >> arr >> dep;
        if (arr == dep) {              // nem megálló állomás: a sorozat folytatódik vagy most indul
            if (curLen == 0) curStart = i;
            curLen++;
            if (curLen > bestLen) {
                bestLen = curLen;
                bestS = curStart;
                bestE = i;
            }
        } else {                       // valódi megállás: megszakítja a sorozatot
            curLen = 0;
        }
    }

    cout << bestS << ' ' << bestE << ' ' << bestLen << '\n';
    return 0;
}
