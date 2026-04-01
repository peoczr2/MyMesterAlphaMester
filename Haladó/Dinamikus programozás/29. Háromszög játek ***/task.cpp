/*
Egy részfeladatot a megmaradt kis háromszög topcsúcsa és oldalmérete ír le. Ha ebből a háromszögből az aktuális
játékos a bal, jobb vagy alsó oldalt viszi el, akkor az ellenfélre egy eggyel kisebb, megfelelően eltolódott háromszög
marad. A minimaxot ezért érdemes pontkülönbségként felírni: f állapotban az aktuális játékos által megszerezhető
maximális előny az egyik oldal összege mínusz a maradó részállapot értéke. A három oldalszakasz összege előre
prefixekkel lekérdezhető, így az egész DP O(N^3)-ban kiszámítható.
*/
/*
Hint 1: || A maradó háromszög mindig ugyanilyen alakú, csak kisebb és esetleg eltolódott. ||
Hint 2: || Pontkülönbségre érdemes DP-zni: amit most megszerzel, abból levonódik az ellenfél optimális előnye. ||
Hint 3: || A három oldal összegét előre számold, hogy ne minden állapotban újra összegezgesd. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<long long>> a(n + 1, vector<long long>(n + 1, 0));
    long long total = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            cin >> a[i][j];
            total += a[i][j];
        }
    }

    vector<vector<long long>> row_pref(n + 1, vector<long long>(n + 1, 0));
    vector<vector<long long>> col_pref(n + 1, vector<long long>(n + 1, 0));
    vector<vector<long long>> diag_pref(n + 1, vector<long long>(n + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            row_pref[i][j] = row_pref[i][j - 1] + a[i][j];
            col_pref[i][j] = col_pref[i - 1][j] + a[i][j];
            diag_pref[i][j] = diag_pref[i - 1][j - 1] + a[i][j];
        }
    }

    static long long dp[105][105][105];
    auto bottom_sum = [&](int r, int c, int s) {
        int row = r + s - 1;
        return row_pref[row][c + s - 1] - row_pref[row][c - 1];
    };
    auto left_sum = [&](int r, int c, int s) {
        return col_pref[r + s - 1][c] - col_pref[r - 1][c];
    };
    auto right_sum = [&](int r, int c, int s) {
        return diag_pref[r + s - 1][c + s - 1] - diag_pref[r - 1][c - 1];
    };

    for (int s = 1; s <= n; ++s) {
        for (int r = 1; r + s - 1 <= n; ++r) {
            for (int c = 1; c <= r; ++c) {
                if (s == 1) {
                    dp[r][c][s] = a[r][c];
                    continue;
                }
                long long best = bottom_sum(r, c, s) - dp[r][c][s - 1];
                best = max(best, left_sum(r, c, s) - dp[r + 1][c + 1][s - 1]);
                best = max(best, right_sum(r, c, s) - dp[r + 1][c][s - 1]);
                dp[r][c][s] = best;
            }
        }
    }

    cout << (total + dp[1][1][n]) / 2 << '\n';
    return 0;
}