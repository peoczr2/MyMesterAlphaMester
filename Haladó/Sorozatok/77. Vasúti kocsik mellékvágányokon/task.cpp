/*
Megoldás lényege:
Az első i kocsi akkor rendezhető el a fő vágány és a kitérő között, ha létezik egy t határ, amelynél
az annál nem nagyobb kocsik és az annál nagyobb kocsik külön-külön növekvő sorrendben állnak az
érkezési sorrendben. Ez azt jelenti, hogy az addigi prefix minden inverziója ugyanazon értékhatáron
ível át.

Balról jobbra haladva minden új kocsinál megkeressük a legkisebb korábbi nagyobb elemet. Ezzel az
összes eddigi inverzió kisebb oldalának maximumát és nagyobb oldalának minimumát tartjuk karban.
Amíg ez a két határ nem keresztezi egymást, a prefix rendezhető; az első ütközés előtti hossz a válasz.
*/
/*
Hint 1: || Nem kell rögtön az egész sorozatot kezelni: elég a leghosszabb jó prefixet keresni. ||
Hint 2: || Egy jó prefixben minden inverzió ugyanazon értékhatár két oldalára esik. ||
Hint 3: || Rendezett halmazból lekérdezhető az aktuális elem legkisebb korábbi nagyobbja. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    set<int> seen;
    int lowerBound = 0;
    int upperBound = n + 1;
    int answer = n;

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;

        auto it = seen.upper_bound(x);
        if (it != seen.end()) {
            lowerBound = max(lowerBound, x);
            upperBound = min(upperBound, *it);
        }
        seen.insert(x);

        if (lowerBound >= upperBound) {
            answer = i - 1;
            break;
        }
    }

    cout << answer << '\n';
    return 0;
}