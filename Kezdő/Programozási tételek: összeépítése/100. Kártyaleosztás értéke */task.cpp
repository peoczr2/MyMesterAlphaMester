/*
Megoldás lényege:
A lap értéke a figurától függ, a szín csak szorzót jelent: a piros lapok értéke duplázódik. A figurákhoz tartozó pontokat egy táblázatban tároljuk: a számozott figurák (7-es, 8-as, 9-es, 10-es) értéke maga a szám, az alsó 2, a felső 3, a király 4, az ász 11 pont. Minden kihúzott lapot beolvasunk (szín, figura), kikeressük az értékét, a pirosnál megduplázzuk, és hozzáadjuk az összeghez. A táblázat mérete állandó, ezért az időigény O(N), a 32 lap pedig gyorsan feldolgozható.
*/
/*
Hint 1: || Minden lapnál két dolgot kell meghatározni: a figura alapértékét, és azt, hogy a szín piros-e. A teljes pontszám az összes lap értékének összege. ||
Hint 2: || A figura szövegéhez (például „7-es”, „also”, „asz”) tárolj számértéket egy `map<string, int>` táblázatban. Ha a szín „piros”, az értéket szorozd kettővel, mielőtt az összeghez adod. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    map<string, int> ertek = {
        {"7-es", 7}, {"8-as", 8}, {"9-es", 9}, {"10-es", 10},
        {"also", 2}, {"felso", 3}, {"kiraly", 4}, {"asz", 11}
    };

    int n;
    cin >> n;
    int osszeg = 0;
    for (int i = 0; i < n; i++) {
        string szin, figura;
        cin >> szin >> figura;
        int pont = ertek[figura];
        if (szin == "piros") pont *= 2;
        osszeg += pont;
    }
    cout << osszeg << endl;
    return 0;
}
