/*
Az N-hez relatív prím, nála kisebb természetes számok száma az Euler-féle phi függvény: N * (1 - 1/p1) * (1 - 1/p2) * ... a különböző p prímosztókra.
A prímosztókat próbaosztással keressük (p * p <= n), és minden megtalált p-nél n-ből teljesen kiosztjuk a p-t, az eredményre pedig az ans -= ans / p lépést alkalmazzuk.
Mivel p osztja az aktuális eredményt, az egészosztás pontos; a maradék n > 1 esetén maga is prímosztó.
Az időigény O(sqrt(N)), ami N <= 10^8 mellett bőven belefér a 0,1 mp-es limitbe.
*/
/*
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
