/*
Megoldás lényege:
A P pont a körlemezen van, ha a középponttól mért távolságának négyzete nem nagyobb a sugár négyzeténél: (cx - x)^2 + (cy - y)^2 <= r^2. Gyökvonás nélkül, egész számokkal számolunk, így nincs pontossági hiba, és a határon lévő pont is a lemezen van. A koordináták és a sugár legfeljebb 10^5 nagyságúak, így a négyzetösszeg legfeljebb 8 * 10^10 lehet, ezért long long típust használunk. Az időigény és a memóriaigény O(1).
*/
/*
Hint 1: || Ne számolj gyököt: a távolság négyzetét hasonlítsd a sugár négyzetéhez. ||
Hint 2: || A koordináta-különbségek négyzete és összege meghaladhatja az int tartományt, ezért long long típust használj. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long cx, cy, r;
    cin >> cx >> cy >> r;

    long long x, y;
    cin >> x >> y;

    long long dist2 = (cx - x) * (cx - x) + (cy - y) * (cy - y);
    if (dist2 <= r * r) {
        cout << "rajta van\n";
    } else {
        cout << "kivul van\n";
    }
    return 0;
}
