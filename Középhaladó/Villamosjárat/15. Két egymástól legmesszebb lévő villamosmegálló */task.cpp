/*
Megoldás lényege:
A feladat a szomszédos állomások közötti távolságok közül a legnagyobbat keresi. Az (i-1, i) szomszédos pár távolsága T_i, ezért egyetlen beolvasási ciklusban végignézzük a T_i értékeket, és megjegyezzük a legnagyobbat a hozzá tartozó sorszámmal. Egyenlő távolságnál a szigorú összehasonlítás miatt a legkisebb sorszámú pár marad meg. Az időigény O(N).
*/
/*
Hint 1: || A szomszédos állomások távolsága a beolvasott T_i érték. Nem kell az összes párt vizsgálni, csak a szomszédosakat. ||
Hint 2: || Egy ciklusban olvasd be az állomásokat, és tartsd nyilván a legnagyobb T_i-t és az i sorszámát. A kiírásban a pár sorszámai i-1 és i, a távolság pedig a legnagyobb T_i. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int bestIdx = 0;   // a pár második állomásának sorszáma
    int bestDist = -1; // a legnagyobb szomszédos távolság
    for (int i = 1; i <= n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        if (dist > bestDist) {
            bestDist = dist;
            bestIdx = i;
        }
    }

    cout << bestIdx - 1 << ' ' << bestIdx << ' ' << bestDist << '\n';
    return 0;
}
