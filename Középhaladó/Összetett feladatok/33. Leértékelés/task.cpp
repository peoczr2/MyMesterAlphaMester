/*
Megoldás lényege:
Minden leértékelést egyszer végigolvasunk: a termékenkénti darabszámot növeljük, a leértékelt termék árát a Nap sorszámú napon (ha az esemény lefedi ezt a napot) felülírjuk, a legnagyobb árengedményt a (alapár − leértékelt ár) maximumaként tartjuk nyilván, és a leértékelt napokat egy 365 elemű jelölőtömbbel állítjuk be. A darabszám, a soha nem leértékelt termékek száma és a Nap sorszámú napi árak ebből már közvetlenül adódnak, a leghosszabb leértékelésmentes időszak pedig a jelölőtömb egyszeri bejárásával (a döntetlennél a korábbi kezdetű) kapható meg. Az idő O(M·365 + N), ami N, M ≤ 10 000 mellett bőven belefér.
*/
/*
Hint 1: || Egy leértékelés csak az adott termékre és a leértékelt napok tartományára hat, így a három darabszámlálás (leértékelések száma, soha nem leértékelt termékek, Nap sorszámú napi ár) egyetlen végigolvasásban elvégezhető. ||
Hint 2: || Az 5. részfeladathoz jelöld meg a 365 napból azokat, amelyeken bármelyik termék le volt értékelve, és a jelöletlen napok leghosszabb egybefüggő szakaszát keresd meg; ha nincs jelöletlen nap, a válasz -1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> base(n + 1, 0);
    for (int i = 1; i <= n; ++i) cin >> base[i];

    int m, nap;
    cin >> m >> nap;

    vector<int> cnt(n + 1, 0);
    vector<long long> dayPrice(base);
    vector<bool> covered(366, false);
    long long bestDiscount = 0;

    for (int k = 0; k < m; ++k) {
        int s, e, u;
        long long leAr;
        cin >> s >> e >> u >> leAr;

        cnt[s]++;
        for (int d = e; d <= u; ++d) covered[d] = true;
        if (e <= nap && nap <= u) dayPrice[s] = leAr;
        bestDiscount = max(bestDiscount, base[s] - leAr);
    }

    // 1. részfeladat: termékenkénti leértékelések száma
    cout << "#\n";
    for (int i = 1; i <= n; ++i) {
        cout << cnt[i];
        cout << (i < n ? ' ' : '\n');
    }
    if (n == 0) cout << "\n";

    // 2. részfeladat: soha nem leértékelt termékek száma
    int never = 0;
    for (int i = 1; i <= n; ++i)
        if (cnt[i] == 0) never++;
    cout << "#\n";
    cout << never << "\n";

    // 3. részfeladat: termékek ára a Nap sorszámú napon
    cout << "#\n";
    for (int i = 1; i <= n; ++i) {
        cout << dayPrice[i];
        cout << (i < n ? ' ' : '\n');
    }
    if (n == 0) cout << "\n";

    // 4. részfeladat: az év legnagyobb árengedménye
    cout << "#\n";
    cout << bestDiscount << "\n";

    // 5. részfeladat: leghosszabb leértékelésmentes időszak
    int bestA = -1, bestB = -1, bestLen = 0;
    int d = 1;
    while (d <= 365) {
        if (covered[d]) {
            ++d;
            continue;
        }
        int a = d;
        while (d <= 365 && !covered[d]) ++d;
        int b = d - 1;
        if (b - a + 1 > bestLen) {
            bestLen = b - a + 1;
            bestA = a;
            bestB = b;
        }
    }
    cout << "#\n";
    if (bestLen == 0) cout << "-1\n";
    else cout << bestA << " " << bestB << "\n";

    return 0;
}
