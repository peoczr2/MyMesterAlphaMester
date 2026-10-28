/*
Megoldás lényege:
A két csoport határát mindig egy pontszám-szakasz adja: az erősek csoportja a magasabb, a gyengék az alacsonyabb pontszámokat tartalmazzák, így a távolság két, pontszám szerint szomszédos versenyző pontszámának különbsége. Ezért a válasz a különböző pontszámok rendezett sorában a szomszédos különbségek maximuma. Mivel a pontszám legfeljebb M, nem kell külön rendezni: egy M+1 méretű jelölőtömbbel megjelöljük az előforduló pontszámokat, majd növekvő sorrendben végigmenve kiszámoljuk a szomszédos különbségeket. A legnagyobb különbséget akkor írjuk ki, ha nagyobb T-nél, különben -1 a válasz. Az időigény O(N+M).
*/
/*
Hint 1: || Gondolj a pontszámok sorrendjére: ha az erősek csoportja a legkisebb erős pontszámmal kezdődik, a gyengék legerősebb tagja pedig a tőle közvetlenül kisebb pontszám, akkor a távolság két szomszédos érték különbsége. ||
Hint 2: || Nem kell külön rendezni: mivel a pontszámok legfeljebb M-esek, egy M-hez igazított jelölőtömbbel végigmehetsz az előforduló értékeken növekvő sorrendben, és közben nyilvántartod az előző előfordulót. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t;
    cin >> n >> m >> t;

    vector<bool> present(m + 1, false);
    for (int i = 0; i < n; i++) {
        int e;
        cin >> e;
        present[e] = true;
    }

    int best = -1;
    int prev = -1;
    for (int x = 0; x <= m; x++) {
        if (!present[x]) continue;
        if (prev != -1) best = max(best, x - prev);
        prev = x;
    }

    cout << (best > t ? best : -1) << "\n";
    return 0;
}
