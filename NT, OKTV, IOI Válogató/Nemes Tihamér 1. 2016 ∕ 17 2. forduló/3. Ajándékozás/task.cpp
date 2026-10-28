/*
Megoldás lényege:
A szétosztások sorrendje nem számít (3+2 és 2+3 ugyanaz), ezért N szaloncukor felosztásainak száma pontosan
az N összegpartícióinak száma, ahol minden rész legfeljebb M lehet. Ezt pénzváltáshoz hasonló dinamikus
programmal számoljuk: a részméreteket egyenként, 1-től M-ig dolgozzuk fel, és dp[s] az eddig vizsgált
méretekből kirakható s összegek száma. Mivel egy méret többször is felhasználható, a belső ciklust növekvő s
szerint futtatjuk. Az időigény O(N·M), a memóriaigény O(N).
*/
/*
Hint 1: || A felosztás sorrendje nem számít (a 3+2 és a 2+3 ugyanaz), és ugyanaz a csomagméret többször is előfordulhat. Ha a csomagméreteket egyenként, sorban dolgozod fel, minden felosztás pontosan egyszer számolódik. ||
Hint 2: || Legyen dp[s] az s szaloncukor felosztásainak száma az eddig vizsgált méretekkel, kezdetben dp[0] = 1. Egy új r méret bevételekor minden s-re dp[s] += dp[s - r]. ||
Hint 3: || A belső ciklust s szerint r-től N-ig növekvő sorrendben futtasd: így a már frissített dp[s - r] tartalmazza az r méretű csomagokat is, ami engedi, hogy egy méret többször szerepeljen. Csökkenő sorrendben minden méret legfeljebb egyszer kerülne be. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> dp(n + 1);
    dp[0] = 1;
    for (int resz = 1; resz <= m; ++resz) {
        for (int s = resz; s <= n; ++s) {
            dp[s] += dp[s - resz];
        }
    }

    cout << dp[n] << '\n';
    return 0;
}
