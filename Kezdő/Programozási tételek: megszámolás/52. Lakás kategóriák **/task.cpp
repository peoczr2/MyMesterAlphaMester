/*
Megoldás lényege:
A lakások árát a feladat szerint nem kell figyelembe venni, csak a területükkel foglalkozunk. A területből egyetlen képlettel kapjuk meg a kategória sorszámát: a terület tízzel való egész osztása adja a 0-tól induló indexet.
A legnagyobb, 190–200 közötti kategória 19-es indexet kap, és a 200 is ide esik, ezért az indexet 19-re korlátozzuk.
A 20 kategóriához egy 20 elemű számlálótömböt használunk, és minden lakásnál a megfelelő elemet növeljük. A végén a tömb elemeit sorban kiírjuk.
Az időigény O(N), a tárigény O(1), mert a tömb mérete állandó.
*/
/*
Hint 1: || Az árral nem kell foglalkozni, csak a lakások területe számít. Minden lakásnál határozd meg, melyik kategóriába esik a területe, és ott növeld a darabszámot. ||
Hint 2: || A kategória sorszáma a terület tízzel való egészosztásából adódik, mert a 0–9, 10–19, … intervallumok tízesével követik egymást. Figyelj a felső határra: a 200 a 190–200 kategóriába tartozik, így a sorszámot 19-re kell korlátozni. ||
Hint 3: || Tarts egy 20 elemű tömböt, amelynek minden eleme 0-ról indul. Miután az összes lakást beolvastad és a számlálókat növelted, a tömb elemeit sorban kiírva megkapod az eredményt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int kategoria[20] = {0};
    for (int i = 0; i < n; i++) {
        int ar, terulet;
        cin >> ar >> terulet;
        int index = min(terulet / 10, 19);
        kategoria[index]++;
    }
    for (int i = 0; i < 20; i++) {
        cout << kategoria[i] << (i < 19 ? " " : "\n");
    }
    return 0;
}
