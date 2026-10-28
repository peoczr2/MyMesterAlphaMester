/*
Megoldás lényege:
Egy nap akkor fagyos, ha a mért hőmérséklet 0 foknál kisebb. A mérések egyesével beolvashatók, és minden negatív értéknél egy számlálót növelünk. A végén a számláló értéke adja a fagyos napok számát. A mintán (5 nap) a -82, -13 és -47 negatív, így a válasz 3. Az időigény O(N), N legfeljebb 50.
*/
/*
Hint 1: || Egy nap akkor fagyos, ha a mért hőmérséklet kisebb 0-nál. Minden mérést külön kell megvizsgálni erre a feltételre. ||
Hint 2: || Használj egy számlálót, amelyet nullától indítasz. Minden olyan mérésnél növeld eggyel, amely negatív, a végén pedig ezt írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int fagyos = 0;
    for (int i = 0; i < n; i++) {
        int homerseklet;
        cin >> homerseklet;
        if (homerseklet < 0) {
            fagyos++;
        }
    }
    cout << fagyos << "\n";
    return 0;
}
