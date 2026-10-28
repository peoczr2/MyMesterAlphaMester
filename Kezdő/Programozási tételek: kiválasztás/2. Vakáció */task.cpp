/*
Megoldás lényege:
A vakáció az első olyan egyesekből álló sorozat, amelynek hossza legalább 7. Balról jobbra haladva számoljuk, hány egymást követő szünetnap van; tanítási napnál a számláló nullázódik, így a rövid szünetek (például két nap) nem számítanak. Amint a számláló eléri a 7-et, a sorozat első napja a mostani nap sorszáma mínusz 6, és ennyi éjszakát kell aludni a vakáció kezdetéig. Mivel az első ilyen sorozat kezdete a keresett érték, az első találatnál kiírjuk az eredményt. A program egyetlen menetben, O(N) időben fut.
*/
/*
Hint 1: || Nem kell az összes napot eltárolni: elég egy számlálót vezetned arról, hány egymást követő szünetnap volt eddig. ||
Hint 2: || Amikor a számláló eléri a 7-et, a sorozat már vakáció; a kezdőnap sorszámát a jelenlegi napból visszafelé számolva kapod meg. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int run = 0;  // az egymást követő szünetnapok száma az aktuális napig
    for (int day = 1; day <= n; ++day) {
        int type;
        cin >> type;

        if (type == 1) {
            ++run;
            if (run == 7) {
                // A sorozat 7 napja: day-6, ..., day. Az első nap sorszáma a keresett érték.
                cout << day - 6 << '\n';
                return 0;
            }
        } else {
            run = 0;
        }
    }

    // A feladat garantálja, hogy van vakáció, így ide nem jutunk.
    cout << 0 << '\n';
    return 0;
}
