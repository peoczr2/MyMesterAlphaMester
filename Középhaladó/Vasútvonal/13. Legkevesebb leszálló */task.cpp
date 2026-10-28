/*
Megoldás lényege:
Az állomásokat egyetlen bejárással dolgozzuk fel. Csak azok az állomások számítanak, ahol volt leszálló (le > 0), a 0 leszállójú állomásokat kihagyjuk. Az eddigi legkisebb pozitív leszállószámot és a hozzá tartozó sorszámot tároljuk. A szigorú "<" összehasonlítás miatt egyenlőség esetén a korábbi állomás marad, így a legkisebb sorszámút kapjuk. Az időigény O(N), ami N <= 1000 mellett bőven belefér az időlimitbe.
*/
/*
Hint 1: || Nem kell az összes adatot tárolni: elég egy minimumkeresés a leszállók számán, de a 0 értékű állomásokat át kell ugrani. ||
Hint 2: || Két változóval dolgozz: az eddigi legkisebb pozitív leszállószám (kezdetben egy nagy érték) és az ehhez tartozó sorszám; csak szigorúan kisebb értéknél írd felül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int best_le = INT_MAX, best_idx = 0;
    for (int i = 1; i <= n; i++) {
        int le, fel;
        cin >> le >> fel;
        if (le > 0 && le < best_le) {
            best_le = le;
            best_idx = i;
        }
    }
    cout << best_idx << "\n";
    return 0;
}
