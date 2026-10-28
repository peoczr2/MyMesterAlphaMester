/*
Megoldás lényege:
A tiltott párok (cd, ce, ed, ee) miatt a következő betű megengedettsége csak az aktuális betűtől függ, ezért elég az utolsó betű szerinti darabszámokat nyilvántartani: egy 5 állapotú DP-t használunk.
A c és az e után csak a, b vagy c jöhet, a többi betű után bármi. Így az a, b, c állapotok új értéke az összes előző érték összege, a d és az e állapotoké pedig az a, b, d előző értékek összege.
A láncok száma legfeljebb 5^30 ≈ 9·10^20, ami már meghaladja a 64 bites egész tartományát, ezért nagy egész számokkal (BigInt) számolunk; az időigény O(N) nagy egész összeadás.
*/
/*
Hint 1: || Csak az utolsó betű számít: írd fel, mely betűk állhatnak egy adott betű után, és ezek alapján vezess be betűnkénti darabszám-állapotokat. ||
Hint 2: || A c és az e után csak a, b vagy c jöhet, így az új darabszámok egyszerű összegek lesznek; mivel a végeredmény nagy, a számokat nagy egész típussal add össze. ||
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

    vector<BigInt> dp(5, 1), nextDp(5);
    for (int len = 2; len <= n; ++len) {
        BigInt total;
        for (const auto& x : dp) total += x;

        nextDp[0] = total;
        nextDp[1] = total;
        nextDp[2] = total;
        nextDp[3] = dp[0];
        nextDp[3] += dp[1];
        nextDp[3] += dp[3];
        nextDp[4] = dp[0];
        nextDp[4] += dp[1];
        nextDp[4] += dp[3];
        dp.swap(nextDp);
    }

    BigInt ans;
    for (const auto& x : dp) ans += x;
    cout << ans << '\n';
    return 0;
}