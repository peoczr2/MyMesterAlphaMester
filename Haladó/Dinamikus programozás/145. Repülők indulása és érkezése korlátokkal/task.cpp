/*
Ötlet:
Az induló és érkező gépek saját sorrendje kötött, ezért csak azt kell eldönteni,
hogy a következő szabad kifutópálya-időpontban a soron következő indulót vagy a
soron következő érkezőt engedjük-e. Ha ismert az utoljára kiszolgált gép tényleges
ideje, akkor a következő kiválasztott gép legkorábbi lehetséges ideje egyértelmű:
max(tervezett_idő, előző_tényleges + P). Emiatt egy rögzített összefésülési sorrendhez
az optimális ütemezés mindig a mohón legkorábbi.

Dinamikus programozást használunk. Az állapot azt mondja meg, hogy az első i indulót
és j érkezőt már beütemeztük, az utolsó gép típusa ismert, és az utolsó gép mennyit
várt a saját tervezett idejéhez képest. Ez a várakozás legfeljebb 100 lehet, ezért az
állapottér kicsi. Ha az utolsó gép várakozása w, akkor a tényleges ideje egyszerűen
tervezett + w, innen pedig a következő gép új várakozása közvetlenül kiszámolható.

Kétféle állapotsort tartunk fenn gördülő sorokkal:
- dpF: az utolsó gép induló,
- dpL: az utolsó gép érkező.

Egy cellából csak két irányba lehet továbblépni: új indulót vagy új érkezőt adunk a
végére. Minden átmenetnél csak az új gép várakozási idejét kell hozzáadni az összeghez.
Az állapotok számát a kis várakozási korlát fogja meg, így az algoritmus
O(N * M * (FV + LV)) idejű és O(M * (FV + LV)) memóriájú.
*/
/*
Hint 1: || Egy rögzített induló/érkező sorrendnél a legjobb ütemezés az, ha minden gépet a lehető legkorábbi megengedett pillanatban indítasz vagy szállítasz le. ||
Hint 2: || Nem kell a teljes tényleges időt eltárolni: elég az utolsó gép várakozása, mert a tényleges idő = tervezett idő + várakozás. ||
Hint 3: || Az indulók és érkezők saját sorrendje fix, ezért a DP cellája természetesen az első i induló és első j érkező beütemezett állapota lesz. ||
Hint 4: || A memóriát gördülő sorokkal csökkentheted, mert az i-edik sor csak az i-1-edik sorból és a saját bal szomszédjából számolódik. ||
*/

#include <bits/stdc++.h>

using namespace std;

