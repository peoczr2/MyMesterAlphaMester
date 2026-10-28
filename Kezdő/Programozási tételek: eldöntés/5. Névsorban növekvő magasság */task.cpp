/*
Megoldás lényege:
A névsor már adott, ezért csak azt kell eldönteni, hogy a magasságok a névsor szerinti sorrendben sosem csökkennek-e. Egy logikai változóban nyilvántartjuk, volt-e csökkenés: minden tanuló magasságát összehasonlítjuk az előző tanuló magasságával. Az egyenlő magasság megengedett, így csak a szigorú csökkenés ad NEM választ. A neveket a válaszhoz nem használjuk, de be kell olvasni őket. Az időigény N-nel arányos.
*/
/*
Hint 1: || A névsor adott, nem kell rendezni: csak azt kell látni, hogy a magasságok a sorrendben nem csökkennek-e. ||
Hint 2: || Egy logikai változóval jegyezd meg, történt-e csökkenés: minden tanuló magasságát hasonlítsd az előző tanuló magasságához, és csak a kisebb érték számít hibának. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    bool novekvo = true;
    int elozo = 0;
    for (int i = 0; i < n; i++) {
        string nev;
        int magassag;
        cin >> nev >> magassag;

        if (i > 0 && magassag < elozo) {
            novekvo = false;
        }
        elozo = magassag;
    }

    cout << (novekvo ? "IGEN" : "NEM") << '\n';
    return 0;
}
