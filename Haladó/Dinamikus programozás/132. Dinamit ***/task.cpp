/*
Megoldási ötlet:
Egy útvonal hossza pontosan N+M-1 mező, és összesen legfeljebb K robbantás használható fel. Ha tudjuk, hogy egy
mezőn pontosan t dinamit robban, akkor a mező költsége egyszerűen kiszámítható: ennyiszer felezzük egészrészre.

Legyen dp[i][j][k] a minimális kényelmetlenség az (i,j) mezőig úgy, hogy összesen k robbantást használtunk fel.
Az aktuális mezőre kiosztott robbantások számát végigpróbáljuk, az előd pedig felülről vagy balról jöhet.
*/
/*
Hint 1: || Előre számold ki minden mezőre, mennyi lesz a költsége 0,1,2,...,K robbantás után. ||
Hint 2: || A robbantások számát az útvonal mentén kell szétosztani, ezért a felhasznált robbantások száma is legyen DP-dimenzió. ||
Hint 3: || Az aktuális cellára jutó robbantások számát külön ciklusban próbáld végig. ||
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> value(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> value[i][j];
    }

    vector<vector<vector<int>>> cellCost(n + 1, vector<vector<int>>(m + 1, vector<int>(k + 1, 0)));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int current = value[i][j];
            for (int used = 0; used <= k; ++used) {
                cellCost[i][j][used] = current;
                current /= 2;
            }
        }
    }

    const long long inf = numeric_limits<long long>::max() / 4;
    vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(m + 1, vector<long long>(k + 1, inf)));
    for (int used = 0; used <= k; ++used) dp[1][1][used] = cellCost[1][1][used];

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == 1 && j == 1) continue;
            for (int total = 0; total <= k; ++total) {
                for (int here = 0; here <= total; ++here) {
                    long long bestPrev = inf;
                    if (i > 1) bestPrev = min(bestPrev, dp[i - 1][j][total - here]);
                    if (j > 1) bestPrev = min(bestPrev, dp[i][j - 1][total - here]);
                    if (bestPrev == inf) continue;
                    dp[i][j][total] = min(dp[i][j][total], bestPrev + cellCost[i][j][here]);
                }
            }
        }
    }

    long long answer = inf;
    for (int used = 0; used <= k; ++used) answer = min(answer, dp[n][m][used]);
    cout << answer << '\n';
    return 0;
}