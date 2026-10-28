/*
Megoldás lényege:
Egy szakasz menetideje az érkezési idő mínusz az előző megálló indulási ideje; az első szakasznál az előző indulás a 0. percben van. Egy bejárásban kiszámoljuk minden szakasz idejét, és az előző szakasz idejéhez hasonlítjuk. Ha az aktuális szakasz szigorúan hosszabb, növeljük a darabszámot. Az első szakaszt nincs mihez hasonlítani, ezért a számlálás a második szakasztól indul. Az időigény O(N).
*/
/*
Hint 1: || Egy szakasz ideje az érkezési idő mínusz az előző megállóból való indulási idő. Az első szakasz előző indulása a 0. perc. ||
Hint 2: || Egy ciklusban tartsd nyilván az előző szakasz idejét és az előző indulási időt. A második szakasztól kezdve, ha az aktuális szakasz hosszabb az előzőnél, növeld a számlálót. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int prevDep = 0;  // a 0. állomásról a 0. percben indul a villamos
    int prevSeg = 0;  // az előző szakasz ideje
    int cnt = 0;

    for (int i = 1; i <= n; i++) {
        int t, erk, ind;
        cin >> t >> erk >> ind;
        int seg = erk - prevDep;
        if (i > 1 && seg > prevSeg) {
            cnt++;
        }
        prevSeg = seg;
        prevDep = ind;
    }

    cout << cnt << '\n';
    return 0;
}
