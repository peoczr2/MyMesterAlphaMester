/*
Megoldás lényege:
Minden bemeneti sor egy vezetéknév-keresztnév pár, ezeket egy pair<string, string> elemekből álló vektorban tároljuk. A pár az összehasonlításnál először az első (vezetéknév), azonos vezetéknév esetén a második (keresztnév) elem szerint rendeződik, ami pontosan az ábécé szerinti sorrend a feladat szerint. A nevek csak angol betűket tartalmaznak, ezért a string szerinti lexikografikus összehasonlítás az ABC-sorrendet adja. A rendezés után a párokat 1-től kezdődő sorszámmal írjuk ki. Az időigény O(N log N), a memóriaigény O(N), ahol N a nevek száma.
*/
/*
Hint 1: || Egy nevet két szóként olvasz be a cin, ezért érdemes a vezetéknevet és a keresztnevet egy párban együtt tárolni. Így a rendezést nem kell kézzel megírni. ||
Hint 2: || A pár-tömböt a beépített sort függvénnyel rendezd, majd a kiírásnál a sorszámot a ciklusváltozóból számold, 1-től kezdve. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<string, string>> nevek(n);
    for (auto& nev : nevek) {
        cin >> nev.first >> nev.second;
    }

    sort(nevek.begin(), nevek.end());

    for (int i = 0; i < n; i++) {
        cout << i + 1 << " " << nevek[i].first << " " << nevek[i].second << "\n";
    }
    return 0;
}
