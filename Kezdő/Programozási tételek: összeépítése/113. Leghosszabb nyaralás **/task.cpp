/*
Megoldás lényege:
Mivel minden nap ára pozitív, egy szakasz összege bővítéskor nő, szűkítéskor csökken, ezért a P-t nem meghaladó összegű leghosszabb szakasz kétmutatós csúszóablakkal kereshető meg.
A jobb végpontot egyesével léptetjük, és az összeghez hozzáadjuk az adott nap árát.
Amíg az összeg meghaladja P-t, a bal végpontot eggyel jobbra visszük, és levonjuk az eldobott nap árát.
Minden lépés után a két végpont közötti szakasz hosszával frissítjük a legjobb eredményt.
Mindkét mutató csak előre halad, így az időigény O(N), ami N ≤ 100 000 mellett bőven belefér a 0,2 mp-es limitbe.
*/
/*
Hint 1: || Mivel minden ár pozitív, a bal végpont jobbra lépése csökkenti, a jobb végpont jobbra lépése növeli az összeget. Ha egy szakasz már túl drága, elég a bal végpontot előrébb tolni, nem kell újrakezdeni. ||
Hint 2: || Tartsd nyilván az aktuális szakasz összegét: a jobb végpont léptetésekor hozzáadod az árat, a bal végpont léptetésekor pedig levonod az eldobott nap árát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long p;
    cin >> n >> p;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    int best = 0;
    long long sum = 0;
    int l = 0;
    for (int r = 0; r < n; ++r) {
        sum += a[r];
        while (sum > p) {
            sum -= a[l];
            ++l;
        }
        best = max(best, r - l + 1);
    }
    cout << best << '\n';
    return 0;
}
