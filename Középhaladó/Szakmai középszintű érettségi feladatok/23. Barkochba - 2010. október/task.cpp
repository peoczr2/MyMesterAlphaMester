/*
Megoldás lényege:
Az intervallumot két határral (alsó és felső) tartjuk nyilván. Minden lépésben kiszámoljuk a középső számot: páratlan hosszúságnál ez az intervallum pontos közepe, páros hosszúságnál a két középső szám közül a nullához közelebbi. Ezt a számot kérdezzük meg. Ha a válasz „kisebb”, a felső határt állítjuk a kérdezett szám alá, ha „nagyobb”, az alsó határt a kérdezett szám fölé; ha „megvan”, a játék véget ér. Ha a határok átfordulnak (az intervallum üres lesz), a válaszadó hibázott, és a „hiba” szót kell kiírni. Minden lépésben az intervallum felezódik, így az időigény O(log(B − A)).
*/
/*
Hint 1: || Minden kérdés után a gondolt szám csak az egyik félintervallumban lehet, a kérdezett szám pedig már nem része az intervallumnak. Ezért elég egy alsó és egy felső határt nyilvántartani. ||
Hint 2: || A középső számhoz az intervallum hosszát (felső − alsó + 1) használd. Páratlan hossznál a közép egyértelmű; páros hossznál a két középső elem közül azt válaszd, amelynek az abszolút értéke kisebb, mert a feladat a nullához közelebbit kéri. ||
Hint 3: || „Kisebb” válasznál a felső határ a kérdezett szám eggyel alatti értéke lesz, „nagyobb” esetén az alsó határ az eggyel feletti. Ha ezután az alsó határ nagyobb a felsőnél, a válaszok hibásak, és „hiba” a kiírás. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long also, felso;
    int n;
    cin >> also >> felso >> n;

    for (int i = 0; i < n; i++) {
        long long hossz = felso - also + 1;

        long long kozep;
        if (hossz % 2 == 1) {
            kozep = also + (hossz - 1) / 2;
        } else {
            long long c1 = also + hossz / 2 - 1;
            long long c2 = also + hossz / 2;
            kozep = (llabs(c1) <= llabs(c2)) ? c1 : c2;
        }

        cout << kozep << "\n";

        string valasz;
        cin >> valasz;

        if (valasz == "megvan") {
            return 0;
        }

        if (valasz == "kisebb") {
            felso = kozep - 1;
        } else {
            also = kozep + 1;
        }

        if (also > felso) {
            cout << "hiba\n";
            return 0;
        }
    }

    return 0;
}
