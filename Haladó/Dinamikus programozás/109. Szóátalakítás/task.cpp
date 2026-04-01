/*
Megoldási ötlet:
Ez a klasszikus szerkesztési távolság feladat. Legyen dp[i][j] az első i karakterből és az első j karakterből
álló prefixek egymásba alakításának minimális költsége.

Ha az utolsó karakterek megegyeznek, nincs új költség. Különben három lehetőség közül választunk:
beszúrás, törlés vagy csere. A táblázat kitöltése után a dp[n][m] lesz a minimális műveletszám.
*/
/*
Hint 1: || Prefixekre érdemes DP-t felírni, mert a három művelet mindig a végéről is értelmezhető. ||
Hint 2: || Három átmenet van: balról beszúrás, felülről törlés, átlóból csere vagy egyezés. ||
Hint 3: || A válasz a teljes két szóhoz tartozó jobb alsó DP-cellában lesz. ||
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    cin >> a >> b;

    int n = static_cast<int>(a.size());
    int m = static_cast<int>(b.size());
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i <= n; ++i) dp[i][0] = i;
    for (int j = 0; j <= m; ++j) dp[0][j] = j;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1});
            }
        }
    }

    cout << dp[n][m] << '\n';
    return 0;
}