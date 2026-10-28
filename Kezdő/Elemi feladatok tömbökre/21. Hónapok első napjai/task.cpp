/*
Megoldás lényege:
Az év 12 hónapját egyesével végigjárjuk, és nyilvántartjuk, melyik hétköznap kezdődik az aktuális hónap. Egy hónap első napjáról a következő hónap első napjára úgy lépünk, hogy az aktuális hónap napjainak számát hétre vett maradékkal hozzáadjuk. A hónapok hossza fix, csak február függ attól, hogy szökőév-e. Mivel mindig csak 12 hónapot járunk be, a megoldás állandó idejű.
*/
/*
Hint 1: || Egy év hónapjainak hossza fix, kivéve a februárt: az 28 nap, de szökőévben 29. A szökőév szabálya: a 4-gyel osztható évek szökőévek, kivéve a 100-zal osztható évek, azok közül viszont szökőév a 400-zal osztható. ||
Hint 2: || Egy hét napjait 0-tól 6-ig számozd (0 = hétfő), és egy számlálóval tartsd nyilván, hogy az aktuális hónap első napja melyik nap. Minden hónap után a számlálót növeld a hónap hosszának 7-tel vett maradékával, és a hét 7 napjára külön számold a hónapok kezdőnapjait. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int ev, s;
    cin >> ev >> s;

    int napok[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool szokoev = (ev % 4 == 0 && ev % 100 != 0) || ev % 400 == 0;
    if (szokoev) napok[1] = 29;

    // a nap sorszáma: 0 = hétfő, ..., 6 = vasárnap; s = 1 jelenti a hétfőt
    int nap = s - 1;
    int hanyadik[7] = {0, 0, 0, 0, 0, 0, 0};
    for (int h = 0; h < 12; h++) {
        hanyadik[nap]++;
        nap = (nap + napok[h]) % 7;
    }

    for (int i = 0; i < 7; i++) {
        if (i) cout << ' ';
        cout << hanyadik[i];
    }
    cout << '\n';
    return 0;
}
