/*
Megoldás lényege:
Egyszer végigmegyünk a méréseken, és nyilvántartjuk az aktuális földrengés erősségét (E) és a legutóbbi nem nulla mérés (földrengés vagy utórengés) percét. Egy nem nulla S mérés utórengés, ha legfeljebb K perc telt el az utolsó nem nulla méréshez képest és S kisebb E-nél; minden más nem nulla mérés új földrengés, ekkor a számlálót növeljük és E-t S-re állítjuk. A nulla méréseknél nincs változás. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egy földrengés után az utórengések a legutóbbi nem nulla méréstől legfeljebb K percen belül következnek, és erősségük kisebb a földrengésénél. Minden más nem nulla mérés új földrengés. ||
Hint 2: || Tárold az aktuális földrengés erősségét és a legutóbbi nem nulla mérés percét. Egy nem nulla méréshez ellenőrizd, hogy az időkülönbség legfeljebb K, és az erősség kisebb az aktuális földrengésénél. ||
Hint 3: || Ha a feltétel nem teljesül, a mérés új földrengés: növeld a számlálót és írd felül az aktuális erősséget. Minden nem nulla mérés után frissítsd a legutóbbi mérés percét, a végén a számlálót írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int erosseg = 0;               // az aktuális földrengés erőssége
    int utolso = -1000000;         // a legutóbbi nem nulla mérés (földrengés vagy utórengés) perce
    int db = 0;
    for (int i = 1; i <= n; i++) {
        int s;
        cin >> s;
        if (s == 0) continue;
        bool utorengese = (i - utolso <= k) && (s < erosseg);
        if (!utorengese) {
            db++;
            erosseg = s;
        }
        utolso = i;
    }
    cout << db << "\n";
    return 0;
}
