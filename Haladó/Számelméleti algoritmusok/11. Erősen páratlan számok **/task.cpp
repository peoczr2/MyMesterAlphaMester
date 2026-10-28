/*
Megoldás lényege:
A definíció szerint egy páratlan szám akkor erősen páratlan, ha egyjegyű, vagy a
számjegyeinek összege erősen páratlan. Ezt a láncot követjük: egyjegyű (páratlan)
szám esetén IGEN a válasz; különben vesszük a számjegyek összegét. Ha ez páros,
NEM a válasz, és maga az összeg a kiírandó első páros szám. Ha páratlan és többjegyű,
ugyanezt a lépést megismételjük rá. A lánc minden lépésben jelentősen lerövidül,
így a teljes futásidő az N jegyeinek számával (legfeljebb 100 000) arányos.
*/
/*
Hint 1: || A definíció rekurzív: egyjegyű szám mindig megfelel, többjegyűnél a számjegyösszeget kell ugyanígy vizsgálni, ezért egy ciklus elég. ||
Hint 2: || Az első páros számjegyösszegnél megállhatsz: az ott kapott összeget kell kiírni NEM után, és csak akkor IGEN a válasz, ha a lánc egyjegyű páratlan számhoz ér. ||
*/

#include "../common.hpp"

static long long sum_digits(const string& s) {
    long long sum = 0;
    for (char c : s) sum += c - '0';
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    while (s.size() > 1) {
        long long sum = sum_digits(s);
        if (sum % 2 == 0) {
            cout << "NEM\n" << sum << '\n';
            return 0;
        }
        s = to_string(sum);
    }
    cout << "IGEN\n";
    return 0;
}
