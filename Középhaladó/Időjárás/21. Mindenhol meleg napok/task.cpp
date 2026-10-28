/*
Megoldás lényege:
Egy nap akkor felel meg, ha az ott szereplő összes település hőmérséklete 0 foknál nagyobb. Minden naphoz egy igaz/hamis jelzőt tartunk, kezdetben igazat. A bemenet beolvasása közben minden nem pozitív értéknél a megfelelő nap jelzőjét hamisra állítjuk. Az idő O(N·M), a memória O(M).
*/
/*
Hint 1: || Egy nap akkor jó, ha a benne szereplő *összes* érték pozitív. Elég egyetlen 0-t vagy negatív számot találni, és a nap kiesik. ||
Hint 2: || Ne tárold el a teljes táblázatot: a bemenetet egyenként olvasd be, és minden naphoz (oszlophoz) tarts egy logikai jelzőt, amely kezdetben igaz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // jo[j]: a j. napon (0-tól számozva) minden településen 0 foknál melegebb-e
    vector<bool> jo(m, true);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            if (x <= 0) jo[j] = false;
        }
    }

    vector<int> napok;
    for (int j = 0; j < m; j++)
        if (jo[j]) napok.push_back(j + 1);

    cout << napok.size();
    for (int nap : napok) cout << ' ' << nap;
    cout << '\n';
    return 0;
}
