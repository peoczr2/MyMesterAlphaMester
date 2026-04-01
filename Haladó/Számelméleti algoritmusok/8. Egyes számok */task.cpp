/*
 * Egyes szám pontosan akkor keletkezik, ha a szám digitális gyöke 1, vagyis a
 * szám 9-cel osztva 1 maradékot ad.
 
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
