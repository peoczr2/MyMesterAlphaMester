/*
 * Egy szám különböző prímosztóinak kiszámítása faktorizálással.
 
Hint 1: || A különböző prímosztókhoz nem kell semmi extra: elég a szokásos próbaosztásos faktorizálás. ||
Hint 2: || Amikor találsz egy osztó prímet, oszd ki teljesen a számból, hogy ugyanaz a prímosztó csak egyszer kerüljön a kimenetbe. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 n;
    cin >> n;
    auto factors = factorize_int(n);
    for (int i = 0; i < (int)factors.size(); ++i) {
        if (i) cout << ' ';
        cout << factors[i].first;
    }
    cout << '\n';
    return 0;
}
