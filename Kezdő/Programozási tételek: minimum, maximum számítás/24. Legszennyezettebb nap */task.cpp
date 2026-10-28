/*
Megoldás lényege:
Egy menetben végigolvassuk a napi szennyezettségi értékeket, és tároljuk az eddigi legnagyobb értéket és annak nap-sorszámát. Csak akkor cseréljük a tárolt eredményt, ha az aktuális érték szigorúan nagyobb, így egyenlőségnél az első előfordulás marad, ahogy a feladat kéri. Az elromlott műszer 0 értéke a maximumkeresést nem befolyásolja, ezért külön kezelésre nincs szükség. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Nem kell a teljes sorozatot eltárolni: egyetlen végigolvasás során elég az eddigi legnagyobb értéket és a hozzá tartozó nap sorszámát nyilvántartani. ||
Hint 2: || A napok sorszámát 1-től számold, és a csere feltétele legyen szigorú (>), így ha két nap ugyanannyit mért, a korábbi marad. ||
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
