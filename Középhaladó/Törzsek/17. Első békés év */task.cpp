/*
Megoldás lényege:
Minden háborút a kezdő és a befejező év közötti zárt évintervallumnak tekintünk, egy év pedig akkor békés, ha egyik intervallumba sem esik.
Az intervallumok végpontjait eseményekként kezeljük: a kezdő évnél a háborúk száma nő eggyel, a befejező év utáni évnél csökken eggyel.
Ezeket egy rendezett map-ben gyűjtjük, így a bejárás során minden eseménypontnál tudjuk, hány háború tart éppen.
Az első olyan eseménypont, ahol a számláló 0 lesz, adja a legkorábbi békés évet, mert a számláló csak az eseményeknél változik.
Ha a bejárás az utolsó befejezés évéig nem talál ilyet, a válasz 0.
Az idő O(K log K), ahol K a háborúk száma, ez bőven belefér az időlimitbe.
*/
/*
Hint 1: || Egy év akkor békés, ha egyetlen háború intervallumába sem esik bele (a kezdő és a befejező év is háborús év). Keresd azokat az éveket, amelyek a háborúk között vannak. ||
Hint 2: || Ne minden évet végigpróbálj: a számláló csak a háborúk kezdő événél és a befejező év utáni évnél változik. Rendezett map-ben tárold a változásokat (kezdésnél +1, befejezés utáni évnél -1), és sorban számold a tartó háborúk számát. ||
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
        if (aktiv == 0) {
            valasz = ev;
            break;
        }
    }
    cout << valasz << '\n';
}
