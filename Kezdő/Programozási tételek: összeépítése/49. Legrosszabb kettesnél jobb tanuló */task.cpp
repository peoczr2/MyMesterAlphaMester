/*
Megoldás lényege:
Egyetlen menetben haladunk végig a jegyeken, és nyilvántartjuk az eddigi legjobb, azaz legalább 3-as jegyet és annak sorszámát. A kezdő értéket 6-nak választjuk, ami nagyobb minden lehetséges jegynél, így az első legalább 3-as jegy biztosan átveszi a helyét. Csak szigorúan kisebb jegynél cserélünk, így egyenlőség esetén a korábbi, azaz kisebb sorszámú tanuló marad meg. Ha nem volt legalább 3-as jegy, a sorszám a kezdő –1 marad, és ezt írjuk ki. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Csak a legalább 3-as jegyek érdekesek, közülük kell a legkisebbet megkeresni. A feladat tehát egy minimumkeresés egy szűrt sorozaton, és a sorszámot is meg kell jegyezni. ||
Hint 2: || Tarts egy változót a legjobb jegynek és egy másikat a sorszámának. Egy jegy beolvasása után ellenőrizd, hogy 3 vagy nagyobb-e, és csak akkor írd felül a két változót, ha kisebb az eddigi legjobbnál. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int legjobbJegy = 6, legjobbSorszam = -1;
    for (int i = 1; i <= n; i++) {
        int jegy;
        cin >> jegy;
        if (jegy >= 3 && jegy < legjobbJegy) {
            legjobbJegy = jegy;
            legjobbSorszam = i;
        }
    }
    if (legjobbSorszam == -1) cout << -1 << endl;
    else cout << legjobbSorszam << " " << legjobbJegy << endl;
    return 0;
}
