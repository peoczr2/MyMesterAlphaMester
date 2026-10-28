/*
Megoldás lényege:
Az F és az I betűk külön számítanak: egy széria egymás utáni, azonos betűből álló maximális szakasz. Egyetlen lineáris bejárással minden széria hosszát megkapjuk, és két gyakorisági tömbben (F-re és I-re) számoljuk, hogy az adott hosszból hány van. A leggyakoribb hossz a gyakorisági tömb legnagyobb értékéhez tartozik; döntetlen esetén a nagyobb hosszt írjuk ki. Ha egy betű egyáltalán nem fordul elő, a válasz 0. Az időigény O(N), mert minden dobást egyszer nézünk meg.
*/
/*
Hint 1: || Egy széria egymás utáni, azonos betűből álló maximális szakasz: a sorozatot egyszer végigolvasva, a betűváltásoknál lezárva minden széria hosszát megkapod. ||
Hint 2: || Külön gyakorisági tömböt vezess az F és az I számára: a tömb i-edik eleme azt adja meg, hány i hosszúságú széria van. ||
Hint 3: || A legtöbbször előforduló hossz kiválasztásánál a tömböt végigjárva keresd a legnagyobb gyakoriságot, és egyenlőség esetén a nagyobb indexet tartsd meg; ha a betű nem fordul elő, a válasz 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A gyakorisági tömb alapján a leggyakoribb hosszt adja vissza (döntetlennél a nagyobbat).
int leggyakoribbHossz(const vector<int>& gyakori) {
    int legjobbHossz = 0;
    int legjobbDb = 0;
    for (int hossz = 1; hossz < (int)gyakori.size(); ++hossz) {
        if (gyakori[hossz] == 0) continue;
        if (gyakori[hossz] >= legjobbDb) {
            legjobbDb = gyakori[hossz];
            legjobbHossz = hossz;
        }
    }
    return legjobbHossz;
}

int main() {
    int n;
    cin >> n;

    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;
        s.push_back(c);
    }

    vector<int> fejGyak(n + 1, 0), irasGyak(n + 1, 0);
    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && s[j] == s[i]) ++j;
        int hossz = j - i;
        if (s[i] == 'F') ++fejGyak[hossz];
        else ++irasGyak[hossz];
        i = j;
    }

    cout << leggyakoribbHossz(fejGyak) << '\n';
    cout << leggyakoribbHossz(irasGyak) << '\n';
    return 0;
}
