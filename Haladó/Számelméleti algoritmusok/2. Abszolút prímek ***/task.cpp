/*
 * Egy M és N közé eső abszolút prím keresése. Egy szám abszolút prím, ha
 * minden különböző számjegy-permutációja is prímszám. A megoldás végigpróbálja
 * a prímeket, és a permutációkat rendezve kiírja.
 
Hint 1: || Csak az M és N közötti prímeket érdemes vizsgálni, a többi biztosan nem lehet jó. ||
Hint 2: || Egy jelölt szám összes különböző számjegy-permutációját generáld le, a vezető nullásakat hagyd ki, és ellenőrizd, hogy mind prím-e. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    auto primes = sieve_primes(1000);
    int answer = -1;
    vector<int> permutations;
    for (int x = m; x <= n; ++x) {
        if (!is_prime_int(x, primes)) continue;
        string s = to_string(x);
        sort(s.begin(), s.end());
        bool ok = true;
        vector<int> seen;
        do {
            if (s[0] == '0') continue;
            int y = stoi(s);
            if (!is_prime_int(y, primes)) {
                ok = false;
                break;
            }
            seen.push_back(y);
        } while (next_permutation(s.begin(), s.end()));
        if (ok) {
            answer = x;
            sort(seen.begin(), seen.end());
            seen.erase(unique(seen.begin(), seen.end()), seen.end());
            permutations = seen;
            break;
        }
    }
    if (answer == -1) {
        cout << 0 << '\n' << 0 << '\n';
        return 0;
    }
    cout << answer << '\n';
    for (int i = 0; i < (int)permutations.size(); ++i) {
        if (i) cout << ' ';
        cout << permutations[i];
    }
    cout << '\n';
    return 0;
}
