/*
Minden poharat 0-szor, 1-szer vagy 2-szer lehet felhasznalni. Ha egyszer hasznaljuk, az nem novel
a koltseget, ha ketszer, akkor pontosan 1-gyel no a ketszer hasznalt poharak szama. Ezert legyen
dp[x] a pontosan x mennyiseg kimérésehez szukseges legkisebb ilyen koltseg. Egy uj pohar beolvasasakor
harom lehetoseg van: nem hasznaljuk, egyszer hasznaljuk (koltseg 0), vagy ketszer hasznaljuk
(koltseg 1). Az allapotok 0-1 jelleggel frissithetoek, mert ugyanazt a poharat egy korben legfeljebb
egyszer valaszthatjuk ki a harom opcio kozul.
*/
/*
Hint 1: || Egy pohar masodik hasznalata az, ami koltseget jelent. ||
Hint 2: || Egy poharra egyszerre harom opciod van: 0, 1 vagy 2 darab felhasznalas. ||
Hint 3: || A DP-ben a minimalizalt ertek nem a poharak szama, hanem a ketszer hasznalt poharak darabszama. ||
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    cin >> n >> target;

    const int inf = numeric_limits<int>::max() / 4;
    vector<int> dp(target + 1, inf);
    dp[0] = 0;

    for (int i = 0; i < n; ++i) {
        int size;
        cin >> size;
        vector<int> next = dp;
        for (int amount = 0; amount <= target; ++amount) {
            if (dp[amount] >= inf) {
                continue;
            }
            if (amount + size <= target) {
                next[amount + size] = min(next[amount + size], dp[amount]);
            }
            if (amount + 2 * size <= target) {
                next[amount + 2 * size] = min(next[amount + 2 * size], dp[amount] + 1);
            }
        }
        dp.swap(next);
    }

    if (dp[target] >= inf) {
        cout << -1 << '\n';
    } else {
        cout << dp[target] << '\n';
    }
    return 0;
}