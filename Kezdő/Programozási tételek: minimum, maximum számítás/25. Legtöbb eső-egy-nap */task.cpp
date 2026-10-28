/*
Megoldás lényege:
Azt a napot keressük, amelyen a legtöbb eső esett, ezért egy menetes maximumkiválasztást végzünk: az eddigi legnagyobb csapadékmennyiséget és annak nap-sorszámát tároljuk. A csere feltétele szigorú nagyobb, így több azonos értéknél a kisebb sorszámú nap marad, ahogy a feladat kéri. Nem kell a napi adatokat eltárolni. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egyetlen végigolvasás elég: nem kell a napi értékeket tömbben tárolni, csak az eddigi legnagyobb mennyiséget és a hozzá tartozó nap sorszámát. ||
Hint 2: || A csere feltétele legyen szigorú (>), így egyenlő mennyiségnél a kisebb sorszámú nap marad meg; a napok sorszámát 1-től számold. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int bestDay = 1;
    int bestRain = -1;
    for (int i = 1; i <= n; i++) {
        int rain;
        cin >> rain;
        if (rain > bestRain) {
            bestRain = rain;
            bestDay = i;
        }
    }

    cout << bestDay << "\n";
    return 0;
}
