/*
Megoldás lényege:
A jegyek darabszámát egy 6 elemű tömbben tartjuk nyilván, ahol a tömb i. eleme az i-es jegyek számát adja. A 0. elemet nem használjuk, így a jegy értéke közvetlenül indexként szolgál.
Minden beolvasott jegynél a megfelelő elemet eggyel növeljük, a végén pedig az 1-től 5-ig terjedő darabszámokat írjuk ki szóközzel elválasztva.
Egy menetben végzünk, az időigény O(N).
*/
/*
Hint 1: || Nem kell eltárolni a jegyeket: elég számolni, hányszor szerepel az egyes értékek közül minden jegy. ||
Hint 2: || Egy 6 elemű tömböt úgy használj, hogy a jegy értéke legyen az index; így minden jegy egy lépésben növeli a saját számlálóját. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int db[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < n; i++) {
        int jegy;
        cin >> jegy;
        db[jegy]++;
    }
    for (int j = 1; j <= 5; j++) {
        cout << db[j] << (j < 5 ? " " : "\n");
    }
    return 0;
}
