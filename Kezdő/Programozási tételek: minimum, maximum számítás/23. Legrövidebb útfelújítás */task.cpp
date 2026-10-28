/*
Megoldás lényege:
Minden felújításhoz kiszámoljuk a hosszát, és egy menetes minimumkiválasztással megtartjuk a legkisebbet. A hossz a mintából következően V − K + 1: mindkét végpont (kilométerkő) beleszámít, így a [13, 14] felújítás 2 hosszú. Az N értékére nincs szükség, mert a felújítások (0 ≤ K < V ≤ N) már a pályán belül vannak. Az időigény O(M), a memóriaigény O(1).
*/
/*
Hint 1: || Nem kell tárolni a felújításokat: minden sor után számold ki a hosszát, és tartsd nyilván az eddigi minimumot. ||
Hint 2: || A hossz nem a V − K különbség: a mintában a [13, 14] szakasz hossza 2, azaz a két végpont kilométerkövét is beleszámoljuk, ezért a hossz V − K + 1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int best = INT_MAX;
    for (int i = 0; i < m; i++) {
        int k, v;
        cin >> k >> v;
        int len = v - k + 1;
        best = min(best, len);
    }

    cout << best << "\n";
    return 0;
}
