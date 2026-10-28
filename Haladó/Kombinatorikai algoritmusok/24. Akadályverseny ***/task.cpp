/*
Megoldás lényege:
A feltétel szerint a próbák nehézsége felváltva nő és csökken, vagyis a sorrend
alternáló permutáció. Ha N>1, az alternáló permutációk száma 2·E_N, ahol E_N az
Euler-féle zigzag-szám, azaz az egyik irányban kezdődő alternáló permutációk száma.
Az E_N az Entringer-háromszöggel számolható: E(0,0) = 1, E(n,0) = 0, ha n>0, és
E(n,k) = E(n,k-1) + E(n-1,n-k), ha 1<=k<=n. Ekkor E_n = E(n,n). A kettes szorzó a
két kezdési irány miatt kell. N=1 esetén a válasz 1.
Időigény O(N^2) nagy egész számokkal számolva; N<=23 esetén az eredmény 2·10^18
alatt marad.
*/
/*
Hint 1: || A szomszédos próbák nehézsége felváltva nő és csökken, tehát a sorrend fel-le-fel-... vagy le-fel-le-... alakú. A két kezdési irányt külön kell számolni, és N=4 esetén a példában 10 ilyen sorrend van. ||
Hint 2: || Egy háromszög táblázat adja a számokat: E(0,0) = 1, E(n,0) = 0 ha n>0, és E(n,k) = E(n,k-1) + E(n-1,n-k) ha 1<=k<=n. Az n-edik sor utolsó eleme E(n,n), ami az egy irányban kezdődő alternáló permutációk száma. ||
Hint 3: || A válasz E(N,N) kétszerese, ha N>1, és 1, ha N=1. Mivel a számok gyorsan nőnek (N=23 esetén 10^18 körüli), elég egy sort tárolni, és az összeadásokat nagy egész számokkal végezni. Időigény O(N^2). ||
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