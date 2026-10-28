/*
Megoldás lényege:
Egy szakasz ideje az előző állomásról való indulástól az adott állomásra való érkezésig tart; a 0. állomásról a villamos a 0. percben indul. Egyetlen ciklusban végigmegyünk a szakaszokon, és nyilvántartjuk az eddigi leghosszabb időt és a szakasz két végpontját. Csak szigorúan nagyobb érték írja felül a jelöltet, így egyenlőség esetén a kisebb sorszámú szakasz marad. Az időigény O(N).
*/
/*
Hint 1: || Minden szakasz ideje az i-1. állomásról való indulástól az i. állomásra való érkezésig tart; az i-1. állomásról való indulás idejét minden sorban az előző sor adataiból ismered. ||
Hint 2: || Tartsd nyilván az eddigi legnagyobb szakaszidőt és annak két végpontját; csak szigorúan nagyobb érték írja felül, így egyenlőség esetén a kisebb sorszámú szakasz marad meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long prevDep = 0;     // a 0. állomásról a villamos a 0. percben indul
    long long best = -1;       // a legnagyobb szakaszidő
    int bestFrom = 0, bestTo = 0;
    for (int i = 1; i <= n; i++) {
        long long t, arr, dep;
        cin >> t >> arr >> dep;
        long long travel = arr - prevDep;
        if (travel > best) {
            best = travel;
            bestFrom = i - 1;
            bestTo = i;
        }
        prevDep = dep;
    }

    cout << bestFrom << ' ' << bestTo << ' ' << best << '\n';
    return 0;
}
