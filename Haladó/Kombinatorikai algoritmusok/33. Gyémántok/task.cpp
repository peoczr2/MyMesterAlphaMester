/*
Megoldás lényege:
N gyémántot osztunk szét úgy, hogy a kapó munkások mind különböző számú
gyémántot kapnak, és a munkások sorrendje nem számít, így a kérdés N különböző
részekre bontott felbontásainak számát adja meg.
Az 1D DP-ben dp[s] az s összeg előállításainak számát tárolja. Mivel minden
részméret legfeljebb egyszer szerepelhet, a méreteket egyenként dolgozzuk fel,
és az összegeket csökkenő sorrendben frissítjük: így a dp[s - méret] értéke még
nem tartalmazza az aktuális méretet, tehát egy méret nem kerül kétszer a
felosztásba.
A válasz dp[N], a számolás O(N²) összeadás, ami N ≤ 200 mellett bőven gyors.
*/
/*
Hint 1: || Egy felosztásban a kapott számok különbözőek, a munkások sorrendje
pedig nem számít, így csak a különböző tagokból álló, N-et kiadó összegeket kell
megszámolni. Ez egy 0-1 hátizsák típusú DP: minden részméretet legfeljebb
egyszer használhatunk fel. ||
Hint 2: || Legyen dp[s] az s összeg előállításainak száma az eddig figyelembe
vett méretekből (kezdetben dp[0] = 1). Egy m méret bevételekor az s értékeket
csökkenő sorrendben frissítjük: dp[s] += dp[s - m]. Ha növekvő sorrendben
haladnánk, ugyanaz az m többször is bekerülne az összegbe. ||
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