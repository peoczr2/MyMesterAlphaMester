/*
Megoldás lényege:
Minden autó csak a saját célvárosába megy, ezért a városok egymástól függetlenül kezelhetők.
Egy városban az autók legfeljebb 3 · (autók száma) utast tudnak elvinni, és legfeljebb annyi
utas jöhet, ahány ott utazni szeretne. A városonkénti minimumot összegezzük a-tól z-ig.
A számlálás egy menetben történik, az idő O(N+M).
*/
/*
Hint 1: || Az autók és az utasok csak azonos célvárosba utazhatnak együtt, ezért minden várost külön kell vizsgálni. ||
Hint 2: || Városonként számold meg az autók és az utasok számát. Az autók férőhelyét úgy kapod meg, hogy az autók számát megszorzod 3-mal, és az eredmény a két szám minimuma. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    string autok, utasok;
    cin >> n >> autok >> m >> utasok;

    long long autoDb[26] = {0}, utasDb[26] = {0};
    for (char c : autok) autoDb[c - 'a']++;
    for (char c : utasok) utasDb[c - 'a']++;

    long long ans = 0;
    for (int i = 0; i < 26; i++) {
        ans += min(3 * autoDb[i], utasDb[i]);
    }
    cout << ans << "\n";
    return 0;
}
