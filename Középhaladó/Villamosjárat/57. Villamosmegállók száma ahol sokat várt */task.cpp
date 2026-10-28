/*
Megoldás lényege:
Egy megállóban a villamos várakozási ideje az indulási és az érkezési idő különbsége, azaz Ind_i - Erk_i. Ezt minden megállóra kiszámoljuk, és ha nagyobb K-nál, a számlálót eggyel növeljük. A távolságok ehhez nem kellenek, ezért csak a második és harmadik számot használjuk. A kérdés csak darabszámot kér, így egyetlen beolvasó ciklus elég. A feltétel szigorú: aki pontosan K percet várt, az nem „többet” várt, ezért nem számít. Időigény O(N), ahol N legfeljebb 100.
*/
/*
Hint 1: || Egy megálló várakozási ideje az indulási idő és az érkezési idő különbsége. A távolság (az első szám) erre nincs hatással. ||
Hint 2: || Egy ciklusban olvass be minden megállót, számold ki a várakozást, és ha nagyobb K-nál, növeld a darabszámot. A kiíráshoz csak ezt a számot kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int darab = 0;
    for (int i = 0; i < n; i++) {
        int tav, erk, ind;
        cin >> tav >> erk >> ind;
        if (ind - erk > k) {
            darab++;
        }
    }
    cout << darab << '\n';
    return 0;
}
