/*
Megoldás lényege:
Egy intervallum akkor jó, ha minden ember legalább egyszer szerepel benne, ezért csúszóablakot használunk.
A jobb végpontot napról napra léptetjük, és számoljuk, hány ember szerepel az aktuális szakaszban (ez a distinct számláló).
Amikor már mindenki benne van, a bal végpontot addig léptetjük jobbra, amíg a kieső napon ügyeletes ember még legalább egyszer a szakaszban marad.
Így minden jobb végponthoz a lehető legrövidebb jó szakasz tartozik, és ezek hosszát összehasonlítjuk az eddigi legjobbal.
Csak szigorúan rövidebb szakasznál frissítünk, így a legkorábban kezdődő legrövidebb intervallum marad meg.
Mindkét mutató csak előre halad, ezért az időigény O(N + M), ami N ≤ 100 000 mellett bőven belefér az 0,1 mp-es limitbe.
*/
/*
Hint 1: || Egy intervallum akkor jó, ha minden ember szerepel benne. Ezért a legrövidebb jó intervallumok csúszóablakkal kereshetők: a jobb végpont mindig előre lép, a bal végpont csak akkor, ha a kiesett nap embere még a szakaszban marad. ||
Hint 2: || Tarts nyilván egy darabszám-tömböt, hogy az egyes embereknek hány ügyelete van az aktuális szakaszban, és egy számlálót arról, hány embernek van legalább egy ügyelete. Ha a számláló eléri M-et, a bal végpontot addig léptetheted, amíg egy ember nem csak egyszer szerepel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> s(n);
    for (auto &x : s) cin >> x;

    vector<int> cnt(m + 1, 0);
    int distinct = 0;
    int l = 0;
    int bestLen = INT_MAX, bestL = -1, bestR = -1;

    for (int r = 0; r < n; ++r) {
        if (cnt[s[r]]++ == 0) ++distinct;
        if (distinct == m) {
            while (cnt[s[l]] > 1) {
                --cnt[s[l]];
                ++l;
            }
            if (r - l + 1 < bestLen) {
                bestLen = r - l + 1;
                bestL = l;
                bestR = r;
            }
        }
    }

    if (bestL < 0) {
        cout << -1 << '\n';
    } else {
        cout << bestL + 1 << ' ' << bestR + 1 << '\n';
    }
    return 0;
}
