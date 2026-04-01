/*
Legyen dp[i][j] a maximális benzinmennyiség, amellyel az (i,j) mezőre el lehet jutni. A kezdőmezőn
felvesszük az ott lévő benzint, minden további lépés pedig B litert fogyaszt, majd felvesszük az új mező
benzinkészletét. Egy mező csak felülről vagy balról érkezve érhető el, ezért a legjobb megoldás egyszerű
mátrixos dinamikus programozással számolható, és szülőmutatóval a lépéssorozat is visszaállítható.
*/
/*
Hint 1: || A mezőn lévő benzint akkor kapod meg, amikor odaérsz. ||
Hint 2: || Minden cellához elég a két lehetséges előd közül a jobbik. ||
Hint 3: || A második sorhoz tárold azt is, hogy felülről vagy balról érkeztél az optimális megoldásban. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long cost;
    cin >> n >> m >> cost;

    vector<vector<long long>> fuel(n + 1, vector<long long>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> fuel[i][j];
        }
    }

    const long long NEG = -(1LL << 60);
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, NEG));
    vector<vector<char>> parent(n + 1, vector<char>(m + 1, '?'));
    dp[1][1] = fuel[1][1];

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == 1 && j == 1) {
                continue;
            }
            if (i > 1 && dp[i - 1][j] >= cost) {
                long long candidate = dp[i - 1][j] - cost + fuel[i][j];
                if (candidate > dp[i][j]) {
                    dp[i][j] = candidate;
                    parent[i][j] = 'L';
                }
            }
            if (j > 1 && dp[i][j - 1] >= cost) {
                long long candidate = dp[i][j - 1] - cost + fuel[i][j];
                if (candidate > dp[i][j]) {
                    dp[i][j] = candidate;
                    parent[i][j] = 'J';
                }
            }
        }
    }

    if (dp[n][m] < 0) {
        cout << -1 << '\n';
        return 0;
    }

    cout << dp[n][m] << '\n';
    string path;
    int i = n, j = m;
    while (i != 1 || j != 1) {
        path.push_back(parent[i][j]);
        if (parent[i][j] == 'L') {
            --i;
        } else {
            --j;
        }
    }
    reverse(path.begin(), path.end());
    cout << path << '\n';
    return 0;
}