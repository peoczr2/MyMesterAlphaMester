/*
Megoldási ötlet:
A klasszikus rúdvágásos intervallum-DP-t használjuk. Ha az optimális első vágás a k-adik helyen van az [l,r] intervallumban, akkor a
teljes költség: dp[l][k] + dp[k][r] + (poz[r] - poz[l]).

Mivel a költségfüggvény megfelel a Knuth-optimalizáció feltételeinek, az optimális első vágás indexe monoton, ezért a teljes DP O(N^2)
időben kiszámítható. A vágási sorrendet az első vágások rekurzív, pre-order visszafejtése adja.
*/
/*
Hint 1: || Egy intervallum első vágása kettéosztja a feladatot két független részre. ||
Hint 2: || A teljes költség mindig tartalmazza az éppen vágott darab hosszát is. ||
Hint 3: || A választott első vágásokat rekurzívan kiírva pont egy optimális vágási sorrendet kapsz. ||
*/

#include <bits/stdc++.h>
using namespace std;

static const long long INF = (1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, n;
    cin >> h >> n;
    vector<int> pos(n + 2);
    pos[0] = 0;
    for (int i = 1; i <= n; ++i) cin >> pos[i];
    pos[n + 1] = h;

    int m = n + 2;
    vector<vector<long long>> dp(m, vector<long long>(m, 0));
    vector<vector<int>> opt(m, vector<int>(m, 0));

    for (int i = 0; i + 1 < m; ++i) opt[i][i + 1] = i + 1;

    for (int len = 2; len < m; ++len) {
        for (int l = 0; l + len < m; ++l) {
            int r = l + len;
            dp[l][r] = INF;
            int from = opt[l][r - 1];
            int to = opt[l + 1][r];
            if (from == 0) from = l + 1;
            if (to == 0) to = r - 1;
            from = max(from, l + 1);
            to = min(to, r - 1);
            for (int k = from; k <= to; ++k) {
                long long cand = dp[l][k] + dp[k][r] + (pos[r] - pos[l]);
                if (cand < dp[l][r]) {
                    dp[l][r] = cand;
                    opt[l][r] = k;
                }
            }
        }
    }

    vector<int> order;
    function<void(int, int)> build = [&](int l, int r) {
        if (r - l <= 1) return;
        int k = opt[l][r];
        order.push_back(pos[k]);
        build(l, k);
        build(k, r);
    };
    build(0, m - 1);

    cout << dp[0][m - 1] << '\n';
    for (int i = 0; i < (int)order.size(); ++i) {
        if (i) cout << ' ';
        cout << order[i];
    }
    cout << '\n';
    return 0;
}