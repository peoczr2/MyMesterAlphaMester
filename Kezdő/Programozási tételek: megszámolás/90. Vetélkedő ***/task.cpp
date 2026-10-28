/*
Megoldás lényege:
Ugyanazon csapat tagjainak azonosítója ugyanazokat a karaktereket tartalmazza, csak más sorrendben, ezért az azonosítók karaktereit ASCII-sorrendbe rendezve minden tag ugyanarra a kulcsra jut, ami a csapat azonosítója. Egy map-ben megszámoljuk, hány tag tartozik az egyes kulcsokhoz: minden csapat létszáma páros, kivéve azt, amelyikből hiányzik egy játékos, ennek darabszáma páratlan. Ennek a csapatnak a kulcsa a keresett azonosító. A futásidő O(N * L log L + N log N), ahol L legfeljebb 20 az azonosító hossza.
*/
/*
Hint 1: || Ugyanazon csapat tagjainak azonosítója csak a karakterek sorrendjében különbözik. Keress olyan jellemzőt, amely a sorrendtől független, például a karakterek rendezett alakját. ||
Hint 2: || Minden azonosító karaktereit rendezd, és a rendezett szöveget használd kulcsként egy map-ben, amely megszámolja az előfordulásokat. A keresett csapat az, amelynek darabszáma páratlan. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    map<string, int> db;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        sort(s.begin(), s.end());
        db[s]++;
    }
    for (const auto &p : db) {
        if (p.second % 2 == 1) {
            cout << p.first << "\n";
            break;
        }
    }
    return 0;
}
