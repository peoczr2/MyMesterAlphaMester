/*
Megoldás lényege:
A műszer javítását az jelzi, ha egy 0-s mérés után nullánál nagyobb érték következik. Ezért elég az egymást követő napokat párban nézni: ha az előző nap értéke 0, a mai pedig pozitív, a javítások számát növeljük.
Az előző nap értékét egy változóban tároljuk, így a teljes sorozatot nem kell eltárolni. Az időigény O(N), N ≤ 100 mellett elhanyagolható.
*/
/*
Hint 1: || Nem kell a teljes sorozatot végignézni egyszerre: elég minden nap az előző naphoz képest vizsgálni a változást. ||
Hint 2: || Tárold az előző nap értékét. Ha az előző érték 0 volt, a mai pedig nagyobb nullánál, egy javítás történt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int db = 0;
    int prev;
    cin >> prev;
    for (int i = 1; i < n; i++) {
        int cur;
        cin >> cur;
        if (prev == 0 && cur > 0) {
            db++;
        }
        prev = cur;
    }
    cout << db << endl;
    return 0;
}
