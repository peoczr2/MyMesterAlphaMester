/*
Megoldás lényege:
Állomásonként kiszámoljuk, hány utas van a vonaton az állomás elhagyása után. Az i. és az (i+1). állomás közötti szakasz akkor üres, ha ez az érték 0. Az egymás utáni üres szakaszok egy összefüggő üres utat alkotnak: ha a sorozat az a. állomástól a b. állomásig tart, a legmesszebbi pár az a. és a (b+1). állomás. Egy bejárással követjük az aktuális üres sorozat kezdetét, és csak szigorúan hosszabb sorozatnál frissítünk, így egyenlőség esetén a korábbi pár marad. Ha nincs üres szakasz, a megoldás 0 0. Az időigény O(N).
*/
/*
Hint 1: || Számold ki minden állomás után, hány utas van a vonaton: az előző érték + felszállók - leszállók. Az i. és (i+1). állomás közötti szakasz utasszáma ez az érték. ||
Hint 2: || Keresd a leghosszabb, egymást követő nulla utasszámú szakaszok sorozatát; ha az a. állomástól a b. állomásig tart, a megoldás az a. és a (b+1). állomás. Vezess nyilván a sorozat kezdetét, és csak szigorúan hosszabb sorozatnál frissíts. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> le(n + 1), fel(n + 1);
    for (int i = 1; i <= n; i++) cin >> le[i] >> fel[i];

    int load = 0;                 // utasok száma az aktuális állomás elhagyása után
    int best_len = 0, best_a = 0, best_b = 0;
    int run_start = 0;            // az aktuális üres sorozat kezdő állomása (0: nincs)
    for (int i = 1; i <= n; i++) {
        load += fel[i] - le[i];
        if (i == n) break;        // az utolsó állomás után nincs szakasz
        if (load == 0) {
            if (run_start == 0) run_start = i;
            int len = (i + 1) - run_start;
            if (len > best_len) {
                best_len = len;
                best_a = run_start;
                best_b = i + 1;
            }
        } else {
            run_start = 0;
        }
    }
    cout << best_a << " " << best_b << "\n";
    return 0;
}
