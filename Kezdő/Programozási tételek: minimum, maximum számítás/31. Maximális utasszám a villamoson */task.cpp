/*
Megoldás lényege:
Az állomásokon sorban haladunk, és követjük, hány utas ül a villamoson. Minden állomáson előbb a leszállók mennek le, utána a felszállók jönnek fel, vagyis az aktuális létszám az eddigi létszám − L + F. A maximális utasszámot az eddigi legnagyobb létszámban tartjuk nyilván, és minden állomás után frissítjük. A leszállás után a létszám nem nő, így a maximum mindig egy felszállás utáni állapotban lehet, ezért ezeket vizsgáljuk. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Nem kell az utasok egyéni adatait tárolni: elég minden állomás után az aktuális létszámot követni, és közben a legnagyobb értéket megjegyezni. ||
Hint 2: || Az állomáson a leszállók előbb mennek le, utána a felszállók jönnek fel; a villamos kezdetben üres, így a létszám 0-ról indul. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int stations;
    cin >> stations;

    int passengers = 0;
    int maxPassengers = 0;
    for (int i = 0; i < stations; i++) {
        int boarding, alighting;
        cin >> boarding >> alighting;
        passengers = passengers - alighting + boarding;
        maxPassengers = max(maxPassengers, passengers);
    }

    cout << maxPassengers << "\n";
    return 0;
}
