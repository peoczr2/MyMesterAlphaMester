/*
Megoldás lényege:
A napokat balról jobbra egyszer végigjárjuk, és közben nyilvántartjuk az eddigi legnagyobb bevételt.
Egy nap akkor különösen sikeres, ha a bevétele szigorúan nagyobb az eddigi maximumnál; az első nap
mindig ilyen, mert a kezdő maximum kisebb bármely bevételnél. Az aktuális sikeres sorozat hosszát
növeljük sikeres nap esetén, sikertelen napnál nullázzuk, és a sorozat kezdő napját is megjegyezzük.
Ha az aktuális sorozat hossza meghaladja az eddigi legjobbat, átírjuk a legjobb hosszt és kezdő napot.
Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egy nap pontosan akkor sikeres, ha a bevétele szigorúan nagyobb az összes korábbi napénál, ezért elég az eddigi legnagyobb bevételt tárolni, nem kell minden korábbi napot megnézni. ||
Hint 2: || Egyetlen menetben haladj a napokon: tartsd számon az aktuális sikeres sorozat hosszát és kezdő napját; sikeres nap esetén a sorozat hosszabbodik, sikertelen napnál újra kezdődik, és mindig hasonlítsd össze az eddigi legjobbal. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int eddigiMax = -1;          // eddigi legnagyobb bevétel (bevétel >= 0, így az első nap sikeres lesz)
    int legjobbHossz = 0;        // a leghosszabb sikeres sorozat hossza
    int legjobbKezd = 0;         // ennek a sorozatnak az első napja
    int aktHossz = 0;            // az aktuális sikeres sorozat hossza
    int aktKezd = 0;             // az aktuális sikeres sorozat első napja

    for (int nap = 1; nap <= n; nap++) {
        int bevetel;
        cin >> bevetel;
        if (bevetel > eddigiMax) {
            eddigiMax = bevetel;
            if (aktHossz == 0) aktKezd = nap;
            aktHossz++;
            if (aktHossz > legjobbHossz) {
                legjobbHossz = aktHossz;
                legjobbKezd = aktKezd;
            }
        } else {
            aktHossz = 0;
        }
    }

    cout << legjobbHossz << '\n' << legjobbKezd << '\n';
    return 0;
}
