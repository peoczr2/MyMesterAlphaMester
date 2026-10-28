/*
Megoldás lényege:
Egy háború pontosan akkor lépi át az évszázad határát, ha a kezdő és a befejező évének százada különbözik. Az évszázad sorszáma egész osztással kiszámolható: (év - 1) / 100 + 1, így az 1700 a XVII., az 1701 a XVIII. századba esik.
A háborúkat a bemenet sorrendjében olvassuk, és az első olyan háború sorszámát írjuk ki, amelyre ez teljesül; mivel a sorszámok növekvő sorrendben jönnek, ez a legkisebb sorszám. Ha nincs ilyen háború, a 0-t írjuk ki.
Az idő O(K), ahol K a háborúk száma.
*/
/*
Hint 1: || Egy háború pontosan akkor lépi át az évszázad határát, ha a kezdő és a befejező éve más századba esik. Nézd meg, hogy az 1700 és az 1701 már más századba esik-e. ||
Hint 2: || Az évszázad sorszáma egész osztással kiszámolható: (év - 1) / 100 + 1. Olvasd be a háborúkat sorban, számold a sorszámukat 1-től, és az első olyan háborúnál írd ki a sorszámát és fejezd be a programot. Ha nincs ilyen, a 0 a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Az évszázad sorszáma: az 1601–1700 évek a XVII., az 1701–1800 a XVIII. századba esnek.
int szazad(int ev) {
    return (ev - 1) / 100 + 1;
}

int main() {
    // A minta be1 fájlja elején UTF-8 BOM állhat (3 bájt): ezt átugorjuk.
    if (cin.peek() == 0xEF) cin.ignore(3);

    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= k; i++) {
        int a, b, kezdet, vege;
        cin >> a >> b >> kezdet >> vege;
        if (szazad(kezdet) != szazad(vege)) {
            cout << i << '\n';
            return 0;
        }
    }
    cout << 0 << '\n';
}
