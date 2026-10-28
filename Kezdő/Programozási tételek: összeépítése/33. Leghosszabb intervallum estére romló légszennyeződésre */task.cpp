/*
Megoldás lényege:
Minden napra eldöntjük, hogy az esti érték (E) nagyobb-e a reggelinél (R). A jó napok egybefüggő szakaszait egy bejárással követjük: jó napnál nő az aktuális szakasz hossza, különben nullázódik. A leghosszabb szakasz első és utolsó napját írjuk ki. Döntetlennél a korábbi szakasz marad, mert csak szigorúan hosszabb szakasz cserél, így a legkisebb első napot kapjuk. Ha nincs jó nap, a kimenet 0. Az időigény O(N).
*/
/*
Hint 1: || Egy naphoz két szám tartozik, és csak az esti érték és a reggeli összehasonlítása számít. ||
Hint 2: || Egy menetben, balról jobbra haladva számold az egymást követő jó napok hosszát. Ha egy nap nem jó, a számláló nullázódik, a legjobb szakasz kezdő- és végnapját pedig csak akkor frissítsd, ha a szakasz hosszabb. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int bestLen = 0, bestL = 0, bestR = 0;
    int curLen = 0, curStart = 0;
    for (int i = 1; i <= n; i++) {
        long long r, e;
        cin >> r >> e;
        if (e > r) {
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
