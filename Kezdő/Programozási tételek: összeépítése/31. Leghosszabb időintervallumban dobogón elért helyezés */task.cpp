/*
Megoldás lényege:
A kérdés szempontjából csak a helyezés számít, az idő két oszlopát (perc, másodperc) nem kell használni. Egy versenyt akkor veszünk a sorozatba, ha a helyezése legalább 3., vagyis H <= 3. Egyetlen balról jobbra haladó bejárással követjük az egymást követő megfelelő versenyek számát, és közben rögzítjük a leghosszabb futam első és utolsó sorszámát. Csak szigorúan hosszabb futam cserél, így döntetlennél a korábbi sorozat marad. Ha nincs megfelelő verseny, 0 a kimenet. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Csak a helyezés számít, az idő két oszlopát nyugodtan figyelmen kívül hagyhatod. ||
Hint 2: || Tarts két számlálót: az aktuális futam hosszát, és a legjobb futam kezdetét és végét. Ha egy verseny nem felel meg a feltételnek, az aktuális futam nullázódik. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int bestLen = 0, bestL = 0, bestR = 0;
    int curLen = 0, curStart = 0;
    for (int i = 1; i <= n; i++) {
        int h, p, mp;
        cin >> h >> p >> mp;
        if (h <= 3) {
            if (curLen == 0) curStart = i;
            curLen++;
            if (curLen > bestLen) {
                bestLen = curLen;
                bestL = curStart;
                bestR = i;
            }
        } else {
            curLen = 0;
        }
    }

    if (bestLen == 0) cout << 0 << "\n";
    else cout << bestL << " " << bestR << "\n";
    return 0;
}
