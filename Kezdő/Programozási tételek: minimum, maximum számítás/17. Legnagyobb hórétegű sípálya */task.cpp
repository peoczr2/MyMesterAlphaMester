/*
Megoldás lényege:
Egyszeri bejárással megkeressük a legnagyobb hóréteg értékét és annak sorszámát. Menet közben az eddigi legnagyobb értéket és a hozzá tartozó sípályaszámot tároljuk. Csak szigorúan nagyobb érték esetén cserélünk, így ha több pályán is ugyanakkora a legnagyobb hóréteg, az első marad, ahogy a feladat kéri. Nem kell a teljes sorozatot eltárolni. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egyetlen maximumkiválasztás kell: elég az eddigi legnagyobb hóréteget és a hozzá tartozó sorszámot megtartani. ||
Hint 2: || A sípályák sorszámát 1-től számold, és egyenlő értéknél ne cserélj, így az első sípálya marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int bestIndex = 1;
    int bestValue = INT_MIN;
    for (int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        if (v > bestValue) {
            bestValue = v;
            bestIndex = i;
        }
    }

    cout << bestIndex << "\n";
    return 0;
}
