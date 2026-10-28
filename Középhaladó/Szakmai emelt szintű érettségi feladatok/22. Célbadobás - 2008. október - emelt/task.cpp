/*
Megoldás lényege:
A pontszámhoz csak a becsapódás Manhattan-távolságát kell kiszámolni: d = |x| + |y|. Ezután a t = K − d értéket vesszük: ha t negatív, a feladat szerint a pont 0, egyébként a pontszám (K − d) mod M, azaz t és M maradéka. Minden dobás konstans idejű számítás, így az egész feladat O(N) időben fut. A koordináták abszolútértéke legfeljebb 100 000, az összegek így long long típuson is biztonságosan elférnek.
*/
/*
Hint 1: || A pontszám csak a d = |x| + |y| távolságtól függ, ezért minden dobásnál ezt a két abszolútértéket kell összeadni. Utána már csak egy képletet kell alkalmazni. ||
Hint 2: || A maradékképzés csak nemnegatív K − d értéknél adja a kívánt pontszámot; ha K − d negatív, a feladat szerint nulla pontot kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, k, m;
    cin >> n >> k >> m;
    for (long long i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        long long d = llabs(x) + llabs(y);
        long long t = k - d;
        long long p = (t < 0) ? 0 : t % m;
        cout << p << '\n';
    }
    return 0;
}
