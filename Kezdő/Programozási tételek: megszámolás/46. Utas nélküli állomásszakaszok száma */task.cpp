/*
Megoldás lényege:
Az állomásokon végighaladva követjük, hány utas van éppen a villamoson: minden állomás után az eddigi utasszámhoz hozzáadjuk a felszállók, és kivonjuk a leszállók számát.
Az i-edik és az (i+1)-edik állomás közötti szakaszon akkor nem utazott senki, ha az i-edik állomás után a villamoson nincs utas, vagyis az utasszám 0.
Az utolsó állomás után már nincs további szakasz, ezért az N-edik állomás utasszámát nem vesszük figyelembe.
Elég egyetlen egész számot tárolni, a teljes bejárás időigénye O(N).
*/
/*
Hint 1: || Nem kell az egész villamos állapotát tárolni: elég egyetlen számot (az éppen a villamoson utazók számát) követned az állomások sorrendjében. ||
Hint 2: || Egy állomás után az utasok száma: az előző érték, plusz a felszállók, mínusz a leszállók. Akkor számolj egy üres szakaszt, ha ez az érték 0, de az utolsó állomás után már nincs szakasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int utas = 0;
    int ures = 0;
    for (int i = 1; i <= n; i++) {
        int felszall, leszall;
        cin >> felszall >> leszall;
        utas += felszall - leszall;
        if (i < n && utas == 0) {
            ures++;
        }
    }
    cout << ures << endl;
    return 0;
}
