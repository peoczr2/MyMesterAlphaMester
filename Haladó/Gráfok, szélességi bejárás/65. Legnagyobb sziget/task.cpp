/*
Megoldás lényege:
A szigetek most is a zöld cellák 8 irányban összefüggő részei. Minden szigetet szélességi bejárással (BFS) járunk be, és közben megszámoljuk, hány cella tartozik hozzá. Az eredményt az eddigi legnagyobb mérettel hasonlítjuk össze, a végén a maximumot írjuk ki. Mivel minden cella legfeljebb egyszer kerül a sorba, az időigény O(N·M), azaz legfeljebb 10^6 lépés.
*/
/*
Hint 1: || A sziget mérete alatt a komponens cellaszámát értjük. Ugyanazt a bejárást használd, mint a szigetek számolásánál, csak most a méretet kell figyelni. ||
Hint 2: || Az indítás után a sorból kivett cellákat számold meg, és tartsd nyilván a legnagyobb értéket. Az eredmény ennek a maximuma. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (auto &row : grid) cin >> row;

    vector<vector<char>> seen(n, vector<char>(m, 0));
    int best = 0;
    queue<pair<int, int>> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] != 'Z' || seen[i][j]) continue;
            seen[i][j] = 1;
            q.push({i, j});
            int cells = 0;
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                ++cells;
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        int a = x + dx, b = y + dy;
                        if (a < 0 || a >= n || b < 0 || b >= m) continue;
                        if (grid[a][b] != 'Z' || seen[a][b]) continue;
                        seen[a][b] = 1;
                        q.push({a, b});
                    }
                }
            }
            best = max(best, cells);
        }
    }
    cout << best << "\n";
    return 0;
}
