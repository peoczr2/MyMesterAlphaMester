/*
Az optimalis vegallapotban a kontenerek K csoportba oszlanak, es minden csoport ugyanarra a
vegso helyre kerul. Egy adott [l..r] intervallumot egyetlen helyre rakni a sulyozott medianra
erdemes, mert a koltseg sum(s_i * |i-j|). Elore kiszamoljuk minden intervallumhoz ezt az egycsoportos
minimumot, majd dp[g][i]-vel vesszuk az elso i kontener minimumkoltseget g vegso helyre rendezve:
az utolso csoport valamilyen j+1..i intervallum. A valasz dp[K][N].
*/
/*
Hint 1: || Ha egy blokk egy helyre kerul, a legjobb hely a blokk sulyozott medianja. ||
Hint 2: || Elobb szamold ki minden [l..r] intervallum egyhelyes koltseget. ||
Hint 3: || Utana mar klasszikus szakasz-DP jon: az utolso csoport hol kezdodik. ||
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<long long> weight(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> weight[i];
    }

    vector<vector<long long>> cost(n + 1, vector<long long>(n + 1, 0));
    for (int left = 1; left <= n; ++left) {
        for (int right = left; right <= n; ++right) {
            long long total_weight = 0;
            for (int i = left; i <= right; ++i) {
                total_weight += weight[i];
            }
            long long prefix = 0;
            int median = left;
            while (median <= right && prefix * 2 < total_weight) {
                prefix += weight[median];
                ++median;
            }
            --median;

            long long current_cost = 0;
            for (int i = left; i <= right; ++i) {
                current_cost += weight[i] * llabs(i - median);
            }
            cost[left][right] = current_cost;
        }
    }

    const long long inf = numeric_limits<long long>::max() / 4;
    vector<vector<long long>> dp(k + 1, vector<long long>(n + 1, inf));
    dp[0][0] = 0;
    for (int groups = 1; groups <= k; ++groups) {
        for (int right = 1; right <= n; ++right) {
            for (int left = 1; left <= right; ++left) {
                if (dp[groups - 1][left - 1] == inf) {
                    continue;
                }
                dp[groups][right] = min(dp[groups][right], dp[groups - 1][left - 1] + cost[left][right]);
            }
        }
    }

    cout << dp[k][n] << '\n';
    return 0;
}