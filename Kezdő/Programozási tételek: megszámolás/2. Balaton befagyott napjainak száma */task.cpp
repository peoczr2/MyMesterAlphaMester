/*
Megoldás lényege:
A Balaton egy adott napon akkor van befagyva, ha a mért jégvastagság pozitív (K > 0). A mérések számát és a mért
értékeket egyesével olvassuk be, és minden pozitív vastagságú mérésnél növeljük a számlálót. A számláló végső értéke
a befagyott napok száma. Az időigény O(N), ahol N ≤ 100.
*/
/*
Hint 1: || Egy mérés alapján el lehet dönteni, hogy az adott nap befagyott volt-e: elég megnézni, hogy a jég vastagsága nulla-e. Tömbre nincs szükség. ||
Hint 2: || Olvasd be az N-et, majd N darab K értéket egyenként, és a K > 0 feltételt egy számlálóban vizsgáld. A végén a számlálót írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        if (k > 0) ans++;
    }
    cout << ans << "\n";
    return 0;
}
