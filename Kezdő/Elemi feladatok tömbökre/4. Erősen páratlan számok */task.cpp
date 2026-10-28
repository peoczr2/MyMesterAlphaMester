/*
Megoldás lényege:
A számot karakterláncként olvassuk be, mert akár 10 000 számjegyű is lehet, így egész típusba nem férne bele. A ciklusban mindig az aktuális szám utolsó számjegyét vizsgáljuk, mert ez dönti el a paritást. Ha az aktuális szám páros, akkor ez a sorozat első páros tagja: a válasz NEM EROSEN PARATLAN, a második sorban pedig ez a szám áll. Ha a szám páratlan és már egyjegyű, akkor erősen páratlan. Egyéb esetben a számjegyek összegét képezzük, és a lépést megismételjük. A számjegyösszeg már az első lépés után legfeljebb ötjegyű, így a sorozat gyorsan egyjegyűvé válik, és a munkaigény a bemenet hosszával arányos.
*/
/*
Hint 1: || Egy szám páros vagy páratlan voltát az utolsó számjegye dönti el, így a teljes számot nem kell számmá alakítanod. Gondold végig, mikor kell megállnia a vizsgálatnak. ||
Hint 2: || Ismételten képezd a számjegyek összegét, és minden lépésben nézd meg, páros-e az aktuális érték. Az első páros értéket kell kiírni; ha egyjegyű páratlan szám lesz a vége, a szám erősen páratlan. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    while (true) {
        int utolso = s.back() - '0';
        if (utolso % 2 == 0) {
            // Az első páros szám a sorozatban
            cout << "NEM EROSEN PARATLAN\n" << s << "\n";
            return 0;
        }
        if (s.size() == 1) {
            cout << "EROSEN PARATLAN\n";
            return 0;
        }
        long long osszeg = 0;
        for (char c : s) osszeg += c - '0';
        s = to_string(osszeg);
    }
}
