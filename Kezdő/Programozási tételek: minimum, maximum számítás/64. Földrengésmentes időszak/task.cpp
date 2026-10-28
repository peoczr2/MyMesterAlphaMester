/*
Megoldás lényege:
Minden földrengést zárt perc-intervallumként olvasunk be (a kezdő- és a végperc is benne van), és az összes intervallumot kezdőpercük szerint rendezzük.
Balról jobbra haladva nyilvántartjuk az eddig lefedett legkésőbbi percet (kezdetben 0), és a következő intervallum előtti szabad percek számát (kezdőperc - lefedett vég - 1) hasonlítjuk a legjobb eddigi értékhez.
Az utolsó földrengés után a szabad szakasz M - lefedett vég perc hosszú, ezt is figyelembe vesszük.
Az időigény O(S log S), ahol S az összes földrengés száma (legfeljebb 100 000), így az M akár 10 000 000 is lehet, nem kell percenként végigmenni rajta.
*/
/*
Hint 1: || Egy perc akkor "nem volt földrengés", ha egyik sziget földrengési intervallumába sem esik. A keresett érték tehát a földrengésekkel le nem fedett leghosszabb összefüggő szakasz hossza. ||
Hint 2: || Ne a szigetek szerinti blokkokkal dolgozz: gyűjtsd össze az összes intervallumot, rendezd őket kezdőperc szerint, és haladj végig rajtuk egy "eddig lefedett utolsó perc" változóval. ||
Hint 3: || Két egymás utáni intervallum között a szabad percek száma: kezdőperc - (eddigi legnagyobb végperc) - 1. Az eddigi végpercet kezdetben 0-nak véve az első intervallum előtti szakasz is ugyanígy számolható, a végén pedig M - (legnagyobb végperc) adja az utolsó szakaszt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    long long m;
    cin >> k >> m;

    vector<pair<long long, long long>> quakes;
    for (int i = 0; i < k; i++) {
        int f;
        cin >> f;
        for (int j = 0; j < f; j++) {
            long long s, e;
            cin >> s >> e;
            quakes.push_back({s, e});
        }
    }

    sort(quakes.begin(), quakes.end());

    long long best = 0;
    long long covered = 0; // az eddig lefedett legkésőbbi perc
    for (auto [s, e] : quakes) {
        best = max(best, s - covered - 1);
        covered = max(covered, e);
    }
    best = max(best, m - covered);

    cout << best << '\n';
    return 0;
}
