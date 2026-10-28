/*
Megoldás lényege:
Minden tanárnak minden napra külön megnézzük, mely órákon van óra (0-tól 8-ig, napok 1-től 5-ig).
Egy napon a lyukasórák száma: az első és az utolsó óra közötti órák száma, mínusz a ténylegesen tartott órák száma.
Így a napi lyukasórák összege tanáronként kiszámítható, és a legkisebb összegű tanár sorszámát írjuk ki.
Egyenlő összegnél a kisebb sorszám nyer, ezt a sorszám szerinti bejárás adja. Időigény: O(O + N * 5 * 9).
*/
/*
Hint 1: || Tanáronként és naponként külön kell vizsgálni, hogy mely órákon van óra. Egy napon két órának a közötti, de üres óráit kell megszámolni. ||
Hint 2: || Egy logikai táblázat (tanár, nap, óra) elég ehhez: az órák 0-tól 8-ig, a napok 1-től 5-ig vannak. Egy napon a legkisebb és a legnagyobb órát megkeresve a köztes üres órák száma (max - min + 1) - darabszám. ||
Hint 3: || Összegezd minden tanárra a napi lyukasórákat, majd a tanárokat sorszám szerint bejárva a legkisebb összegű tanár sorszámát tartsd meg. Egy szigorú összehasonlítás automatikusan a kisebb sorszámút tartja meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int o, n, m;
    cin >> o >> n >> m;
    // has[t][nap][ora] = igaz, ha a t. tanárnak van órája az adott napon, óraszámban
    vector<array<array<bool, 9>, 6>> has(n + 1);
    for (int k = 0; k < o; k++) {
        int t, s, nap, ora;
        cin >> t >> s >> nap >> ora;
        has[t][nap][ora] = true;
    }

    int bestT = 1;
    long long bestGap = LLONG_MAX;
    for (int t = 1; t <= n; t++) {
        long long gaps = 0;
        for (int d = 1; d <= 5; d++) {
            int lo = -1, hi = -1, cnt = 0;
            for (int h = 0; h <= 8; h++) {
                if (has[t][d][h]) {
                    if (lo < 0) lo = h;
                    hi = h;
                    cnt++;
                }
            }
            if (cnt > 0) gaps += (hi - lo + 1) - cnt;
        }
        if (gaps < bestGap) {
            bestGap = gaps;
            bestT = t;
        }
    }
    cout << bestT << "\n";
    return 0;
}
