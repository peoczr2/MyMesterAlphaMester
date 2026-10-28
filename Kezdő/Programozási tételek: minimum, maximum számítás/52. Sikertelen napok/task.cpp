/*
Megoldás lényege:
Egy nap sikeres, ha a bevétele nagyobb, mint bármely korábbi napé. Az első napnak nincs korábbi napja, ezért sikeresnek tekintjük. Egy menetben haladunk végig a napokon, és az eddigi legnagyobb bevételt tároljuk. A sikeres nap megszakítja a futó sorozatot, ezért a hosszát nullázzuk; a sikertelen nap növeli a futó hosszt, és közben nyilvántartjuk a leghosszabb szakasz hosszát és kezdő sorszámát. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egy napot elég az eddigi legnagyobb bevételhez hasonlítani; nem kell minden korábbi napot végignézni. ||
Hint 2: || Egy menetben haladj végig a napokon: a sikeres nap a futó sorozatot megszakítja, a sikertelen nap növeli a hosszát. Tartsd nyilván a leghosszabb ilyen szakasz hosszát és kezdő sorszámát, és ne felejtsd el a -1 esetet, ha nincs sikertelen nap. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // a bevételek nemnegatívak, így -1 kezdőérték esetén az 1. nap biztosan sikeres
    long long legnagyobb = -1;
    int futoHossz = 0;
    int futoKezdet = 0;
    int legHossz = 0;
    int legKezdet = -1;

    for (int i = 1; i <= n; i++) {
        long long b;
        cin >> b;
        if (b > legnagyobb) {
            legnagyobb = b;
            futoHossz = 0;
        } else {
            if (futoHossz == 0) {
                futoKezdet = i;
            }
            futoHossz++;
            if (futoHossz > legHossz) {
                legHossz = futoHossz;
                legKezdet = futoKezdet;
            }
        }
    }

    cout << legHossz << "\n" << (legHossz > 0 ? legKezdet : -1) << "\n";
    return 0;
}
