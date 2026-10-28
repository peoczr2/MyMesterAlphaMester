/*
Megoldás lényege:
A feladat szerint a megfigyelések időrendben következnek, ezért két egymás utáni sor időpontja között nincs más áthaladás. Az időpontokat percre váltjuk át (óra · 60 + perc), és a szomszédos sorok különbségét vesszük: a leghosszabb különbséghez tartozó két időpont adja a keresett szakaszt. Egyetlen bejárással megkapjuk, és a szigorú összehasonlítás miatt a legkorábbi ilyen szakasz marad meg. A megfigyelési helyek sorszámára nincs szükség. Az időigény O(N).
*/
/*
Hint 1: || Két egymást követő megfigyelés közötti időszakon akkor nem haladt át jármű, ha nincs köztük másik megfigyelés. Ezért a megfigyelések időpontjai közötti különbségeket kell összehasonlítani. ||
Hint 2: || Alakítsd át az időpontokat a nap kezdetétől eltelt percekre (óra · 60 + perc), így a különbség egyszerű kivonás. A legnagyobb különbségnél jegyezd fel a kezdő és a záró időpontot, és csak szigorúan nagyobb különbség esetén írd felül őket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;

    vector<int> ido(n);
    for (int i = 0; i < n; i++) {
        int hely, ora, perc;
        cin >> hely >> ora >> perc;
        ido[i] = ora * 60 + perc;
    }

    int legjobb = -1, kezdet = 0, veg = 0;
    for (int i = 0; i + 1 < n; i++) {
        int kulonbseg = ido[i + 1] - ido[i];
        if (kulonbseg > legjobb) {
            legjobb = kulonbseg;
            kezdet = ido[i];
            veg = ido[i + 1];
        }
    }
    cout << kezdet / 60 << " " << kezdet % 60 << " "
         << veg / 60 << " " << veg % 60 << "\n";
    return 0;
}
