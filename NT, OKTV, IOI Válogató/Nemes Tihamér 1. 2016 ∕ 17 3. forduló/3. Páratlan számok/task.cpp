/*
Megoldás lényege:
    Sorban végigszámoljuk a természetes számokat, és csak azokat számláljuk,
    amelyek bináris alakjában páratlan számú 1-es bit szerepel. A beépített
    __builtin_popcountll adja meg az 1-esek számát, így egy szám ellenőrzése
    állandó idejű; az i. találatnál megállunk, ez kb. 2i lépés.
*/
/*
Hint 1: || Nem kell tárolni a számokat: 1-től kezdve sorban végignézed a természetes számokat, és számolod a találatokat. Az i. találatnál megállsz, és azt a számot írod ki. ||
Hint 2: || Egy szám akkor találat, ha a kettes számrendszerbeli alakjában az 1-esek száma páratlan. Ezt a beépített bitszámláló függvény (például __builtin_popcountll) eredményének legalsó bitje mondja meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int i;
    cin >> i;

    int db = 0;
    long long szam = 0;
    while (db < i) {
        ++szam;
        if (__builtin_popcountll(szam) & 1) {
            ++db;
        }
    }

    cout << szam << '\n';
    return 0;
}
