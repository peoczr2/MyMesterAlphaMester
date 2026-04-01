/*
   Autókódolás: a megadott számmal azonos számú 1-est tartalmazó előző és
   következő számot kell kiírni.
*/
#include <bits/stdc++.h>
using namespace std;

static bool nextSame(unsigned long long n, unsigned long long& ans) {
    unsigned long long c = n;
    int c0 = 0, c1 = 0;
    while ((c & 1ULL) == 0 && c != 0) {
        ++c0;
        c >>= 1;
    }
    while ((c & 1ULL) == 1) {
        ++c1;
        c >>= 1;
    }
    int p = c0 + c1;
    if (p >= 63 || c1 == 0) return false;
    ans = n | (1ULL << p);
    ans &= ~((1ULL << p) - 1ULL);
    ans |= (1ULL << (c1 - 1)) - 1ULL;
    return true;
}

static bool prevSame(unsigned long long n, unsigned long long& ans) {
    unsigned long long temp = n;
    int c1 = 0;
    while ((temp & 1ULL) == 1) {
        ++c1;
        temp >>= 1;
    }
    if (temp == 0) return false;
    int c0 = 0;
    while ((temp & 1ULL) == 0 && temp != 0) {
        ++c0;
        temp >>= 1;
    }
    if (c0 == 0) return false;
    int p = c0 + c1;
    ans = n;
    ans &= (~0ULL) << (p + 1);
    unsigned long long mask = (1ULL << (c1 + 1)) - 1ULL;
    ans |= mask << (c0 - 1);
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long n;
    cin >> n;
    unsigned long long prv, nxt;
    if (prevSame(n, prv)) cout << prv << '\n';
    else cout << -1 << '\n';
    if (nextSame(n, nxt)) cout << nxt << '\n';
    else cout << -1 << '\n';
    return 0;
}