/*
Megoldás lényege:
A pozitív és a negatív sebességeket külön gyűjtjük: mindkét irányhoz egy összeget és egy darabszámot tartunk nyilván. A negatív értékeknél az abszolút értéket adjuk az összeghez, így mindkét átlag pozitív szám lesz. A bemenetet a 0-ig olvassuk, a számolás egyetlen menet, az időigény O(N), a memóriaigény O(1). Az átlagot egész számtani művelettel kerekítjük: a (2 * S + C) / (2 * C) egész osztás a S / C értéket a .5 eseteket felfelé kerekítve adja, így lebegőpontos hiba nem léphet fel. Ha egy irányban nem haladt autó, az átlag helyett -1 kerül a kimenetre.
*/
/*
Hint 1: || Két irányt kell külön kezelni: a pozitív és a negatív előjelű sebességeket külön összegezd és számold meg, a 0 pedig jelzi a bemenet végét. ||
Hint 2: || Az átlagot egész osztással is kiszámolhatod, ha a 2 * S + C számot 2 * C-vel osztod egészben. Ha egy irányban nincs darab, az átlag nem értelmezett, ilyenkor -1 a kiírt érték. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Egész kerekítés: S / C, a .5 értékeket felfelé kerekítve (S >= 0, C > 0).
long long kerekit(long long S, long long C) {
    return (2 * S + C) / (2 * C);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long pozOsszeg = 0, pozDb = 0;
    long long negOsszeg = 0, negDb = 0;
    int s;
    while (cin >> s && s != 0) {
        if (s > 0) {
            pozOsszeg += s;
            pozDb++;
        } else {
            negOsszeg += -s;
            negDb++;
        }
    }
    cout << (pozDb ? kerekit(pozOsszeg, pozDb) : -1) << " "
         << (negDb ? kerekit(negOsszeg, negDb) : -1) << "\n";
    return 0;
}
