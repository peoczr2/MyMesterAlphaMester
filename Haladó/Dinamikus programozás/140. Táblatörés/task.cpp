/*
Megoldási ötlet:
A játék aktuális állapotát a megmaradt rész-téglalap írja le. Ha ismerjük, hogy ebből a téglalapból a soron levő játékos
mekkora pontkülönbséget tud kiharcolni az ellenfelével szemben, akkor a négy lehetséges lépés közül egyszerűen a legjobbat
választja.

Legyen dp[top][bottom][left][right] a maximális különbség (aktuális játékos pontjai mínusz az ellenfélé), amikor a tábla
megmaradt része ez a téglalap. Egy lépésben elvisszük valamelyik szélső sort vagy oszlopot, és levonjuk a maradék részállapot
ellenfél számára kedvező dp-értékét.
*/
/*
Hint 1: || A játék állapotát teljesen meghatározza a megmaradt téglalap négy határa. ||
Hint 2: || A különbség-DP egyszerűbb, mint külön mindkét játékos pontszámát tárolni. ||
Hint 3: || A szélső sorok és oszlopok összegét prefixösszegekből O(1)-ben kérdezheted le. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<vector<int>> a;
vector<vector<int>> rowPrefix, colPrefix;
vector<int> memo;
vector<char> seen;

int encode(int top, int bottom, int left, int right) {
    return (((top * 31 + bottom) * 31 + left) * 31 + right);
}

int rowSum(int row, int left, int right) {
    return rowPrefix[row][right] - rowPrefix[row][left - 1];
}

int colSum(int col, int top, int bottom) {
    return colPrefix[col][bottom] - colPrefix[col][top - 1];
}

int solve(int top, int bottom, int left, int right) {
    if (top > bottom || left > right) return 0;
    int key = ((top * 31 + bottom) * 31 + left) * 31 + right;
    if (seen[key]) return memo[key];
    seen[key] = 1;

    int best = rowSum(top, left, right) - solve(top + 1, bottom, left, right);
    best = max(best, rowSum(bottom, left, right) - solve(top, bottom - 1, left, right));
    best = max(best, colSum(left, top, bottom) - solve(top, bottom, left + 1, right));
    best = max(best, colSum(right, top, bottom) - solve(top, bottom, left, right - 1));
    memo[key] = best;
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    a.assign(n + 1, vector<int>(m + 1));
    rowPrefix.assign(n + 1, vector<int>(m + 1, 0));
    colPrefix.assign(m + 1, vector<int>(n + 1, 0));
    long long total = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            total += a[i][j];
            rowPrefix[i][j] = rowPrefix[i][j - 1] + a[i][j];
            colPrefix[j][i] = colPrefix[j][i - 1] + a[i][j];
        }
    }

    int maxKey = ((30 * 31 + 30) * 31 + 30) * 31 + 30 + 1;
    memo.assign(maxKey, 0);
    seen.assign(maxKey, 0);

    int diff = solve(1, n, 1, m);
    cout << (total + diff) / 2 << '\n';
    return 0;
}