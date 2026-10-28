/*
Megoldás lényege:
Egy megállóban akkor nem áll meg a villamos, ha az érkezési és az indulási idő megegyezik, a távolság ehhez nem kell. A 0. állomás nincs a bemenetben, a végállomás (N.) pedig a példa szerint nem számít bele, ezért az N-edik sort beolvassuk, de nem vizsgáljuk. A megállókat sorban olvassuk, és a feltételt teljesítő sorszámokat egy vektorba tesszük, így a növekvő sorrend magától adódik. A kimenet első száma a darabszám, utána a sorszámok állnak egy sorban. Minden állomást egyszer nézünk meg, így az időigény O(N).
*/
/*
Hint 1: || Egy megállóban akkor nincs megállás, ha az érkezési és az indulási idő egyenlő. A távolságokra ehhez nincs szükség. ||
Hint 2: || Olvasd be a megállókat sorban, és az 1-től N-1-ig tartó sorszámoknál gyűjtsd egy vektorba azokat, ahol az érkezési és az indulási idő egyenlő. Az utolsó (N.) megállót ne vedd figyelembe. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> stops;
    for (int i = 1; i <= n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        if (i < n && arr == dep) {
            stops.push_back(i);
        }
    }

    cout << stops.size();
    for (int x : stops) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
