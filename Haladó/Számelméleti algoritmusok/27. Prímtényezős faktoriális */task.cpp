/*
 * N! prímtényezős felbontásának kiszámításához Legendre-képletet használunk: egy p prím kitevője N!-ban
 * N/p + N/p^2 + N/p^3 + ... (egész osztásokkal), vagyis az 1..N számok közül a p, p^2, p^3, ... többszöröseinek darabszáma.
 * A prímeket a sieve_primes függvénnyel gyűjtjük ki 1..N között, és mindegyikre ezt a sorozatot összegezzük.
 * Így a prímek növekvő sorrendben kerülnek a kimenetbe, az időigény pedig O(N log log N).
 */
/*
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
