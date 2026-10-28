/*
Megoldás lényege:
A szám alsó bitjei: c0 darab 0, utána c1 darab 1, majd egy 0 bit a c0+c1 pozícióban. Ezt a 0-t 1-re állítjuk,
az alatta lévő biteket nullázzuk, és a régi 1-esek közül eggyel kevesebbet a legalsó pozíciókba tesszük.
Így az 1-esek száma megmarad, és a szám a lehető legkisebb, a kiindulásnál nagyobb ilyen szám lesz.
A szám legfeljebb 40 bites, így az időigény O(log N).
*/
/*
Hint 1: || Nézd a szám legalsó bitjeit: előbb 0-k, utána egy 1-esekből álló blokk áll, a blokk fölött pedig egy 0 bit következik. Ennek a 0 bitnek kell 1-essé válnia, ha nagyobb számot akarunk. ||
Hint 2: || A 0-ból lett 1-es alatti biteket mind nullázd, és a régi 1-esek számánál eggyel kevesebbet tölts vissza a legalsó pozíciókba. Így az 1-esek száma változatlan marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long n;
    cin >> n;

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
    if (p >= 63 || c1 == 0) {
        cout << -1 << '\n';
        return 0;
    }

    n |= (1ULL << p);
    n &= ~((1ULL << p) - 1ULL);
    n |= (1ULL << (c1 - 1)) - 1ULL;
    cout << n << '\n';
    return 0;
}