/*
Megoldás lényege: mohó sorrend. Minden lépésben a még kirakható legnagyobb K * K-as négyzetet vesszük, vagyis K a maradék lapok számának egész négyzetgyöke (K * K nem nagyobb a maradéknál, de (K + 1) * (K + 1) már nem fér bele). A K * K lapot levonjuk a maradékból, és ugyanezt ismételjük, amíg a lapok el nem fogynak. A feladat a sorrendet előírja, így nincs döntési lehetőség: egyszerű szimulációról van szó. Az N legfeljebb 10 000, a K-keresés egy rövid ciklus, a lépések száma kicsi, így az időigény elhanyagolható.
*/
/*
Hint 1: || A feladat előírja a sorrendet: mindig a még kirakható legnagyobb négyzet jön, ezért nincs visszalépés vagy több lehetőség vizsgálata, csak a maradékkal ugyanezt ismételve haladsz. ||
Hint 2: || Egy lépésben a legnagyobb K-t egyszerű ciklussal keresd meg úgy, hogy K * K még ne legyen nagyobb a maradéknál; ezt kiírod, a maradékból levonod a K * K-t, és addig ismételsz, amíg a maradék nulla nem lesz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    bool elso = true;
    while (n > 0) {
        // A legnagyobb K, amelyre K * K még nem nagyobb a maradék lapok számánál
        int k = 1;
        while ((k + 1) * (k + 1) <= n) {
            k++;
        }
        if (!elso) cout << ' ';
        cout << k;
        elso = false;
        n -= k * k;
    }
    cout << '\n';
    return 0;
}
