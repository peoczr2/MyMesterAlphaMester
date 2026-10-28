/*
Megoldás lényege:
Egy háború hossza a befejezés és a kezdés évének különbsége. Végigmegyünk az összes háborún, és csak azokat vesszük figyelembe, amelyekben a kérdezett törzs részt vesz.
Az eddig legrövidebb háborút egy változóban tartjuk (ellenség, kezdet, befejezés, hossz); ha találunk rövidebbet, azt cseréljük le.
Egyenlő hossz esetén a korábban kezdődő háborút tartjuk meg. A kiírt ellenség az a törzs, amely nem a kérdezett törzs.
Ha a törzs nem háborúzott, a válasz 0 0 0. Az idő O(K), a memória O(1) plusz a beolvasott adatok.
*/
/*
Hint 1: || Egy háború hosszát a befejezés és a kezdés évének különbsége adja; most a legrövidebbet kell megtalálni a kérdezett törzs háborúi között. ||
Hint 2: || Tartsd nyilván egy változóban az eddigi legrövidebb háborút: az ellenséges törzs sorszámát, a kezdő és záró évet, és a hosszát. Egyenlőségnél a korábbi kezdésű marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<array<int, 4>> wars(k); // támadó, védő, kezdet, befejezés
    for (auto &w : wars) cin >> w[0] >> w[1] >> w[2] >> w[3];
    int s;
    cin >> s;

    bool found = false;
    int bestLen = 0, bestEnemy = 0, bestStart = 0, bestEnd = 0;
    for (auto &w : wars) {
        if (w[0] != s && w[1] != s) continue;
        int enemy = (w[0] == s) ? w[1] : w[0];
        int len = w[3] - w[2];
        if (!found || len < bestLen || (len == bestLen && w[2] < bestStart)) {
            found = true;
            bestLen = len;
            bestEnemy = enemy;
            bestStart = w[2];
            bestEnd = w[3];
        }
    }

    if (!found) cout << "0 0 0\n";
    else cout << bestEnemy << " " << bestStart << " " << bestEnd << "\n";
    return 0;
}
