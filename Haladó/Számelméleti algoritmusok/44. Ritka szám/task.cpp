/*
 * A ritka számok azok, որոնց bináris alakjában nincs egymás melletti 1-es.
 * Az N-edik ilyen számot Fibonacci-számlálással állítjuk elő.
 
Hint 1: || A bináris alakban szomszédos 1-esek tiltása miatt a darabszámok Fibonacci-szerű rekurziót követnek. ||
Hint 2: || Előbb számold meg, hány jó szám van adott bithosszon, utána bitenként döntsd el greedyn, hogy a keresett N-edik számnál 0 vagy 1 kerülhet-e a következő helyre. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;

    vector<long long> exact(65, 0), pref(65, 0);
    exact[1] = 1;
    exact[2] = 1;
    for (int len = 3; len <= 64; ++len) exact[len] = exact[len - 1] + exact[len - 2];
    for (int len = 1; len <= 64; ++len) pref[len] = pref[len - 1] + exact[len];

    int len = 1;
    while (pref[len] < n) ++len;
    long long rank = n - pref[len - 1];

    string bits(len, '0');
    bits[0] = '1';
    int prev = 1;
    for (int pos = 1; pos < len; ++pos) {
        int rem = len - pos - 1;
        long long count_if_zero = exact[rem + 1];
        if (prev == 1) {
            bits[pos] = '0';
            prev = 0;
        } else {
            if (rank <= count_if_zero) {
                bits[pos] = '0';
                prev = 0;
            } else {
                rank -= count_if_zero;
                bits[pos] = '1';
                prev = 1;
            }
        }
    }

    long long value = 0;
    for (char c : bits) value = value * 2 + (c - '0');
    cout << value << '\n';
    return 0;
}
