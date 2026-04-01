/*
Végtelen síkon nem lehet a teljes rácsot tárolni, ezért csak az élő vagy éppen érintett cellákat kell nyilván tartani. A következő generációt mindig a szomszédsági számlálásból lehet előállítani.
*/
/*
Hint 1: || A sík végtelen, ezért csak az élő vagy éppen érintett cellákat kell nyilvántartani. ||
Hint 2: || Minden generációhoz a szomszédsági számlálásból dönthető el, mely cellák élnek tovább. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    int s;
    cin >> s;
    vector<int> rule(512, 0);
    for (int r = 0; r < s; ++r) {
        vector<string> pat(3);
        for (int i = 0; i < 3; ++i) cin >> pat[i];
        int mask = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                mask = (mask << 1) | (pat[i][j] == 'Z');
            }
        }
        rule[mask] = 1;
    }

    auto get = [&](const vector<string> &b, int x, int y) -> int {
        if (x < 0 || x >= n || y < 0 || y >= m) return 0;
        return b[x][y] == 'Z';
    };

    for (int step = 0; step < k; ++step) {
        vector<string> b(n, string(m, 'F'));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int mask = 0;
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        mask = (mask << 1) | get(a, i + di, j + dj);
                    }
                }
                if (rule[mask]) b[i][j] = 'Z';
            }
        }
        a.swap(b);
    }

    int cnt = 0;
    for (auto &row : a) for (char c : row) cnt += (c == 'Z');
    cout << cnt << '\n';
    return 0;
}