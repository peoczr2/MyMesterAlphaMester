/*
Megoldás lényege:
A villamos a 0. állomásról a 0. percben indul, és csak azokon az állomásokon áll meg, ahol az érkezési és az indulási idő különbözik. Egy megállás nélküli szakasz két egymást követő határ között van, a határ a 0. állomás, egy megálló vagy a végállomás (N). Egyetlen ciklusban összegezzük a távolságot az utolsó határ óta, és ha az állomás határ, a kapott szakaszt összevetjük az eddigi legjobbal. A szigorú összehasonlítás miatt a legkorábbi szakasz marad meg. Az időigény O(N).
*/
/*
Hint 1: || A szakasz határai a 0. állomás, a megállók és a végállomás. Két határ között a villamos nem áll meg, a szakasz hossza a köztes távolságok összege. ||
Hint 2: || Haladj végig az állomásokon, és mindig add hozzá a távolságot. Ha az állomás megálló vagy az utolsó, zárd le a szakaszt: hasonlítsd össze a hosszát az eddigi legjobbal, majd az utolsó határt állítsd erre az állomásra. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int lastStop = 0;    // a jelenlegi szakasz kezdő határának sorszáma
    int dist = 0;        // a lastStop óta megtett távolság
    int bestLen = -1;    // a leghosszabb eddig talált szakasz hossza
    int bestFrom = 0;
    int bestTo = 0;

    for (int i = 1; i <= n; i++) {
        int t, arr, dep;
        cin >> t >> arr >> dep;
        dist += t;
        if (arr != dep || i == n) {
            if (dist > bestLen) {
                bestLen = dist;
                bestFrom = lastStop;
                bestTo = i;
            }
            lastStop = i;
            dist = 0;
        }
    }

    cout << bestFrom << ' ' << bestTo << ' ' << bestLen << '\n';
    return 0;
}
