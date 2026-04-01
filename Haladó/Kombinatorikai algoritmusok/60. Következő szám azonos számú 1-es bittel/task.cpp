/*
   Következő szám azonos számú 1-es bittel: klasszikus bitműveletes megoldás.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long n;
    cin >> n;

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
    if (p >= 63 || c1 == 0) {
        cout << -1 << '\n';
        return 0;
    }

    n |= (1ULL << p);
    n &= ~((1ULL << p) - 1ULL);
    n |= (1ULL << (c1 - 1)) - 1ULL;
    cout << n << '\n';
    return 0;
}