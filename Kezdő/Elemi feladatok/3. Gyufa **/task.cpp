/*
Megoldás lényege: a háromszög oldalait nagyság szerint rendezve (a ≤ b ≤ c) írjuk fel, mert a sorrend nem számít, így minden háromszöget pontosan egyszer kapunk meg. Az összhossz a + b + c = N, ezért c = N - a - b, a háromszög-egyenlőtlenségből pedig elég a + b > c teljesülését ellenőrizni. Két egymásba ágyazott ciklussal minden (a, b) párt végigpróbálunk, a ciklusok sorrendje pedig a kiírás lexikografikus sorrendjét adja. N ≤ 100, így az időigény elhanyagolható.
*/
/*
Hint 1: || Mivel a sorrend nem számít, csak a nagyság szerint rendezett oldalhármasokat (a ≤ b ≤ c) kell megszámolni, és az oldalak összege a + b + c = N. ||
Hint 2: || A c oldal ebből egyértelműen adódik: c = N - a - b. Elég megnézni, hogy a + b > c teljesül-e, és az a, b értékeket két ciklussal végigjárhatod. ||
Hint 3: || Ha c kisebb b-nél, akkor b további növelésével c már csak csökken, így a b-ciklus abbahagyható. A ciklusok a-ra és b-re nézve növekvő sorrendben haladjanak, akkor a kiírás is a megfelelő sorrendben lesz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    for (int a = 1; a <= n; a++) {
        for (int b = a; a + b <= n; b++) {
            int c = n - a - b;
            if (c < b) break;
            if (a + b > c) {
                cout << a << " " << b << " " << c << "\n";
            }
        }
    }
    return 0;
}
