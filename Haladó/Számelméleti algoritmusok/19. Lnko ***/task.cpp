/*
Megoldás lényege: a kulcsazonosság gcd(2^N-1, 2^M-1) = 2^gcd(N,M)-1, így minden lekérdezésre elég a gcd(N,M)
értéket meghatározni az Euklideszi algoritmussal. A 2^k-1 nagy számokat 10^9-es alapú egész számként tároljuk;
a sorozat tagjai a 2^k-1 = 2*(2^(k-1)-1)+1 összefüggéssel egymásból kiszámolhatók. Mivel N, M <= 830, legfeljebb
830 ilyen lépés kell, a válasz pedig a 2^g-1 szám kiírása.
*/
/*
Hint 1: || A kulcsazonosság: gcd(2^N-1, 2^M-1) = 2^gcd(N,M)-1, így a feladat visszavezethető a gcd(N,M) kiszámolására. ||
Hint 2: || Miután megvan a g = gcd(N,M), a 2^g-1 nagy számot kell előállítani; erre a 2^k-1 = 2*(2^(k-1)-1)+1 összefüggés és a 10^9-es alapú számábrázolás elég. ||
*/

#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int64 gcdll(int64 a, int64 b) {
    while (b) {
        int64 t = a % b;
        a = b;
        b = t;
    }
    return a >= 0 ? a : -a;
}

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
