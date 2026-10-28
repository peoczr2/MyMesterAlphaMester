/*
Megoldás lényege:
Az állomások egy vonal mentén, 0-tól N-ig sorban helyezkednek el, így két nem szomszédos állomás távolsága legalább két szomszédos szakasz összege. Ezért a legközelebbi pár mindig szomszédos állomások közül kerül ki, elég a T_i távolságokat végignézni: az (i-1, i) pár távolsága T_i. Egyenlő távolságnál a szigorú összehasonlítás miatt a legkisebb sorszámú pár marad meg. Az időigény O(N).
*/
/*
Hint 1: || Két állomás távolsága a köztük lévő szakaszok távolságainak összege. Gondold végig, melyik két állomás lehet egymáshoz a legközelebb. ||
Hint 2: || Ha két állomás között több szakasz van, a távolságuk nagyobb, mint bármelyik közbülső szomszédos szakasz. Így elég a szomszédos párok közül a legkisebb T_i-t megkeresni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int bestIdx = 0;         // a pár második állomásának sorszáma
    int bestDist = INT_MAX;  // a legkisebb szomszédos távolság
    for (int i = 1; i <= n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        if (dist < bestDist) {
            bestDist = dist;
            bestIdx = i;
        }
    }

    cout << bestIdx - 1 << ' ' << bestIdx << ' ' << bestDist << '\n';
    return 0;
}
