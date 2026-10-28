/*
Megoldás lényege:
A fenyőfákat sorszám szerint haladva végigvizsgáljuk, és az első olyan fa sorszámát jegyezzük fel, amelynek ára kisebb K-nál. Mivel a legkisebb sorszámút kell kiírni, az első találat már a válasz, a további árak nem befolyásolják az eredményt. Ha egyetlen fa sem olcsóbb K-nál, a kiírandó érték -1 marad. Az időigény O(N), ami N ≤ 100 esetén bőven belefér az időlimitbe.
*/
/*
Hint 1: || Nincs szükség rendezésre vagy bonyolult adatszerkezetre: elég egyszer végigmenni az árakon, és figyelni, melyik az első olyan ár, amely K-nál kisebb. ||
Hint 2: || Ha a ciklusban találsz egy K-nál olcsóbb fát, az aktuális sorszámát jegyezd fel, és a többi fát már nem kell vizsgálnod. Ha egyik sem olcsóbb, a kiírandó érték -1 marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    int valasz = -1;
    for (int i = 1; i <= n; ++i) {
        int ar;
        cin >> ar;
        if (valasz == -1 && ar < k) valasz = i;
    }
    cout << valasz << '\n';
}
