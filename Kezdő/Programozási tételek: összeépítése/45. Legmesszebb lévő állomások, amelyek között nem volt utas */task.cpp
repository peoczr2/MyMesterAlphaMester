/*
Megoldás lényege:
Minden állomás után kiszámoljuk, hányan utaznak a vonaton: az előző utasszámból kivonjuk a leszállókat, és hozzáadjuk a felszállókat.
Két állomás közötti szakaszon akkor nincs utas, ha az előző állomás utáni utasszám 0. Az utolsó állomás után már nincs szakasz, ezért csak az 1..N-1 állomásokat vizsgáljuk.
Az egymás utáni nulla értékű állomások futamot alkotnak: ha az i..e állomások utáni utasszám mind 0, akkor a legtávolabbi pár az i. és az (e+1). állomás, a távolságuk e+1-i.
Egy balról jobbra haladó bejárással megkeressük a leghosszabb futamot; egyenlőség esetén a korábbit tartjuk meg. Ha nincs ilyen futam, a kiírás 0 0.
Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Minden állomás után számold ki az utasok számát: az előző érték mínusz a leszállók, plus a felszállók. Ebből látszik, mely szakaszokon volt üres a vonat. ||
Hint 2: || Keress egymást követő nulla utasszámokat. Ha az i-edik és az e-edik állomás utáni érték is nulla, és köztük minden is nulla, akkor a pár az i. és az (e+1). állomás. Egyetlen végigfutással a leghosszabb ilyen szakaszt találod meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> utas(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int le, fel;
        cin >> le >> fel;
        utas[i] = utas[i - 1] - le + fel;
    }

    int legjobbHossz = 0, legjobbI = 0, legjobbJ = 0;
    int i = 1;
    while (i <= n - 1) {
        if (utas[i] != 0) {
            i++;
            continue;
        }
        int kezd = i;
        while (i <= n - 1 && utas[i] == 0) {
            i++;
        }
        // a [kezd, i-1] állomások utáni szakaszokon nincs utas, a pár: kezd és i
        int hossz = i - kezd;
        if (hossz > legjobbHossz) {
            legjobbHossz = hossz;
            legjobbI = kezd;
            legjobbJ = i;
        }
    }

    if (legjobbHossz == 0) {
        cout << "0 0" << endl;
    } else {
        cout << legjobbI << " " << legjobbJ << endl;
    }
    return 0;
}
