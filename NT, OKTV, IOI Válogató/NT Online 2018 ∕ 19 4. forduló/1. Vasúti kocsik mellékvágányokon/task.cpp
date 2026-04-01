/*
Megoldás lényege:
Az első i kocsi akkor rendezhető el a fő vágány és a kitérő között, ha létezik
egy értékhatár t, amelynél a t-nél nem nagyobb kocsik és a t-nél nagyobb kocsik
külön-külön növekvő sorrendben állnak az érkezési sorrendben. Ez pontosan azt
jelenti, hogy az i-edik prefixben minden inverzió (nagyobb elem előzi a kisebbet)
ugyanazon a határon átível: a kisebb végek legnagyobbja kisebb a nagyobb végek
legkisebbjénél.

Bejárjuk a permutációt balról jobbra. Fenntartjuk a már látott értékeket egy
rendezett halmazban, hogy az aktuális elemnél megkapjuk a legkisebb korábbi
nagyobb elemet. Ezzel frissítjük az inverziók kisebb és nagyobb oldalának
globális határait. Amíg a két határ nem metszik egymást, a prefix még rendezhető;
az első ütközés után több elem már nem javíthatja a helyzetet.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    set<int> latott;
    int alsoHatar = 0;
    int felsoHatar = n + 1;
    int valasz = n;

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;

        auto it = latott.upper_bound(x);
        if (it != latott.end()) {
            alsoHatar = max(alsoHatar, x);
            felsoHatar = min(felsoHatar, *it);
        }
        latott.insert(x);

        if (alsoHatar >= felsoHatar) {
            valasz = i - 1;
            break;
        }
    }

    cout << valasz << '\n';
    return 0;
}
