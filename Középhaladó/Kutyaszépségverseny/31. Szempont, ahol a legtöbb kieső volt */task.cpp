/*
Megoldás lényege:
Szempontonként (oszloponként) számoljuk, hány kutya esett ki az adott szempontból, vagyis hány pontszám kisebb az adott szempont alsó ponthatáránál (P < Min). Egy kutya minden olyan szempontnál beleszámít, ahol az alsó határ alatt van, mert a kérdés az egyes szempontok kieséseire vonatkozik. A pontszámokat egyszer olvassuk be, és közben növeljük a megfelelő számlálókat, így az idő O(N·M), ami legfeljebb 10^4 lépés. Végül megkeressük a legnagyobb számlálót: a szigorú > összehasonlítás miatt holtverseny esetén a kisebb sorszám marad.
*/
/*
Hint 1: || Egy kutya egy szempontból akkor esik ki, ha a pontszáma kisebb, mint az adott szempont alsó ponthatára. Ezt szempontonként külön kell nézni. ||
Hint 2: || Tarts egy M elemű tömböt, amelyben szempontonként számolod a kieséseket, majd keresd meg azt a helyet, ahol a legnagyobb érték van. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // a maximális pontokra a számításhoz nincs szükség, csak beolvassuk őket
    vector<int> maxPont(m);
    for (int j = 0; j < m; j++) cin >> maxPont[j];

    vector<int> alsoHatar(m);
    for (int j = 0; j < m; j++) cin >> alsoHatar[j];

    // kiesett[j]: hány kutya esett ki a j. szempontból
    vector<int> kiesett(m, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int p;
            cin >> p;
            if (p < alsoHatar[j]) kiesett[j]++;
        }
    }

    // a legnagyobb számláló helye; holtversenynél a kisebb sorszám marad
    int legjobb = 0;
    for (int j = 1; j < m; j++) {
        if (kiesett[j] > kiesett[legjobb]) legjobb = j;
    }

    cout << legjobb + 1 << "\n";
    return 0;
}
