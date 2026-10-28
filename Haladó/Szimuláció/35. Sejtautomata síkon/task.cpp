/*
A tábla véges N×M-es rács, a szélső sorok és oszlopok cellái mindig fehérek maradnak, ezért csak a belső cellákat kell számolni. Minden lépésben a régi tábla alapján építünk egy újat, így a cellák változásai nem hatnak egymásra egy lépésen belül. Egy belső cella új állapotát a 3×3-as környezetének 9 bites maszkja határozza meg, amit egy 512 elemű szabálytáblában nézünk meg. Egy lépés O(N·M) munka, így az összes lépés O(N·M·K).
*/
/*
Hint 1: || A szélső cellák mindig fehérek, ezért csak a belső cellákat kell kiszámolni, és minden lépésben a régi táblából dolgozz. ||
Hint 2: || Egy cella 3×3-as környezetét egyetlen 9 bites számmal lehet azonosítani, ha a sorokat fentről lefelé, balról jobbra fűzöd össze. ||
Hint 3: || A szabályokat egy 512 elemű tömbbe írd be: az i-edik elem 1, ha az i maszkú környezetben a középső cella zöld lesz. ||
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
        for (int i = 1; i < n - 1; ++i) {
            for (int j = 1; j < m - 1; ++j) {
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