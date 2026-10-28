/*
Megoldás lényege:
Minden versenyzőnél a 6 dobást egymás után olvassuk be, és egy változóban tartjuk az eddig talált utolsó sikeres dobás sorszámát (kezdetben 0). A sikertelen dobás értéke -1, a sikeres dobásoké 1 és 9000 közötti pozitív szám, így minden nem -1 dobásnál felülírjuk a változót az aktuális sorszámmal, és a végén ez lesz az utolsó sikeres dobás sorszáma. Versenyzőnként 6 lépés történik, az összidőigény O(6·N), ami a korlátok mellett bőven elég.
*/
/*
Hint 1: || Nem kell a dobásokat eltárolni: elég egy olyan változó, amelyben a legutóbb látott nem -1 dobás sorszámát tartod, miközben beolvasod őket. ||
Hint 2: || A változót 0-val indítsd (ha nincs sikeres dobás, ez marad), és minden j-edik dobás beolvasása után, ha a dobás nem -1, írd felül a változót j-vel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int utolso = 0;
        for (int j = 1; j <= 6; j++) {
            int d;
            cin >> d;
            if (d != -1) {
                utolso = j;
            }
        }
        if (i > 0) {
            cout << ' ';
        }
        cout << utolso;
    }
    cout << '\n';
    return 0;
}
