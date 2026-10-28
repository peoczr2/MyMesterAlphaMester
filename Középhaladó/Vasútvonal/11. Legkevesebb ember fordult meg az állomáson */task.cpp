/*
Megoldás lényege:
Egy állomáson azok fordultak meg, akik leszálltak vagy felszálltak, vagyis az állomás értéke le_i + fel_i. A vonat menetét nem kell szimulálni,
csak a minimális értékű állomás sorszámát kell megtalálni. Egy bejárásban követjük az eddigi legkisebb értéket és annak sorszámát.
Mivel a legkisebb sorszám kell, egyenlőség esetén a korábbi állomás marad, ezért szigorú "<" összehasonlítást használunk.
Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egy állomásra csak az számít, hány ember szállt le és hány szállt fel, összeadva. A keresett érték a minimum helye. ||
Hint 2: || Tartsd nyilván az eddig látott legkisebb összeget és annak sorszámát. Egyenlőségnél ne cseréld le a korábbi állomást, mert a kisebb sorszám kell. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int best = 1;
    long long bestVal = 0;
    for (int i = 1; i <= n; i++) {
        long long le, fel;
        cin >> le >> fel;
        long long val = le + fel;
        if (i == 1 || val < bestVal) {
            bestVal = val;
            best = i;
        }
    }

    cout << best << "\n";
    return 0;
}
