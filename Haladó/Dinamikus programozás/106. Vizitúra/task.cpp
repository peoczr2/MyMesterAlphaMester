/*
Megoldási ötlet:
Pontosan M hosszú cső kell, és bármelyik boltban korlátlan darabszám vásárolható, ezért ez egy
korlátlan hátizsák / pénzváltás típusú feladat. Legyen dp[x] a pontosan x hossz megvásárlásának
minimális költsége.

A boltokat sorban feldolgozva minden hosszra megpróbáljuk az adott bolt csövét még egyszer felhasználni.
Ha javul a költség, eltároljuk, melyik előző hosszúságból és melyik bolttal jutottunk ide. A végén a
visszafejtés során megszámoljuk, melyik boltból hány darab csövet vettünk.
*/
/*
Hint 1: || Mivel korlátlan darabszám vehető, egy hossz többször is kialakulhat ugyanazzal a bolttal. ||
Hint 2: || Legyen dp[x] a pontosan x hossz legkisebb ára, és indulj dp[0]=0 állapotból. ||
Hint 3: || Rekonstrukcióhoz minden javításnál mentsd el az előző hosszt és a választott bolt indexét. ||
*/

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> length(n + 1), cost(n + 1);
    for (int i = 1; i <= n; ++i) cin >> length[i] >> cost[i];

    const long long inf = numeric_limits<long long>::max() / 4;
    vector<long long> dp(m + 1, inf);
    vector<int> prevLen(m + 1, -1), prevStore(m + 1, -1);
    dp[0] = 0;

    for (int store = 1; store <= n; ++store) {
        for (int x = length[store]; x <= m; ++x) {
            if (dp[x - length[store]] == inf) continue;
            long long candidate = dp[x - length[store]] + cost[store];
            if (candidate < dp[x]) {
                dp[x] = candidate;
                prevLen[x] = x - length[store];
                prevStore[x] = store;
            }
        }
    }

    if (dp[m] == inf) {
        cout << 0 << '\n';
        return 0;
    }

    vector<int> used(n + 1, 0);
    for (int x = m; x > 0; x = prevLen[x]) ++used[prevStore[x]];

    int countStores = 0;
    for (int store = 1; store <= n; ++store) {
        if (used[store] > 0) ++countStores;
    }

    cout << dp[m] << '\n';
    cout << countStores << '\n';
    for (int store = 1; store <= n; ++store) {
        if (used[store] > 0) cout << store << ' ' << used[store] << '\n';
    }
    return 0;
}