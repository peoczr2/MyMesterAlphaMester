/*
Megoldás lényege:
A szöveget szavanként olvassuk be a `cin >> word` utasítással. Ez a művelet átugorja a szóközöket, így a szöveg elején és végén álló, valamint a több egymás utáni szóköz sem okoz gondot: minden sikeres beolvasás pontosan egy, szóközzel határolt karaktersorozatot ad. A sikeres beolvasások számát egy számlálóban gyűjtjük, és ezt írjuk ki. Ha a sor üres vagy csak szóközt tartalmaz, a beolvasás azonnal sikertelen, és a válasz 0. Az időigény O(n), ahol n a szöveg hossza (legfeljebb 200 000 karakter), a memóriaigény a leghosszabb szó hosszával arányos.
*/
/*
Hint 1: || Nem kell a betűket egyesével vizsgálnod. Elég megszámolni, hány szó kezdődik a szövegben: egy szó ott kezdődik, ahol nem szóköz áll, és előtte szóköz van (vagy a sor eleje). ||
Hint 2: || Olvasd be a szöveget egy `string` változóba szavanként a `cin >>` segítségével, mert ez a szóközöket magától átugorja. Egy számlálóval jegyezd fel, hány sikeres beolvasás történt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string word;
    int count = 0;
    while (cin >> word) {
        count++;
    }

    cout << count << "\n";
    return 0;
}
