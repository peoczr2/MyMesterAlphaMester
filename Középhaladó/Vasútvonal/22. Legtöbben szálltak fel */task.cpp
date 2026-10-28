/*
Megoldás lényege:
A kérdés csak a felszállók számára vonatkozik, a leszállók nem számítanak, ezért állomásonként elég a felszállók számát vizsgálni.
A feladat a legtöbb felszállót tartalmazó állomás sorszámát keresi, ami egy maximumkiválasztás.
Egy bejárással megoldható: az eddigi legnagyobb felszállószámot és annak sorszámát tároljuk, és csak szigorúan nagyobb érték esetén frissítünk.
Így döntetlen esetén a korábbi (kisebb sorszámú) állomás marad meg, ahogy a feladat kéri.
Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || A leszállókra nincs szükség, csak az egyes állomásokon felszállók számát kell figyelembe venni. ||
Hint 2: || Egyetlen bejárásban tartsd az eddigi legnagyobb felszállószámot és annak sorszámát, és csak szigorúan nagyobb érték esetén frissíts. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int best_idx = 1;
    int best_boarding = INT_MIN;
    for (int i = 1; i <= n; i++) {
        int le, fel;
        cin >> le >> fel;
        if (fel > best_boarding) {
            best_boarding = fel;
            best_idx = i;
        }
    }

    cout << best_idx << "\n";
    return 0;
}
