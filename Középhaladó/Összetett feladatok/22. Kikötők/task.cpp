/*
Megoldás lényege:
A kikötők távolságai növekvő sorrendben vannak, így a szomszédos különbségek és a három egymást követő kikötő szélső távolsága közvetlenül kiszámolható. A középső kikötőnél az első és az utolsó kikötőtől mért távolságok különbsége 2 * T[i] - T[0] - T[N - 1], ennek abszolút értékét kell minimalizálni, döntetlennél a kisebb sorszámút választjuk. A leghosszabb, szomszédos távolságokkal összekötött szakaszt egy bejárással keressük: a szakasz végét ott zárjuk le, ahol a következő kikötő távolsága nagyobb K-nál, a hosszt az első és az utolsó kikötő távolságából számoljuk. Az 5. részfeladatban kétmutatós módszerrel keressük a legtöbb kikötőt tartalmazó L hosszú ablakot. Az időigény O(N).
*/
/*
Hint 1: || A kikötők távolsága sorrendben adott, így a szomszédos különbségek és az egymást követő három kikötő szélső távolsága közvetlenül kiszámolható. Az 1. részfeladatban a forrástól az első kikötőig és az utolsótól a Duna végéig tartó szakaszt is vedd figyelembe. ||
Hint 2: || A középső kikötőnél nem kell a két távolságot külön kiszámolni: az első és az utolsó kikötőtől mért távolságok különbsége 2 * T[i] - T[0] - T[N - 1], ennek abszolút értékét kell minimalizálni. ||
Hint 3: || A 4. részfeladatban egy bejárás elég: a szakasz végét akkor zárd le, ha a következő kikötő távolsága nagyobb K-nál. Az 5. részfeladatban az L hosszú ablakhoz tartozó kikötőszám két mutatóval számolható, a bal mutató mindig az aktuális kikötő. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h, k, l;
    cin >> n >> h >> k >> l;
    vector<int> t(n);
    for (int i = 0; i < n; i++) cin >> t[i];

    // 1. részfeladat: a leghosszabb kikötőmentes szakasz (a forrástól és a Duna végéig is)
    int gap = max(t[0], h - t[n - 1]);
    for (int i = 0; i + 1 < n; i++) gap = max(gap, t[i + 1] - t[i]);
    cout << "#\n" << gap << "\n";

    // 2. részfeladat: az egymást követő kikötőhármasok száma, ahol a szélsők legfeljebb K-ra vannak
    int triples = 0;
    for (int i = 0; i + 2 < n; i++)
        if (t[i + 2] - t[i] <= k) triples++;
    cout << "#\n" << triples << "\n";

    // 3. részfeladat: a középső kikötő sorszáma (döntetlennél a kisebb)
    long long total = (long long)t[0] + t[n - 1];
    int mid = 0;
    long long bestDiff = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        long long d = llabs(2LL * t[i] - total);
        if (d < bestDiff) {
            bestDiff = d;
            mid = i;
        }
    }
    cout << "#\n" << mid + 1 << "\n";

    // 4. részfeladat: a leghosszabb szakasz első és utolsó kikötője (ha egy kikötő, akkor -1)
    int bestA = 0, bestB = 0, bestLen = -1;
    int a = 0;
    for (int i = 0; i < n; i++) {
        if (i == n - 1 || t[i + 1] - t[i] > k) {
            int len = t[i] - t[a];
            if (len > bestLen) {
                bestLen = len;
                bestA = a;
                bestB = i;
            }
            a = i + 1;
        }
    }
    cout << "#\n";
    if (bestA == bestB)
        cout << -1 << "\n";
    else
        cout << bestA + 1 << ' ' << bestB + 1 << "\n";

    // 5. részfeladat: a legtöbb kikötőt tartalmazó L kilométeres szakaszon levő kikötők száma
    int most = 0;
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (j < i) j = i;
        while (j < n && t[j] - t[i] <= l) j++;
        most = max(most, j - i);
    }
    cout << "#\n" << most << "\n";
    return 0;
}
