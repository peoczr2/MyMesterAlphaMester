/*
Az a legnagyobb penzosszeg, amely biztosan benne van a perselyben, eppen a lehetseges osszes
osszetetel kozul a legkisebb ertek. Ha lenne ennel kisebb erteku, pontosan S sulyu osszetetel,
akkor annal tobbet nem lehetne garantalni. Ezert ugyanazt a korlatlan hatizsak-DP-t kell
megoldani, mint a minimumos malacpersely-feladatban: dp[w] a pontosan w suly eleresehez szukseges
legkisebb ertek. A valasz dp[S], ha a suly eloallithato.
*/
/*
Hint 1: || A "biztosan legalabb ennyi" allitas a lehetseges osszes eset kozul a legkisebb ertekre vezet. ||
Hint 2: || Ezert itt is pontos sulyra vett minimumot keresunk korlatlan cimletszammal. ||
Hint 3: || A DP ugyanaz, csak a bemenet sorrendje mas, mint az elozo feladatban. ||
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int target_weight, n;
    cin >> target_weight >> n;

    const int inf = numeric_limits<int>::max() / 4;
    vector<int> dp(target_weight + 1, inf);
    dp[0] = 0;

    for (int i = 0; i < n; ++i) {
        int value, weight;
        cin >> value >> weight;
        for (int current = weight; current <= target_weight; ++current) {
            dp[current] = min(dp[current], dp[current - weight] + value);
        }
    }

    if (dp[target_weight] >= inf) {
        cout << -1 << '\n';
    } else {
        cout << dp[target_weight] << '\n';
    }
    return 0;
}