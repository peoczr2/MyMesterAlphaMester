/*
Megoldás lényege:
Egy hetet akkor tekintünk jónak, ha a hét csapadékösszege legfeljebb 10 mm.
Egyszer végigmegyünk a heteken, és közben nyilvántartjuk az aktuális folyamatos
jó szakasz kezdetét és hosszát. Ha egy hét nem jó, a szakasz megszakad, ezért
a hossz nullázódik. Minden jó hétnél megnézzük, hogy az aktuális szakasz
szigorúan hosszabb-e a legjobbnál; így a döntetlen esetén a korábbi (kisebb
sorszámú) szakasz marad meg. Az időigény a hetek számával arányos, O(N·7).
*/
/*
Hint 1: || Először minden hétre számold ki a csapadékösszeget, és döntsd el, hogy a hét jó-e. ||
Hint 2: || Tartsd nyilván az aktuális folyamatos jó szakasz kezdetét és hosszát, és egy rossz hétnél szakíts meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int bestLen = 0, bestStart = 0;   // a legjobb jó szakasz hossza és első hete
    int curLen = 0, curStart = 0;     // az aktuális jó szakasz

    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = 0; j < 7; j++) {
            int c;
            cin >> c;
            sum += c;
        }

        if (sum <= 10) {
            if (curLen == 0) curStart = i;
            curLen++;
            if (curLen > bestLen) {
                bestLen = curLen;
                bestStart = curStart;
            }
        } else {
            curLen = 0;
        }
    }

    if (bestLen == 0) {
        cout << 0 << '\n';
    } else {
        cout << bestStart << ' ' << bestStart + bestLen - 1 << '\n';
    }
    return 0;
}
