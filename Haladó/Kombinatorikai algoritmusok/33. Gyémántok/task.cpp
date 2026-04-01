/*
Megoldás lényege:
N gyémántot úgy osztunk szét, hogy a kapó munkások mind különböző számú
gyémántot kapjanak. Ez a N szám különböző részekre bontott partícióinak száma.

A klasszikus 1D DP-ben minden részméretet legfeljebb egyszer használhatunk,
ezért az összegeket visszafelé frissítjük.
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

    int n;
    if (!(cin >> n)) return 0;

    vector<BigInt> dp(n + 1);
    dp[0] = 1;
    for (int part = 1; part <= n; ++part) {
        for (int sum = n; sum >= part; --sum) {
            dp[sum] += dp[sum - part];
        }
    }

    cout << dp[n] << '\n';
    return 0;
}