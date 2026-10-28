/*
Megoldás lényege:
A kiosztott utalványok száma a versenyzők sorrendjében szigorúan csökken, ezért a
nem nulla értékek különböző pozitív egészek. Így a feladat: hányféleképpen írható
fel N különböző, M-nél nem nagyobb tag összegeként. Ez egy 0/1 hátizsák-típusú DP:
minden 1..M számot legfeljebb egyszer használunk fel, és a dp tömböt az összegek
szerint nagytól kicsi felé frissítjük, hogy egy szám ne kerüljön bele kétszer.
Az eredmény N<=500 esetén 10^15 alatt marad, a BigInt-tel való tárolás ettől
függetlenül biztonságos.
Időigény O(N·M) nagy számú összeadással, ami a korlátok mellett gyors.
*/
/*
Hint 1: || A versenyzők sorrendjében a kapott utalványok száma szigorúan csökken, így a nullától különböző értékek különbözőek. A kiosztás tehát N különböző, legfeljebb M nagyságú szám összege, a tagok sorrendje nem számít. ||
Hint 2: || Tekintsük az 1..M számokat tárgyaknak, mindegyiket legfeljebb egyszer használhatjuk. Legyen dp[s] az olyan felbontások száma, amelyek összege s. Kezdetben dp[0] = 1, majd minden tárgyra az s értékeket N-től a tárgy értékéig csökkenő sorrendben frissítjük: dp[s] növelése a dp[s - tárgy] értékkel. ||
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
        for (int sum = n; sum >= part; --sum) {
            dp[sum] += dp[sum - part];
        }
    }

    cout << dp[n] << '\n';
    return 0;
}