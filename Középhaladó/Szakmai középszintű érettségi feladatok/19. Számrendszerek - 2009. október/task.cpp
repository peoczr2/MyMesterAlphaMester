/*
Megoldás lényege:
A 16 bites bináris számot balról jobbra négy, egyenként 4 bites csoportra osztjuk. Minden csoport értékét úgy kapjuk meg, hogy a bitjein balról jobbra haladva az eddigi értéket megduplázzuk és hozzáadjuk az új bitet; így az érték 0 és 15 közé esik. Ez az érték egyetlen hexadecimális jegyet ad, amelyet a "0123456789ABCDEF" karakterlánc megfelelő karaktereként írunk ki. A négy jegy egymás után adja a hexadecimális alakot, nagybetűkkel. Az időigény O(N), ahol N legfeljebb 10^4, és minden számnál állandó (16 karakteres) munkát végzünk.
*/
/*
Hint 1: || Egy 16 bites szám hexadecimális alakja pontosan négy jegyű, és minden jegy a bináris szám egy-egy 4 bites részletéből származik. Ezért a bitsorozatot négy darab, egyenként 4 karakteres csoportra kell bontanod. ||
Hint 2: || Egy 4 bites csoport értékét a bitek balról jobbra haladó feldolgozásával kapod meg: minden lépésben szorozd kettővel az eddigi értéket, és add hozzá az aktuális bitet. Az így kapott 0-15 közötti számhoz a "0123456789ABCDEF" karakterlánc megfelelő karaktere tartozik. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const string jegyek = "0123456789ABCDEF";

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        while (s.size() < 16) {
            s = "0" + s; // rövidebb bemenet esetén balról nullákkal egészítjük ki
        }

        string hex;
        for (int csoport = 0; csoport < 4; csoport++) {
            int ertek = 0;
            for (int b = 0; b < 4; b++) {
                ertek = ertek * 2 + (s[4 * csoport + b] - '0');
            }
            hex += jegyek[ertek];
        }

        cout << hex << "\n";
    }

    return 0;
}
