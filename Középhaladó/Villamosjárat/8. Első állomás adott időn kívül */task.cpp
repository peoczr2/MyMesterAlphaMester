/*
Megoldás lényege:
A villamos a 0. állomásról nulla perckor indul, ezért az i-edik megállóba az érkezés ideje egyben az eljutási idő: Erk_i. Végigmegyünk a megállókon sorrendben, és az első olyan megállónál, ahol az érkezési idő nagyobb K-nál, kiírjuk a sorszámot és az eljutási időt, majd befejezzük. Mivel minden távolság legalább 1, a távolság szerint is az első találat a legközelebbi. Ha egyetlen megállóba sem jut el K percnél később, a válasz -1. Időigény O(N), ahol N legfeljebb 100.
*/
/*
Hint 1: || A 0. állomásról nulla időpontban indulunk, így az eljutási idő az érkezési idő. Az indulási időt ehhez nem kell figyelembe venni. ||
Hint 2: || Sorrendben haladj a megállókon, és az első olyan megállónál, ahol az érkezési idő nagyobb K-nál, írd ki a sorszámát és az érkezési időt, majd fejezd be a programot. Ha a ciklus végig nem talál ilyet, -1 a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int tav, erk, ind;
        cin >> tav >> erk >> ind;
        if (erk > k) {
            cout << i << ' ' << erk << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
    return 0;
}
