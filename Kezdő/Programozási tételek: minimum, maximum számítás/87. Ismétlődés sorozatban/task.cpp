/*
Megoldás lényege:
Az X sorozatot a képlettel egyenként generáljuk (X_0 a kezdőérték, az X_1 ... X_n elemekből készül a sorozat), és minden X_i-ből Y_i = X_i mod k. Nem kell eltárolni a teljes sorozatot: egy k elemű tömbben minden Y-értékhez az utolsó előfordulásának sorszámát tároljuk. Ha egy érték újra megjelenik, a két szomszédos előfordulás távolsága az aktuális és az utolsó sorszám különbsége. Ezt szigorú összehasonlítással tartjuk nyilván a legnagyobb távolság mellett, így több megoldás esetén a legelső marad meg. Az időigény O(n), a tárigény O(k), ami legfeljebb 2^20 elem.
*/
/*
Hint 1: || Nem kell eltárolni az egész sorozatot: a képletet egyenként követve minden elemnél elég tudni, hogy az adott érték mikor fordult elő legutoljára. ||
Hint 2: || Tarts minden lehetséges Y-értékhez egy tömbben az utolsó előfordulás sorszámát (0, ha még nem volt). Új előfordulásnál a távolság az aktuális és az utolsó sorszám különbsége; a legnagyobb távolságot szigorú összehasonlítással tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long x, a, b, m, k;
    int n;
    cin >> x >> a >> b >> m >> k >> n;

    vector<int> last(k, 0);  // egy Y-érték utolsó előfordulásának sorszáma (1-től számozva), 0: még nincs
    int bestVal = -1, bestDist = 0;
    for (int i = 1; i <= n; i++) {
        x = (a * x + b) % m;
        int y = x % k;
        if (last[y] != 0) {
            int dist = i - last[y];
            if (dist > bestDist) {
                bestDist = dist;
                bestVal = y;
            }
        }
        last[y] = i;
    }

    if (bestVal < 0) {
        cout << -1 << "\n";
    } else {
        cout << bestVal << " " << bestDist << "\n";
    }
    return 0;
}
