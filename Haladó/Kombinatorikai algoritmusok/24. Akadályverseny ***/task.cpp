/*
Megoldás lényege:
A helyes sorrendek az alternáló permutációk. Ezek száma az Euler-féle
zigzag-számokkal írható le, amelyeket az Entringer-triangle dinamikával
számolunk.

Az N hosszú, először növekvő permutációk száma a triangle utolsó eleme.
Mivel a feladat nem rögzíti, hogy a sorozat emelkedéssel vagy süllyedéssel
induljon, a válasz ennek kétszerese (N>1 esetén).
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

    void mul(int m) {
        if (m == 0 || d.empty()) {
            d.clear();
            return;
        }
        long long carry = 0;
        for (int& x : d) {
            long long cur = carry + 1LL * x * m;
            x = int(cur % BASE);
            carry = cur / BASE;
        }
        while (carry > 0) {
            d.push_back(int(carry % BASE));
            carry /= BASE;
        }
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

    vector<BigInt> prev(1), cur;
    prev[0] = 1;
    for (int len = 1; len <= n; ++len) {
        cur.assign(len + 1, 0);
        cur[0] = 0;
        for (int k = 1; k <= len; ++k) {
            cur[k] = cur[k - 1];
            cur[k] += prev[len - k];
        }
        prev.swap(cur);
    }

    BigInt ans = prev[n];
    if (n > 1) ans.mul(2);
    cout << ans << '\n';
    return 0;
}