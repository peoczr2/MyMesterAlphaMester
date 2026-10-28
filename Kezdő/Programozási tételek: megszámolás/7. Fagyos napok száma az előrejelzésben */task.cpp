/*
Megoldás lényege:
Egy nap akkor fagy, ha a várható legkisebb hőmérséklete 0 foknál kisebb, a legnagyobb hőmérséklet ehhez nem számít.
Minden napot egyszer beolvasunk, és ha a minimum negatív, növeljük a fagyos napok számlálóját.
Az időigény O(N), ami N ≤ 100 mellett elhanyagolható.
*/
/*
Hint 1: || Egy nap akkor lesz fagyos, ha a várható legkisebb hőmérséklete kisebb 0-nál. A legnagyobb hőmérséklet erre a kérdésre nincs hatással. ||
Hint 2: || Olvasd be a napokat sorban, és csak a minimumot vizsgáld: ha az 0-nál kisebb, a számlálót növeld eggyel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int freezing = 0;
    for (int i = 0; i < n; i++) {
        int minTemp, maxTemp;
        cin >> minTemp >> maxTemp;
        if (minTemp < 0) freezing++;
    }

    cout << freezing << "\n";
    return 0;
}
