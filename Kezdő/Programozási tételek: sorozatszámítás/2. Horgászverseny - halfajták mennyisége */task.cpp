/*
Megoldás lényege:
A mátrix j-edik oszlopa a j-edik halfajta fogásait tartalmazza minden horgász szerint, így a halfajta összes fogása az oszlop elemeinek összege.
Egy K hosszú tömbben oszloponként gyűjtjük az összegeket: a bemenet soronként érkezik, és minden M(i,j) értéket a j-edik elemhez adunk.
A végén a tömb elemeit egy sorba kiírjuk; az időigény O(N·K), ami a korlátok mellett gyors.
*/
/*
Hint 1: || Egy halfajta összes fogását a mátrix egy oszlopa tartalmazza. Melyik indexet kell rögzíteni, amikor egy halfajta összegét számolod? ||
Hint 2: || Tárolj egy K hosszú tömböt, és minden beolvasott számot adj hozzá a saját oszlopindexéhez tartozó elemhez. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> osszeg(k, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            int m;
            cin >> m;
            osszeg[j] += m;
        }
    }
    for (int j = 0; j < k; j++) {
        cout << osszeg[j] << (j + 1 < k ? " " : "\n");
    }
    return 0;
}
