/*
Megoldás lényege: minden hallgatóra egyszerűen megvizsgáljuk a két feltételt: a röpzárthelyi pontja legalább 10 (különben nincs joga pót zárthelyit írni), és a három jegy (Cs1, Cs2, Ef) közül legalább az egyik 0, vagyis valamelyik zárthelyit nem írta meg. Ha mindkét feltétel teljesül, a hallgató sorszámát (1-től kezdve) felvesszük a listába; mivel a sorszámokat a beolvasás sorrendjében adjuk, a lista növekvő lesz. A megoldás O(N) időben fut.
*/
/*
Hint 1: || A feltételek egyszerű logikai kifejezések: a röpzárthelyi pontja legyen legalább 10, és a három jegy közül legalább egy legyen 0. ||
Hint 2: || A hallgatók sorszámait a beolvasás sorrendjében számozd 1-től, így a lista automatikusan növekvő lesz, a darabszám pedig a lista mérete. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> pot;
    for (int i = 1; i <= n; i++) {
        int r, cs1, cs2, ef;
        cin >> r >> cs1 >> cs2 >> ef;
        if (r >= 10 && (cs1 == 0 || cs2 == 0 || ef == 0))
            pot.push_back(i);
    }
    cout << pot.size() << "\n";
    for (size_t i = 0; i < pot.size(); i++) {
        if (i) cout << ' ';
        cout << pot[i];
    }
    cout << "\n";
    return 0;
}
