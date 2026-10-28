/*
Megoldás lényege:
Minden háború kezdő napjánál a különbségtömbben +1-et, az utolsó nap utáni napnál −1-et írunk. A prefixösszeg megmondja, hány háború tart az adott napon: ahol ez 0, ott béke van. A napokat sorban bejárva követjük az aktuális békés szakasz hosszát és kezdetét, és a leghosszabb szakaszt tartjuk meg. Egyenlő hossznál a korábbit hagyjuk meg, mert csak szigorúan hosszabb szakasz írja felül a korábbit. Az idő O(N + M), ami a 100 000-es korlátok mellett bőven belefér a 0,2 másodpercbe.
*/
/*
Hint 1: || Nem kell minden napot külön ellenőrizni a háborúk között. Elég egy különbségtömb: a háború kezdő napját növeled, az utolsó utáni napját csökkented. Az egymás utáni összegekből kiolvasható, melyik nap van háborúban. ||
Hint 2: || Egy menetben haladj a napokon: ha a futó összeg 0, a békés szakasz hosszát növeled, különben a szakasz hosszát nullázod. Mentsd el a leghosszabb szakasz hosszát és kezdetét, és csak a szigorúan hosszabb szakasz írja felül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // kulonbseg: a háborúk számának különbségtömbje (a végén egy extra elemmel)
    vector<int> kulonbseg(n + 2, 0);
    for (int i = 0; i < m; i++) {
        int e, u;
        cin >> e >> u;
        kulonbseg[e]++;
        kulonbseg[u + 1]--;
    }

    int hossz = 0, kezdet = 0;               // az aktuális békés szakasz
    int legjobb = 0, legjobbKezdet = -1;     // a leghosszabb eddig talált szakasz
    int folyo = 0;                           // az adott napon zajló háborúk száma

    for (int nap = 1; nap <= n; nap++) {
        folyo += kulonbseg[nap];
        if (folyo == 0) {
            if (hossz == 0) {
                kezdet = nap;
            }
            hossz++;
            if (hossz > legjobb) {
                legjobb = hossz;
                legjobbKezdet = kezdet;
            }
        } else {
            hossz = 0;
        }
    }

    if (legjobb == 0) {
        cout << -1 << "\n";
    } else {
        cout << legjobb << " " << legjobbKezdet << "\n";
    }
    return 0;
}
