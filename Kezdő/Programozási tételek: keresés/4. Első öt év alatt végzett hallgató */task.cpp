/*
Megoldás lényege:
A születési dátum a döntéshez nem kell, csak a szak kezdésének éve (K) és a diplomázás éve (V). Egy végzett akkor fejezte be a szakot 5 év alatt, ha V-K legfeljebb 5. A sorokat sorban olvassuk, és az első ilyen sor sorszámát írjuk ki; ha egyik sor sem felel meg, a válasz -1. Mivel minden sort legfeljebb egyszer olvasunk, az időigény O(N).
*/
/*
Hint 1: || A születési dátum (az első három szám) nem befolyásolja az eredményt, csak a negyedik és az ötödik szám: a kezdés éve és a végzés éve. ||
Hint 2: || Egy sorban vond ki a végzés évéből a kezdés évét: ha az eredmény legfeljebb 5, ez a végzett az 5 év alatt diplomázók közül való. Az első ilyen sorszámát írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int e, h, nap, k, v;
        cin >> e >> h >> nap >> k >> v;
        if (v - k <= 5) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}
