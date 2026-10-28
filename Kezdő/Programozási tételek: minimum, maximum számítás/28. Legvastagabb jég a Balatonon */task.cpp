/*
Megoldás lényege:
Egy menetes maximumkiválasztást végzünk: végigolvassuk a méréseket, és tároljuk az eddigi legvastagabb jég vastagságát és annak napjának sorszámát. Csak akkor frissítünk, ha az aktuális érték szigorúan nagyobb a tárolt maximumnál, így egyenlőség esetén a korábbi nap marad, ahogy a feladat a legkisebb sorszámot kéri. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Nem kell az összes mérést eltárolni: elég egy változó az eddigi legnagyobb vastagságnak és egy a hozzá tartozó nap sorszámának. ||
Hint 2: || A csere feltétele legyen szigorú (>), így ha két nap ugyanannyi jeget mért, a korábbi marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int bestDay = 1;
    int bestValue = -1;
    for (int i = 1; i <= n; i++) {
        int value;
        cin >> value;
        if (value > bestValue) {
            bestValue = value;
            bestDay = i;
        }
    }

    cout << bestDay << "\n";
    return 0;
}
