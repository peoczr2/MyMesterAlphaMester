/*
Megoldas: a racs egy iranyitott aciklikus graf. Egy cellabol csak delre vagy
keletre lephetunk, ha a magassagkulonbseg legfeljebb 1. A leghosszabb utat DP-vel
szamoljuk visszafele: dp[i][j] a legjobb ut hossza az adott cellabol indulva.
Minden cellahoz eltesszuk a kovetkezo cellat is, majd a legnagyobb dp-ju
kezdocellat kiirjuk.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> h(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> h[i][j];
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> nr(n + 1, vector<int>(m + 1, -1));
    vector<vector<int>> nc(n + 1, vector<int>(m + 1, -1));

    for (int i = n; i >= 1; --i) {
        for (int j = m; j >= 1; --j) {
            int bestLen = 0;
            int bestR = -1, bestC = -1;
            auto relax = [&](int r, int c) {
                if (r < 1 || r > n || c < 1 || c > m) return;
                if (abs(h[r][c] - h[i][j]) > 1) return;
                if (dp[r][c] + 1 > bestLen) {
                    bestLen = dp[r][c] + 1;
                    bestR = r;
                    bestC = c;
                }
            };
            relax(i + 1, j);
            relax(i, j + 1);
            dp[i][j] = bestLen;
            nr[i][j] = bestR;
            nc[i][j] = bestC;
        }
    }

    int si = 1, sj = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (dp[i][j] > dp[si][sj]) {
                si = i;
                sj = j;
            }
        }
    }

    int ei = si, ej = sj;
    while (nr[ei][ej] != -1) {
        int ni = nr[ei][ej];
        int nj = nc[ei][ej];
        ei = ni;
        ej = nj;
    }

    cout << dp[si][sj] << '\n';
    cout << si << ' ' << sj << '\n';
    cout << ei << ' ' << ej << '\n';
    return 0;
}
