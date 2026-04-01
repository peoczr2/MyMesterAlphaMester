/*
Megoldási ötlet:
Itt is csak jobbra és lefelé léphetünk, ezért minden mező optimális értéke a felső és bal szomszéd legjobb értékéből számolható. A
költség most az, hogy hány büntető mezőre lépünk rá; a kezdőmezőt külön kivesszük a számolásból.

Csapdamező elérhetetlen. A minimális büntetőszámot DP-vel kiszámítjuk, az előd irányát eltároljuk, majd a célból visszafelé felírjuk a
J/L lépéssorozatot.
*/
/*
Hint 1: || A célfüggvény most minimum, nem maximum. ||
Hint 2: || A kezdőmező büntetését nem kell beleszámolni. ||
Hint 3: || A szokásos rács-DP itt is működik, csak a mezők költsége 0 vagy 1. ||
*/

#include <bits/stdc++.h>
using namespace std;

static const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> a[i][j];
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INF));
    vector<vector<char>> parent(n + 1, vector<char>(m + 1, 0));

    if (a[1][1] == 2 || a[n][m] == 2) {
        cout << -1 << '\n';
        return 0;
    }

    dp[1][1] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == 1 && j == 1) continue;
            if (a[i][j] == 2) continue;
            int cost = (a[i][j] == 1 ? 1 : 0);
            if (dp[i - 1][j] <= dp[i][j - 1]) {
                if (dp[i - 1][j] != INF) {
                    dp[i][j] = dp[i - 1][j] + cost;
                    parent[i][j] = 'L';
                }
            } else {
                if (dp[i][j - 1] != INF) {
                    dp[i][j] = dp[i][j - 1] + cost;
                    parent[i][j] = 'J';
                }
            }
        }
    }

    if (dp[n][m] == INF) {
        cout << -1 << '\n';
        return 0;
    }

    string path;
    int x = n, y = m;
    while (!(x == 1 && y == 1)) {
        char c = parent[x][y];
        path.push_back(c);
        if (c == 'L') --x;
        else --y;
    }
    reverse(path.begin(), path.end());

    cout << dp[n][m] << '\n';
    cout << path << '\n';
    return 0;
}