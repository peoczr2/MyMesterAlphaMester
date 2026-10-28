/*
Megoldás lényege:
Egy háború hossza a befejezés és a kezdés évének különbsége.
Végigmegyünk a háborúkon, és egy változóban tartjuk az eddig legrövidebbet a kezdő és a befejező évével együtt.
Egyenlő hossz esetén a korábban kezdődő háborút tartjuk meg, ezért a két feltételt sorrendben vizsgáljuk.
Az idő O(K), a memória O(1) a beolvasott adatokon kívül.
*/
/*
Hint 1: || Egy háború hossza egyszerű különbség: a befejezés és a kezdés évének különbsége. Nincs szükség rendezésre, elég egyszer végigmenni a háborúkon. ||
Hint 2: || Tartsd nyilván az eddigi legrövidebb háború kezdő és befejező évét, valamint a hosszát. Új háborúnál csak akkor cseréld le, ha rövidebb, vagy egyenlő hossznál korábban kezdődik. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int bestLen = INT_MAX, bestStart = 0, bestEnd = 0;
    for (int i = 0; i < k; i++) {
        int a, b, s, e;
        cin >> a >> b >> s >> e;
        int len = e - s;
        if (len < bestLen || (len == bestLen && s < bestStart)) {
            bestLen = len;
            bestStart = s;
            bestEnd = e;
        }
    }
    cout << bestStart << " " << bestEnd << "\n" << bestLen << "\n";
    return 0;
}
