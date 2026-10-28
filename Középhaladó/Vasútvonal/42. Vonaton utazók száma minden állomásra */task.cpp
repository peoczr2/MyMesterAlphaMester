/*
Megoldás lényege:
Az aktuális utasszámot egy változóban tartjuk nyilván: minden állomáson előbb levonjuk a leszállók számát, majd hozzáadjuk a felszállókat.
Az így kapott értéket az állomás sorrendjében azonnal kiírjuk, szóközzel elválasztva, egy sorba.
Egyetlen bejárás, O(N) időben fut, ami N ≤ 1000 esetén messze az időlimit alatt marad.
*/
/*
Hint 1: || Az utasok számát nem kell minden állomásnál újraszámolni: elég az előző állomás utáni értékhez hozzáigazítani a változást. ||
Hint 2: || Az értékeket a beolvasás sorrendjében kell kiírni egy sorba, szóközökkel elválasztva. Az első állomás előtt az utasszám 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long utasok = 0;
    for (int i = 0; i < n; i++) {
        int leszallo, felszallo;
        cin >> leszallo >> felszallo;
        utasok = utasok - leszallo + felszallo;
        if (i > 0) cout << ' ';
        cout << utasok;
    }
    cout << endl;
    return 0;
}
