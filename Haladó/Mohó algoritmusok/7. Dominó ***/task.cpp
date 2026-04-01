/*
Feladat: A bemeneti dominókból a leghosszabb olyan sorrendet kell kiválasztani, ahol a domino végei egymásra illeszkednek, és az elemeket csak sorrendben használhatjuk.
Ötlet: Mivel a számok 0..9 közé esnek, az aktuális láncvégeket egy 10x10-es dinamikus táblában tároljuk. Minden új dominó csak a régi láncok egyik végére illeszthető.
Hint 1: || Egy állapotot az aktuális bal és jobb végpont száma ír le. ||
Hint 2: || Az új dominóval az állapotok száma kicsi marad, ezért az összes átmenet végigpróbálható. ||
Hint 3: || Az első dominó kötelező, utána már csak hosszabbíthatunk vagy eldobhatunk. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int,int>> d(n + 1);
    for (int i = 1; i <= n; ++i) cin >> d[i].first >> d[i].second;

    const int NEG = -1e9;
    int dp[10][10];
    for (int i = 0; i < 10; ++i) for (int j = 0; j < 10; ++j) dp[i][j] = NEG;
    dp[d[1].first][d[1].second] = 1;
    dp[d[1].second][d[1].first] = max(dp[d[1].second][d[1].first], 1);

    for (int i = 2; i <= n; ++i) {
        int ndp[10][10];
        for (int a = 0; a < 10; ++a) for (int b = 0; b < 10; ++b) ndp[a][b] = dp[a][b];
        int x = d[i].first, y = d[i].second;
        for (int a = 0; a < 10; ++a) for (int b = 0; b < 10; ++b) if (dp[a][b] >= 0) {
            if (a == x) ndp[y][b] = max(ndp[y][b], dp[a][b] + 1);
            if (a == y) ndp[x][b] = max(ndp[x][b], dp[a][b] + 1);
            if (b == x) ndp[a][y] = max(ndp[a][y], dp[a][b] + 1);
            if (b == y) ndp[a][x] = max(ndp[a][x], dp[a][b] + 1);
        }
        memcpy(dp, ndp, sizeof(dp));
    }

    int ans = 0;
    for (int a = 0; a < 10; ++a) for (int b = 0; b < 10; ++b) ans = max(ans, dp[a][b]);
    cout << ans << '\n';
    return 0;
}