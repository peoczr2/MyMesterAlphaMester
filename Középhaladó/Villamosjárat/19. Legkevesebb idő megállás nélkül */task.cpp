/*
Megoldás lényege:
A megállás nélküli időtartamok határai a 0. állomásról való indulás, a tényleges megállások (ahol az érkezési és az indulási idő különbözik) és a végállomás érkezése. Két egymást követő határ között a villamos nem áll meg, így a nem megálló állomásokon való áthaladás nem szakítja meg az időszakot. Egy menetben nyilvántartjuk az utolsó megállás indulási idejét (kezdetben 0), és minden határnál vesszük az érkezés és ez közötti különbséget; ezek minimuma a válasz. Az időigény O(N).
*/
/*
Hint 1: || A megállás nélküli időszakokat a tényleges megállások határolják. Egy nem megálló állomás nem szakítja meg az időszakot, tehát nem minden állomás számít határnak. ||
Hint 2: || Egy ciklusban tartsd nyilván az utolsó tényleges megállás indulási idejét (kezdetben 0). Minden határnál, azaz minden megállásnál és a végállomásnál, számold ki a határ érkezési ideje mínusz ez az érték, és vedd a minimumot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long lastDep = 0;  // az utolsó tényleges megállás indulási ideje (kezdetben a 0. állomás)
    long long best = LLONG_MAX;

    for (int i = 1; i <= n; i++) {
        long long t, arr, dep;
        cin >> t >> arr >> dep;
        if (arr != dep || i == n) {
            best = min(best, arr - lastDep);
            lastDep = dep;
        }
    }

    cout << best << '\n';
    return 0;
}
