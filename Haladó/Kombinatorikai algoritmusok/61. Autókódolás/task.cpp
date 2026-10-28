/*
Megoldás lényege:
A következő szám ugyanúgy adódik, mint az előző feladatban: a legalsó 1-esekből álló blokk fölötti első 0 bitet
1-re állítjuk. Az előző szám: a legalsó 1-esekből álló blokk fölötti első 1 bitet 0-ra csökkentjük, és a neki
alatta lévő részben a régi 1-esek számánál eggyel többet a lehető legfelső pozíciókba írunk. Ha a szám csupa
1-esből áll (2^k-1 alak), nincs kisebb szám, ilyenkor -1 a kimenet. Mindkét művelet egy bitblokkon fut, így az
időigény O(log N).
*/
/*
Hint 1: || Az előző szám is ugyanannyi 1-est tartalmaz, és kisebb. Vizsgáld meg a szám alsó bitjeit: az 1-esek legalsó blokkja fölött 0-k állnak, majd egy 1-es bit. Melyik bit változtatása ad kisebb számot? ||
Hint 2: || Ez az 1-es bit 0-ra változik. Az alatta lévő részbe, amely a 0-kból és a régi 1-esekből áll, egyel több 1-est kell a lehető legfelső pozíciókba tenni. ||
Hint 3: || Ha a szám csupa 1-esből áll, nincs alatta 0, és nincs kisebb szám, ilyenkor -1-et kell kiírni. Próbáld ki kézzel az 1, 3, 7 számokat (ezeknek nincs előzőjük), és a 6-ot. ||
*/
#include <bits/stdc++.h>
using namespace std;

static bool nextSame(unsigned long long n, unsigned long long& ans) {
    unsigned long long c = n;
    int c0 = 0, c1 = 0;
    while ((c & 1ULL) == 0 && c != 0) {
        ++c0;
        c >>= 1;
    }
    while ((c & 1ULL) == 1) {
        ++c1;
        c >>= 1;
    }
    int p = c0 + c1;
    if (p >= 63 || c1 == 0) return false;
    ans = n | (1ULL << p);
    ans &= ~((1ULL << p) - 1ULL);
    ans |= (1ULL << (c1 - 1)) - 1ULL;
    return true;
}

static bool prevSame(unsigned long long n, unsigned long long& ans) {
    unsigned long long temp = n;
    int c1 = 0;
    while ((temp & 1ULL) == 1) {
        ++c1;
        temp >>= 1;
    }
    if (temp == 0) return false;
    int c0 = 0;
    while ((temp & 1ULL) == 0 && temp != 0) {
        ++c0;
        temp >>= 1;
    }
    if (c0 == 0) return false;
    int p = c0 + c1;
    ans = n;
    ans &= (~0ULL) << (p + 1);
    unsigned long long mask = (1ULL << (c1 + 1)) - 1ULL;
    ans |= mask << (c0 - 1);
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long n;
    cin >> n;
    unsigned long long prv, nxt;
    if (prevSame(n, prv)) cout << prv << '\n';
    else cout << -1 << '\n';
    if (nextSame(n, nxt)) cout << nxt << '\n';
    else cout << -1 << '\n';
    return 0;
}