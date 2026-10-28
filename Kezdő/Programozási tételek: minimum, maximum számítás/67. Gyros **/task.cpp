/*
Megoldás lényege:
A napok egymástól függetlenek, ezért naponként külön számolunk. Ha z darab vegyes gyrost készítünk, a maradék csirkehúsból legfeljebb (A - z) / 2 csirkés, a maradék borjúhúsból legfeljebb (B - z) / 2 borjús gyros készíthető, és mindkét típusból legfeljebb annyi, ahány ilyen rendelés érkezett.
Ezért minden lehetséges z-re (0-tól min(V, A, B)-ig) kiszámoljuk az elkészíthető gyrosok összes számát, és a legnagyobbat írjuk ki.
Az időigény naponként O(N), összesen az érkező rendelések számával arányos (legfeljebb 100 000).
*/
/*
Hint 1: || A vegyes gyros az egyetlen rendelés, amely mindkét hússzeletet használja, ezért a döntés kulcsa, hány vegyes gyros készül. Ha ezt rögzíted, a csirkés és a borjús rendelések már függetlenül számolhatók. ||
Hint 2: || Ha z vegyest készítesz, akkor A - z csirkehús és B - z borjúhús marad; ebből legfeljebb (A - z) / 2 csirkés és (B - z) / 2 borjús gyros fér bele, de legfeljebb annyi, ahány ilyen rendelés érkezett. Próbáld ki az összes lehetséges z értéket, és válaszd a legnagyobb z + x + y összeget. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, ac, ab; // n: vendégek, ac: csirkehús adag, ab: borjúhús adag
        string s;
        cin >> n >> ac >> ab >> s;

        int cntC = 0, cntB = 0, cntV = 0;
        for (char ch : s) {
            if (ch == 'C') cntC++;
            else if (ch == 'B') cntB++;
            else cntV++;
        }

        int best = 0;
        for (int z = 0; z <= min({cntV, ac, ab}); z++) {
            int x = min(cntC, (ac - z) / 2);
            int y = min(cntB, (ab - z) / 2);
            best = max(best, z + x + y);
        }
        cout << best << '\n';
    }
    return 0;
}
