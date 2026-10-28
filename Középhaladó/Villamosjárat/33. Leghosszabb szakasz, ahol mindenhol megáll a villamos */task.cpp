/*
Megoldás lényege:
Egy állomáson a villamos akkor áll meg, ha az érkezési és az indulási idő különbözik. Egy bejárásban követjük az aktuális, egymást követő megállókból álló szakasz kezdő sorszámát és hosszát: megálló állomásnál a hossz nő (ha az új szakasz most kezdődik, a kezdő sorszám az aktuális állomás), nem megálló állomásnál a hossz nullázódik. Minden növelés után összevetjük az eddigi legjobb szakasszal, és csak szigorúan hosszabb szakasz írja felül, így az első ilyen szakasz marad meg. Ha nincs megálló állomás, nincs ilyen szakasz, ekkor 0 0 0 a kimenet. Az időigény O(N).
*/
/*
Hint 1: || Egyetlen bejárásban elég a jelenleg futó, csupa megállóból álló sorozat hosszát követni: egy nem megálló állomás megszakítja a sorozatot, egy megálló állomás folytatja vagy elindítja. ||
Hint 2: || Tartsd nyilván az aktuális sorozat kezdő sorszámát és hosszát, valamint a legjobb sorozat kezdetét, végét és hosszát. Minden megálló állomás után a legjobbat csak szigorúan nagyobb hossz írja felül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int curStart = 0, curLen = 0;          // az aktuális megállókból álló sorozat
    int bestS = 0, bestE = 0, bestLen = 0; // a legjobb sorozat kezdete, vége, hossza

    for (int i = 1; i <= n; i++) {
        long long t, arr, dep;
        cin >> t >> arr >> dep;
        if (arr < dep) {               // valódi megállás: a sorozat folytatódik vagy most indul
            if (curLen == 0) curStart = i;
            curLen++;
            if (curLen > bestLen) {
                bestLen = curLen;
                bestS = curStart;
                bestE = i;
            }
        } else {                       // nem megálló állomás: megszakítja a sorozatot
            curLen = 0;
        }
    }

    cout << bestS << ' ' << bestE << ' ' << bestLen << '\n';
    return 0;
}
