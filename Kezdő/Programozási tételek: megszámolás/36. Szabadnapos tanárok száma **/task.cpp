/*
Megoldás lényege:
Az óra sorszámára nincs szükség, csak arra kell figyelni, hogy egy tanár az adott napon tart-e legalább egy órát. Egy (nap, tanár) táblázatba bejelöljük az órát tartó tanárokat; ha ugyanaz a tanár egy napon több órát is tart, a jelölés ezt magától kezeli. Ezután minden napra megszámoljuk a jelöletlen tanárokat, vagyis a szabadnapos tanárokat. Az időigény a bemenet méretével arányos, O(O + N), ahol O az órák száma, a memóriaigény O(N).
*/
/*
Hint 1: || Az óra sorszáma nem számít; csak az, hogy a tanár az adott napon tart-e legalább egy órát. ||
Hint 2: || Használj egy táblázatot tanár és nap szerint: a beolvasott sorban a megfelelő cellát állítsd igazra. Egy napra a szabadnapos tanárok száma: N mínusz az adott napon igazra állított cellák száma. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int o, n;
    cin >> o >> n;
    vector<vector<bool>> dolgozik(6, vector<bool>(n + 1, false));
    for (int i = 0; i < o; i++) {
        int t, nap, ora;
        cin >> t >> nap >> ora;
        dolgozik[nap][t] = true;
    }
    for (int nap = 1; nap <= 5; nap++) {
        int szabad = 0;
        for (int t = 1; t <= n; t++)
            if (!dolgozik[nap][t]) szabad++;
        cout << szabad << (nap < 5 ? " " : "\n");
    }
    return 0;
}
