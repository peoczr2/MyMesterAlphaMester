/*
Megoldás lényege:
Minden állomáson kiszámoljuk, hogy a vonaton az utasok száma mennyivel változott: fel - le. Növekedésnek azok az állomások számítanak, ahol a szám legalább 1-gyel nőtt, vagyis fel - le >= 1. Ezek közül keressük a legkisebb növekedést, és egyenlőség esetén a korábbi állomás marad. Egyetlen bejárás elég, az időigény O(N).
*/
/*
Hint 1: || Egy állomáson az utasok számának változása fel - le; csak a pozitív változásokat, vagyis a növekedéseket kell figyelembe venni. ||
Hint 2: || Tartsd nyilván a legkisebb pozitív növekedést (fel - le) és az állomás sorszámát; szigorú összehasonlítással a korábbi sorszám marad egyenlőségnél. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int best_rise = INT_MAX, best_idx = 0;
    for (int i = 1; i <= n; i++) {
        int le, fel;
        cin >> le >> fel;
        int rise = fel - le;
        if (rise >= 1 && rise < best_rise) {
            best_rise = rise;
            best_idx = i;
        }
    }
    cout << best_idx << "\n";
    return 0;
}
