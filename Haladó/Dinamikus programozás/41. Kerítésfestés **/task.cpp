/*
Egyszínű kerítést kell kapni, ezért minden színt külön lehet vizsgálni: az adott szín dobozaiból kell pontosan L hosszúságot
kirakni a lehető legkevesebb dobozzal. Ez színenként egy darabszámra optimalizált részösszegfeladat, ahol a dp[s] az s
méterhez szükséges minimális dobozszám. A legjobb szín megtalálása után ugyanazzal a DP-vel a felhasznált dobozok is
visszafejthetők.
*/
/*
Hint 1: || Mivel a kerítés egyszínű, a különböző színek teljesen függetlenül vizsgálhatók. ||
Hint 2: || Egy dobozt vagy teljesen felhasználsz, vagy egyáltalán nem, tehát ez 0/1 részösszegfeladat. ||
Hint 3: || A cél nem csak az, hogy kijöjjön L, hanem hogy ehhez a lehető legkevesebb doboz kelljen. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, n, m;
    cin >> L >> n >> m;
    vector<vector<pair<int, int>>> by_color(m + 1);
    for (int i = 1; i <= n; ++i) {
        int color, len;
        cin >> color >> len;
        by_color[color].push_back({len, i});
    }

    const int INF = 1e9;
    int best_color = -1;
    int best_count = INF;

    for (int color = 1; color <= m; ++color) {
        vector<int> dp(L + 1, INF);
        dp[0] = 0;
        for (auto [len, idx] : by_color[color]) {
            (void)idx;
            for (int s = L; s >= len; --s) {
                dp[s] = min(dp[s], dp[s - len] + 1);
            }
        }
        if (dp[L] < best_count) {
            best_count = dp[L];
            best_color = color;
        }
    }

    if (best_color == -1 || best_count == INF) {
        cout << -1 << '\n';
        return 0;
    }

    vector<int> dp(L + 1, INF), parent_sum(L + 1, -1), parent_can(L + 1, -1);
    dp[0] = 0;
    for (auto [len, idx] : by_color[best_color]) {
        for (int s = L; s >= len; --s) {
            if (dp[s - len] + 1 < dp[s]) {
                dp[s] = dp[s - len] + 1;
                parent_sum[s] = s - len;
                parent_can[s] = idx;
            }
        }
    }

    vector<int> chosen;
    for (int s = L; s > 0; s = parent_sum[s]) {
        chosen.push_back(parent_can[s]);
    }
    reverse(chosen.begin(), chosen.end());

    cout << best_count << '\n';
    for (int i = 0; i < (int)chosen.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}
