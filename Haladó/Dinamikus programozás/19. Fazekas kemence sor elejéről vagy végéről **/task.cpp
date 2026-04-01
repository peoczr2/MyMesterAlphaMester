/*
Az állapot a még sorban álló [l,r] korsók intervalluma. Egy menetben legfeljebb két korsót rakhatunk be, és
mindig csak az aktuális két vég valamelyikéről választhatunk, ezért az első menet csak ötféle lehet: bal egyedül,
jobb egyedül, két bal szélső, két jobb szélső, vagy a két szélső együtt. Ezek mindegyikére ismert a menet költsége,
és a maradó kisebb intervallumra rekurzívan ugyanaz a feladat marad, így O(N^2) intervallum-DP adja a minimumot.
*/
/*
Hint 1: || A megmaradó állapotot a bal és jobb vég indexe egyértelműen leírja. ||
Hint 2: || Gondold végig, az első menetben pontosan milyen 1 vagy 2 korsó választható a végekről. ||
Hint 3: || Az első döntés után mindig ismét ugyanilyen kisebb részfeladat marad. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 2, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    const int INF = 1e9;
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
    vector<vector<char>> act(n + 2, vector<char>(n + 2, 0));

    for (int len = 1; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            int best = INF;
            char best_act = 0;

            if (a[l] + dp[l + 1][r] < best) {
                best = a[l] + dp[l + 1][r];
                best_act = 1;
            }
            if (a[r] + dp[l][r - 1] < best) {
                best = a[r] + dp[l][r - 1];
                best_act = 2;
            }
            if (l + 1 <= r && max(a[l], a[l + 1]) + dp[l + 2][r] < best) {
                best = max(a[l], a[l + 1]) + dp[l + 2][r];
                best_act = 3;
            }
            if (l <= r - 1 && max(a[r - 1], a[r]) + dp[l][r - 2] < best) {
                best = max(a[r - 1], a[r]) + dp[l][r - 2];
                best_act = 4;
            }
            if (l < r && max(a[l], a[r]) + dp[l + 1][r - 1] < best) {
                best = max(a[l], a[r]) + dp[l + 1][r - 1];
                best_act = 5;
            }

            dp[l][r] = best;
            act[l][r] = best_act;
        }
    }

    vector<string> lines;
    function<void(int, int)> build = [&](int l, int r) {
        if (l > r) {
            return;
        }
        char c = act[l][r];
        if (c == 1) {
            lines.push_back(to_string(l));
            build(l + 1, r);
        } else if (c == 2) {
            lines.push_back(to_string(r));
            build(l, r - 1);
        } else if (c == 3) {
            lines.push_back(to_string(l) + " " + to_string(l + 1));
            build(l + 2, r);
        } else if (c == 4) {
            lines.push_back(to_string(r) + " " + to_string(r - 1));
            build(l, r - 2);
        } else if (c == 5) {
            lines.push_back(to_string(l) + " " + to_string(r));
            build(l + 1, r - 1);
        }
    };
    build(1, n);

    cout << dp[1][n] << '\n';
    for (const string& line : lines) {
        cout << line << '\n';
    }
    return 0;
}