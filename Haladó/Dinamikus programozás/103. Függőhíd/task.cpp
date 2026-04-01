/*
Megoldási ötlet:
A híd két sorból és N oszlopból áll, ezért minden oszlopnál csak két állapotunk van: az adott oszlop
bal vagy jobb lapján állunk. Egy oszlopba ugyanazon az oldalon előrelépve jutunk, vagy az előrelépés
után még ugyanabban az oszlopban át is lépünk a másik oldalra.

Legyen dp[i][0/1] a minimális veszélyesség az i. oszlop bal illetve jobb lapjára érkezve. Az átmenetek
egyszerűek: ugyanazon az oldalon csak az adott lap költségét adjuk hozzá, oldalváltásnál pedig az új
oszlop mindkét lapjára rá kell lépnünk. A szülőállapotok eltárolásával a lépéssor is visszaépíthető.
*/
/*
Hint 1: || Egy optimális út pozitív költségek miatt egy oszlopban legfeljebb egyszer vált oldalt. ||
Hint 2: || Írj DP-t arra, hogy minimális költséggel melyik oldalon állsz az i. oszlopban. ||
Hint 3: || Ha az i. oszlopban másik oldalra érkezel, akkor az előző oszlopból előbb előre kell lépni, és csak utána lehet oldalt váltani. ||
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> leftCost(n + 1), rightCost(n + 1);
    for (int i = 1; i <= n; ++i) cin >> leftCost[i];
    for (int i = 1; i <= n; ++i) cin >> rightCost[i];

    const long long inf = (1LL << 60);
    vector<vector<long long>> dp(n + 1, vector<long long>(2, inf));
    vector<vector<int>> parent(n + 1, vector<int>(2, -1));

    dp[1][0] = leftCost[1];
    dp[1][1] = rightCost[1];

    for (int i = 2; i <= n; ++i) {
        long long stayLeft = dp[i - 1][0] + leftCost[i];
        long long switchToLeft = dp[i - 1][1] + rightCost[i] + leftCost[i];
        if (stayLeft <= switchToLeft) {
            dp[i][0] = stayLeft;
            parent[i][0] = 0;
        } else {
            dp[i][0] = switchToLeft;
            parent[i][0] = 1;
        }

        long long stayRight = dp[i - 1][1] + rightCost[i];
        long long switchToRight = dp[i - 1][0] + leftCost[i] + rightCost[i];
        if (stayRight <= switchToRight) {
            dp[i][1] = stayRight;
            parent[i][1] = 1;
        } else {
            dp[i][1] = switchToRight;
            parent[i][1] = 0;
        }
    }

    int endSide = (dp[n][0] <= dp[n][1] ? 0 : 1);
    long long best = dp[n][endSide];

    vector<string> segments;
    int side = endSide;
    for (int i = n; i >= 2; --i) {
        int prevSide = parent[i][side];
        if (prevSide == side) {
            segments.push_back("E");
        } else if (side == 0) {
            segments.push_back("EB");
        } else {
            segments.push_back("EJ");
        }
        side = prevSide;
    }

    string path;
    path += (side == 0 ? 'B' : 'J');
    path += 'E';
    reverse(segments.begin(), segments.end());
    for (const string& part : segments) path += part;
    path += "E#";

    cout << best << '\n';
    cout << path << '\n';
    return 0;
}