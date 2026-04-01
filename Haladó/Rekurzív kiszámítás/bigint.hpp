#pragma once

#include <bits/stdc++.h>

struct BigInt {
    static constexpr int BASE = 1000000000;
    std::vector<int> d;

    BigInt(long long v = 0) { *this = v; }

    BigInt& operator=(long long v) {
        d.clear();
        if (v == 0) return *this;
        while (v > 0) {
            d.push_back((int)(v % BASE));
            v /= BASE;
        }
        return *this;
    }

    bool isZero() const { return d.empty(); }

    BigInt& operator+=(const BigInt& other) {
        int n = std::max(d.size(), other.d.size());
        d.resize(n, 0);
        long long carry = 0;
        for (int i = 0; i < n; ++i) {
            long long cur = carry + d[i] + (i < (int)other.d.size() ? other.d[i] : 0LL);
            d[i] = (int)(cur % BASE);
            carry = cur / BASE;
        }
        while (carry > 0) {
            d.push_back((int)(carry % BASE));
            carry /= BASE;
        }
        trim();
        return *this;
    }

    BigInt& operator*=(long long m) {
        if (isZero() || m == 0) {
            d.clear();
            return *this;
        }
        long long carry = 0;
        for (int i = 0; i < (int)d.size(); ++i) {
            long long cur = carry + 1LL * d[i] * m;
            d[i] = (int)(cur % BASE);
            carry = cur / BASE;
        }
        while (carry > 0) {
            d.push_back((int)(carry % BASE));
            carry /= BASE;
        }
        trim();
        return *this;
    }

    friend BigInt operator+(BigInt a, const BigInt& b) { a += b; return a; }
    friend BigInt operator*(BigInt a, long long m) { a *= m; return a; }

    friend std::ostream& operator<<(std::ostream& os, const BigInt& x) {
        if (x.d.empty()) return os << 0;
        os << x.d.back();
        for (int i = (int)x.d.size() - 1; i-- > 0;) {
            os << std::setw(9) << std::setfill('0') << x.d[i];
        }
        return os;
    }

private:
    void trim() {
        while (!d.empty() && d.back() == 0) d.pop_back();
    }
};
