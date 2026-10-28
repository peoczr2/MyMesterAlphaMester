/*
Megoldás lényege:
Az inch → cm átváltás 2,54-gyel való szorzás, a cm → inch átváltás ugyanezzel a számmal való osztás. Az irányt a sor első száma (1 vagy 0) dönti el, így soronként egy elágazás és egy művelet szükséges. Az eredményt fixed formátumban, két tizedesjegyre kerekítve írjuk ki. Az N sor feldolgozása O(N) idő, a memóriaigény O(1). Az értékek legfeljebb 10^4 · 2,54 nagyságúak, így a double pontossága elegendő a két tizedesjegy helyes kerekítéséhez.
*/
/*
Hint 1: || A két átváltási irány ugyanabból a 2,54-es szorzóból áll: inch → cm esetén szorozni, cm → inch esetén osztani kell. Az irányt a sor első száma (1 vagy 0) dönti el. ||
Hint 2: || A kiírásnál használj fixed formátumot és setprecision(2) beállítást, így az eredmény mindig két tizedesjeggyel jelenik meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const double INCH_CM = 2.54;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int irany;
        double osszeg;
        cin >> irany >> osszeg;

        double eredmeny = (irany == 1) ? osszeg * INCH_CM : osszeg / INCH_CM;
        cout << fixed << setprecision(2) << eredmeny << "\n";
    }

    return 0;
}
