/*
 * Euler-féle phi függvény számítása prímtényezős bontással.
 
Hint 1: || Az Euler-féle phi függvényhez a szám különböző prímosztóira van szükség, nem a teljes osztólistára. ||
Hint 2: || Ha `N` osztható egy `p` prímmel, akkor a válaszban egyszer kell megszorozni `(1 - 1/p)` tényezővel, vagyis `ans -= ans/p`. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 n;
    cin >> n;
    int64 result = n;
    for (int64 p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    cout << result << '\n';
    return 0;
}
