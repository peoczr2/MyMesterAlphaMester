/*
Megoldási ötlet:
Egy kereszteződésből csak jobbra vagy lefelé lehet továbbmenni, ezért a rács irányított aciklikus gráf.
Legyen dp[i][j] a leghosszabb érvényes út hossza az (i,j) mezőről indulva. Mivel csak a jobb és az alsó
szomszéd jöhet szóba, a DP visszafelé, jobb alsó saroktól tölthető ki.

Ha egy szomszéd magasságkülönbsége legfeljebb K, akkor oda lehet lépni, és 1 + dp[szomszéd] érték adódik.
A legjobb következő lépést is eltároljuk, így a legjobb kezdőpontból az útvonal egyszerűen visszaépíthető.
*/
/*
Hint 1: || A mozgások iránya miatt nincs kör, ezért elég a jobb és alsó szomszédokra támaszkodni. ||
Hint 2: || Írj DP-t arra, hogy egy mezőről indulva legfeljebb hány útszakasz tehető meg. ||
Hint 3: || Az útvonal kiírásához minden mezőben jegyezd meg, melyik volt a jobb folytatás. ||
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> height(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> height[i][j];
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<vector<char>> nextMove(n + 1, vector<char>(m + 1, 0));

    for (int i = n; i >= 1; --i) {
        for (int j = m; j >= 1; --j) {
            if (j + 1 <= m && abs(height[i][j + 1] - height[i][j]) <= k && dp[i][j + 1] + 1 > dp[i][j]) {
                dp[i][j] = dp[i][j + 1] + 1;
                nextMove[i][j] = 'J';
            }
            if (i + 1 <= n && abs(height[i + 1][j] - height[i][j]) <= k && dp[i + 1][j] + 1 > dp[i][j]) {
                dp[i][j] = dp[i + 1][j] + 1;
                nextMove[i][j] = 'L';
            }
        }
    }

    int startR = 1, startC = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (dp[i][j] > dp[startR][startC]) {
                startR = i;
                startC = j;
            }
        }
    }

    string path;
    int r = startR, c = startC;
    while (nextMove[r][c] != 0) {
        char move = nextMove[r][c];
        path.push_back(move);
        if (move == 'J') ++c;
        else ++r;
    }

    cout << dp[startR][startC] << '\n';
    cout << startR << ' ' << startC << '\n';
    cout << path << '\n';
    return 0;
}