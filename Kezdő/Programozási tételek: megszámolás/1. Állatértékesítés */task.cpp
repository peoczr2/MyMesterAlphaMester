/*
Megoldás lényege:
A kumulált bevétel a napok során nem csökken, így egy adott napon akkor volt eladás, ha a bevétel nagyobb az előző napinál.
Az első nap előző értéke 0, ezért az első napon is akkor számít eladás, ha a bevétel pozitív.
Egyetlen beolvasással és egy számlálóval végigmegyünk a napokon, az időigény O(N).
*/
/*
Hint 1: || Nem a bevétel nagyságát kell vizsgálni, hanem azt, hogy két egymást követő nap között nőtt-e a kumulált bevétel. ||
Hint 2: || Tárold az előző nap bevételét egy változóban (kezdetben 0), és minden beolvasott értéknél nézd meg, nagyobb-e nála. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long elozo = 0;
    int eladasok = 0;
    for (int i = 0; i < n; i++) {
        long long bevetel;
        cin >> bevetel;
        if (bevetel > elozo) {
            eladasok++;
        }
        elozo = bevetel;
    }
    cout << eladasok << endl;
    return 0;
}
