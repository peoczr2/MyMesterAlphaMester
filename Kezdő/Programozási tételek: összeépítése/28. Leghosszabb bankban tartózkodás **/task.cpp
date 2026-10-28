/*
Megoldás lényege:
Csak a belépés (1) és a kilépés (-1) események számítanak, a pénzműveletek nem befolyásolják a bent tartózkodást. Egy map-ban kártyaszámonként eltároljuk a belépés időpontját percekben (óra * 60 + perc). Kilépéskor a kilépési és a hozzá tartozó belépési idő különbsége egy benntartózkodás hossza; ezt hasonlítjuk az eddigi maximumhoz, majd töröljük a kártyát a map-ból. Az események végén a még bent lévőket 24:00-kor (1440 perc) kitessékelik, így az ő benntartózkodásuk 1440 mínusz a belépési idő. Mivel N ≤ 100, az idő O(N log N), ami bőven belefér az időlimitbe.
*/
/*
Hint 1: || Kilépéskor mindig a kártyaszámhoz tartozó belépési időpontot kell megtalálni. A pénzfelvétel és a befizetés események egyáltalán nem változtatják a bent tartózkodási időt. ||
Hint 2: || Használj asszociatív tömböt (map), amelyben a kártyaszám a kulcs, a belépés ideje percben az érték. Kilépéskor vond ki a belépési időt a kilépési időből, majd töröld a bejegyzést. ||
Hint 3: || Az események feldolgozása után a még bent lévők hosszát a nap végi 24:00-s időpontból (1440 perc) számold ki, és ezeket is vedd bele a maximumba. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    map<int, int> bent;  // kártyaszám -> belépés ideje percben
    int leghosszabb = 0;

    for (int i = 0; i < n; i++) {
        int ora, perc, tipus, szam;
        cin >> ora >> perc >> tipus >> szam;
        int ido = ora * 60 + perc;

        if (tipus == 1) {
            bent[szam] = ido;
        } else if (tipus == -1) {
            auto it = bent.find(szam);
            if (it != bent.end()) {
                leghosszabb = max(leghosszabb, ido - it->second);
                bent.erase(it);
            }
        }
    }

    for (const auto &par : bent) {
        leghosszabb = max(leghosszabb, 24 * 60 - par.second);
    }

    cout << leghosszabb << "\n";
    return 0;
}
