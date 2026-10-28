/*
Megoldás lényege:
A legtávolabbi város az a sor, ahol a távolság a legnagyobb. Egyetlen menetben haladunk végig a városokon, és nyilvántartjuk az eddigi legnagyobb távolságot és a hozzá tartozó legkisebb árat. Ha egy város távolabb van az eddigi legtávolabbinál, mindkét értéket felülírjuk; ha pontosan ugyanolyan távoli, akkor csak akkor frissítjük az árat, ha az olcsóbb. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Nem kell az összes várost eltárolni: menet közben elég a legnagyobb távolságot és a hozzá tartozó árat nyilvántartani. ||
Hint 2: || Két eset van: ha a város távolabb van az eddigi legtávolabbinál, cseréld a párost; ha pontosan ugyanolyan távoli, akkor az olcsóbb árat tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int cities;
    cin >> cities;

    int bestDistance = 0;
    int bestPrice = INT_MAX;
    for (int i = 0; i < cities; i++) {
        int distance, price;
        cin >> distance >> price;
        if (distance > bestDistance || (distance == bestDistance && price < bestPrice)) {
            bestDistance = distance;
            bestPrice = price;
        }
    }

    cout << bestPrice << "\n";
    return 0;
}
