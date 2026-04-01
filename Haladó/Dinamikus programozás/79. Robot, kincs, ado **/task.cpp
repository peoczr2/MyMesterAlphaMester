/*
Megoldási ötlet:
A robot minden lépésben csak olyan szomszédos mezőre mehet, amelynek a kiindulási ponttól mért Csebisev-távolsága eggyel nagyobb.
Ez azt jelenti, hogy a mezőket koncentrikus „gyűrűkben” lehet feldolgozni: az r-edik gyűrűbe csak az (r-1)-edikből érkezhetünk.

Legyen dp[i][j] a (i,j) mezőn elérhető legnagyobb összeg. Egy mező legfeljebb 8 szomszédos előző gyűrűbeli mezőből kaphat átmenetet,
ezért az egész tábla O(N*M) időben feldolgozható. A válasz a tábla szélén levő mezők közül a legjobb.
*/
/*
Hint 1: || A távolság most a sor- és oszlopeltérés maximuma, tehát a mezők négyzetgyűrűkbe rendeződnek. ||
Hint 2: || Egy engedélyezett lépés mindig az r távolságú gyűrűből az r+1 távolságúba visz. ||
Hint 3: || Elég minden mezőnél a 8 szomszéd közül azokat nézni, amelyek egy gyűrűvel közelebb vannak a startponthoz. ||
*/

#include <bits/stdc++.h>
using namespace std;

static const long long NEG = -(1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, sr, sc;
    cin >> n >> m >> sr >> sc;
    --sr;
    --sc;

    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> a[i][j];
    }

    int maxRing = 0;
    vector<vector<pair<int, int>>> rings(max(n, m) + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int r = max(abs(i - sr), abs(j - sc));
            maxRing = max(maxRing, r);
            rings[r].push_back({i, j});
        }
    }

    vector<vector<long long>> dp(n, vector<long long>(m, NEG));
    dp[sr][sc] = a[sr][sc];

    for (int r = 1; r <= maxRing; ++r) {
        for (auto [x, y] : rings[r]) {
            long long bestPrev = NEG;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0) continue;
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    if (max(abs(nx - sr), abs(ny - sc)) != r - 1) continue;
                    bestPrev = max(bestPrev, dp[nx][ny]);
                }
            }
            if (bestPrev != NEG) dp[x][y] = bestPrev + a[x][y];
        }
    }

    long long ans = NEG;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, dp[i][0]);
        ans = max(ans, dp[i][m - 1]);
    }
    for (int j = 0; j < m; ++j) {
        ans = max(ans, dp[0][j]);
        ans = max(ans, dp[n - 1][j]);
    }

    cout << ans << '\n';
    return 0;
}