/*
Megoldás lényege:
Minden állomáson kiszámoljuk, hogy a vonaton az utasok száma mennyivel változott: fel - le. Csökkenésnek azok az állomások számítanak, ahol a szám legalább 1-gyel csökkent, vagyis le - fel >= 1. Ezek közül keressük a legkisebb csökkenést, és egyenlőség esetén a korábbi állomás marad. Egyetlen bejárás elég, az időigény O(N).
*/
/*
Hint 1: || Egy állomáson az utasok számának változása fel - le; csak a negatív változásokat, vagyis a csökkenéseket kell figyelembe venni. ||
Hint 2: || Tartsd nyilván a legkisebb pozitív csökkenést (le - fel) és az állomás sorszámát; szigorú összehasonlítással a korábbi sorszám marad egyenlőségnél. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int best_drop = INT_MAX, best_idx = 0;
    for (int i = 1; i <= n; i++) {
        int le, fel;
        cin >> le >> fel;
        int drop = le - fel;
        if (drop >= 1 && drop < best_drop) {
            best_drop = drop;
            best_idx = i;
        }
    }
    cout << best_idx << "\n";
    return 0;
}
