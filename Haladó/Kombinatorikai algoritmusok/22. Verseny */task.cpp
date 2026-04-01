/*
Megoldás lényege:
A kiosztott jutalmak száma egy N összegű, szigorúan csökkenő pozitív részösszeg-
felbontás. Ez pontosan az N szám partícióinak a száma különböző tagokkal,
ahol a tagok legfeljebb M értékűek lehetnek.

Ezért egy egyszerű 1D dinamikus program elég: minden részméretet egyszer
felhasználhatunk, és visszafelé frissítjük az összegeket.
*/

#include <bits/stdc++.h>
using namespace std;

struct BigInt {
    static const int BASE = 1000000000;
    vector<int> d;

    BigInt(long long x = 0) { *this = x; }

    BigInt& operator=(long long x) {
        d.clear();
        if (x == 0) return *this;
        while (x > 0) {
            d.push_back(int(x % BASE));
            x /= BASE;
        }
        return *this;
    }

    BigInt& operator+=(const BigInt& other) {
        long long carry = 0;
        if (d.size() < other.d.size()) d.resize(other.d.size(), 0);
        for (size_t i = 0; i < other.d.size() || carry; ++i) {
            if (i == d.size()) d.push_back(0);
            long long cur = carry + d[i] + (i < other.d.size() ? other.d[i] : 0LL);
            d[i] = int(cur % BASE);
            carry = cur / BASE;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const BigInt& x) {
        if (x.d.empty()) return os << 0;
        os << x.d.back();
        for (int i = (int)x.d.size() - 2; i >= 0; --i) {
            os << setw(9) << setfill('0') << x.d[i];
        }
        return os;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<BigInt> dp(n + 1);
    dp[0] = 1;
    for (int part = 1; part <= m; ++part) {
        for (int sum = n; sum >= part; --sum) {
            dp[sum] += dp[sum - part];
        }
    }

    cout << dp[n] << '\n';
    return 0;
}