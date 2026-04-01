/*
A következő generációt mindig az előző táblából kell kiszámítani, különben egy frissített sejt hatása idő előtt belekeveredik a többiek számításába. A szabály csak a nyolc szomszéd élő sejtjeinek számától függ, ezért a feladat egy ismételt táblaátalakítás.
*/
/*
Hint 1: || Minden generációt külön másolattal számolj, mert egy cella új állapota a teljes előző táblától függ. ||
Hint 2: || A túléléshez és születéshez elég a nyolc szomszéd élő sejtjeinek száma. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, l;
    cin >> n >> m >> l;
    vector<vector<int>> a(n, vector<int>(n, 0)), b;
    for (int i = 0; i < m; ++i) {
        int r, c;
        cin >> r >> c;
        a[r - 1][c - 1] = 1;
    }

    for (int step = 0; step < l; ++step) {
        b = a;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int cnt = 0;
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        if (!di && !dj) continue;
                        int ni = i + di, nj = j + dj;
                        if (0 <= ni && ni < n && 0 <= nj && nj < n) cnt += a[ni][nj];
                    }
                }
                b[i][j] = (a[i][j] && (cnt == 2 || cnt == 3)) || (!a[i][j] && cnt == 3);
            }
        }
        a.swap(b);
        int alive = 0;
        for (auto &row : a) for (int v : row) alive += v;
        cout << alive << '\n';
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j]) cout << i + 1 << ' ' << j + 1 << '\n';
        }
    }
    return 0;
}