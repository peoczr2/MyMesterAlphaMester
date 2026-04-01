#pragma once

#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

inline int64 gcdll(int64 a, int64 b) {
    while (b) {
        int64 t = a % b;
        a = b;
        b = t;
    }
    return a >= 0 ? a : -a;
}

inline vector<int> sieve_primes(int limit) {
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

inline bool is_prime_int(int64 n, const vector<int>& primes) {
    if (n < 2) return false;
    for (int p : primes) {
        if (1LL * p * p > n) break;
        if (n % p == 0) return n == p;
    }
    return true;
}

inline vector<pair<int64, int>> factorize_int(int64 n) {
    vector<pair<int64, int>> result;
    for (int64 p = 2; p * p <= n; ++p) {
        if (n % p != 0) continue;
        int exponent = 0;
        while (n % p == 0) {
            n /= p;
            ++exponent;
        }
        result.push_back({p, exponent});
    }
    if (n > 1) result.push_back({n, 1});
    return result;
}

inline bool is_palindrome(const string& s) {
    for (int i = 0, j = (int)s.size() - 1; i < j; ++i, --j) {
        if (s[i] != s[j]) return false;
    }
    return true;
}

inline string strip_leading_zeros(const string& s) {
    size_t pos = s.find_first_not_of('0');
    if (pos == string::npos) return "0";
    return s.substr(pos);
}

inline int64 digit_sum_string(const string& s) {
    int64 sum = 0;
    for (char c : s) sum += c - '0';
    return sum;
}

inline string smallest_valid_permutation(string s) {
    sort(s.begin(), s.end());
    if (s[0] != '0') return s;
    int pos = 0;
    while (pos < (int)s.size() && s[pos] == '0') ++pos;
    if (pos == (int)s.size()) return s;
    swap(s[0], s[pos]);
    sort(s.begin() + 1, s.end());
    return s;
}
