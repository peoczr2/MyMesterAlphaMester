/*
Csak jobbra és lefelé lehet haladni, ezért minden mező optimális értéke a balról és felülről érkező optimális
érték maximumából számolható. A csapda mezők tiltottak, azokra nem vezethet út. A szülőirányok tárolásával a
maximális gyöngyszámhoz tartozó útvonal visszafejthető.
*/
/*
Hint 1: || A csapda egyszerűen azt jelenti, hogy az adott cella állapota elérhetetlen. ||
Hint 2: || Egy cellába csak felülről vagy balról érkezhetsz. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c;
    cin >> r >> c;
    vector<vector<long long>> a(r + 1, vector<long long>(c + 1));
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            cin >> a[i][j];
        }
    }

    const long long NEG = -(1LL << 60);
    vector<vector<long long>> dp(r + 1, vector<long long>(c + 1, NEG));
    vector<vector<char>> par(r + 1, vector<char>(c + 1, '?'));
    dp[1][1] = a[1][1];

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            if (i == 1 && j == 1) {
                continue;
            }
            if (a[i][j] == -1) {
                continue;
            }
            if (i > 1 && dp[i - 1][j] != NEG && dp[i - 1][j] + a[i][j] > dp[i][j]) {
                dp[i][j] = dp[i - 1][j] + a[i][j];
                par[i][j] = 'L';
            }
            if (j > 1 && dp[i][j - 1] != NEG && dp[i][j - 1] + a[i][j] > dp[i][j]) {
                dp[i][j] = dp[i][j - 1] + a[i][j];
                par[i][j] = 'J';
            }
        }
    }

    cout << dp[r][c] << '\n';
    string path;
    int i = r, j = c;
    while (i != 1 || j != 1) {
        path.push_back(par[i][j]);
        if (par[i][j] == 'L') {
            --i;
        } else {
            --j;
        }
    }
    reverse(path.begin(), path.end());
    cout << path << '\n';
    return 0;
}