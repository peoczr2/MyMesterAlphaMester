/*
Megoldási ötlet:
A szánkó csak jobbra vagy lefelé mozoghat, ezért minden mezőre meghatározható, hogy legfeljebb hány kincs
gyűjthető be odáig. Mivel a szánkó egy gyűjtőponton megáll, gyűjtőponton át nem lehet továbbhaladni: egy
gyűjtőpont csak célként számít, a rajta keresztül vezető útvonalakat nem folytatjuk.

Rács-DP-t készítünk: dp[i][j] az (i,j) mezőig összegyűjthető legtöbb kincs, feltéve hogy útközben nem álltunk
meg gyűjtőponton. Egy mező értéke a felső és a bal szomszédja közül a nem gyűjtőpont szomszédok jobbik értéke
plusz az ott levő kincsek száma. A végén a gyűjtőpontok közül azt választjuk, amelyikhez a dp-érték maximális.
Az időigény O(N·M).
*/
/*
Hint 1: || A megengedett lépések miatt egy mezőre csak felülről vagy balról érkezhetsz. ||
Hint 2: || Egy mező értéke a két elődje közül a nagyobbik plusz az ott levő kincsek száma, de csak olyan elődről léphetsz tovább, amely nem gyűjtőpont. ||
Hint 3: || Egy gyűjtőponton a szánkó megáll, ezért a gyűjtőpontot csak célként értékeld, és a DP-t ne terjeszd tovább rajta keresztül. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, g;
    cin >> n >> m >> k >> g;

    vector<vector<int>> treasure(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < k; ++i) {
        int r, c;
        cin >> r >> c;
        ++treasure[r][c];
    }

    vector<pair<int, int>> goals(g);
    for (int i = 0; i < g; ++i) cin >> goals[i].first >> goals[i].second;

    vector<vector<bool>> isGoal(n + 1, vector<bool>(m + 1, false));
    for (const auto& goal : goals) isGoal[goal.first][goal.second] = true;

    // dp = -1: a mező nem érhető el úgy, hogy közben gyűjtőponton ne álltunk volna meg
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int incoming = (i == 1 && j == 1) ? 0 : -1;
            if (dp[i - 1][j] >= 0 && !isGoal[i - 1][j]) incoming = max(incoming, dp[i - 1][j]);
            if (dp[i][j - 1] >= 0 && !isGoal[i][j - 1]) incoming = max(incoming, dp[i][j - 1]);
            if (incoming >= 0) dp[i][j] = incoming + treasure[i][j];
        }
    }

    pair<int, int> bestGoal = goals[0];
    int bestValue = -1;
    for (const auto& goal : goals) {
        int current = dp[goal.first][goal.second];
        if (current > bestValue) {
            bestValue = current;
            bestGoal = goal;
        }
    }

    cout << bestValue << '\n';
    cout << bestGoal.first << ' ' << bestGoal.second << '\n';
    return 0;
}