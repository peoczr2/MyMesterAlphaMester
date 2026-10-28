/*
Megoldás lényege:
A j-edik benzinkút után akkor nem kell már tankolni, ha a kúton lévő benzin elég a céltól fogyasztásig, vagyis ha a kút utáni benzin legalább akkora, mint a kúttól a célig tartó fogyasztás. A kút utáni benzin B - L*H_j/100 + (M_1 + ... + M_j), a hátralévő fogyasztás L*(K - H_j)/100, és a H_j távolságok a két oldalon kiesnek. Így a feltétel: B + M_1 + ... + M_j >= L*K/100, vagyis csak a kezdeti benzint és a tankolt mennyiségek összegét kell követni. Ez az összeg nő, ezért az első teljesülő j a legkorábbi jó kút; ha már a kezdeti benzin is elég, a válasz 0. A program egyetlen bejárással, O(N) időben fut.
*/
/*
Hint 1: || Írd fel külön a kút utáni benzint és a kúttól a célig tartó fogyasztást: a kút távolsága mindkettőben szerepel, és az összevetésben kiesik. ||
Hint 2: || Ebből következik, hogy elég a kezdeti benzin és a tankolt mennyiségek összegét követni, a fogyasztást pedig egyszer, az egész útra kiszámolni. ||
Hint 3: || Az első olyan sorszámot keresd, ahol az összeg eléri az út teljes fogyasztását; ha már a kezdeti benzin is elég, a válasz 0. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    long long k, n, b, l;
    cin >> k >> n >> b >> l;

    // A litereket 100-zal szorozva dolgozunk, hogy a fogyasztás (L / 100 liter km-enként) egész szám maradjon.
    long long fuel = 100 * b;  // az eddig rendelkezésre álló benzin, 100-szorosa
    long long need = l * k;    // az egész út fogyasztása, 100-szorosa

    if (fuel >= need) {
        cout << 0 << '\n';
        return 0;
    }

    for (long long i = 1; i <= n; ++i) {
        long long position, amount;
        cin >> position >> amount;  // a kút távolsága nem befolyásolja az eredményt
        fuel += 100 * amount;
        if (fuel >= need) {
            cout << i << '\n';
            return 0;
        }
    }

    // A feladat garantálja, hogy a célba lehet jutni, így ide nem jutunk.
    cout << 0 << '\n';
    return 0;
}
