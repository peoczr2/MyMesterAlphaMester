/*
Megoldás lényege:
Minden állomás elhagyása után kiszámoljuk, hányan vannak a vonaton: az előző létszámhoz hozzáadjuk a felszállókat, és kivonjuk a leszállókat. Azt keressük, hogy melyik az utolsó olyan állomás, ahonnan induláskor még volt utas; a keresett sorszám ennek az állomásnak a sorszáma plusz egy, mert onnantól kezdve végig üres a vonat. Egyetlen bejárás elég: elég egy futó létszámot és az utolsó nem nulla létszámú állomás sorszámát megjegyezni. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Számold végig az állomásokat, és minden állomás után jegyezd fel, hányan vannak a vonaton: a felszállók hozzáadódnak, a leszállók levonódnak. ||
Hint 2: || Keresd az utolsó olyan állomást, ahol a létszám még nem nulla. A válasz az utána következő állomás sorszáma, ezért elég egy futó létszám és egy változó, amiben az utolsó nem nulla állomás sorszámát tartod. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long cur = 0;     // a vonaton lévő utasok száma az aktuális állomás elhagyása után
    int last_nonzero = 0;  // az utolsó olyan állomás sorszáma, ahonnan indulva még volt utas
    for (int i = 1; i <= n; i++) {
        long long le, fel;
        cin >> le >> fel;
        cur += fel - le;
        if (cur != 0) last_nonzero = i;
    }

    cout << last_nonzero + 1 << "\n";
    return 0;
}
