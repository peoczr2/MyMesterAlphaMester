/*
Megoldás lényege:
Minden háborút a kezdő és a befejező év közötti zárt évintervallumnak tekintünk, és egy évhez azt számoljuk, hány háború tart benne.
A háborúk kezdő és befejező eseményeit egy rendezett map-ben gyűjtjük: a kezdő évnél a számláló nő eggyel, a befejező év utáni évnél csökken eggyel.
Az eseményeket sorban bejárva a számláló mindig azt mutatja, hány háború tart az adott eseménypontól a következőig.
Az első olyan eseménypont, ahol a számláló éppen 1, adja a legkorábbi évet, amikor csak egy háború volt, mert a számláló csak az eseményeknél változik.
Ha nincs ilyen év, a válasz 0.
Az idő O(K log K), ahol K a háborúk száma, ez bőven belefér az időlimitbe.
*/
/*
Hint 1: || Egy év pontosan akkor esik a „csak egy háború” kategóriába, ha éppen egyetlen háború intervallumába esik. Számold meg minden évhez, hány háború tart benne. ||
Hint 2: || Nem kell minden évet külön vizsgálni: a számláló csak a háborúk kezdő és befejező évei körül változik. Rendezett eseménylistával (kezdésnél +1, befejezés utáni évnél -1) menj végig, és az első olyan eseménypont a válasz, ahol a számláló éppen 1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    map<int, int> esemeny; // év -> a tartó háborúk számának változása
    int utolso = INT_MIN;
    for (int i = 0; i < k; i++) {
        int a, b, kezdet, vege;
        cin >> a >> b >> kezdet >> vege;
        esemeny[kezdet]++;
        esemeny[vege + 1]--;
        utolso = max(utolso, vege);
    }

    int aktiv = 0, valasz = 0;
    for (auto [ev, dv] : esemeny) {
        if (ev > utolso) break;
        aktiv += dv;
        if (aktiv == 1) {
            valasz = ev;
            break;
        }
    }
    cout << valasz << '\n';
}
