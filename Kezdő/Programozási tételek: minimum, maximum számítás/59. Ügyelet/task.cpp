/*
Megoldás lényege:
Először napra bontva megszámoljuk, hány diák jelentkezett az egyes napokra (gyakorisági tömb). Ezután egyetlen bejárással végigmegyünk a napokon: az egymás utáni, legalább egy jelentkezőt tartalmazó napok egy szakaszt alkotnak. Futó hosszal és a szakaszon belüli napi maximummal dolgozunk, és amikor egy nap kiesik, lezárjuk a szakaszt. A leghosszabb szakasz hosszát és a hozzá tartozó maximumot maximumkiválasztással tartjuk nyilván. Az időigény O(N + M).
*/
/*
Hint 1: || Előbb számold meg, hány diák jelentkezett az egyes napokra. A nap sorszáma alkalmas tömbindex. ||
Hint 2: || Egy nap akkor "lefedett", ha legalább egy jelentkező van rá. Keress egymás utáni lefedett napokból álló szakaszokat, és számold a hosszukat. ||
Hint 3: || Egy szakasz lezárásakor hasonlítsd a hosszát az eddigi legjobbhoz. Nagyobb hossznál cseréld le mindkét értéket, egyenlő hossznál a napi maximumot frissítsd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // letszam[d]: hány diák jelentkezett a d. napra
    vector<int> letszam(m + 2, 0);
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;
        letszam[s]++;
    }

    int legHossz = 0;     // a leghosszabb, minden napra ügyeletes szakasz hossza
    int legTobb = 0;      // ezeken a szakaszokon a napi jelentkezők maximuma
    int hossz = 0;        // az aktuális szakasz hossza
    int aktualisMax = 0;  // az aktuális szakaszon a napi jelentkezők maximuma

    // a d = m+1 egy lezáró "nap": így az utolsó szakasz is kiértékelődik
    for (int d = 1; d <= m + 1; d++) {
        bool van = (d <= m) && letszam[d] > 0;
        if (van) {
            hossz++;
            aktualisMax = max(aktualisMax, letszam[d]);
        } else {
            if (hossz > legHossz) {
                legHossz = hossz;
                legTobb = aktualisMax;
            } else if (hossz == legHossz && hossz > 0) {
                legTobb = max(legTobb, aktualisMax);
            }
            hossz = 0;
            aktualisMax = 0;
        }
    }

    cout << legHossz << "\n" << legTobb << "\n";
    return 0;
}
