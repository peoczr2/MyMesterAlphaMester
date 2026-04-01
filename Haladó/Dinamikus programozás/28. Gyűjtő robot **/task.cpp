/*
Minden oszlopban csak a legfelső és a legalsó tárgy sora érdekes: ha a robot monoton halad egy oszlopban,
akkor a köztük levő tárgyak automatikusan útba esnek. Egy közbülső oszlopból ezért csak kétféle optimális
kilépést kell tárolni: a legfelső tárgy sorában vagy a legalsó tárgy sorában állunk. Az oszloponkénti DP ezekre
az állapotokra számolja a minimális lépésszámot, a szülőtáblából pedig maga az optimális robotprogram is
visszaépíthető.
*/
/*
Hint 1: || Egy oszlopban a köztes tárgyak nem adnak új döntést, csak az oszlop két széle számít. ||
Hint 2: || Ha egy oszlopot lefelé pásztázol végig, akkor balról csak a legfelső kötelező tárgy fölé vagy arra érkezhetsz. ||
Hint 3: || Az utolsó oszlop különleges: ott már nem egy szélső tárgynál kell megállni, hanem le kell jutni az (N,N) mezőre. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> lo(n + 1, n + 1), hi(n + 1, 0);
    for (int i = 0; i < k; ++i) {
        int r, c;
        cin >> r >> c;
        lo[c] = min(lo[c], r);
        hi[c] = max(hi[c], r);
    }

    if (n == 1) {
        cout << 0 << '\n' << '\n';
        return 0;
    }

    const int INF = 1e9;
    vector<array<int, 2>> dp(n + 1, array<int, 2>{INF, INF});
    vector<array<int, 2>> parent(n + 1, array<int, 2>{-1, -1});

    auto row_of = [&](int col, int state) {
        return state == 0 ? lo[col] : hi[col];
    };

    if (hi[1] == 1) {
        dp[1][0] = 0;
    }
    dp[1][1] = hi[1] - 1;

    for (int col = 2; col < n; ++col) {
        for (int prev_state = 0; prev_state < 2; ++prev_state) {
            if (dp[col - 1][prev_state] == INF) {
                continue;
            }

            int prev_row = row_of(col - 1, prev_state);

            if (prev_row >= hi[col]) {
                int cand = dp[col - 1][prev_state] + 1 + (prev_row - lo[col]);
                if (cand < dp[col][0]) {
                    dp[col][0] = cand;
                    parent[col][0] = prev_state;
                }
            }
            if (prev_row <= lo[col]) {
                int cand = dp[col - 1][prev_state] + 1 + (hi[col] - prev_row);
                if (cand < dp[col][1]) {
                    dp[col][1] = cand;
                    parent[col][1] = prev_state;
                }
            }
        }
    }

    int answer = INF;
    int last_state = -1;
    for (int prev_state = 0; prev_state < 2; ++prev_state) {
        int prev_cost = dp[n - 1][prev_state];
        if (prev_cost == INF) {
            continue;
        }
        int prev_row = row_of(n - 1, prev_state);
        if (prev_row > lo[n]) {
            continue;
        }
        int cand = prev_cost + 1 + (n - prev_row);
        if (cand < answer) {
            answer = cand;
            last_state = prev_state;
        }
    }

    vector<int> exit_row(n + 1, 0);
    exit_row[n] = n;
    int state = last_state;
    for (int col = n - 1; col >= 1; --col) {
        exit_row[col] = row_of(col, state);
        if (col >= 2) {
            state = parent[col][state];
        }
    }

    string path;
    path.append(exit_row[1] - 1, 'L');
    for (int col = 2; col <= n; ++col) {
        path.push_back('J');
        if (exit_row[col] > exit_row[col - 1]) {
            path.append(exit_row[col] - exit_row[col - 1], 'L');
        } else if (exit_row[col] < exit_row[col - 1]) {
            path.append(exit_row[col - 1] - exit_row[col], 'F');
        }
    }

    cout << answer << '\n' << path << '\n';
    return 0;
}
