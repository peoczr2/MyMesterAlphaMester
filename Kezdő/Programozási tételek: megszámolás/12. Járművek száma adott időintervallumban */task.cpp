/*
Megoldás lényege:
Az eredmény csak az óra részétől függ: egy megfigyelés akkor esik az X óra 0 perc és Y óra 59 perc közötti időbe, ha az óra értéke X és Y közé esik (a perc nem számít).
A helyszám és a rendezettség nincs hatással az eredményre, ezért elég egyetlen számlálóval végigmenni a megfigyeléseken, az időigény O(N).
*/
/*
Hint 1: || Egy megfigyelés beleszámít, ha az órája legalább X és legfeljebb Y. A percek értékét nem kell figyelembe venni. ||
Hint 2: || Az M (helyszámok száma) és a rendezettség a megoldáshoz nem kell: elég minden sort beolvasni és egy számlálót növelni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n, x, y;
    cin >> m >> n >> x >> y;

    int db = 0;
    for (int i = 0; i < n; i++) {
        int hely, ora, perc;
        cin >> hely >> ora >> perc;
        if (ora >= x && ora <= y) {
            db++;
        }
    }
    cout << db << endl;
    return 0;
}
