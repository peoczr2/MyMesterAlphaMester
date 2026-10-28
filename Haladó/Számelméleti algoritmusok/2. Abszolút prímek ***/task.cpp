/*
Megoldás lényege: M és N között növekvő sorrendben vizsgáljuk a számokat, és az első olyan prímnél állunk meg,
amelynek minden különböző számjegy-permutációja is prím. Az 1000-ig terjedő prímeket szitával állítjuk elő.
A jelölt számjegyeit rendezve a next_permutation adja a permutációkat; a vezető nullával kezdődő sorrendeket
kihagyjuk, a többit prímvizsgálattal ellenőrizzük. A számok legfeljebb háromjegyűek, ezért az időigény elhanyagolható.
*/
/*
Hint 1: || A keresett szám csak prím lehet, ezért elég az [M,N] intervallum prímjeit növekvő sorrendben végignézni, és az első megfelelőnél megállni. ||
Hint 2: || Egy jelölt szám összes különböző számjegy-permutációját a rendezett számjegyekből indulva generáld (next_permutation), a vezető nullásakat hagyd ki, és ellenőrizd, hogy mind prím-e. ||
*/

#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

vector<int> sieve_primes(int limit) {
    vector<bool> is_prime(limit + 1, true);
    if (limit >= 0) is_prime[0] = false;
    if (limit >= 1) is_prime[1] = false;
    for (int i = 2; 1LL * i * i <= limit; ++i) {
        if (!is_prime[i]) continue;
        for (int j = i * i; j <= limit; j += i) is_prime[j] = false;
    }
    vector<int> primes;
    for (int i = 2; i <= limit; ++i) if (is_prime[i]) primes.push_back(i);
    return primes;
}

bool is_prime_int(int64 n, const vector<int>& primes) {
    if (n < 2) return false;
    for (int p : primes) {
        if (1LL * p * p > n) break;
        if (n % p == 0) return n == p;
    }
    return true;
}

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
