/*
 * Az intervallumban azokat a számokat írjuk ki, amelyekre egyetlen négyzetszám
 * sem osztójuk.
 
Hint 1: || A keresett számok pontosan a squarefree számok, vagyis amelyeket nem oszt semelyik `p^2`. ||
Hint 2: || Az `[A,B]` intervallumban jelöld meg minden prímszám négyzetének többszöröseit, és ami nem lett megjelölve, azt kell kiírni. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;
    vector<char> bad(b - a + 1, false);
    vector<int> primes = sieve_primes((int)sqrt(b) + 1);
    for (int p : primes) {
        long long sq = 1LL * p * p;
        long long first = (a + sq - 1) / sq * sq;
        for (long long x = first; x <= b; x += sq) bad[x - a] = true;
    }
    bool first = true;
    for (int x = a; x <= b; ++x) if (!bad[x - a]) {
        if (!first) cout << ' ';
        first = false;
        cout << x;
    }
    cout << '\n';
    return 0;
}
