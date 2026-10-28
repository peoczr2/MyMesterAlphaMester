/*
Egy kastély összes termébe ugyanakkora négyzetet kell lerakni, így a négyzet oldala minden terem minden oldalát osztja: a lehetséges méretek a termek oldalainak közös osztói.
A legnagyobb ilyen méret az összes oldalhossz legnagyobb közös osztója, amelyet a kastélyonkénti gcd-láncként számolunk ki.
Egy gcd-számítás az Euklideszi algoritmussal O(log) időben fut, így a teljes bemenet feldolgozása az összes oldalhossz számával arányos.
*/
/*
Hint 1: || Egy közös négyzetlap oldala minden terem mindkét oldalát kell, hogy ossza. ||
Hint 2: || Ezért kastélyonként az összes terem szélességének és hosszának közös osztói közül a legnagyobbat, vagyis a teljes gcd-t kell kiszámolni. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    while (k--) {
        int t;
        cin >> t;
        int64 g = 0;
        for (int i = 0; i < t; ++i) {
            int64 a, b;
            cin >> a >> b;
            g = gcdll(g, gcdll(a, b));
        }
        cout << g << '\n';
    }
    return 0;
}
