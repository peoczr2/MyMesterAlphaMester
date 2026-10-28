/*
Megoldás lényege: N ≤ 8, ezért az összes érkezési sorrendet végigpróbáljuk. Egy adott sorrendben
a legnagyobb biztonsági idő min_{i<j} (b_j - a_i) / (j - i), ahol a_i és b_i az i-edik, illetve a
j-edik járat intervallumának határai másodpercben. Ezt a törtet egész számlálóval és nevezővel
tároljuk, így nincs lebegőpontos hiba; a végén a legjobb értéket a legközelebbi másodpercre
kerekítjük. Időigény: O(N! * N^2), N ≤ 8 esetén ez bőven belefér az időlimitbe.
*/
/*
Hint 1: || Egy adott sorrendben érdemes minden járatot a lehető legkorábbi, még megengedett időpontra tenni. ||
Hint 2: || Ha az i-edik és j-edik járat között legalább dt másodperc a távolság, akkor (j - i) * dt <= b_j - a_i, vagyis dt legfeljebb (b_j - a_i) / (j - i) lehet. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
        a[i] *= 60;
        b[i] *= 60;
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    // a legjobb érték tört alakban: bestNum / bestDen, bestDen > 0
    long long bestNum = -1, bestDen = 1;
    do {
        // az adott sorrend értéke: a páronkénti korlátok minimuma
        long long curNum = 1000000000LL, curDen = 1;
        for (int j = 1; j < n; ++j) {
            for (int i = 0; i < j; ++i) {
                long long num = b[p[j]] - a[p[i]], den = j - i;
                if (num * curDen < curNum * den) {
                    curNum = num;
                    curDen = den;
                }
            }
        }
        if (curNum * bestDen > bestNum * curDen) {
            bestNum = curNum;
            bestDen = curDen;
        }
    } while (next_permutation(p.begin(), p.end()));

    // legközelebbi másodpercre kerekítés (bestNum >= 0)
    long long best = (2 * bestNum + bestDen) / (2 * bestDen);
    cout << best / 60 << ':' << setw(2) << setfill('0') << best % 60 << '\n';
    return 0;
}
