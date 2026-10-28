/*
Megoldás lényege:
A határon egyszerre csak egy autó vizsgálata folyhat, és az autók az érkezési sorrendben haladnak át. Egy autó vizsgálata akkor kezdődik, amikor megérkezett és az előző autó vizsgálata már véget ért, különben az előzőre vár. Ezért elég egyetlen változóban tárolni, mikor lesz szabad a határőr: az aktuális kezdési idő az érkezési idő és ez az időpont közül a nagyobb, a vizsgálat vége pedig a kezdés plusz P, ami egyben a Törpeországba lépés ideje és a következő autó szabadulási ideje. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egyszerre csak egy vizsgálat folyhat, ezért egy autó kezdési ideje attól is függ, hogy az előző autó mikor végzett, nem csak attól, mikor érkezett. ||
Hint 2: || Elég egyetlen szám: az, hogy a határőr mikor lesz szabad. Az aktuális autó kezdése a két időpont maximuma, a befejezése a kezdés plusz P, és ezt az értéket viszi tovább a következő autónak. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p;
    cin >> n >> p;

    int borderFree = 0;
    for (int i = 0; i < n; i++) {
        int h, m;
        cin >> h >> m;
        int arrive = h * 60 + m;

        int start = max(arrive, borderFree);
        borderFree = start + p;

        cout << borderFree / 60 << " " << borderFree % 60 << "\n";
    }
    return 0;
}
