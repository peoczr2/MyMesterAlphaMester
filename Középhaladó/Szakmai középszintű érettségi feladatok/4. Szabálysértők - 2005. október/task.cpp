/*
Megoldás lényege:
A mért sebességeket egyesével olvassuk be a 0 záró értékig, és közben számoljuk, hányadik értékről van szó. Mivel a szembe haladók sebessége negatív, a szabálysértés feltételét az abszolút értékkel vizsgáljuk: ha |S| legalább 100, az a sor szabálysértő. Az első ilyen sorszámot eltároljuk, a későbbieket már nem vesszük figyelembe. Ha nem volt szabálysértő, a kezdeti -1 marad a kimeneten. Az időigény O(N), ahol N a mért sebességek száma, a memóriaigény O(1).
*/
/*
Hint 1: || A szembe haladó járművek sebessége negatív, a szabálysértés viszont a sebesség nagyságára vonatkozik. Gondold végig, melyik számot kell a 100-zal összehasonlítani. ||
Hint 2: || Olvass be számokat egy ciklusban, a 0 beolvasásánál állj meg, és számláld a sorszámot. Egy változóban tartsd az első szabálysértő sorszámát, kezdetben -1 értékkel, és csak az első találatnál írd felül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int sebesseg;
    int sorszam = 0;
    int elso = -1;

    while (cin >> sebesseg && sebesseg != 0) {
        sorszam++;
        if (elso == -1 && abs(sebesseg) >= 100) {
            elso = sorszam;
        }
    }

    cout << elso << "\n";
    return 0;
}
