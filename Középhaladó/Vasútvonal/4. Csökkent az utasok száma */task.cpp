/*
Megoldás lényege:
Az állomás után a vonaton lévő utasok száma a felszállók és a leszállók különbségével változik, így ott csökken a létszám, ahol több utas szállt le, mint fel.
Az állomásokat sorban nézzük, és az első olyan állomás sorszámát írjuk ki, ahol a leszállók száma nagyobb a felszállókénál.
Mivel a sorszámok növekvő sorrendben jönnek, az első találat adja a legkisebb sorszámú megoldást, ezért a további állomások már nem változtatnak az eredményen.
Ha nincs ilyen állomás, a program 0-t ír ki, mert a feladat erről nem rendelkezik.
Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Az állomás utáni létszám a felszállók és a leszállók különbségétől függ: mikor lesz ez a különbség negatív? ||
Hint 2: || Haladj az állomásokon sorrendben, és az első olyan állomás sorszámát jegyezd fel, ahol a leszállók száma nagyobb a felszállókénál. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int answer = 0;  // az első olyan állomás sorszáma, ahol csökkent az utasok száma (0, ha nincs)
    for (int i = 1; i <= n; i++) {
        int le, fel;
        cin >> le >> fel;
        if (answer == 0 && le > fel) answer = i;
    }

    cout << answer << "\n";
    return 0;
}
