/*
Megoldás lényege:
A határok a 0. állomás, a végállomás és azok a közbülső állomások, ahol a villamos nem áll meg (az érkezési és az indulási idő egyenlő). Két egymást követő határ között minden közbülső állomáson megáll a villamos, ezért a keresett szakasz mindig két szomszédos határ közötti rész, és a leghosszabb ilyen rész a válasz. Egy menetben összegezzük a távolságot az utolsó határ óta, és minden határnál összehasonlítjuk az eddigi legjobbal; a szigorú összehasonlítás miatt a legkorábbi szakasz marad meg. Az időigény O(N).
*/
/*
Hint 1: || A szakasz határait a 0. állomás, a végállomás és azok az állomások adják, ahol nem áll meg a villamos. Két határ között minden közbülső állomáson megáll, ezért elég a szomszédos határok közötti részeket vizsgálni. ||
Hint 2: || Egyetlen menetben haladj végig az állomásokon, és a távolságot összegezd az utolsó határ óta. Ha az aktuális állomás határ vagy a végállomás, hasonlítsd össze a szakasz hosszát az eddigi legjobbal szigorú > relációval. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int lastBorder = 0;  // az utolsó határ sorszáma (kezdetben a 0. állomás)
    long long dist = 0;  // a lastBorder óta megtett távolság
    long long bestLen = -1;
    int bestFrom = 0;
    int bestTo = 0;

    for (int i = 1; i <= n; i++) {
        long long t, arr, dep;
        cin >> t >> arr >> dep;
        dist += t;
        if (arr == dep || i == n) {
            if (dist > bestLen) {
                bestLen = dist;
                bestFrom = lastBorder;
                bestTo = i;
            }
            lastBorder = i;
            dist = 0;
        }
    }

    cout << bestFrom << ' ' << bestTo << ' ' << bestLen << '\n';
    return 0;
}
