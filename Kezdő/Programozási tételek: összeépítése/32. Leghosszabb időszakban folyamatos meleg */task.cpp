/*
Megoldás lényege:
A feladat a leghosszabb olyan egybefüggő napsorozatot keresi, amelyen minden napi hőmérséklet szigorúan nagyobb K-nál. Egyetlen balról jobbra haladó bejárással követjük az aktuális, K felettiekből álló szakasz hosszát, és ha az hosszabb a legjobbnál, rögzítjük annak kezdő- és végnapját. A feltétel szigorú, így a K-val egyenlő hőmérséklet megszakítja a szakaszt. Döntetlennél a korábbi szakasz marad, mert csak szigorúan hosszabb szakasz cserél. Az időigény O(N), a memóriaigény O(1). Ha nincs ilyen szakasz, a kiírás nincs.
*/
/*
Hint 1: || Egy hőmérséklet akkor felel meg, ha K-nál szigorúan nagyobb. Az egyenlő érték már nem számít K felettinek. ||
Hint 2: || Egy menetben, balról jobbra haladva számold az egymást követő jó napok számát: jó napnál nő, különben nullázódik. Minden növekedésnél nézd meg, nagyobb-e a legjobbnál. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;

    int bestLen = 0, bestL = 0, bestR = 0;
    int curLen = 0, curStart = 0;
    for (int i = 1; i <= n; i++) {
        long long h;
        cin >> h;
        if (h > k) {
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

    if (bestLen == 0) cout << "nincs" << "\n";
    else cout << bestL << " " << bestR << "\n";
    return 0;
}
