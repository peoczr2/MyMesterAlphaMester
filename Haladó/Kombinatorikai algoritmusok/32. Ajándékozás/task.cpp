/*
Megoldás lényege:
Az N szaloncukrot úgy osztjuk szét, hogy a csomagok sorrendje nem számít, és egy
csomagba legfeljebb M szaloncukor kerülhet, így a feladat az N szám legfeljebb
M-es tagokból álló felbontásainak (partícióinak) számát kérdezi.
Az 1D DP-ben dp[s] azt tárolja, hányféleképpen állítható elő az s összeg az
eddig figyelembe vett csomagméretekből. A csomagméreteket egyenként, 1-től M-ig
dolgozzuk fel, és egy méret bevételekor az s értékeket növekvő sorrendben
frissítjük: dp[s] += dp[s - méret]. Így egy méret tetszőleges számszor
szerepelhet, a tagok sorrendje pedig nem számít.
A végső válasz dp[N], a számolás O(N·M) összeadás. A kód a számokhoz BigInt
típust használ biztonsági tartalékként, bár N ≤ 100 esetén a végeredmény akár 32
bites egészbe is belefér.
*/
/*
Hint 1: || A csomagok sorrendje nem számít, így két felosztás akkor azonos, ha
ugyanazok a csomagméretek szerepelnek benne. A kérdés tehát az N szám olyan
felbontásainak száma, ahol minden tag legfeljebb M. ||
Hint 2: || Legyen dp[s] az s összeg előállításainak száma az eddig megengedett
méretekből (kezdetben dp[0] = 1). Egy m méret bevételekor minden s-re, növekvő s
szerint, dp[s] += dp[s - m]. A végén dp[N] a válasz. ||
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
        for (int sum = part; sum <= n; ++sum) {
            dp[sum] += dp[sum - part];
        }
    }

    cout << dp[n] << '\n';
    return 0;
}