/*
 * Minden kastély termére kiszámoljuk a közös osztók legnagyobbikát.
 
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
