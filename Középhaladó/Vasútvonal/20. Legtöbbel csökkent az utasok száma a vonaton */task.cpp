/*
Megoldás lényege:
Egy állomáson a vonaton lévő utasok száma fel - le értékkel változik, ezért elég minden állomáson ezt a különbséget kiszámolni, a teljes utasszámot nem kell nyilvántartani.
A feladat azt az állomást keresi, ahol ez a változás a legkisebb, vagyis ahol a legtöbbel csökkent az utasok száma.
Egy bejárással megoldható: az eddigi legkisebb változást és annak sorszámát tároljuk, és csak akkor frissítünk, ha az aktuális érték szigorúan kisebb.
Így döntetlen esetén a korábbi (kisebb sorszámú) állomás marad meg, ahogy a feladat kéri.
Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Az utasok száma egy állomáson fel - le értékkel változik, ezért elég az állomásonkénti változást vizsgálni, nem kell az egész útvonal utasszámát követni. ||
Hint 2: || Egyetlen bejárásban tartsd az eddigi legkisebb különbséget és annak sorszámát, és csak szigorúan kisebb érték esetén frissíts. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int best_idx = 1;
    int best_change = INT_MAX;
    for (int i = 1; i <= n; i++) {
        int le, fel;
        cin >> le >> fel;
        int change = fel - le;
        if (change < best_change) {
            best_change = change;
            best_idx = i;
        }
    }

    cout << best_idx << "\n";
    return 0;
}