namespace {

const int INF = 1'000'000'000;

inline void relaxTransition(
    int *target,
    int targetBound,
    const int *source,
    int sourceBound,
    int base
) {
    if (base > targetBound) {
        return;
    }

    if (base <= 0) {
        int limitZero = min(sourceBound, -base);
        int bestZero = INF;
        for (int sourceWait = 0; sourceWait <= limitZero; ++sourceWait) {
            bestZero = min(bestZero, source[sourceWait]);
        }
        target[0] = min(target[0], bestZero);

        int maxTargetWait = min(targetBound, sourceBound + base);
        for (int targetWait = 1; targetWait <= maxTargetWait; ++targetWait) {
            int sourceCost = source[targetWait - base];
            if (sourceCost == INF) {
                continue;
            }
            target[targetWait] = min(target[targetWait], sourceCost + targetWait);
        }
        return;
    }

    int maxTargetWait = min(targetBound, sourceBound + base);
    for (int targetWait = base; targetWait <= maxTargetWait; ++targetWait) {
        int sourceCost = source[targetWait - base];
        if (sourceCost == INF) {
            continue;
        }
        target[targetWait] = min(target[targetWait], sourceCost + targetWait);
    }
}

} // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int indulokSzama, felszalloVarakozas, palyaSzukseg;
    cin >> indulokSzama >> felszalloVarakozas >> palyaSzukseg;

    vector<int> indulasiIdo(indulokSzama + 1);
    for (int index = 1; index <= indulokSzama; ++index) {
        cin >> indulasiIdo[index];
    }

    int erkezokSzama, leszalloVarakozas;
    cin >> erkezokSzama >> leszalloVarakozas;

    vector<int> erkezesiIdo(erkezokSzama + 1);
    for (int index = 1; index <= erkezokSzama; ++index) {
        cin >> erkezesiIdo[index];
    }

    if (indulokSzama == 0 && erkezokSzama == 0) {
        cout << 0 << '\n';
        return 0;
    }

    const int indulasiAllapotok = felszalloVarakozas + 1;
    const int erkezesiAllapotok = leszalloVarakozas + 1;

    vector<int> elozoIndulo((erkezokSzama + 1) * indulasiAllapotok, INF);
    vector<int> aktualisIndulo((erkezokSzama + 1) * indulasiAllapotok, INF);
    vector<int> elozoErkezo((erkezokSzama + 1) * erkezesiAllapotok, INF);
    vector<int> aktualisErkezo((erkezokSzama + 1) * erkezesiAllapotok, INF);

    if (erkezokSzama > 0) {
        elozoErkezo[erkezesiAllapotok] = 0;
        for (int j = 2; j <= erkezokSzama; ++j) {
            int *target = &elozoErkezo[j * erkezesiAllapotok];
            const int *source = &elozoErkezo[(j - 1) * erkezesiAllapotok];
            int base = erkezesiIdo[j - 1] + palyaSzukseg - erkezesiIdo[j];
            relaxTransition(target, leszalloVarakozas, source, leszalloVarakozas, base);
        }
    }

    for (int i = 1; i <= indulokSzama; ++i) {
        fill(aktualisIndulo.begin(), aktualisIndulo.end(), INF);
        fill(aktualisErkezo.begin(), aktualisErkezo.end(), INF);

        if (i == 1) {
            aktualisIndulo[0] = 0;
        } else {
            int *target = &aktualisIndulo[0];
            const int *source = &elozoIndulo[0];
            int base = indulasiIdo[i - 1] + palyaSzukseg - indulasiIdo[i];
            relaxTransition(target, felszalloVarakozas, source, felszalloVarakozas, base);
        }

        for (int j = 1; j <= erkezokSzama; ++j) {
            {
                int *target = &aktualisIndulo[j * indulasiAllapotok];

                if (i > 1) {
                    const int *source = &elozoIndulo[j * indulasiAllapotok];
                    int base = indulasiIdo[i - 1] + palyaSzukseg - indulasiIdo[i];
                    relaxTransition(target, felszalloVarakozas, source, felszalloVarakozas, base);
                }

                const int *source = &elozoErkezo[j * erkezesiAllapotok];
                int base = erkezesiIdo[j] + palyaSzukseg - indulasiIdo[i];
                relaxTransition(target, felszalloVarakozas, source, leszalloVarakozas, base);
            }

            {
                int *target = &aktualisErkezo[j * erkezesiAllapotok];

                const int *sourceFromIndulo = &aktualisIndulo[(j - 1) * indulasiAllapotok];
                int baseFromIndulo = indulasiIdo[i] + palyaSzukseg - erkezesiIdo[j];
                relaxTransition(target, leszalloVarakozas, sourceFromIndulo, felszalloVarakozas, baseFromIndulo);

                if (j > 1) {
                    const int *sourceFromErkezo = &aktualisErkezo[(j - 1) * erkezesiAllapotok];
                    int baseFromErkezo = erkezesiIdo[j - 1] + palyaSzukseg - erkezesiIdo[j];
                    relaxTransition(target, leszalloVarakozas, sourceFromErkezo, leszalloVarakozas, baseFromErkezo);
                }
            }
        }

        swap(elozoIndulo, aktualisIndulo);
        swap(elozoErkezo, aktualisErkezo);
    }

    int valasz = INF;
    if (indulokSzama == 0) {
        for (int wait = 0; wait <= leszalloVarakozas; ++wait) {
            valasz = min(valasz, elozoErkezo[erkezokSzama * erkezesiAllapotok + wait]);
        }
    } else {
        for (int wait = 0; wait <= felszalloVarakozas; ++wait) {
            valasz = min(valasz, elozoIndulo[erkezokSzama * indulasiAllapotok + wait]);
        }
        for (int wait = 0; wait <= leszalloVarakozas; ++wait) {
            valasz = min(valasz, elozoErkezo[erkezokSzama * erkezesiAllapotok + wait]);
        }
    }

    if (valasz == INF) {
        cout << -1 << '\n';
    } else {
        cout << valasz << '\n';
    }

    return 0;
}