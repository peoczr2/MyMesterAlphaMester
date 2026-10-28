/*
Megoldás lényege:
A kérdés csak arra vonatkozik, hogy egy adott évben született-e világcsúcs, a magasságok a válaszhoz nem kellenek. Az összes világcsúcs-évet egy halmazba (set) tesszük, így egy évről gyorsan eldönthető, hogy volt-e benne rekord. A legújabb világcsúcs éve a bemenetben szereplő legnagyobb évszám; ettől eggyel kisebb évtől visszafelé lépkedve az első olyan évet keressük, amely nincs a halmazban, ez lesz a válasz. Legfeljebb 100 rekord van, így az időigény O(N log N).
*/
/*
Hint 1: || Az eredmény mindig kisebb, mint a legutolsó világcsúcs éve, és a válaszhoz csak az évszámok kellenek, a magasságokat nyugodtan figyelmen kívül hagyhatod. ||
Hint 2: || Tegyük az összes világcsúcs-évet egy set<int>-be (ha egy évben több rekord is van, a halmaz egyszerűen összevonja őket), majd a legnagyobb évnél eggyel kisebbtől kezdve csökkentsd az évet, amíg az a halmazban van. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    set<int> evek;
    int legutolso = 0;
    for (int i = 0; i < n; i++) {
        int t, mag;
        cin >> t >> mag;
        evek.insert(t);
        legutolso = max(legutolso, t);
    }
    int ev = legutolso - 1;
    while (evek.count(ev)) {
        ev--;
    }
    cout << ev << '\n';
    return 0;
}
