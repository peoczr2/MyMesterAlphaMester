/*
Megoldás lényege:
A települések távolság szerint növekvően vannak megadva, ezért egy település K legközelebbi
másik települése mindig egy összefüggő szakaszt alkot a sorban: balra és jobbra egy-egy
folytonos sorozat. Minden településnél két mutatóval (bal: i-1 felé, jobb: i+1 felé)
K lépést teszünk, mindig a kisebb távolságú oldalt véve. Egyenlő távolságnál a bal oldali
települést választjuk, így a legkisebb sorszámú baloldali szomszéd marad meg. A kiírt
érték a kiválasztott települések legkisebb és legnagyobb sorszáma. Az időigény O(N · K),
ami legfeljebb 10^7 lépés.
*/
/*
Hint 1: || A K legközelebbi település mindig egy-egy folytonos szakasz i körül: balra az i-1, i-2, ... indexek, jobbra az i+1, i+2, ... indexek közül kerülnek ki. Ezért elég két irányba külön-külön haladni. ||
Hint 2: || Két mutatóval (l = i-1, r = i+1) K-szor lépj: mindig azt az oldalt léptesd, ahol a távolság kisebb. Egyenlőségnél a bal oldalt válaszd. Ha az egyik oldalon már nincs település, a másik oldalt léptesd. A végén a kiválasztott indexek minimuma és maximuma kell. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> t(n + 1);
    for (int i = 1; i <= n; ++i) cin >> t[i];

    for (int i = 1; i <= n; ++i) {
        int l = i - 1, r = i + 1;
        int cnt = 0;
        int bal = n + 1, jobb = 0;
        while (cnt < k) {
            bool chooseLeft;
            if (l < 1) chooseLeft = false;
            else if (r > n) chooseLeft = true;
            else {
                int dl = t[i] - t[l];
                int dr = t[r] - t[i];
                chooseLeft = (dl < dr) || (dl == dr);
            }
            if (chooseLeft) {
                bal = min(bal, l);
                jobb = max(jobb, l);
                --l;
            } else {
                bal = min(bal, r);
                jobb = max(jobb, r);
                ++r;
            }
            ++cnt;
        }
        cout << bal << ' ' << jobb << '\n';
    }
    return 0;
}
