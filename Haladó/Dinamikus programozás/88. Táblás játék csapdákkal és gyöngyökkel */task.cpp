/*
Megoldási ötlet:
Mivel csak jobbra és lefelé lehet lépni, minden mezőbe csak a felső vagy a bal oldali szomszédból érkezhetünk. Ez klasszikus rács-DP:
dp[i][j] a (i,j) mezőig elérhető maximális gyöngyszám.

Csapdára nem lehet lépni, ezeket elérhetetlennek jelöljük. A jobb értékű előd irányát eltároljuk, így a végén a célból visszafelé
visszaépíthető egy optimális J/L lépéssorozat.
*/
/*
Hint 1: || Egy mezőbe legfeljebb két irányból lehet beérkezni. ||
Hint 2: || A csapdamezőt kezeld úgy, mintha oda nem is vezetne állapot. ||
Hint 3: || Ha minden mezőnél eltárolod, hogy fentről vagy balról jöttél, a végén visszaírható az út. ||
*/

#include <bits/stdc++.h>
using namespace std;

static const long long NEG = -(1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> a[i][j];
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, NEG));
    vector<vector<char>> parent(n + 1, vector<char>(m + 1, 0));

    if (a[1][1] == -1 || a[n][m] == -1) {
        cout << -1 << '\n';
        return 0;
    }

    dp[1][1] = a[1][1];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == 1 && j == 1) continue;
            if (a[i][j] == -1) continue;
            if (dp[i - 1][j] >= dp[i][j - 1]) {
                if (dp[i - 1][j] != NEG) {
                    dp[i][j] = dp[i - 1][j] + a[i][j];
                    parent[i][j] = 'L';
                }
            } else {
                if (dp[i][j - 1] != NEG) {
                    dp[i][j] = dp[i][j - 1] + a[i][j];
                    parent[i][j] = 'J';
                }
            }
        }
    }

    if (dp[n][m] == NEG) {
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