/*
Megoldás lényege:
Az időeredményt másodpercben számoljuk: a perc értékét 60-nal szorozzuk és hozzáadjuk a másodperceket, így két időeredmény egyetlen számmal összehasonlítható.
A versenyeket sorban olvassuk, és az előző verseny idejét egy változóban tároljuk. Ha az aktuális idő kisebb, mint az előzőé, a számlálót eggyel növeljük.
A helyezés nincs hatással az eredményre, ezért beolvassuk, de nem használjuk. Az időigény O(N).
*/
/*
Hint 1: || Az időeredményt alakítsd át egyetlen egész számmá (másodperc), így az összehasonlítás egyszerű lesz. ||
Hint 2: || Elég az előző verseny idejét egy változóban megőrizni, és minden újabb versenynél azzal összevetni a mostanit. Az első versenynek nincs előzője, azt nem számoljuk. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int db = 0;
    int elozo = 0;
    for (int i = 0; i < n; i++) {
        int helyezes, perc, masodperc;
        cin >> helyezes >> perc >> masodperc;
        int ido = perc * 60 + masodperc;
        if (i > 0 && ido < elozo) {
            db++;
        }
        elozo = ido;
    }
    cout << db << endl;
    return 0;
}
