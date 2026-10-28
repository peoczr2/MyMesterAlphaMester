/*
Megoldás lényege:
Az i. és (i+1). állomás közötti szakaszon akkor vannak utasok, ha az i. állomás elhagyása után a létszám pozitív. Egy bejárással megkeressük a leghosszabb, egymás után következő pozitív szakaszokból álló sorozatot: ha az a. állomástól a b. állomásig tart, a legmesszebb levő pár az a. és a (b+1). állomás. Egy sorozat hosszát a kezdete óta számoljuk, és csak szigorúan hosszabb sorozatnál frissítünk, így egyenlőség esetén a korábbi pár marad. Ha a vonat végig üres, a megoldás 0 0. Az időigény O(N).
*/
/*
Hint 1: || Számold ki minden szakaszon a vonaton lévő utasok számát: az előző érték + felszállók − leszállók. Nézd meg, mely szakaszokon pozitív ez az érték. ||
Hint 2: || A pozitív szakaszok egymás utáni sorozatai közül keresd a leghosszabbat. Ha a sorozat az a. állomástól a b. állomásig tart, a megoldás az a. és a (b+1). állomás; egyenlőségnél a korábbit tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> le(n + 1), fel(n + 1);
    for (int i = 1; i <= n; i++) cin >> le[i] >> fel[i];

    long long load = 0;              // utasok száma az i. állomás elhagyása után
    int bestLen = 0, bestA = 0, bestB = 0;
    int runStart = 0;                // az aktuális pozitív sorozat kezdő állomása (0: nincs)
    for (int i = 1; i < n; i++) {    // az i. és (i+1). állomás közötti szakasz
        load += fel[i] - le[i];
        if (load > 0) {
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
