/*
Megoldás lényege:
Évenként beolvassuk a bor mennyiségét és árát, és csak azokat az éveket vesszük figyelembe, ahol a mennyiség nagyobb mint 1000 liter.
Ezek közül a legnagyobb árat keressük egy változóban, amelyet -1-ről indítunk; ha egyetlen év sem felel meg, a -1 marad a kimenet.
Az algoritmus egyetlen bejárással, O(N) időben fut, az éveket nem kell eltárolni.
*/
/*
Hint 1: || Egyetlen végigolvasás elég: évenként csak a termés mennyisége és az ára ismeretében kell eldönteni, hogy az év számításba jön-e. ||
Hint 2: || A maximumot egy változóban tartsd, és csak akkor frissítsd, ha az év mennyisége nagyobb 1000-nél és az ára nagyobb az eddigi maximumnál; kezdetben a -1 jelzi, hogy még nincs ilyen év. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long best = -1;
    for (int i = 0; i < n; i++) {
        long long mennyiseg, ar;
        cin >> mennyiseg >> ar;
        if (mennyiseg > 1000 && ar > best) best = ar;
    }

    cout << best << "\n";
    return 0;
}
