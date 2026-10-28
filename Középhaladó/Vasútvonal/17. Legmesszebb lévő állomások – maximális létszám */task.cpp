/*
Megoldás lényege:
Állomásonként kiszámoljuk, hány utas van a vonaton az állomás elhagyása után; ez adja a következő szakasz létszámát. Egy szakasz akkor „telt”, ha a létszáma eléri vagy meghaladja a hivatalos maximumot. Az egymás utáni telt szakaszok összefüggő sorozatot alkotnak: ha a sorozat az a. állomástól a b. állomásig tart, a legmesszebb levő pár az a. és a (b+1). állomás. Egy bejárással követjük az aktuális sorozat kezdetét, és csak szigorúan hosszabb sorozatnál frissítünk, így egyenlőség esetén a korábbi pár marad. Ha nincs telt szakasz, a megoldás 0 0. Az időigény O(N).
*/
/*
Hint 1: || Számold ki minden szakaszon a vonaton lévő utasok számát: az előző érték + felszállók − leszállók. Egy szakasz akkor telt, ha ez az érték eléri a maximumot. ||
Hint 2: || Keresd a leghosszabb, egymás után következő telt szakaszok sorozatát. Ha az a. állomástól a b. állomásig tart, a megoldás az a. és a (b+1). állomás; a sorozat kezdetét egy bejárásban jegyezd fel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long mx;
    cin >> n >> mx;
    vector<long long> le(n + 1), fel(n + 1);
    for (int i = 1; i <= n; i++) cin >> le[i] >> fel[i];

    long long load = 0;              // utasok száma az i. állomás elhagyása után
    int bestLen = 0, bestA = 0, bestB = 0;
    int runStart = 0;                // az aktuális telt sorozat kezdő állomása (0: nincs)
    for (int i = 1; i < n; i++) {    // az i. és (i+1). állomás közötti szakasz
        load += fel[i] - le[i];
        if (load >= mx) {
            if (runStart == 0) runStart = i;
            int len = (i + 1) - runStart;
            if (len > bestLen) {
                bestLen = len;
                bestA = runStart;
                bestB = i + 1;
            }
        } else {
            runStart = 0;
        }
    }
    cout << bestA << " " << bestB << "\n";
    return 0;
}
