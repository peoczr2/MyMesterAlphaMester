#include <bits/stdc++.h>
using namespace std;

/*
    Minden csúcspárra kiszámítjuk a legjobb bottleneck-értéket.
    A központi gép az, amelyből minden másik csúcs a lehető legnagyobb
    minimális kapcsolatsebességgel érhető el.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    const int INF = 1e9 + 7;
    vector<vector<int>> best(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; ++i) best[i][i] = INF;
    for (int i = 0; i < k; ++i) {
        int a, b, s;
        cin >> a >> b >> s;
        best[a][b] = max(best[a][b], s);
    }

    for (int mid = 1; mid <= n; ++mid) {
        for (int i = 1; i <= n; ++i) {
            if (best[i][mid] == 0) continue;
            for (int j = 1; j <= n; ++j) {
                if (best[mid][j] == 0) continue;
                best[i][j] = max(best[i][j], min(best[i][mid], best[mid][j]));
            }
        }
    }

    int ans = 1;
    int score = -1;
    for (int i = 1; i <= n; ++i) {
        int cur = INF;
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            cur = min(cur, best[i][j]);
        }
        if (cur > score) {
            score = cur;
            ans = i;
        }
    }

    cout << ans << '\n';
    return 0;
}