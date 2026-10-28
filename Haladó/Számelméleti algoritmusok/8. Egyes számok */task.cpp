/*
Megoldás lényege:
A számjegyösszeg ismételt képzése végül a szám digitális gyökét adja, ami pozitív szám esetén akkor 1, ha a szám 9-cel osztva 1 maradékot ad. A számjegyösszeg 9-cel osztva ugyanazt a maradékot adja, mint maga a szám, így elég egyszer összeadni a számjegyeket, és megnézni, hogy az összeg 9-cel osztva 1-et ad-e. A bemenet legfeljebb 100 jegyű, ezért a számot sztringként olvassuk be, és egyetlen menetben összegezzük a számjegyeket, O(jegyek száma) időben.
*/
/*
Hint 1: || A többszöri számjegyösszeg végül a digitális gyökhöz vezet, nem kell sokszor újraszámolni. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int64 sum = digit_sum_string(s);
    cout << (sum % 9 == 1 ? "EGYES" : "NEM EGYES") << '\n';
    return 0;
}
