/*
Megoldás lényege: a kosárlabdacsapatok (5 fő) és a kézilabdacsapatok (7 fő) minden lehetséges darabszám-párját végigpróbáljuk, ami N legfeljebb 100 miatt gyorsan lefut. Minden párnál a kimaradók száma N - 5 * kosar - 7 * kez, és azt a párt tartjuk meg, amelyiknél ez a legkisebb. Ha több azonos kimaradású megoldás is van (például 35 tanulónál 7 kosárlabda- vagy 5 kézilabdacsapat), bármelyik elfogadható, a program az elsőt írja ki.
*/
/*
Hint 1: || A csapatok száma kicsi, ezért nem kell okos képlet: próbáld ki az összes lehetséges kosárlabda- és kézilabdacsapat-számot. ||
Hint 2: || Egy párnál a kimaradók száma N - (5 * kosar + 7 * kez); a legkisebb ilyen értéket keresed, és csak szigorúan kisebb érték esetén írod felül a korábbi legjobbat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int legjobbKimarad = INT_MAX, legjobbKosar = 0, legjobbKez = 0;
    for (int kosar = 0; 5 * kosar <= n; kosar++) {
        for (int kez = 0; 5 * kosar + 7 * kez <= n; kez++) {
            int kimarad = n - 5 * kosar - 7 * kez;
            if (kimarad < legjobbKimarad) {
                legjobbKimarad = kimarad;
                legjobbKosar = kosar;
                legjobbKez = kez;
            }
        }
    }
    cout << legjobbKosar << " " << legjobbKez << " " << legjobbKimarad << "\n";
    return 0;
}
