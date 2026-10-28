/*
Megoldás lényege: a bemenet minden sora egy világcsúcs-elérés (megdöntés vagy beállítás), ezért nincs szükség szűrésre.
Elég a szomszédos sorok évszámának különbségét venni, és ezek közül a legnagyobbat kiválasztani.
Ez egyszerű maximumkiválasztás: az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Minden sor egy világcsúcs, ezért nem kell szűrni: a kérdés csak az, hogy két egymás utáni sor évszáma között mennyi az eltérés. ||
Hint 2: || Olvasd be soronként az évet és a magasságot, a magasságot nem kell használni. Az aktuális év és az előző sor éve különbségének abszolút értékét hasonlítsd a dolgozó maximumhoz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int prevYear = 0, best = 0;
    for (int i = 0; i < n; i++) {
        int year, height;
        cin >> year >> height;
        if (i > 0) best = max(best, abs(year - prevYear));
        prevYear = year;
    }
    cout << best << "\n";
    return 0;
}
