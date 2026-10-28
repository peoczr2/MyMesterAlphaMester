/*
Megoldás lényege:
Egy sorozat akkor keresősorozat, ha van olyan keresőfa és keresett elem, amelyre a sorozat pontosan a keresési út. A sorozaton végighaladva nyilvántartjuk azt az (alsó, felső) intervallumot, amelybe a keresett elem eshet: ha az aktuális elemtől balra lépünk, az aktuális elem lesz az új felső határ, ha jobbra, akkor az új alsó határ. A következő elemnek szigorúan ebbe az intervallumba kell esnie, különben a sorozat nem lehet keresősorozat. Mivel a keresőfa elemei különbözőek, az egyenlő egymás utáni elemek is hibát adnak. Egy sorozatot O(H) idő alatt ellenőrzünk, így az összes adat beolvasása dominál.
*/
/*
Hint 1: || Haladj végig a sorozaton, és minden lépésnél tartsd számon, milyen határok közé eshet a keresett elem: balra lépésnél a felső határ csökken az aktuális elemre, jobbra lépésnél az alsó határ nő az aktuális elemre. ||
Hint 2: || A sorozat pontosan akkor keresősorozat, ha minden következő elem szigorúan az aktuális alsó és felső határ közé esik. Ezt egy bejárással, két változóval ellenőrizheted, és az első hibás elemnél azonnal NEM a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    while (k--) {
        int h;
        cin >> h;
        vector<long long> s(h);
        for (auto& x : s) cin >> x;

        bool lehet = true;
        long long also = LLONG_MIN, felso = LLONG_MAX;
        for (int i = 0; i + 1 < h && lehet; i++) {
            if (s[i + 1] < s[i]) {
                felso = min(felso, s[i]);
            } else {
                also = max(also, s[i]);
            }
            if (!(also < s[i + 1] && s[i + 1] < felso)) lehet = false;
        }

        cout << (lehet ? "IGEN" : "NEM") << "\n";
    }
    return 0;
}
