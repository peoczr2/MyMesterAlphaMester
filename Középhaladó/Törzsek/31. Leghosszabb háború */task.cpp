/*
Megoldás lényege:
Egy háború hossza a befejezés és a kezdés évének különbsége. Egyetlen végigmenéssel megkeressük a leghosszabb háborút: az eddigi legjobbat egy változóban tartjuk, és egyenlő hossz esetén a korábban kezdődő háborút hagyjuk meg. Végül kiírjuk a legjobb háború kezdő és záró évét, majd a két törzs sorszámát a bemenetben szereplő sorrendben. Az időigény O(K), ami K ≤ 2000 mellett azonnali.
*/
/*
Hint 1: || Egy háború hossza a befejezés és a kezdés évének különbsége. Elég egyszer végigmenni a háborúkon, és minden háborúnál összehasonlítani a hosszát az eddigi legjobbal. ||
Hint 2: || Az eddigi legjobb háború indexét tartsd meg egy változóban, és csak akkor cseréld le, ha az új háború hosszabb, vagy egyenlő hossz mellett korábban kezdődik. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<array<int, 4>> wars(k); // támadó, védő, kezdet, befejezés
    for (auto &w : wars) cin >> w[0] >> w[1] >> w[2] >> w[3];

    int best = 0;
    for (int i = 1; i < k; i++) {
        int len = wars[i][3] - wars[i][2];
        int bestLen = wars[best][3] - wars[best][2];
        if (len > bestLen || (len == bestLen && wars[i][2] < wars[best][2])) best = i;
    }

    cout << wars[best][2] << " " << wars[best][3] << "\n";
    cout << wars[best][0] << " " << wars[best][1] << "\n";
    return 0;
}
