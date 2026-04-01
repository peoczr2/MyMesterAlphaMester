/*
Megoldási ötlet:
A játékos mindig a következő oszlopba lép, ezért a rács oszlopai mentén dinamikus programozás használható.
Legyen dp[i][j] a maximálisan megszerezhető pontszám, ha a játékos az (i,j) mezőn áll. Innen a következő lépés
jobbra, jobbra-fel vagy jobbra-le lehet.

A DP-t jobbról balra töltjük. Az első oszlopban levő értékek közül választjuk a maximumot; holtverseny esetén a
legkisebb sorszámú kezdősort kell kiírni.
*/
/*
Hint 1: || Egy mezőről mindig eggyel jobbra lépsz, ezért érdemes az oszlopok mentén visszafelé gondolkodni. ||
Hint 2: || Az (i,j) mező legjobb folytatása a három lehetséges jobb oldali szomszéd legnagyobb DP-értéke. ||
Hint 3: || A végén csak az első oszlop sorait kell összehasonlítani, és holtversenyben a kisebb indexet választani. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<long long>> value(n + 2, vector<long long>(m + 2, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> value[i][j];
    }

    vector<vector<long long>> dp(n + 2, vector<long long>(m + 2, 0));
    for (int j = m; j >= 1; --j) {
        for (int i = 1; i <= n; ++i) {
            long long bestNext = 0;
            if (j < m) {
                bestNext = max({dp[i][j + 1], dp[i - 1][j + 1], dp[i + 1][j + 1]});
            }
            dp[i][j] = value[i][j] + bestNext;
        }
    }

    int bestRow = 1;
    for (int i = 2; i <= n; ++i) {
        if (dp[i][1] > dp[bestRow][1]) bestRow = i;
    }

    cout << dp[bestRow][1] << '\n';
    cout << bestRow << '\n';
    return 0;
}