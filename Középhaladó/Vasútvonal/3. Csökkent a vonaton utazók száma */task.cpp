/*
Megoldás lényege:
Egy állomás után a vonaton lévő utasok száma az előző állomás utáni létszám plusz a felszállók, mínusz a leszállók száma.
A létszám tehát pontosan akkor csökken egy állomáson, ha ott több utas szállt le, mint fel, vagyis le > fel.
Ezért elég egyszer végigmenni az állomásokon, és megszámolni, hányszor teljesül ez a feltétel.
Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Az utasok száma egy állomáson fel - le szerint változik. Mikor lesz ez a változás negatív? ||
Hint 2: || Akkor csökken a létszám, ha a leszállók száma nagyobb a felszállókénál. Ezt az állomások közül minden állomásnál külön kell megnézni, és a találatokat összeszámolni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int count = 0;  // azon állomások száma, ahol csökkent a vonaton utazók száma
    for (int i = 0; i < n; i++) {
        int le, fel;
        cin >> le >> fel;
        if (le > fel) count++;
    }

    cout << count << "\n";
    return 0;
}
