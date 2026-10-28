/*
Megoldás lényege:
Egy K-homogén részsorozatban van egy v érték, és a részsorozat többi eleme legfeljebb K darab lehet, ezért az ablakokat értékenként vizsgáljuk.
Egy v-hez tekintjük a v előfordulásainak növekvő P[0], P[1], … pozícióit. Ha az ablak a P[i]…P[j] tartományt fedi le, a közbülső nem-v elemek száma belső(i,j) = P[j]−P[i]−(j−i), és ez legfeljebb K lehet.
Minden i-hez kétmutatós módszerrel megkeressük a legnagyobb j-t, amelyre belső(i,j) ≤ K; ez a j mutató csak előre halad, így értékenként a lépések száma a v-k számával arányos.
A széleken a maradék K − belső(i,j) törlési keret a bal és jobb oldali nem-v szakaszokra oszlik, ezért a hossz S + min(K − belső, bal + jobb), a kezdőpontot pedig a lehető legbaloldalibbra toljuk.
Az összes értékre O(N + M) idő alatt megkapjuk a leghosszabb ablakot, azonos hossz esetén a legkisebb kezdőponttal.
*/
/*
Hint 1: || Rögzíts egy v értéket: a részsorozatban a v-től különböző elemeket törölhetjük, és legfeljebb K ilyen lehet. Így minden jó részsorozat egy v értékre épül, és elég értékenként a v előfordulásait nézni. ||
Hint 2: || Ha a részsorozat a v-k P[i]…P[j] tartományát fedi le, a belsejében lévő nem-v elemek száma P[j]−P[i]−(j−i). Ez legyen legfeljebb K, és a két szélén még a szomszédos nem-v elemeket is hozzávehetjük. ||
Hint 3: || Minden i-re keresd meg a legnagyobb j-t kétmutatós módszerrel, a j mutatót ne léptesd vissza. A széleken a maradék K − belső keret adja a bővítést, a kezdőpont pedig a lehető legkisebb index legyen. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n + 1);
    int maxv = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        maxv = max(maxv, a[i]);
    }

    // Értékenként csoportosítjuk a pozíciókat: a v pozíciói pos[start[v]..start[v+1]-1]-ben, növekvő sorrendben.
    vector<int> start(maxv + 2, 0);
    for (int i = 1; i <= n; i++) start[a[i] + 1]++;
    for (int v = 1; v <= maxv + 1; v++) start[v] += start[v - 1];
    vector<int> pos(n);
    vector<int> fillp(start);
    for (int i = 1; i <= n; i++) pos[fillp[a[i]]++] = i;

    int bestLen = 0, bestStart = 1;
    for (int v = 1; v <= maxv; v++) {
        int lo = start[v], c = start[v + 1] - start[v];
        if (c == 0) continue;
        auto P = [&](int t) { return pos[lo + t]; };

        int j = 0;
        for (int i = 0; i < c; i++) {
            if (j < i) j = i;
            // kétmutatós: a legnagyobb j, amelyre a belső nem-v szám még legfeljebb K
            while (j + 1 < c && (P(j + 1) - P(i)) - (j + 1 - i) <= k) j++;

            int inside = (P(j) - P(i)) - (j - i);
            int left = P(i) - (i == 0 ? 0 : P(i - 1)) - 1;             // nem-v elemek a P[i] bal oldalán
            int right = (j == c - 1 ? n + 1 : P(j + 1)) - P(j) - 1;    // nem-v elemek a P[j] jobb oldalán
            int extra = min(k - inside, left + right);                 // szélső bővítés
            int len = (P(j) - P(i) + 1) + extra;
            int st = P(i) - min(left, extra);                          // a lehető legbaloldalibb kezdőpont

            if (len > bestLen || (len == bestLen && st < bestStart)) {
                bestLen = len;
                bestStart = st;
            }
        }
    }

    cout << bestLen << "\n" << bestStart << "\n";
    return 0;
}
