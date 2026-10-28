/*
Megoldás lényege:
Ha a rendezett sorozat középső elemét tesszük a gyökérbe, a bal oldalra a kisebb felét, a jobb oldalra a nagyobb felét, akkor a két részfa elemszáma legfeljebb eggyel tér el, így a fa kiegyensúlyozott. Ezt a két részre rekurzívan alkalmazzuk. Minden csúcsot egyszer hozunk létre, a csúcsok azonosítóit a létrehozás sorrendjében osztjuk ki (a jobb részfa előbb), így az 1-es azonosító a gyökér. Az időigény O(N).
*/
/*
Hint 1: || Ha a sorozat középső elemét tesszük a gyökérbe, a bal és a jobb részfa elemszáma legfeljebb egyel tér el. Az egyes részeket ugyanígy, rekurzívan építsd fel. ||
Hint 2: || Írj egy rekurzív függvényt, amely egy [l, r] indextartományból épít részfát. A csúcs adata a kozep = (l + r) / 2, a bal részfa a [l, kozep - 1], a jobb részfa a [kozep + 1, r] tartományból jön. Üres tartománynál a visszaadott azonosító 0. ||
Hint 3: || A csúcsok azonosítóját a létrehozás sorrendjében oszd ki 1-től, így a gyökér az 1-es. Ha a jobb részfát építed előbb, a kimenet megegyezik a mintával. ||
*/
#include <bits/stdc++.h>
using namespace std;

int cnt = 0;
vector<int> ertek, bal, jobb;  // a csúcs azonosítója szerint indexelve (1-től)

// A [l, r] elemeiből kiegyensúlyozott részfát épít, visszaadja a gyökér azonosítóját (0, ha üres)
int epit(int l, int r) {
    if (l > r) return 0;
    int id = ++cnt;
    int kozep = (l + r) / 2;
    ertek[id] = kozep;
    jobb[id] = epit(kozep + 1, r);
    bal[id] = epit(l, kozep - 1);
    return id;
}

int main() {
    int n;
    cin >> n;
    ertek.assign(n + 1, 0);
    bal.assign(n + 1, 0);
    jobb.assign(n + 1, 0);

    epit(1, n);

    for (int i = 1; i <= n; i++)
        cout << ertek[i] << ' ' << bal[i] << ' ' << jobb[i] << '\n';
    return 0;
}
