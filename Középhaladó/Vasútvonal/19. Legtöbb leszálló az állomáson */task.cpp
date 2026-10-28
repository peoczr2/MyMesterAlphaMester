/*
Megoldás lényege:
A legtöbb leszállót egy bejárással keressük: minden állomásnál összehasonlítjuk a leszállók számát az eddigi legnagyobbal, és ha az szigorúan nagyobb, frissítjük a maximumot és a sorszámát. Egyenlőség esetén a korábbi (kisebb sorszámú) állomás marad, ami a feladat kívánsága szerint a helyes válasz. A felszállók számára nincs szükség. Az időigény O(N).
*/
/*
Hint 1: || Nem kell az összes adatot tárolni: elég az eddig talált legnagyobb leszállószámot és az ahhoz tartozó állomás sorszámát megjegyezni, és minden állomásnál ezzel összevetni az aktuálisat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int bestIdx = 1;
    long long bestLe = -1;
    for (int i = 1; i <= n; i++) {
        long long le, fel;
        cin >> le >> fel;
        if (le > bestLe) {
            bestLe = le;
            bestIdx = i;
        }
    }
    cout << bestIdx << "\n";
    return 0;
}
