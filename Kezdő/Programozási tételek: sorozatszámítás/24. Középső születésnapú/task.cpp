/*
Megoldás lényege:
A születésnapok csak 366-féle napot vehetnek fel, ezért nem kell rendezni. Egy tömbben megszámoljuk,
hány ember született az egyes napokon, és minden naphoz feljegyezzük az első előfordulás sorszámát.
A napokat dátum szerint (hónap, nap) növekvő sorrendben végigjárva a darabszámokat halmozzuk, amíg az
összeg el nem éri (N+1)/2-t. Az ott álló nap a középső ember születésnapja, a hozzá tartozó legkisebb
sorszám pedig a kért ember. Az időigény O(N + 366), a beolvasás dominál.
*/
/*
Hint 1: || Nem kell az embereket rendezni: egy születésnap csak 366-féle lehet, így elég a napok gyakoriságát ismerni. ||
Hint 2: || Tömbben számold a napok darabszámát, a kulcs legyen hónap*32+nap, mert ez a sorrendet is megtartja. Közben minden naphoz jegyezd meg az első előfordulás sorszámát. Ezután a napokat sorban járd be, és keresd azt a napot, ahol a halmozott darabszám eléri (N+1)/2-t. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    const int KULCSOK = 13 * 32;
    vector<int> darab(KULCSOK, 0), elso(KULCSOK, 0);
    for (int i = 1; i <= n; i++) {
        int honap, nap;
        cin >> honap >> nap;
        int kulcs = honap * 32 + nap;
        if (darab[kulcs] == 0) elso[kulcs] = i;
        darab[kulcs]++;
    }

    int kell = (n + 1) / 2;
    int halmozott = 0;
    for (int kulcs = 0; kulcs < KULCSOK; kulcs++) {
        if (darab[kulcs] == 0) continue;
        halmozott += darab[kulcs];
        if (halmozott >= kell) {
            cout << kulcs / 32 << " " << kulcs % 32 << "\n";
            cout << elso[kulcs] << "\n";
            break;
        }
    }
    return 0;
}
