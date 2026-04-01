/*
 * N! prímfaktorizálása Legendre-képlettel.
 
Hint 1: || Egy prímszám kitevője az `N!`-ben nem úgy jön ki, hogy felszorzod a faktoriálist, hanem Legendre-képlettel. ||
Hint 2: || Minden prímre add össze `N/p + N/p^2 + N/p^3 + ...` egészrészeit, ez adja a kitevőt a felbontásban. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    auto primes = sieve_primes(n);
    for (int p : primes) {
        long long e = 0, t = n;
        while (t) {
            t /= p;
            e += t;
        }
        cout << p << ' ' << e << '\n';
    }
    return 0;
}
