/*
Megoldás lényege:
Először szűrjük a háborúkat: csak azok érdekelnek, amelyek hossza (befejezés mínusz kezdés) szigorúan nagyobb 10-nél.
A megmaradt háborúk közül egy változóban tartjuk az eddigi legrövidebbet, egyenlő hossznál a korábban kezdődőt.
Ha egyetlen háború sem felel meg a feltételnek, a kiírt válasz 0 0.
Az idő O(K), a memória O(1) a beolvasott adatokon kívül.
*/
/*
Hint 1: || A háború hossza a befejezés és a kezdés évének különbsége. Előbb szűrj: a 10 évnél nem hosszabb háborúk kiesnek. ||
Hint 2: || A megmaradt háborúk közül a legrövidebbet keresd, az eddigi legjobbat egy változóban tartva. Egyenlő hossznál a korábbi kezdésű háború legyen a jobb. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    bool found = false;
    int bestLen = 0, bestStart = 0, bestEnd = 0;
    for (int i = 0; i < k; i++) {
        int a, b, s, e;
        cin >> a >> b >> s >> e;
        int len = e - s;
        if (len <= 10) continue;
        if (!found || len < bestLen || (len == bestLen && s < bestStart)) {
            found = true;
            bestLen = len;
            bestStart = s;
            bestEnd = e;
        }
    }
    if (found) cout << bestStart << " " << bestEnd << "\n";
    else cout << "0 0\n";
    return 0;
}
