/*
Megoldás lényege:
Egy tanuló akkor nagykorú, ha a születése óta legalább 6574 nap eltelt. A születési napok és a mai nap is 1970. január elsejétől számolt sorszámok, ezért a két szám különbsége adja az eltelt napok számát. A mai nap csak a bemenet utolsó sorában szerepel, ezért a születési napokat előbb egy vektorban tároljuk, majd a mai nap beolvasása után egy ciklusban mindegyikre ellenőrizzük a feltételt. Az időigény N-nel arányos.
*/
/*
Hint 1: || A születési nap és a mai nap is 1970. január 1-je óta eltelt napok száma, így a kettő különbsége adja meg, hány napos a tanuló. Ezt a különbséget kell összehasonlítani a 6574 nappal. ||
Hint 2: || A mai nap az utolsó sorban van, ezért a születési napokat előbb tárold el egy vektorban, és csak a mai nap beolvasása után vizsgáld meg őket egy ciklussal. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> szuletes(n);
    for (int i = 0; i < n; i++) {
        string nev;
        cin >> szuletes[i] >> nev;
    }

    long long ma;
    cin >> ma;

    bool van = false;
    for (int i = 0; i < n; i++) {
        if (ma - szuletes[i] >= 6574) {
            van = true;
        }
    }

    cout << (van ? "VAN" : "NINCS") << '\n';
    return 0;
}
