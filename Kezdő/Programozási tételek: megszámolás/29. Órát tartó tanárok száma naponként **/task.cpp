/*
Megoldás lényege:
Az órákat egyesével olvassuk be, és minden (nap, tanár) párt egy logikai táblázatban jelölünk be, így ugyanazon a napon egy tanár több órája is csak egyszer számít.
A táblázat sorai a napok (1-től 5-ig), oszlopai a tanárok sorszámai.
A beolvasás után minden napra megszámoljuk a bejelölt tanárokat, és ezeket szóközzel elválasztva írjuk ki.
Az időigény O(O + N), a tábla mérete pedig legfeljebb 6 x 101 cella.
*/
/*
Hint 1: || Egy tanár egy napon több órát is tarthat, de a kérdés a tanárok száma, nem az óráké: egy tanárt egy napon elég egyszer figyelembe venni. ||
Hint 2: || Készíts logikai táblázatot: a sor a nap, az oszlop a tanár sorszáma. Egy óra beolvasásakor jelöld meg a megfelelő cellát. ||
Hint 3: || A tanárok sorszáma 1-től indul, ezért a tábla oszlopainak száma legyen N+1, különben a tömb határain kívülre írnál. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int o, n;
    cin >> o >> n;
    vector<vector<bool>> tart(6, vector<bool>(n + 1, false));
    for (int i = 0; i < o; i++) {
        int tanar, nap, ora;
        cin >> tanar >> nap >> ora;
        tart[nap][tanar] = true;
    }
    for (int nap = 1; nap <= 5; nap++) {
        int db = 0;
        for (int t = 1; t <= n; t++) {
            if (tart[nap][t]) {
                db++;
            }
        }
        cout << db;
        if (nap < 5) {
            cout << " ";
        }
    }
    cout << endl;
    return 0;
}
