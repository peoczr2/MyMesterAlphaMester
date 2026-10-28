/*
Megoldás lényege:
Minden háborút a kezdő és a befejező év közötti zárt évintervallumnak tekintünk, egy év pedig akkor békés, ha egyik intervallumba sem esik.
Az intervallumok eseményeit (kezdésnél +1, befejezés utáni évnél -1) egy rendezett map-ben gyűjtjük, így minden eseménypontról tudjuk, hány háború tart az adott évtől a következő eseménypontig.
Azokat a szakaszokat, ahol a számláló 0, az első háború kezdetétől az utolsó befejezésig, az összes évvel együtt kiírjuk növekvő sorrendben.
Először a békés évek számát írjuk, a második sorba pedig az évszámokat.
Az idő O(K log K + B), ahol K a háborúk száma, B pedig a békés évek száma, ez bőven belefér az időlimitbe.
*/
/*
Hint 1: || Egy év akkor békés, ha nincs benne háború: a háborús évek a kezdő és a befejező év közötti évek (mindkettővel együtt). A békés éveket a háborúk közötti szakaszok adják. ||
Hint 2: || Ugyanúgy, mint a legkorábbi békés év keresésénél, készíts eseménylistát (kezdésnél +1, befejezés utáni évnél -1). Ha két egymást követő eseménypont között a számláló 0, akkor az e közötti évek mind békések, és sorban kiírhatók. ||
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

    vector<pair<int, int>> ev(esemeny.begin(), esemeny.end());
    vector<int> beke;
    int aktiv = 0;
    for (size_t i = 0; i + 1 < ev.size(); i++) {
        aktiv += ev[i].second;
        if (aktiv != 0) continue;
        int to = min(ev[i + 1].first - 1, utolso);
        for (int y = ev[i].first; y <= to; y++) beke.push_back(y);
    }

    cout << beke.size() << '\n';
    for (int y : beke) cout << y << ' ';
    cout << '\n';
}
