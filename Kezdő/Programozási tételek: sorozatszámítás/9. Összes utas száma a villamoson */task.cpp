/*
Megoldás lényege:
Minden utas pontosan egyszer száll fel a villamosra, ezért az összes utas száma a felszállók számának összege az összes állomáson. Az N állomást sorban beolvassuk, minden állomásnál a felszállók számát egy összeg-változóhoz adjuk, a leszállókat beolvassuk, de nem használjuk fel. Minden állomást pontosan egyszer dolgozunk fel, így az időigény O(N), ami N ≤ 100 esetén messze az időlimit alatt marad. Az eredmény legfeljebb 100 · 35 = 3500, ezért int típus is elegendő.
*/
/*
Hint 1: || Minden utas egyszer száll fel. Melyik oszlopban szerepel az a szám, ami az utasok számát adja egy állomáson, és melyik az, amit nem kell használnod? ||
Hint 2: || Olvasd be N-et, majd N-szer két számot. Az elsőt (felszállók) add egy összeg-változóhoz, a másodikat (leszállók) csak olvasd be és dobd el. A ciklus után írd ki az összeget. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int osszes = 0;
    for (int i = 0; i < n; i++) {
        int felszall, leszall;
        cin >> felszall >> leszall;
        osszes += felszall;
    }

    cout << osszes << "\n";
    return 0;
}
