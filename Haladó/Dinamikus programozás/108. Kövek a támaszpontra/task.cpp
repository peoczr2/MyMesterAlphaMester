/*
Megoldási ötlet:
A marsjáró csak jobbra vagy lefelé haladhat, ezért minden mezőre meghatározható, hogy legfeljebb hány követ
szedhet össze odáig. Az útja egy támaszponton véget ér, ezért támaszponton át nem lehet továbbhaladni: egy
támaszpont csak célként számít, a rajta keresztül vezető útvonalakat nem folytatjuk.

Rács-DP-t készítünk: dp[i][j] az (i,j) mezőig összegyűjthető legtöbb kő, feltéve hogy útközben nem értünk
támaszpontra. Egy mező értéke a felső és a bal szomszédja közül a nem támaszpont szomszédok jobbik értéke plusz
az ott levő kövek száma. A végén a támaszpontok közül azt választjuk, amelyikhez a dp-érték maximális.
Az időigény O(N·M).
*/
/*
Hint 1: || A mozgásirányok pontosan ugyanazt jelentik, mint a klasszikus rács-DP feladatokban. ||
Hint 2: || Egy mező értéke a két elődje közül a nagyobbik plusz az ott levő kövek száma, de csak olyan elődről léphetsz tovább, amely nem támaszpont. ||
Hint 3: || Egy támaszponton véget ér az út, ezért a támaszpontot csak célként értékeld, és a DP-t ne terjeszd tovább rajta keresztül. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, t;
    cin >> n >> m >> k >> t;

    vector<vector<int>> stones(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < k; ++i) {
        int r, c;
        cin >> r >> c;
        ++stones[r][c];
    }

    vector<pair<int, int>> bases(t);
    for (int i = 0; i < t; ++i) cin >> bases[i].first >> bases[i].second;

    vector<vector<bool>> isBase(n + 1, vector<bool>(m + 1, false));
    for (const auto& base : bases) isBase[base.first][base.second] = true;

    // dp = -1: a mező nem érhető el úgy, hogy közben támaszponton ne értünk volna célba
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int incoming = (i == 1 && j == 1) ? 0 : -1;
            if (dp[i - 1][j] >= 0 && !isBase[i - 1][j]) incoming = max(incoming, dp[i - 1][j]);
            if (dp[i][j - 1] >= 0 && !isBase[i][j - 1]) incoming = max(incoming, dp[i][j - 1]);
            if (incoming >= 0) dp[i][j] = incoming + stones[i][j];
        }
    }

    pair<int, int> bestBase = bases[0];
    int bestValue = -1;
    for (const auto& base : bases) {
        int current = dp[base.first][base.second];
        if (current > bestValue) {
            bestValue = current;
            bestBase = base;
        }
    }

    cout << bestValue << '\n';
    cout << bestBase.first << ' ' << bestBase.second << '\n';
    return 0;
}