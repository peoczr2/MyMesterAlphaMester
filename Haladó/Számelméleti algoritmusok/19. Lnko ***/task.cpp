/*
 * gcd(2^N-1, 2^M-1) = 2^gcd(N,M)-1. A nagy értékeket saját base-1e9 big-integerrel
 * állítjuk elő.
 
Hint 1: || A kulcsazonosság itt az, hogy `gcd(2^N-1, 2^M-1) = 2^gcd(N,M)-1`. ||
Hint 2: || Miután kiszámoltad `gcd(N,M)`-et, már csak a `2^g - 1` nagy szám alakját kell előállítani. ||
*/

#include "../common.hpp"

struct BigInt {
    static const int BASE = 1000000000;
    vector<int> a;

    BigInt(long long value = 0) {
        if (value == 0) return;
        while (value > 0) {
            a.push_back((int)(value % BASE));
            value /= BASE;
        }
    }

    void mul2() {
        long long carry = 0;
        for (int& digit : a) {
            long long cur = 2LL * digit + carry;
            digit = (int)(cur % BASE);
            carry = cur / BASE;
        }
        if (carry) a.push_back((int)carry);
    }

    void add1() {
        int carry = 1;
        for (int& digit : a) {
            int cur = digit + carry;
            if (cur >= BASE) {
                digit = cur - BASE;
                carry = 1;
            } else {
                digit = cur;
                carry = 0;
                break;
            }
        }
        if (carry) a.push_back(1);
    }

    string str() const {
        if (a.empty()) return "0";
        string s = to_string(a.back());
        for (int i = (int)a.size() - 2; i >= 0; --i) {
            string part = to_string(a[i]);
            s += string(9 - part.size(), '0') + part;
        }
        return s;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    vector<pair<int,int>> queries(t);
    int mx = 0;
    for (int i = 0; i < t; ++i) {
        cin >> queries[i].first >> queries[i].second;
        mx = max(mx, (int)gcdll(queries[i].first, queries[i].second));
    }
    vector<BigInt> ans(mx + 1);
    ans[1] = BigInt(1);
    for (int k = 2; k <= mx; ++k) {
        ans[k] = ans[k - 1];
        ans[k].mul2();
        ans[k].add1();
    }
    for (auto [n, m] : queries) {
        int g = gcdll(n, m);
        cout << ans[g].str() << '\n';
    }
    return 0;
}
