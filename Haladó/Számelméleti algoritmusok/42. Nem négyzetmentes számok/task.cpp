/*
 * Az N-edik nem squarefree szám keresése. Legyen sqfree(x) igaz, ha x nem osztható
 * egyetlen négyzetszámmal sem.
 
Hint 1: || A keresett számok éppen azok, amelyeket oszt valamely `p^2`, tehát a squarefree számok komplementere kell. ||
Hint 2: || Kis N mellett egyszerűen növeld x-et, és ellenőrizd, hogy van-e olyan `p`, amelyre `p^2 | x`; az N-edik ilyen lesz a válasz. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int count = 0;
    for (int x = 1;; ++x) {
        bool ok = true;
        for (int p = 2; 1LL * p * p <= x; ++p) {
            if (x % (p * p) == 0) { ok = false; break; }
        }
        if (!ok) {
            ++count;
            if (count == n) {
                cout << x << '\n';
                return 0;
            }
        }
    }
}
