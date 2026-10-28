/*
Megoldás lényege:
Az összes csapadék a napi mérések összege, ezért egyetlen összeg-változóban gyűjtjük a mérési eredményeket. Az N darab számot egyenként beolvassuk, és mindegyiket hozzáadjuk az összeghez; N = 0 esetén a ciklus nem fut, és az eredmény 0. Minden mérést pontosan egyszer dolgozunk fel, így az időigény O(N), ami N <= 100 esetén messze az időlimit alatt marad. A mérések nagyságára a feladat nem ad felső korlátot, ezért az összeget long long típusban tároljuk.
*/
/*
Hint 1: || Az összes csapadék a napi mérések összege. Hány számot kell beolvasni, és hol érdemes a köztes eredményt tárolni? ||
Hint 2: || Egy összeg-változót nullázz le, majd N-szer olvass be egy mérést, és minden beolvasás után add hozzá az összeghez. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long osszeg = 0;
    for (int i = 0; i < n; i++) {
        long long eso;
        cin >> eso;
        osszeg += eso;
    }

    cout << osszeg << "\n";
    return 0;
}
