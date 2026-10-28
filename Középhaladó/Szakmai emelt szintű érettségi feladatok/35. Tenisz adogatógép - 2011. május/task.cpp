/*
Megoldás lényege:
A kilövés számított távolsága s = v0^2 * sin(2*alpha) / g, ahol g = 9.81 m/s^2. A szöget fokban adjuk meg, ezért a sin függvénynek radiánt kell átadni. Minden tesztesetre kiszámoljuk a mért és a számított távolság százalékos abszolút eltérését: |mért - számított| / számított * 100. A számított távolság mindig pozitív (v0 >= 10, 30 <= alpha <= 70), így nincs nullával osztás. A bemenetet soronként dolgozzuk fel, és csak a legnagyobb eltérést és annak sorszámát tartjuk meg; a szigorú összehasonlítás miatt döntetlen esetén az első előfordulás marad. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egy kilövés távolsága s = v0^2 * sin(2*alpha) / g. A szög fokban van, ezért a sin függvénynek radiánt add át (fok * pi / 180). ||
Hint 2: || Nem kell tömbben tárolni az adatokat: soronként kiszámolható az eltérés, és elég a maximumot és annak sorszámát megtartani. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    const double g = 9.81;
    const double pi = acos(-1.0);

    int n;
    cin >> n;

    int bestIndex = 0;
    double bestDeviation = -1.0;
    for (int i = 1; i <= n; i++) {
        double v0, alpha, measured;
        cin >> v0 >> alpha >> measured;

        double computed = v0 * v0 * sin(2.0 * alpha * pi / 180.0) / g;
        double deviation = fabs(measured - computed) / computed * 100.0;

        if (deviation > bestDeviation) {
            bestDeviation = deviation;
            bestIndex = i;
        }
    }

    cout << bestIndex << "\n";
    return 0;
}
