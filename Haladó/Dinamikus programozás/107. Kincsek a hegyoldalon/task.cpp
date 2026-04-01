/*
Megoldási ötlet:
Bal felülről indulunk, és csak jobbra vagy lefelé léphetünk, ezért minden mezőre függetlenül meghatározható,
hogy legfeljebb hány kincs vihető oda. Ha egy mezőn van kincs, akkor az értéke az északi vagy nyugati szomszéd
jobbik értéke plusz egy.

Elkészítünk egy teljes rács-DP-t: dp[i][j] a maximális összegyűjthető kincsek száma az (i,j) mezőig. Ezután a
gyűjtőpontok közül kiválasztjuk azt, amelyhez a dp-érték maximális.
*/
/*
Hint 1: || A megengedett lépések miatt egy mezőre csak felülről vagy balról érkezhetsz. ||
Hint 2: || Ha tudod a két elődmező legjobb értékét, akkor az aktuális mező DP-je egyetlen képlettel számolható. ||
Hint 3: || Nem kell minden kincs-gyűjtőpont párt külön vizsgálni: elég egyszer kitölteni az egész rácsot. ||
*/

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

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + treasure[i][j];
        }
    }

    pair<int, int> bestGoal = goals[0];
    int bestValue = dp[bestGoal.first][bestGoal.second];
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