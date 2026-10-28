/*
Megoldás lényege:
Minden háborút a kezdő évének évszázadába sorolunk: az évszázad sorszáma (kezdet - 1) / 100 + 1, így az 1601–1700 évek a XVII., az 1701–1800 a XVIII., az 1801–1900 a XIX. századba esnek.
Beolvasás közben három számlálóban gyűjtjük a háborúk számát a három századra.
Növekedésről akkor beszélünk, ha a XVIII. századi szám nagyobb a XVII. századinál, és a XIX. századi nagyobb a XVIII. századinál; ekkor a válasz „Igen”, különben „Nem”.
A feladat egyetlen menetben, O(K) időben megoldható, ahol K a háborúk száma.
*/
/*
Hint 1: || A háborúkat a kezdő évük százada szerint számold össze. Egy év századát egész osztással is megkapod: például az 1700 a XVII., az 1701 a XVIII. századba esik. ||
Hint 2: || Három számlálót tarts (XVII., XVIII., XIX. század), és beolvasáskor mindig a megfelelőt növeld. A kiíráskor két feltételnek kell egyszerre teljesülnie: a XVIII. század száma nagyobb a XVII.-nél, és a XIX. száma nagyobb a XVIII.-nál. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // A minta be1 fájlja elején UTF-8 BOM állhat (3 bájt): ezt átugorjuk.
    if (cin.peek() == 0xEF) cin.ignore(3);

    int n, k;
    cin >> n >> k;
    int xvii = 0, xviii = 0, xix = 0;
    for (int i = 0; i < k; i++) {
        int a, b, kezdet, vege;
        cin >> a >> b >> kezdet >> vege;
        int szazad = (kezdet - 1) / 100 + 1;
        if (szazad == 17) xvii++;
        else if (szazad == 18) xviii++;
        else if (szazad == 19) xix++;
    }
    cout << (xviii > xvii && xix > xviii ? "Igen" : "Nem") << '\n';
}
