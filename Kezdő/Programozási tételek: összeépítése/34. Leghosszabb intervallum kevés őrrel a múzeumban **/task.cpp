/*
Megoldás lényege:
Minden őr szolgálatát egy különbségtömbbel rögzítem: az első szolgálati napon +1-et, az utolsó utáni napon -1-et írok. Ennek prefixösszege minden napon megadja az aktuálisan szolgálatban lévő őrök számát. Balról jobbra haladva követem a kettőnél kevesebb őrt mutató napokból álló folytonos szakaszokat: a szakasz hosszát minden nap frissítem, és csak szigorúan hosszabb szakasz írja felül a legjobbat, így döntetlennél a kisebb első nap marad. Ha nincs ilyen nap, a kiírt érték 0. Időigény O(M + N), memóriaigény O(M).
*/
/*
Hint 1: || Nem kell minden napra külön összeszámolni az őröket: minden szolgálat egy intervallum, ezért elég az intervallum kezdetét és végét jelölni egy különbségtömbben. ||
Hint 2: || A különbségtömb prefixösszege minden napon megadja a szolgálatban lévő őrök számát. Ezután egy balról jobbra haladó bejárással követheted az egymás utáni, kettőnél kevesebb őrös napok szakaszát. ||
Hint 3: || Egy szakasz csak akkor lesz új legjobb, ha hossza szigorúan nagyobb a jelenleginél; így döntetlen esetén a korábbi, kisebb első napú szakasz marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<int> kulonbseg(m + 2, 0);
    for (int i = 0; i < n; i++) {
        int e, u;
        cin >> e >> u;
        kulonbseg[e]++;
        kulonbseg[u + 1]--;
    }

    int legHossz = 0, legElso = 0, legUtolso = 0;
    int kezdet = 0;   // az aktuális, kettőnél kevesebb őrös szakasz első napja (0: nincs ilyen)
    int osszeg = 0;
    for (int nap = 1; nap <= m; nap++) {
        osszeg += kulonbseg[nap];
        if (osszeg < 2) {
            if (kezdet == 0) kezdet = nap;
            int hossz = nap - kezdet + 1;
            if (hossz > legHossz) {
                legHossz = hossz;
                legElso = kezdet;
                legUtolso = nap;
            }
        } else {
            kezdet = 0;
        }
    }

    if (legHossz == 0) cout << 0 << "\n";
    else cout << legElso << " " << legUtolso << "\n";
    return 0;
}
