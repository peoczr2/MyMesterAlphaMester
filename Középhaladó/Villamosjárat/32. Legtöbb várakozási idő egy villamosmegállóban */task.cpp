/*
Megoldás lényege:
Egy villamosmegállóban a várakozás az indulási és az érkezési idő különbsége; a nem megálló állomásokon ez 0. Egyetlen bejárásban kiszámoljuk minden állomás várakozását, és nyilvántartjuk az eddigi legnagyobbat az állomás sorszámával együtt. Csak szigorúan nagyobb várakozás írja felül a korábbit, így egyenlőség esetén a kisebb sorszámú állomás marad. Az időigény O(N).
*/
/*
Hint 1: || Egy állomáson a várakozási idő az indulási és az érkezési idő különbsége; ahol a villamos nem állt meg, ez a különbség 0. ||
Hint 2: || Egyetlen bejárásban tartsd nyilván az eddigi legnagyobb várakozást és az ahhoz tartozó állomás sorszámát. Csak szigorúan nagyobb érték írja felül a korábbit, így a legkisebb sorszám marad meg egyenlőségnél. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long bestWait = -1;  // az eddigi legnagyobb várakozás
    int bestIdx = 0;          // a hozzá tartozó állomás sorszáma

    for (int i = 1; i <= n; i++) {
        long long t, arr, dep;
        cin >> t >> arr >> dep;
        long long wait = dep - arr;
        if (wait > bestWait) {
            bestWait = wait;
            bestIdx = i;
        }
    }

    cout << bestIdx << ' ' << bestWait << '\n';
    return 0;
}
