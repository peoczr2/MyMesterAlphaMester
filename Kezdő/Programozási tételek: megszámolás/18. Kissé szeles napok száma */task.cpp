/*
Megoldás lényege:
Minden napra egyszer kell megnézni a mért szélsebességet, ezért egyetlen végigolvasás elég, tömbre nincs szükség.
Egy nap akkor volt kis szél, ha a sebesség pozitív, de M-nél kisebb: a szélcsend (0 km/óra) nem számít, mert ilyenkor
nem lehet versenyt rendezni. A feltételnek megfelelő napokat egy számlálóban összegezzük. A versenynapok száma (K)
a kimenetet nem befolyásolja, ezért a számításban nem használjuk. Az időigény O(N).
*/
/*
Hint 1: || Nem kell tárolni a napokat: minden mérést beolvasás után azonnal ellenőrizhetsz. Figyelj a két határra: a sebesség M-nél kisebb legyen, de a szélcsendet ne számold. ||
Hint 2: || Egy naphoz a feltétel 0 < S és S < M. Ezt egy if-ben vizsgáld, és ha teljesül, növeld a számlálót. A végén a számlálót írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;
        if (s > 0 && s < m) ans++;
    }
    cout << ans << "\n";
    return 0;
}
